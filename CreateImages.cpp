#include "lib/CreateHist.hpp"
#include "lib/Contrast.hpp"

int main(int argc, char* argv[]) {
    std::string image_name(argv[1]);
    Mat img = imread("imgs/" + image_name + ".jpg", IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "bad image_name\n";
        return 0;
    }

    Mat dumb_contrast = DumbContrast(img);
    Mat smart_contrast = SmartContrast(img);

    std::vector<Mat> images = {img, dumb_contrast, smart_contrast};
    std::vector<std::string> names = {image_name, image_name + "DumbContrast", image_name + "SmartContrast"};

    for (auto& i: names) {
        i = "contrast_imgs/" + i;
    }

    for (int i = 0; i < images.size(); ++i) {
        SaveHist(images[i], names[i]);
    }
}