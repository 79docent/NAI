#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    bool filpStatus = false;
    bool capturing = true;
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "error while opening" << endl;
        return -1;
    }
    cout << "ROZMIARY KAMERY: " << cap.get(CAP_PROP_FRAME_WIDTH) << "x" << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    do {
        Mat frame;
        Mat dst = frame;
        char k = waitKey(1);
        if (k == 'r') filpStatus = true;
        if (k == 't') filpStatus = false;

        if (cap.read(frame)) {
            
            if (filpStatus) {
                flip(frame, dst, 1);
                imshow("Not-yet smart window", dst);
            }
            else
            imshow("Not-yet smart window", frame);
        }
        else {
            capturing = false;
        }
        if (k == 'q') {
            capturing = false;
        }
    } while (capturing);
    return 0;
}