#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define ESCAPE 27

int main(){

    //Init Object
    Mat frame;

    //Init Video capturing object
    VideoCapture capture;

    //Keyboard pressed
    char pressedkey;

    //Check success for image reading
    bool success;

    //Load video from disk
    capture.open("/home/angel/Desktop/QT_Projects/Percepción/Project_1/Open_Video/Open_Video/honda-asimo.avi");

    //Check for video availability
    if (!capture.isOpened()){
        cout<<"Error in loading video!"<<endl;
    } else {
        //Create windows canvas to show the video
        namedWindow("L01_E02", CV_WINDOW_AUTOSIZE);

        while (pressedkey != ESCAPE) {

            //Read frame by frame in loop
            success = capture.read(frame);

            //Check for successfull read
            if (!success){
                cout<<"Cant read the frame from file!"<<endl;
                return 1;
            }

            //Add the frame to the window
            imshow("L01_E02", frame);

            //Update the pressed key
            pressedkey = waitKey(0);
        }

        //Free Memory
        destroyWindow("L01_E02");
        capture.release();
    }
}
