#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    bool capturing = true;
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cerr << "error while opening" << endl;
        return -1;
    }

    int lowRanges[3] = { 0,10,60 };
    int upRanges[3] = { 20,150,255 };

        namedWindow("RangeHSV", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);

        createTrackbar("Lower Hue", "RangeHSV", &lowRanges[0], 180);
        createTrackbar("Upper Hue", "RangeHSV", &upRanges[0], 180);
    
        createTrackbar("Lower Sat", "RangeHSV", &lowRanges[1], 255);
        createTrackbar("Upper Sat", "RangeHSV", &upRanges[1], 255);
    
        createTrackbar("Lower Val", "RangeHSV", &lowRanges[2], 255);
        createTrackbar("Upper Val", "RangeHSV", &upRanges[2], 255);

    do {
        Mat frame, baseWindow, hsvRange, HSV;
        capture >> frame;
        Mat dst = frame;

        if (capture.read(frame)) {
            resize(frame, baseWindow, { 320,200 });
            putText(frame, "The HSV values: lows: {0,10,60}, highs: {20,150,255}", { 300,30 }, FONT_HERSHEY_PLAIN, 2.0, { 255,4,4,4 });

            GaussianBlur(baseWindow, dst, Size(9, 9), 0);
            imshow("Blurred", dst);
        }
        else {
            capturing = false;
        }

        cvtColor(frame, HSV, COLOR_BGR2HSV);
        cvtColor(frame, hsvRange, COLOR_BGR2HSV);
        inRange(hsvRange,
            Scalar(lowRanges[0], lowRanges[1], lowRanges[2]),
            Scalar(upRanges[0], upRanges[1], upRanges[2]),
            hsvRange);

        imshow("MyRange", hsvRange);
        imshow("HSV", HSV);

        if (waitKey(1) == 'x') {

            Mat frameROI;
            frameROI = frame.clone();
            auto roi = selectROI("Use ROI on this window", frameROI);
            Mat roiField = frameROI(roi);
            imshow("ROI", roiField);
            imwrite("photo.jpg", roiField);
        }

    } while (capturing);

    return 0;
}