#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){

    //Objects
    Mat img;

    //Load image from disk
    img = imread("/home/angel/Desktop/QT_Projects/Percepción/Project_1/Open_Image/Open_Image/mandril.jpg");
    if (!img.data){
        cout<<"error loading image"<<endl;
        return 1;
    }

    //Create window canvas to show image
    namedWindow("original", CV_WINDOW_AUTOSIZE);

    //Show image in the name of the window
    imshow("original", img);

    //Function to show the image in ms.
    //0 meas wait until keyboard is pressed
    waitKey(0);

    //Free memory
    destroyWindow("original");
    img.release();

    //End program
    return 0;
}
