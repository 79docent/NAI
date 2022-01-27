#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
#define MARGIN 150

CascadeClassifier haar_eyes_cascade;
std::vector<Rect> prev_frame_objects;
uint16_t detected_eyes_counter = 0;

void detectAndDisplay(Mat frame) {
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    std::vector<Rect> bodies;
    haar_eyes_cascade.detectMultiScale(frame_gray, bodies);
    for (auto& body : bodies)
    {
        if (!prev_frame_objects.empty())
        {
            bool wasAlreadyDetected = false;
            for (auto& cmp : prev_frame_objects)
            {
                if (abs(cmp.x - body.x) <= MARGIN && abs(cmp.y - body.y) <= MARGIN)
                {
                    wasAlreadyDetected = true;
                }
            }
            if (!wasAlreadyDetected) detected_eyes_counter++;
        }
        else
        {
            detected_eyes_counter++;
        }
        Point center(body.x + body.width / 2, body.y + body.height / 2);
        rectangle(frame, Point(body.x, body.y), Point(body.x + body.width, body.y + body.height), Scalar(255, 0, 0), 2);
    }
    std::string msg{ "Wykryte oczy: " };
    msg.append(std::to_string(detected_eyes_counter));
    cv::putText(frame, msg, cv::Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2, LINE_AA);

    prev_frame_objects.clear();
    std::copy(bodies.begin(), bodies.end(), back_inserter(prev_frame_objects));
    cv::imshow("eyes_detector", frame);
}

int main(int argc, char** argv)
{
    int width = 960;
    int height = 540;
    if (argc == 3)
    {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
    }
    bool capturing = true;
    cv::VideoCapture cap(0);
    cv::Mat frame;
    std::string haar_eyes_cascade_name = samples::findFile("haarcascade_eyes.xml", true);
    if (!haar_eyes_cascade.load(haar_eyes_cascade_name)) {
        std::cout << "--(!)Error loading eyes cascade\n";
        return -1;
    };
    if (!cap.isOpened()) {
        std::cerr << "error opening frames source" << std::endl;
        return -1;
    }
    do {
        if (cap.read(frame)) {
            cv::resize(frame, frame, cv::Size(width, height), cv::INTER_LINEAR);
            cv::flip(frame, frame, 1);
            detectAndDisplay(frame);
        }
        else {
            capturing = false;
        }
        int key_read = (cv::waitKey(1000.0 / 60.0) & 0x0ff);
        switch (key_read)
        {
        case(113):
            capturing = false;
            break;
        default:
            break;
        }
    } while (capturing);
    return 0;
}