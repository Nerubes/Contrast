#include <iostream>
#include <string>
#include <vector>

#include "lib/Consts.hpp"
#include "lib/CreateHist.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
    std::string path(argv[1]);
    Mat img = imread(path, IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "bad path\n";
        return 0;
    }
    DrawHist(img, path);
    waitKey();
}