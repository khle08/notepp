
#include <vector>
#include <string>
#include <iostream>


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



int main()
{
    int res;
    std::vector<std::vector<float>> anchors = {};
    res = make_anchors(72, 128, 8, 0.5, anchors);
    res = make_anchors(36, 64, 16, 0.5, anchors);
    res = make_anchors(18, 32, 32, 0.5, anchors);

    for (auto anc: anchors) {
        std::cout << anc[0] << " " << anc[1] << " " << anc[2] << std::endl;
    }
    std::cout << anchors.size() << std::endl;
    return 0;
}