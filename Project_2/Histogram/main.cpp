#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int IMG_WIDTH  = 512;
const int IMG_HEIGHT = 400;

int main(){

        //Define imagen original, imagen transformada a BN e histograma
        Mat img_gray;
        Mat hist_img = Mat(IMG_HEIGHT, IMG_WIDTH, CV_8UC1, Scalar(0));
        Mat img = imread("/home/angel/Desktop/QT_Projects/Percepción/Project_2/lena.jpg");

        //Comprueba imagen original
        if(!img.data) {
                std::cout << "Error reading image" << std::endl;
                return 1;
        };

        //Carga la imagen original y la destruye
        imshow("Original", img);
        /*waitKey(0);
        destroyWindow("Original");*/

        //Transforma la imagen original en su versión BN
        cvtColor(img, img_gray, CV_BGR2GRAY);
        imshow("Gray Scale", img_gray);

        //Crea una matriz para los pixeles en BN
        int pixel_values[256] = {0};

        // Should be 1 for a gray image, 3 for BGR
        std::cout << "Image channels: " << img_gray.channels() << std::endl;

        const int total_pixels = img_gray.rows * img_gray.cols;
        const int RATIO = 3500 / IMG_HEIGHT ;

        for(int p = 0; p < total_pixels; ++p)
        {
               uint8_t pixel = img_gray.at<uint8_t>(p);
               pixel_values[pixel]++;
        }

        // The histogram is divided into x and y axis
        // X axis goes from 0 to 255
        // Y axis goes from 0 to (img.rows * img.cols) / RATIO
        for(int v = 0; v < 256; ++v)
        {
                Point start(v, IMG_HEIGHT);
                Point end(v, IMG_HEIGHT - (pixel_values[v] / RATIO));
                line(hist_img, start, end, Scalar(255, 255, 255));
        };

        imshow("Histogram", hist_img);
        waitKey(0);
        /*destroyWindow("Histogram");*/

        destroyAllWindows();
        img.release();
        img_gray.release();
        hist_img.release();

}
