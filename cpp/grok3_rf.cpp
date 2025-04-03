#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <emmintrin.h> // SSE2 for SIMD

using namespace std;

// 数据点类型定义
struct DataPoint {
    vector<double> features; // 特征向量
    int label;              // 标签（支持多分类）
    DataPoint(const vector<double>& feats, int lbl) : features(feats), label(lbl) {}
};

// 决策树节点
struct TreeNode {
    int featureIndex = -1;    // 分割特征索引
    double threshold = 0.0;   // 分割阈值
    int label = -1;           // 叶节点标签（若为叶节点）
    shared_ptr<TreeNode> left; // 左子树
    shared_ptr<TreeNode> right;// 右子树

    TreeNode() = default;
    TreeNode(int featIdx, double thresh) : featureIndex(featIdx), threshold(thresh) {}
};

// 简单线程池实现（添加任务计数器）
class ThreadPool {
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queueMutex;
    condition_variable condition;
    condition_variable completedCondition;
    bool stop = false;
    size_t pendingTasks = 0;
    mutex taskCounterMutex;

public:
    ThreadPool(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queueMutex);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                    {
                        lock_guard<mutex> lock(taskCounterMutex);
                        --pendingTasks;
                        if (pendingTasks == 0) completedCondition.notify_all();
                    }
                }
            });
        }
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (auto& worker : workers) worker.join();
    }

    void enqueue(function<void()> task) {
        {
            unique_lock<mutex> lock(queueMutex);
            if (stop) throw runtime_error("Enqueue on stopped ThreadPool");
            tasks.emplace(move(task));
            ++pendingTasks;
        }
        condition.notify_one();
    }

    void wait() {
        unique_lock<mutex> lock(taskCounterMutex);
        completedCondition.wait(lock, [this] { return pendingTasks == 0; });
    }
};

// 决策树类
class DecisionTree {
private:
    shared_ptr<TreeNode> root;
    size_t maxDepth;
    size_t minSamplesSplit;
    size_t numClasses; // 支持多分类
    mt19937 rng;

    double giniImpurity(const vector<DataPoint>& data) const {
        if (data.empty()) return 0.0;
        vector<int> labelCounts(numClasses, 0);
        for (const auto& dp : data) {
            if (dp.label >= 0 && dp.label < numClasses) labelCounts[dp.label]++;
        }
        double impurity = 1.0;
        double n = static_cast<double>(data.size());
        for (int count : labelCounts) {
            double p = count / n;
            impurity -= p * p;
        }
        return impurity;
    }

    pair<vector<DataPoint>, vector<DataPoint>> splitData(const vector<DataPoint>& data, int featureIdx, double threshold) const {
        vector<DataPoint> left, right;
        for (const auto& dp : data) {
            if (dp.features[featureIdx] <= threshold) left.push_back(dp);
            else right.push_back(dp);
        }
        return {left, right};
    }

    pair<int, double> findBestSplit(const vector<DataPoint>& data, const vector<int>& featureIndices) {
        double bestGain = -1.0;
        int bestFeature = -1;
        double bestThreshold = 0.0;

        for (int idx : featureIndices) {
            vector<double> values;
            for (const auto& dp : data) values.push_back(dp.features[idx]);
            sort(values.begin(), values.end());

            for (size_t i = 1; i < values.size(); i += 4) {
                __m128d thresholds = _mm_set_pd((values[min(i+1, values.size()-1)] + values[i]) / 2.0,
                                               (values[i] + values[i-1]) / 2.0);
                for (size_t j = 0; j < min<size_t>(2, values.size() - i); ++j) {
                    double threshold = ((double*)&thresholds)[j];
                    auto [left, right] = splitData(data, idx, threshold);
                    if (left.empty() || right.empty()) continue;

                    double gain = giniImpurity(data) - 
                                 (left.size() * giniImpurity(left) + right.size() * giniImpurity(right)) / data.size();
                    if (gain > bestGain) {
                        bestGain = gain;
                        bestFeature = idx;
                        bestThreshold = threshold;
                    }
                }
            }
        }
        return {bestFeature, bestThreshold};
    }

    shared_ptr<TreeNode> buildTree(const vector<DataPoint>& data, size_t depth, const vector<int>& featureIndices) {
        if (data.size() < minSamplesSplit || depth >= maxDepth || giniImpurity(data) == 0.0) {
            auto node = make_shared<TreeNode>();
            vector<int> counts(numClasses, 0);
            for (const auto& dp : data) counts[dp.label]++;
            node->label = max_element(counts.begin(), counts.end()) - counts.begin();
            return node;
        }

        auto [featureIdx, threshold] = findBestSplit(data, featureIndices);
        if (featureIdx == -1) {
            auto node = make_shared<TreeNode>();
            vector<int> counts(numClasses, 0);
            for (const auto& dp : data) counts[dp.label]++;
            node->label = max_element(counts.begin(), counts.end()) - counts.begin();
            return node;
        }

        auto node = make_shared<TreeNode>(featureIdx, threshold);
        auto [leftData, rightData] = splitData(data, featureIdx, threshold);
        node->left = buildTree(leftData, depth + 1, featureIndices);
        node->right = buildTree(rightData, depth + 1, featureIndices);
        return node;
    }

    int predictPoint(const shared_ptr<TreeNode>& node, const vector<double>& features) const {
        if (node->label != -1) return node->label;
        if (features[node->featureIndex] <= node->threshold) 
            return predictPoint(node->left, features);
        return predictPoint(node->right, features);
    }

    void serializeNode(ofstream& ofs, const shared_ptr<TreeNode>& node) const {
        ofs.write(reinterpret_cast<const char*>(&node->featureIndex), sizeof(int));
        ofs.write(reinterpret_cast<const char*>(&node->threshold), sizeof(double));
        ofs.write(reinterpret_cast<const char*>(&node->label), sizeof(int));
        bool hasLeft = node->left != nullptr;
        bool hasRight = node->right != nullptr;
        ofs.write(reinterpret_cast<const char*>(&hasLeft), sizeof(bool));
        ofs.write(reinterpret_cast<const char*>(&hasRight), sizeof(bool));
        if (hasLeft) serializeNode(ofs, node->left);
        if (hasRight) serializeNode(ofs, node->right);
    }

    shared_ptr<TreeNode> deserializeNode(ifstream& ifs) {
        auto node = make_shared<TreeNode>();
        ifs.read(reinterpret_cast<char*>(&node->featureIndex), sizeof(int));
        ifs.read(reinterpret_cast<char*>(&node->threshold), sizeof(double));
        ifs.read(reinterpret_cast<char*>(&node->label), sizeof(int));
        bool hasLeft, hasRight;
        ifs.read(reinterpret_cast<char*>(&hasLeft), sizeof(bool));
        ifs.read(reinterpret_cast<char*>(&hasRight), sizeof(bool));
        if (hasLeft) node->left = deserializeNode(ifs);
        if (hasRight) node->right = deserializeNode(ifs);
        return node;
    }

public:
    DecisionTree(size_t maxD = 10, size_t minSplit = 2, size_t nClasses = 2, unsigned seed = random_device{}())
        : maxDepth(maxD), minSamplesSplit(minSplit), numClasses(nClasses), rng(seed) {}

    void train(const vector<DataPoint>& data, size_t numFeatures) {
        if (data.empty()) throw runtime_error("Empty training data");
        vector<int> featureIndices(data[0].features.size());
        iota(featureIndices.begin(), featureIndices.end(), 0);
        shuffle(featureIndices.begin(), featureIndices.end(), rng);
        featureIndices.resize(numFeatures);
        root = buildTree(data, 0, featureIndices);
    }

    int predict(const vector<double>& features) const {
        if (!root) throw runtime_error("Tree not trained");
        return predictPoint(root, features);
    }

    void save(const string& filename) const {
        ofstream ofs(filename, ios::binary);
        if (!ofs) throw runtime_error("Cannot open file for saving");
        ofs.write(reinterpret_cast<const char*>(&maxDepth), sizeof(size_t));
        ofs.write(reinterpret_cast<const char*>(&minSamplesSplit), sizeof(size_t));
        ofs.write(reinterpret_cast<const char*>(&numClasses), sizeof(size_t));
        serializeNode(ofs, root);
        ofs.close();
    }

    void load(const string& filename) {
        ifstream ifs(filename, ios::binary);
        if (!ifs) throw runtime_error("Cannot open file for loading");
        ifs.read(reinterpret_cast<char*>(&maxDepth), sizeof(size_t));
        ifs.read(reinterpret_cast<char*>(&minSamplesSplit), sizeof(size_t));
        ifs.read(reinterpret_cast<char*>(&numClasses), sizeof(size_t));
        root = deserializeNode(ifs);
        ifs.close();
    }
};

// 随机森林类
class RandomForest {
private:
    vector<shared_ptr<DecisionTree>> trees;
    size_t numTrees;
    size_t maxDepth;
    size_t minSamplesSplit;
    size_t featureSubsetSize;
    size_t numClasses;
    ThreadPool pool;
    mutable mutex mtx;

    vector<DataPoint> bootstrapSample(const vector<DataPoint>& data, mt19937& rng) {
        vector<DataPoint> sample;
        uniform_int_distribution<size_t> dist(0, data.size() - 1);
        for (size_t i = 0; i < data.size(); ++i) {
            sample.push_back(data[dist(rng)]);
        }
        return sample;
    }

    void trainTree(shared_ptr<DecisionTree>& tree, const vector<DataPoint>& data, mt19937 rng) { // 传入副本
        vector<DataPoint> sample = bootstrapSample(data, rng);
        tree->train(sample, featureSubsetSize);
    }

public:
    RandomForest(size_t nTrees = 100, size_t maxD = 10, size_t minSplit = 2, size_t nClasses = 2, double featureRatio = 0.5)
        : numTrees(nTrees), maxDepth(maxD), minSamplesSplit(minSplit), numClasses(nClasses), 
          pool(thread::hardware_concurrency()) {
        if (featureRatio <= 0 || featureRatio > 1) throw invalid_argument("Feature ratio must be in (0, 1]");
    }

    void train(const vector<DataPoint>& data) {
        if (data.empty() || data[0].features.empty()) throw invalid_argument("Invalid data");
        featureSubsetSize = max<size_t>(1, static_cast<size_t>(data[0].features.size() * 0.5));
        trees.resize(numTrees);
        mt19937 baseRng(random_device{}());

        for (size_t i = 0; i < numTrees; ++i) {
            mt19937 rng(baseRng()); // 每个线程独立的随机数生成器
            trees[i] = make_shared<DecisionTree>(maxDepth, minSamplesSplit, numClasses, rng());
            pool.enqueue([this, i, &data, rng]() mutable { trainTree(this->trees[i], data, rng); });
        }
        pool.wait(); // 显式等待所有任务完成
    }

    int predict(const vector<double>& features) const {
        if (trees.empty()) throw runtime_error("Forest not trained");
        vector<int> votes(numClasses, 0);
        {
            lock_guard<mutex> lock(mtx);
            for (const auto& tree : trees) {
                int pred = tree->predict(features);
                votes[pred]++;
            }
        }
        return max_element(votes.begin(), votes.end()) - votes.begin();
    }

    void save(const string& filename) const {
        ofstream ofs(filename, ios::binary);
        if (!ofs) throw runtime_error("Cannot open file for saving");
        ofs.write(reinterpret_cast<const char*>(&numTrees), sizeof(size_t));
        ofs.write(reinterpret_cast<const char*>(&maxDepth), sizeof(size_t));
        ofs.write(reinterpret_cast<const char*>(&minSamplesSplit), sizeof(size_t));
        ofs.write(reinterpret_cast<const char*>(&featureSubsetSize), sizeof(size_t));
        ofs.write(reinterpret_cast<const char*>(&numClasses), sizeof(size_t));
        for (size_t i = 0; i < numTrees; ++i) {
            string treeFile = filename + "_tree" + to_string(i) + ".bin";
            trees[i]->save(treeFile);
        }
        ofs.close();
    }

    void load(const string& filename) {
        ifstream ifs(filename, ios::binary);
        if (!ifs) throw runtime_error("Cannot open file for loading");
        ifs.read(reinterpret_cast<char*>(&numTrees), sizeof(size_t));
        ifs.read(reinterpret_cast<char*>(&maxDepth), sizeof(size_t));
        ifs.read(reinterpret_cast<char*>(&minSamplesSplit), sizeof(size_t));
        ifs.read(reinterpret_cast<char*>(&featureSubsetSize), sizeof(size_t));
        ifs.read(reinterpret_cast<char*>(&numClasses), sizeof(size_t));
        trees.resize(numTrees);
        for (size_t i = 0; i < numTrees; ++i) {
            string treeFile = filename + "_tree" + to_string(i) + ".bin";
            trees[i] = make_shared<DecisionTree>(maxDepth, minSamplesSplit, numClasses);
            trees[i]->load(treeFile);
        }
        ifs.close();
    }
};

// 示例使用
int main() {
    try {
        vector<DataPoint> data = {
            {{0.1, 0.2, 0.3}, 0},
            {{0.2, 0.3, 0.4}, 0},
            {{0.5, 0.6, 0.7}, 1},
            {{0.6, 0.7, 0.8}, 1},
            {{0.3, 0.8, 0.9}, 2},
            {{0.4, 0.9, 1.0}, 2}
        };

        RandomForest rf(10, 5, 2, 3, 0.5); // 10棵树，最大深度5，最小分割2，3类，特征比例0.5
        rf.train(data);

        vector<double> test = {0.3, 0.4, 0.5};
        int prediction = rf.predict(test);
        cout << "Prediction: " << prediction << endl;

        rf.save("rf_model.bin");
        RandomForest rfLoaded;
        rfLoaded.load("rf_model.bin");
        cout << "Loaded model prediction: " << rfLoaded.predict(test) << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}