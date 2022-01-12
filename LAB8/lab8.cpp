#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    int lower_range[3] = { 36,0,0 }, higher_range[3] = { 86,255,255 }; 

    VideoCapture camera(0);

    while (waitKey(1) != 27) {

        Mat frame;
        Mat frameMask, frameMask2;
        Mat frameWithMask;

        camera >> frame;

        flip(frame, frame, 1); 

        cvtColor(frame, frameMask, COLOR_BGR2HSV); 
        inRange(frameMask, Scalar(lower_range[0], lower_range[1], lower_range[2]), 
            Scalar(higher_range[0], higher_range[1], higher_range[2]), frameMask2);

        vector<vector<Point>>  contours; 
        findContours(frameMask2, contours, RETR_LIST, CHAIN_APPROX_SIMPLE); 

        sort(contours.begin(), contours.end(), 
            [](auto& a, auto& b) {
                return contourArea(a, false) > contourArea(b, false);
            });


        Point middle[2] = { 

        };

        for (int i = 0; i < min(2, (int)contours.size()); i++) 
        {
            approxPolyDP(contours.at(i), contours.at(i), 10, true);
            drawContours(frame, contours, i, { 0,0,255,255 });
            Rect rect = boundingRect(contours.at(i)); 
            middle[i].x = rect.width / 2 + rect.x; 
            middle[i].y = rect.height / 2 + rect.y;
        }

        if (abs((middle[0].y - middle[1].y <= 60))) { 

            line(frame, middle[0], middle[1], Scalar(200, 0, 0), 10); 
        }
        imshow("contours", frame); 

    }
    return 0;
}

