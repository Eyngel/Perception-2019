#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat src = imread("/home/angel/Desktop/QT_Projects/Percepción/Project_4/rayosx.tif");
    Mat gray;

    if (!src.data){
        cout<<"Failed opening the image!"<<endl;
        return 1;
    }

    //Check original channels
    cout<<"Original image has: "<< src.channels()<< " channels.\n" << endl;

    //Transform to Gray
    cvtColor(src, gray, CV_BGR2GRAY);

    //Check Image Size
    cout << "Image size is: " << gray.rows << "x" << gray.cols << "\n" << endl;

    //Calculate total pixels

    double total_pixels = gray.rows*gray.cols;
    cout << "Total pixels are: " << total_pixels << "\n" << endl;

    if(!(src.channels() == 1)){ //In this condition colour will be treated
        cout << "Current image is coloured.\n" << endl;

    }else{
        cout << "Current image is Gray Scaled.\n" << endl;
    }

    //Histogram
    //Inicializations
    int histogram_size = 256;
    float histogram_range[] = {0, 256};
    const float* histogram_ranges[] = {histogram_range};
    int bin_width = 5;
    int histogram_width = 512;
    int histogram_height = 400;
    Mat histogram;
    Mat image_histogram(histogram_height, histogram_width, CV_8UC1, Scalar(0, 0, 0));
    Mat normalized_histogram(histogram_height, histogram_width, CV_8UC1, Scalar(0, 0, 0));

    //Calculations
    calcHist(&gray, 1, 0, Mat(), histogram, 1, &histogram_size, histogram_ranges);

    //Print Histogram
    cout <<"Histogram values:" << endl;

    for(int i = 0; i < histogram_size; i++)
    {
        float bin_value = histogram.at<float>(i);
        cout << bin_value << " ";
    }

    //Normalize histogram to fit
    normalize(histogram, normalized_histogram, 0, histogram_height, NORM_MINMAX, -1, Mat());

    cout <<"Normalized histogram values:" << endl;

    for(int i = 0; i < histogram_size; i++)
    {
        float bin_value = normalized_histogram.at<float>(i);
        cout << bin_value << " ";
    }


    for(int i = 1; i < histogram_size; i++)
    {
        Point p1(bin_width*(i-1), histogram_height - cvRound(normalized_histogram.at<float>(i-1)));
        Point p2(bin_width*(i), histogram_height - cvRound(normalized_histogram.at<float>(i)));
        line(image_histogram, p1, p2, Scalar(255, 255, 255));
    }


    //Create window canvas
    namedWindow("Source", CV_WINDOW_AUTOSIZE);
    namedWindow("Gray", CV_WINDOW_AUTOSIZE);
    namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
    //namedWindow("Normalized", CV_WINDOW_AUTOSIZE);

    //Image to window
    imshow("Source", src);
    imshow("Gray", gray);
    imshow("Histogram", image_histogram);
    //imshow("Normaliced", normalized_histogram);

    //Wait for a key to be pressed
    waitKey(0);

    //Free memory
    destroyAllWindows();

    return 0;
}
