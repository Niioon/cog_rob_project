#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <codecvt>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <bits/stdc++.h>


#include <ros/ros.h>
// #include <usb_cam/image_raw/compressed>
#include <sensor_msgs/CompressedImage.h>
#include <std_msgs/String.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <sstream>

#include <fstream>
#include <map>


using namespace cv;
using namespace std;

bool is_there_new_artwork = false;
vector<cv::KeyPoint> new_keypoints;
string first_two;
string to;
string input;
string oldMsg;

ros::Publisher peoplePub;

// prepare cascadeClassifier
CascadeClassifier detectorBody;
CascadeClassifier detectorLower;
// !! Put your cascade or opencv cascede into project folder !!
string bodyCascade = "/home/luka/catkin_ws/src/people_detection/cascades/body.xml";
string lowerBodyCascade = "/home/luka/catkin_ws/src/people_detection/cascades/lowerBody.xml";
// Load cascade into CascadeClassifier
bool loaded1 = detectorBody.load(bodyCascade);
bool loaded3 = detectorLower.load(lowerBodyCascade);


void display(cv::Mat &im, cv::Mat &bbox)
{
  int n = bbox.rows;
  for(int i = 0 ; i < n ; i++)
  {
    line(im, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
  }
  imshow("Current Image", im);
}

void cameraCallback(const sensor_msgs::CompressedImageConstPtr& msg){
	try{
        Mat color_img = imdecode(cv::Mat(msg->data), IMREAD_COLOR);

        //Resizing image
        resize(color_img, color_img, Size(640, 480));

        // cv::Mat disp_img;
        // //Resizing imae for display putposes
        // cv::resize(color_img, disp_img, cv::Size(0, 0), 0.25, 0.25, cv::INTER_LINEAR);
        // cv::imshow("Current Image", disp_img);

        // vector<Rect> found, found_filtered;
        // cv::HOGDescriptor hog;
        // hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
        // hog.detectMultiScale(color_img, found, 0, Size(8,8), Size(32,32), 1.05, 2);

        // cout << "FOUND" << endl;
        // cout << found << endl;
        
        
        // Just for measure time
        const clock_t begin_time = clock();
        // Store results in these 2 vectors
        vector<Rect> human;
        vector<Rect> lowerBody;
        vector<Rect> found;
        // prepare 2 Mat container
        Mat img;
        Mat original;

        cv::Mat gray_img;
        // color to gray image
        cv::cvtColor(color_img, gray_img, cv::COLOR_RGB2GRAY); 
        // detect people, more remarks in performace section
        detectorBody.detectMultiScale(gray_img, human, 1.04, 1, 0, Size(10, 10));
        detectorLower.detectMultiScale(gray_img, lowerBody, 1.1, 2);

        cv::HOGDescriptor hog;
        hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
        hog.detectMultiScale(gray_img, found, 0, Size(10, 10), Size(100,100), 1.06, 3);
        //Works good:
        // hog.detectMultiScale(gray_img, found, 0, Size(10, 10), Size(100,100), 1.06, 3);
        // Draw results from detectorBody into original colored image

        // Draw results from detectMultiScale, default People Detector into original colored image
        if (found.size() > 0)  
            {
                std::cout << "Human detected !" << std::endl;
                putText(color_img, "Human detected !", Point(100, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
                for (int gg = 0; gg < found.size(); gg++)
                {
                    rectangle(color_img, found[gg].tl(), found[gg].br(), Scalar(0, 170, 255), 2, 8, 0);
                }
            }

         if (human.size() > 0)
            
            {
                std::cout << "Human detected by cascade!" << std::endl;
                putText(color_img, "Human detected !", Point(100, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
                for (int gg = 0; gg < human.size(); gg++)
                {
                    rectangle(color_img, human[gg].tl(), human[gg].br(), Scalar(200, 170, 255), 2, 8, 0);
                }
            }
        // Draw results from detectorUpper into original colored image
        if (lowerBody.size() > 0)
        
        {
            std::cout << "Human - lower body - detected !" << std::endl;
            putText(color_img, "Human detected !", Point(100, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
            for (int gg = 0; gg < lowerBody.size(); gg++)
            {
                rectangle(color_img, lowerBody[gg].tl(), lowerBody[gg].br(), Scalar(255, 0, 0), 2, 8, 0);
            }
        }
        // measure time as current - begin_time
        clock_t diff = clock() - begin_time;
        // convert time into string
        char buffer[126];
        sprintf(buffer, "%ld", diff);
        // display TIME ms on original image
        // putText(color_img, buffer, Point(100, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
        // putText(color_img, "ms", Point(250, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
        // draw results
        namedWindow("prew", WINDOW_AUTOSIZE);
        imshow("prew", color_img);


        int key1 = waitKey(20);

	    cv::waitKey(1);
	}
	
	catch(cv::Exception& e){
		ROS_ERROR("Error converting image, %s", e.what());
	}
}


int main(int argc, char **argv) {

	ros::init(argc, argv, "reading_image"); 
	ros::NodeHandle nh;

	ros::Subscriber subs_camera = nh.subscribe("/camera/rgb/image_raw/compressed", 1, cameraCallback);


	peoplePub = nh.advertise<std_msgs::String>("peopleDet", 1000);


    
	

	ros::Rate rate(10);
	while(ros::ok()){
		ros::spinOnce();
		rate.sleep();
	}
}