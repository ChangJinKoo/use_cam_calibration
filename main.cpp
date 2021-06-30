/*

   reference -> https://geniuskpj.tistory.com/19?category=956076 

 */

#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
	Mat camera_matrix = Mat::eye(3, 3, CV_64FC1);
	Mat dist_coeffs = Mat::zeros(1, 5, CV_64FC1);
   	Mat new_frame, temp_frame, map1, map2;
   	Size imageSize = Size(1280, 720);

	/* After camera calibration, you can get these parameters */
	camera_matrix = (Mat1d(3, 3) << 4.9202194020447860e+02, 0., 640., 0., 4.9202194020447860e+02, 360., 0., 0., 1.);
	dist_coeffs = (Mat1d(1, 5) << -3.2351286691095799e-01, 1.0868592705240288e-01, 0., 0., -1.7181307581560720e-02);
	
	VideoCapture cap(0);
	cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CAP_PROP_FRAME_HEIGHT, 720);
	if (!cap.isOpened()) {		//Error
	   	printf("Webcam can't be opened\n");
		return -1;
   	}

   	namedWindow("Undistorted Video", WINDOW_AUTOSIZE);

	initUndistortRectifyMap(camera_matrix, dist_coeffs, Mat(), camera_matrix, imageSize, CV_32FC1, map1, map2);

   	while(1) {
	   	if (!cap.read(new_frame)) {		//Error
		   	printf("Webcam can't be read\n");
			return -1;
	   	}
		//resize(frame, frame, Size(1280, 720));	// when use video file, resizing file
	   	temp_frame = new_frame.clone();
	   	remap(new_frame, temp_frame, map1, map2, INTER_LINEAR);
	   	imshow("Undistorted Video", temp_frame);
	   	if (waitKey(1) == 27)
			break;
   	}

	return 0;
}
