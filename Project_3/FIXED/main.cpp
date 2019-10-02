#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){

       Mat src = imread("/home/angel/Desktop/QT_Projects/Percepción/Project_3/lightballs.jpg");
       resize(src, src, Size(), 0.5, 0.5);
       if(!src.data){
           cout << "Failed while loading the image." << endl;
           return EXIT_FAILURE;
       }

       Mat trans;
       Mat Blue, Green, Red;
       Mat Hue, Sat, Value;
       Mat BGR[] = {Blue, Green, Red};
       Mat HSV[] = {Hue, Sat, Value};

       cvtColor(src, trans, CV_BGR2HSV);

       split(src, BGR);
       split(trans, HSV);

       int histSize = 256;
       float range[] = { 0, 256 }; //the upper boundary is exclusive
       const float* histRange = { range };

       Mat b_hist, g_hist, r_hist;
       Mat h_hist, s_hist, v_hist;
       calcHist(&BGR[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange);
       calcHist(&BGR[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange);
       calcHist(&BGR[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange);
       calcHist(&HSV[0], 1, 0, Mat(), h_hist, 1, &histSize, &histRange);
       calcHist(&HSV[1], 1, 0, Mat(), s_hist, 1, &histSize, &histRange);
       calcHist(&HSV[2], 1, 0, Mat(), v_hist, 1, &histSize, &histRange);


       int hist_w = 512, hist_h = 400;
       int bin_w = cvRound( (double) hist_w/histSize);

       Mat histImageBGR( hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
       Mat histImageHSV( hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
       normalize(b_hist, b_hist, 0, histImageBGR.rows, NORM_MINMAX, -1, Mat());
       normalize(g_hist, g_hist, 0, histImageBGR.rows, NORM_MINMAX, -1, Mat());
       normalize(r_hist, r_hist, 0, histImageBGR.rows, NORM_MINMAX, -1, Mat());
       normalize(h_hist, h_hist, 0, histImageHSV.rows, NORM_MINMAX, -1, Mat());
       normalize(s_hist, s_hist, 0, histImageHSV.rows, NORM_MINMAX, -1, Mat());
       normalize(v_hist, v_hist, 0, histImageHSV.rows, NORM_MINMAX, -1, Mat());

       for(int i = 1; i < histSize; i++){
           line(histImageBGR, Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))),
                 Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar( 255, 0, 0), 2, 8, 0);
           line(histImageBGR, Point(bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))),
                 Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar( 0, 255, 0), 2, 8, 0);
           line(histImageBGR, Point(bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))),
                 Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar( 0, 0, 255), 2, 8, 0);
       }

       for(int i = 1; i < histSize; i++){

           //Algoritmo para calcular BGR desde HSV

           int H = i, S = 1, V = 1, B, G, R;
           int c, x, m;
           int Ri, Gi, Bi;

           c = V * S;
           x = c * (1 - ((H / 60) % 2 - 1));
           m = V - c;

           if(H < 60){
               Ri = c;
               Gi = x;
               Bi = 0;
           }if(H >= 60 && H < 120){
               Ri = x;
               Gi = c;
               Bi = 0;
           }if(H >= 120 && H < 180){
               Ri = 0;
               Gi = c;
               Bi = x;
           }if(H >= 180 && H < 240){
               Ri = 0;
               Gi = x;
               Bi = c;
           }if(H >= 240 && H < 300){
               Ri = x;
               Gi = 0;
               Bi = c;
           }if(H >= 300 && H < 360){
               Ri = c;
               Gi = 0;
               Bi = x;
           }

           R = (Ri + m) * 255;
           G = (Gi + m) * 255;
           B = (Bi + m) * 255;

           line(histImageHSV, Point(bin_w*(i-1), hist_h - cvRound(h_hist.at<float>(i-1))),
                 Point(bin_w*(i), hist_h - cvRound(h_hist.at<float>(i))), Scalar(R, G, B), 2, 8, 0);
           line(histImageHSV, Point(bin_w*(i-1), hist_h - cvRound(s_hist.at<float>(i-1))),
                 Point(bin_w*(i), hist_h - cvRound(s_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
           line(histImageHSV, Point(bin_w*(i-1), hist_h - cvRound(v_hist.at<float>(i-1))),
                 Point(bin_w*(i), hist_h - cvRound(v_hist.at<float>(i))), Scalar(255, 255, 255), 2, 8, 0);
       }

       imshow("Source image", src);
       imshow("HSV image", trans);
       imshow("calcHist Demo BGR", histImageBGR);
       imshow("calcHist Demo HSV", histImageHSV);
       waitKey();
       destroyAllWindows();

    return 0;
}
