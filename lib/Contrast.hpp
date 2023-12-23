#include <vector>

#include "Consts.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

Mat DumbContrast(const Mat& img) {
    int size = img.cols * img.rows;
    double alpha = AMOUNT_COLORS * 1.0 / size;

    auto cumhist = CreateHist(img);

    for (int k = 0; k < cumhist.size(); ++k) {
        for (int i = 1; i < cumhist[k].size(); ++i) {
            cumhist[k][i] += cumhist[k][i - 1];
        }
    }

    for (auto& i : cumhist) {
        for (auto& j : i) {
            j *= alpha;
        }
    }

    Mat new_img = img.clone();

    for (int y = 0; y < new_img.rows; ++y) {
        for (int x = 0; x < new_img.cols; ++x) {
            Vec3b intensity = new_img.at<Vec3b>(y, x);
            intensity.val[0] = saturate_cast<uchar>(cvRound(cumhist[0][intensity.val[0]]));
            intensity.val[1] = saturate_cast<uchar>(cvRound(cumhist[1][intensity.val[1]]));
            intensity.val[2] = saturate_cast<uchar>(cvRound(cumhist[2][intensity.val[2]]));
            new_img.at<Vec3b>(y, x) = intensity;
        }
    }

    return new_img;
}

Mat SmartContrast(const Mat& img) {
    Mat new_img, tmp;
    cvtColor(img, tmp, COLOR_BGR2YCrCb);
    std::vector<Mat> ch;
    split(tmp, ch); 

    equalizeHist(ch[0], ch[0]);

    merge(ch, tmp);
    cvtColor(tmp, new_img, COLOR_YCrCb2BGR);
    return new_img;
}