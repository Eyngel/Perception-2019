#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int IMG_WIDTH  = 512;
const int IMG_HEIGHT = 400;

int main(){

    double scalar = 0.25;

    //Initialize original image and create channels
    Mat original, resized, /*modified_RGB,*/ modified_HSV;
    /*Mat red_channel(modified_RGB.size(), CV_8UC1);
    Mat green_channel(modified_RGB.size(), CV_8UC1);
    Mat blue_channel(modified_RGB.size(), CV_8UC1);*/
    Mat hue_channel(modified_HSV.size(), CV_8UC1);
    Mat saturation_channel(modified_HSV.size(), CV_8UC1);
    Mat value_channel(modified_HSV.size(), CV_8UC1);

    //Open image
    original = imread("/home/angel/Desktop/QT_Projects/Percepción/Project_3/lightballs.jpg", IMREAD_COLOR);

    //Check image
    if (!original.data){
        cout<<"Can't open the image."<<endl;
        return 1;
    } else {

        //Resize image
        resize(original, resized, Size(), scalar, scalar);

        //Convert image from BGR to RGB and HVS
        //cvtColor(resized, modified_RGB, CV_BGR2RGB);
        cvtColor(resized, modified_HSV, CV_BGR2HSV);

        //Create array of all channels
        //Mat channels_array_RGB[]={red_channel, green_channel, blue_channel};
        Mat channels_array_HSV[]={hue_channel, saturation_channel, value_channel};

        //Split image to separate channels
        //split(modified_RGB, channels_array_RGB);
        split(modified_HSV, channels_array_HSV);

        //Histogram inicialization
        int histogram_size = 256;
        float histrogram_range[] = {0, 256};
        int bin_width = 2;
        const float* histogram_ranges[] = {histrogram_range};
        //Mat image_histogram_RBG(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0, 0, 0));
        Mat image_histogram_HSV(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0, 0, 0));
        //Mat image_normal_RBG(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0, 0, 0));
        Mat image_normal_HSV(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, Scalar(0, 0, 0));

        //Calculate Image Histograms
        calcHist(&modified_HSV, 1, 0, Mat(), image_histogram_HSV, 1, &histogram_size, histogram_ranges);
        /*calcHist(&modified_RGB, 1, 0, Mat(), image_histogram_HSV, 1, &histogram_size, histogram_ranges);*/

        //Normalize
        normalize(image_histogram_HSV, image_normal_HSV, 0, IMG_HEIGHT, NORM_MINMAX, -1, Mat());
        /*normalize(image_histogram_RBG, image_normal_RBG, 0, IMG_HEIGHT, NORM_MINMAX, -1, Mat());*/


        //Print points

        for (int i = 1; i < histogram_size; i++){


            Point p1(bin_width*(i - 1), IMG_HEIGHT - cvRound(channels_array_HSV[0].at<float>(i - 1)));
            Point p2(bin_width*(i), IMG_HEIGHT - cvRound(channels_array_HSV[0].at<float>(i)));
            line(image_histogram_HSV, p1, p2, Scalar(255, 0, 0), 2);
            Point p3(bin_width*(i - 1), IMG_HEIGHT - cvRound(channels_array_HSV[1].at<float>(i - 1)));
            Point p4(bin_width*(i), IMG_HEIGHT - cvRound(channels_array_HSV[1].at<float>(i)));
            line(image_histogram_HSV, p3, p4, Scalar(0, 255, 0), 2);
            Point p5(bin_width*(i - 1), IMG_HEIGHT - cvRound(channels_array_HSV[2].at<float>(i - 1)));
            Point p6(bin_width*(i), IMG_HEIGHT - cvRound(channels_array_HSV[2].at<float>(i)));
            line(image_histogram_HSV, p5, p6, Scalar(0, 0, 255), 2);

            /*Point pa(bin_width*(i - 1), IMG_HEIGHT - cvRound(channels_array_RGB[0].at<float>(i - 1)));
            Point pb(bin_width*(i), IMG_HEIGHT - cvRound(channels_array_RGB[0].at<float>(i)));
            line(image_histogram_RBG, pa, pb, Scalar(255, 0, 0), 2);
            Point pc(bin_width*(i - 1), IMG_HEIGHT - cvRound(channels_array_RGB[1].at<float>(i - 1)));
            Point pd(bin_width*(i), IMG_HEIGHT - cvRound(channels_array_RGB[1].at<float>(i)));
            line(image_histogram_RBG, pc, pd, Scalar(0, 255, 0), 2);
            Point pe(bin_width*(i - 1), IMG_HEIGHT - cvRound(channels_array_RGB[2].at<float>(i - 1)));
            Point pf(bin_width*(i), IMG_HEIGHT - cvRound(channels_array_RGB[2].at<float>(i)));
            line(image_histogram_RBG, pe, pf, Scalar(0, 0, 255), 2);*/

        }

        //Create window canvas
        namedWindow("Original", CV_WINDOW_AUTOSIZE);
        /*namedWindow("Modified_RGB", CV_WINDOW_AUTOSIZE);
        namedWindow("Red", CV_WINDOW_AUTOSIZE);
        namedWindow("Green", CV_WINDOW_AUTOSIZE);
        namedWindow("Blue", CV_WINDOW_AUTOSIZE);*/
        namedWindow("Modified_HSV", CV_WINDOW_AUTOSIZE);
        namedWindow("Hue", CV_WINDOW_AUTOSIZE);
        namedWindow("Saturation", CV_WINDOW_AUTOSIZE);
        namedWindow("Value", CV_WINDOW_AUTOSIZE);
        /*namedWindow("RGB_Histogram", CV_WINDOW_AUTOSIZE);*/
        namedWindow("HSV_Histogram", CV_WINDOW_AUTOSIZE);


        //Link images to windows
        imshow("Original", resized);
        /*imshow("Modified_RGB", modified_RGB);
        imshow("Red", channels_array_RGB[0]);
        imshow("Green",channels_array_RGB[1]);
        imshow("Blue", channels_array_RGB[2]);*/
        imshow("Modified_HSV", modified_HSV);
        imshow("Hue", channels_array_HSV[0]);
        imshow("Saturation",channels_array_HSV[1]);
        imshow("Value", channels_array_HSV[2]);
        /*imshow("RGB_Histogram", image_histogram_RBG);*/
        imshow("HSV_Histogram", image_histogram_HSV);

        //Wait till key is pressed
        waitKey(0);

        //Free memory
        destroyAllWindows();

    return 0;
    }
}
