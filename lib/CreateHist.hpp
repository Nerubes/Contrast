#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Consts.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

void Normalize(std::vector<double>& vec, int size) {
    int max = 0;
    for (int i = 0; i < vec.size(); ++i) {
        if (max < vec[i]) {
            max = vec[i];
        }
    }
    for (auto& i : vec) {
        i = (i * size) / max;
    }
}

std::vector<std::vector<double>> CreateHist(const Mat& img) {
    std::vector<std::vector<double>> channels(3, std::vector<double>(AMOUNT_COLORS, 0));

    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            Vec3b intensity = img.at<Vec3b>(i, j);
            ++channels[0][static_cast<int>(intensity.val[0])];
            ++channels[1][static_cast<int>(intensity.val[1])];
            ++channels[2][static_cast<int>(intensity.val[2])];
        }
    }

    return channels;
}

void DrawHist(const Mat& img, const std::string& name) {
    auto channels = CreateHist(img);

    Mat Hist(HIST_HEIGHT, HIST_WIDTH, CV_8UC3, Scalar(255, 255, 255));

    int scale = cvRound((double)(HIST_WIDTH / AMOUNT_COLORS));

    Normalize(channels[0], HIST_HEIGHT);
    Normalize(channels[1], HIST_HEIGHT);
    Normalize(channels[2], HIST_HEIGHT);

    for( int i = 1 ; i < AMOUNT_COLORS; ++i) {
        line(Hist, Point(scale * (i - 1), HIST_HEIGHT - cvRound(channels[0][i - 1])),
             Point(scale * i, HIST_HEIGHT - cvRound(channels[0][i])),
             Scalar(255, 0, 0), 2, 8, 0);
        line(Hist, Point(scale * (i - 1), HIST_HEIGHT - cvRound(channels[1][i - 1])),
             Point(scale * i, HIST_HEIGHT - cvRound(channels[1][i])),
             Scalar(0, 255, 0), 2, 8, 0);
        line(Hist, Point(scale * (i - 1), HIST_HEIGHT - cvRound(channels[2][i - 1])),
             Point(scale * i, HIST_HEIGHT - cvRound(channels[2][i])),
             Scalar(0, 0, 255), 2, 8, 0);
    }

    

    imshow(name, img);
    imshow(name + " Hist", Hist);
}