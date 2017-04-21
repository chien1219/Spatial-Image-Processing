#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <highgui.h>
#include "cv.h"
#include <math.h>

/* new
Obtain the the following shown in slides of Chapter03.pdf:
1. Slide 10: the three intensity transformed imges
2. Slide 14: the eight binarized images
3. Slide 23: the four images and the two histograms
*/

using namespace std;
using namespace cv;

int ques = 1;
double gamma = 3.0;
string img_name, img_output1,img_output2,img_output3,img_output4,img_output5,img_output6,img_output7,img_output8;
void DrawHistogram(const Mat &src, Mat &dst);

int main(){

	cout << "Input Question Number = ";
	cin >> ques;

	switch (ques){
	case 1:
		img_name = "Fig01_Slide10.tif";
		img_output1 = "Fig01_Slide10_output1.tif";
		img_output2 = "Fig01_Slide10_output2.tif";
		img_output3 = "Fig01_Slide10_output3.tif";
		break;
	case 2:
		img_name = "Fig02_Slide14.tif";
		img_output1 = "Fig02_Slide14_output1.tif";
		img_output2 = "Fig02_Slide14_output2.tif";
		img_output3 = "Fig02_Slide14_output3.tif";
		img_output4 = "Fig02_Slide14_output4.tif";
		img_output5 = "Fig02_Slide14_output5.tif";
		img_output6 = "Fig02_Slide14_output6.tif";
		img_output7 = "Fig02_Slide14_output7.tif";
		img_output8 = "Fig02_Slide14_output8.tif";
		break;
	case 3:
		img_name = "Fig03_Slide23.tif";
		img_output1 = "Fig03_Slide23_dark.tif";
		img_output2 = "Fig03_Slide23_light.tif";
		img_output3 = "Fig03_Slide23_dark_output.tif";
		img_output4 = "Fig03_Slide23_light_output.tif";
		img_output5 = "Fig03_dark_histogram.tif";
		img_output6 = "Fig03_light_histogram.tif";

		break;
	default:
		break;
	}
	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread(img_name, CV_LOAD_IMAGE_GRAYSCALE);

	// Create a grayscale output image matrix
	Mat DstImg1 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg2 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg3 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg4 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg5 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg6 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg7 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg8 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	// 把直方圖秀在一個256*256大的影像上
	Mat histImg_dark,histImg_light;
	Mat showHistImg_dark(256, 256, CV_8UC1, Scalar(255));
	Mat showHistImg_light(256, 256, CV_8UC1, Scalar(255));

	switch (ques) {
	case 1:

		for (int i = 0; i < SrcImg.rows; ++i)
		for (int j = 0; j < SrcImg.cols; ++j){
			DstImg1.at<uchar>(i, j) = pow(SrcImg.at<uchar>(i, j), 0.6) * pow(255.0, 1.0 - 0.6);
			DstImg2.at<uchar>(i, j) = pow(SrcImg.at<uchar>(i, j), 0.4) * pow(255.0, 1.0 - 0.4);
			DstImg3.at<uchar>(i, j) = pow(SrcImg.at<uchar>(i, j), 0.3) * pow(255.0, 1.0 - 0.3);
		}
		// Show images
		cv::imshow("Input Image", SrcImg);
		cv::imshow("Output1(0.6) Image", DstImg1);
		cv::imshow("Output2(0.4) Image", DstImg2);
		cv::imshow("Output3(0.3) Image", DstImg3);

		// Write output images
		cv::imwrite(img_output1, DstImg1);
		cv::imwrite(img_output2, DstImg2);
		cv::imwrite(img_output3, DstImg3);

		cv::waitKey(0);
		break;
	case 2:
		for (int i = 0; i < SrcImg.rows; ++i)
		for (int j = 0; j < SrcImg.cols; ++j){
			/////bit plane 1
			if (SrcImg.at<uchar>(i, j) % 2 == 0)
				DstImg1.at<uchar>(i, j) = 0;
			else
				DstImg1.at<uchar>(i, j) = 255;
			/////bit plane 2
			if ((SrcImg.at<uchar>(i, j) / 2) % 2 == 0)
				DstImg2.at<uchar>(i, j) = 0;
			else
				DstImg2.at<uchar>(i, j) = 255;
			/////bit plane 3
			if ((SrcImg.at<uchar>(i, j) / 4) % 2 == 0)
				DstImg3.at<uchar>(i, j) = 0;
			else
				DstImg3.at<uchar>(i, j) = 255;
			/////bit plane 4
			if ((SrcImg.at<uchar>(i, j) / 8) % 2 == 0)
				DstImg4.at<uchar>(i, j) = 0;
			else
				DstImg4.at<uchar>(i, j) = 255;
			/////bit plane 5
			if ((SrcImg.at<uchar>(i, j) / 16) % 2 == 0)
				DstImg5.at<uchar>(i, j) = 0;
			else
				DstImg5.at<uchar>(i, j) = 255;
			/////bit plane 6
			if ((SrcImg.at<uchar>(i, j) / 32) % 2 == 0)
				DstImg6.at<uchar>(i, j) = 0;
			else
				DstImg6.at<uchar>(i, j) = 255;
			/////bit plane 7
			if ((SrcImg.at<uchar>(i, j) / 64) % 2 == 0)
				DstImg7.at<uchar>(i, j) = 0;
			else
				DstImg7.at<uchar>(i, j) = 255;
			/////bit plane 8
			if (SrcImg.at<uchar>(i, j) < 128)
				DstImg8.at<uchar>(i, j) = 0;
			else
				DstImg8.at<uchar>(i, j) = 255;
		}

		// Show images
		cv::imshow("Input Image", SrcImg);
		cv::imshow("Output(bit plane = 1) Image", DstImg1);
		cv::imshow("Output(bit plane = 2) Image", DstImg2);
		cv::imshow("Output(bit plane = 3) Image", DstImg3);
		cv::imshow("Output(bit plane = 4) Image", DstImg4);
		cv::imshow("Output(bit plane = 5) Image", DstImg5);
		cv::imshow("Output(bit plane = 6) Image", DstImg6);
		cv::imshow("Output(bit plane = 7) Image", DstImg7);
		cv::imshow("Output(bit plane = 8) Image", DstImg8);

		// Write output images
		cv::imwrite(img_output1, DstImg1);
		cv::imwrite(img_output2, DstImg2);
		cv::imwrite(img_output3, DstImg3);
		cv::imwrite(img_output4, DstImg4);
		cv::imwrite(img_output5, DstImg5);
		cv::imwrite(img_output6, DstImg6);
		cv::imwrite(img_output7, DstImg7);
		cv::imwrite(img_output8, DstImg8);

		cv::waitKey(0);

		break;
	case 3:
		int intensity_dark_count[256];
		int intensity_lowcon_count[256];
		int intensity_light_count[256];
		int intensity_dark_transform[256];
		int intensity_light_transform[256];
		int temp;
		///Get the intensity count , generate the data in histogram
		for (int i = 0; i <= 255; i++){
			intensity_dark_count[i] = intensity_light_count[i] = intensity_dark_transform[i] = intensity_light_transform[i] = 0;
		}
		///change input image into low_contra image  y = (x+510)/5
		for (int i = 0; i < SrcImg.rows; ++i) {
			for (int j = 0; j < SrcImg.cols; ++j) {
				DstImg5.at<uchar>(i, j) = ((SrcImg.at<uchar>(i, j)) +510)/5;
			}
		}
		///change input image into dark , light image
		for (int i = 0; i < SrcImg.rows; ++i) {
			for (int j = 0; j < SrcImg.cols; ++j) {
				///change input image into dark image :::  y = x - 50
				DstImg1.at<uchar>(i, j) = ((DstImg5.at<uchar>(i, j)) - 50 <0 ) ? 0 : (DstImg5.at<uchar>(i, j)) - 50;
				///change input image into light image ::: y = (5x - 240)/2
				DstImg2.at<uchar>(i, j) = ((DstImg5.at<uchar>(i, j) * 5 - 240) / 2 > 255) ? 255 : (DstImg5.at<uchar>(i, j) * 5 - 240) / 2;
			}
		}
		for (int i = 0; i < SrcImg.rows; ++i) {
			for (int j = 0; j < SrcImg.cols; ++j) {
				intensity_dark_count[int(DstImg1.at<uchar>(i, j))]++;
				intensity_light_count[int(DstImg2.at<uchar>(i, j))]++;
			}
		}
		///Equalization
		for (int k = 0; k <= 255; k++) {
			int count_dark = 0;
			int count_light = 0;
			for (int j = 0; j <= k; j++) {
				count_dark += intensity_dark_count[j];
				count_light += intensity_light_count[j];
			}
			intensity_dark_transform[k] = count_dark * 255 / (SrcImg.rows*SrcImg.cols);
			intensity_light_transform[k] = count_light * 255 / (SrcImg.rows*SrcImg.cols);
		}
		///generate output inage
		for (int i = 0; i < SrcImg.rows; ++i)
		for (int j = 0; j < SrcImg.cols; ++j){
			DstImg3.at<uchar>(i, j) = intensity_dark_transform[int(DstImg1.at<uchar>(i, j))];
			DstImg4.at<uchar>(i, j) = intensity_light_transform[int(DstImg2.at<uchar>(i, j))];
		}

		int histSize = 256;
		float range[] = { 0, 255 };
		const float* histRange = { range };
		calcHist(&DstImg3, 1, 0, Mat(), histImg_dark, 1, &histSize, &histRange);
		calcHist(&DstImg4, 1, 0, Mat(), histImg_light, 1, &histSize, &histRange);
		DrawHistogram(histImg_dark, showHistImg_dark);
		DrawHistogram(histImg_light, showHistImg_light);
		cv::imshow("Histogram_dark", showHistImg_dark);
		cv::imshow("Histogram_light", showHistImg_light);

		// Show images
		
		cv::imshow("Input Image", SrcImg);
		cv::imshow("Dark Image", DstImg1);
		cv::imshow("Light Image", DstImg2);
		cv::imshow("Dark_output Image", DstImg3);
		cv::imshow("Light_output Image", DstImg4);
		
		cv::imshow("Lowcontrast_output Image", DstImg5);
		// Write output images
		
		cv::imwrite(img_output1, DstImg1);
		cv::imwrite(img_output2, DstImg2);
		cv::imwrite(img_output3, DstImg3);
		cv::imwrite(img_output4, DstImg4);
		

		cv::imwrite(img_output5, showHistImg_dark);
		cv::imwrite(img_output6, showHistImg_light);

		cv::waitKey(0);

		break;
	}

	return 0;
}

void DrawHistogram(const Mat &src, Mat &dst) {
	int histoSize = 256;
	float histoMaxValue = 0;
	for (int i = 0; i < histoSize; i++) {
		float temp = src.at<float>(i);
		if (histoMaxValue < temp)
			histoMaxValue = temp;
	}
	float scale = (0.9 * 256) / histoMaxValue;

	for (int i = 0; i < histoSize; i++) {
		int intensity = int(src.at<float>(i) * scale);
		line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
	}
}