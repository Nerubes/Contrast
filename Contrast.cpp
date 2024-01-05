#include <iostream>
#include <string>
#include <vector>

#include "lib/CreateHist.hpp"
#include "lib/Contrast.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    std::string path(argv[1]);
    Mat img = imread(path, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "bad path\n";
        return 0;
    }

    Mat dumb_contrast = DumbContrast(img);
    Mat smart_contrast = SmartContrast(img);

    std::vector<Mat> images = {img, dumb_contrast, smart_contrast};
    std::vector<std::string> names = {"OldImage", "DumbContrast", "SmartContrast"};

    for (int i = 0; i < images.size(); ++i) {
        DrawHist(images[i], names[i]);
    }

    waitKey();
}