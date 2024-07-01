
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#define print(x) std::cout << x << std::endl


float sigmoid(float x)
{
    return static_cast<float>(1.0f / (1.0f + std::exp(-x)));
}


int read_data(std::string fileName, int start_row, int end_row, std::vector<float>& data)
{
    std::ifstream inFile(fileName, std::ios::in);

    std::string line;
    for (int i = 0; i < end_row; i++) {
        inFile >> line;
        if (i < start_row)
            continue;

        float value = std::stof(line);
        data.push_back(value);
        // std::cout << line << std::endl;
    }
    return 0;
}


int make_anchors(int height, int width, int stride, float offset,
                 std::vector<std::vector<float>>& anchors)
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            std::vector<float> anc(3);

            anc[0] = (float)w + offset;
            anc[1] = (float)h + offset;
            anc[2] = stride;
            anchors.push_back(anc);
        }
    }
    return 0;
}


int post_proc()
{
    // =================================================================

    float conf_thres = 0.4;

    int num_anchors = 12096;
    int num_classes = 8;
    int num_keypoints = 17;

    int reg_max = 16;
    int filter_size[6] = {72, 128, 36, 64, 18, 32};

    int tensor_length = (reg_max * 4 + num_classes) * num_anchors;  // 870912

    // =================================================================

    int res;
    std::vector<std::vector<float>> anchors = {};
    res = make_anchors(filter_size[0], filter_size[1], 8, 0.5, anchors);
    res = make_anchors(filter_size[2], filter_size[3], 16, 0.5, anchors);
    res = make_anchors(filter_size[4], filter_size[5], 32, 0.5, anchors);

    // for (auto anc: anchors) {
    //     std::cout << anc[0] << " " << anc[1] << " " << anc[2] << std::endl;
    // }
    print("anchors size: " << anchors.size());

    // =================================================================

    std::vector<float> tensor = {};
    res = read_data("/home/ubt/Documents/algorithm/yolo/yolov8/outputTensor/v8s-1x72x12096.txt",
                    0, tensor_length, tensor);
    std::cout << "src data: " << tensor.size() << std::endl;

    // std::reverse(tensor.begin(), tensor.end());

    // for (auto v: tensor) {
    //     print(v);
    // }

    // =================================================================

    int ttl = 0;

    // =================================================================

    for (int m = 0; m < num_anchors; m++) {
        int idx_max = -1;
        float conf_max = 0.0;
        std::vector<float> outputs = {};
        std::vector<float> exp_total = {0.0, 0.0, 0.0, 0.0};  // [4] x 16

        std::vector<int> exp_indices = {};
        std::vector<int> conv_weight = {};

        int cnt = reg_max, idx_exp = 0;
        for (int k = 0; k < 4 * reg_max + num_classes; k++) {  // 4 x 16 + 8 = 72
            int idx = tensor_length - 1 - k * num_anchors - m;
            // print(tensor[idx]);

            if (k <= (num_classes - 1)) {
                float conf = sigmoid(tensor[idx]);
                if (conf > conf_max) {
                    conf_max = conf;
                    idx_max = (num_classes - 1) - k;
                }
            } else if (conf_max < conf_thres) {
                break;
            }

            if (k > (num_classes - 1) && conf_max > conf_thres) {
                float data = std::exp(tensor[idx]);
                
                outputs.emplace_back(data);
                exp_indices.emplace_back(idx_exp);
                conv_weight.emplace_back(cnt - 1);

                exp_total[idx_exp] += data;
                cnt -= 1;
                if (cnt == 0) {
                    cnt = reg_max;
                    idx_exp += 1;
                }

                // exp_total[idx_exp] += data;
                // idx_exp += 1;
                // if (idx_exp > 3) {
                //     idx_exp = 0;
                //     cnt -= 1;
                // }
            }
        }

        if (conf_max > conf_thres) {

            std::vector<float> coords = {};
            for (int i = 0; i < 4; i++) {
                float out = 0.0f;
                for (int p = 0; p < reg_max; p++) {
                    int idx = i * reg_max + p;

                    // [!] Softmax
                    outputs[idx] = outputs[idx] / exp_total[exp_indices[idx]];
                    // [!] Conv 1x1
                    out += outputs[idx] * (float)conv_weight[idx];
                }
                coords.emplace_back(out);
            }

            // for (int i = 0; i < 4; i++) {
            //     std::vector<float> outs = {0.0f, 0.0f, 0.0f, 0.0f};
            //     for (int p = 0; p < reg_max; p++) {
            //         int idx = i * reg_max + p;

            //         // [!] Softmax
            //         outputs[idx] = outputs[idx] / exp_total[exp_indices[idx]];
            //         // [!] Conv 1x1
            //         outs[exp_indices[idx]] += outputs[idx] * (float)conv_weight[idx];
            //     }
            //     coords = outs;
            // }

            coords[0] = (anchors[num_anchors - 1 - m][1] + coords[0]) * anchors[num_anchors - 1 - m][2];  // y2
            coords[1] = (anchors[num_anchors - 1 - m][1] + coords[1]) * anchors[num_anchors - 1 - m][2];  // x2
            coords[2] = (anchors[num_anchors - 1 - m][0] - coords[2]) * anchors[num_anchors - 1 - m][2];  // y1
            coords[3] = (anchors[num_anchors - 1 - m][0] - coords[3]) * anchors[num_anchors - 1 - m][2];  // x1
            std::reverse(coords.begin(), coords.end());

            for (auto c: coords) {
                print(c);
            }
            print("====");

            ttl += 1;
            // break;
        }

        // if (m >= 0)
        //     break;
    }

    print("before nms: " << ttl);

    // =================================================================



    // =================================================================

    return 0;
}


int main()
{
    int res = post_proc();
    return 0;
}