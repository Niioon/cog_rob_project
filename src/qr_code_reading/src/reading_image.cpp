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


// using namespace std;
using std::cout;
using std::endl;

bool is_there_new_artwork = false;
std::vector<cv::KeyPoint> new_keypoints;
std::string first_two;
std::string to;
std::string input;
std::string oldMsg;

ros::Publisher qr_pub;


std::string getNumber(const std::string text)  {
	std::string number = boost::regex_replace(
			text,
			boost::regex("[^0-9]*([0-9]+).*"),
			std::string("\\1")
			);
	return number;
	
}

void barcodeCallback(const std_msgs::String& msg){

//    cout << "Detected a QR Code!";
   	// std::cout << "\n";
	std::cout << "-----------" << std::endl;
    std::cout << msg.data << std::endl;
	std::cout << "-----------" << std::endl;

	//TODO:fix that the camera windows gets bigger on qr code in windows. It works without the if statement
	if(oldMsg == msg.data) return;
	// std::string::difference_type n = std::count(msg.data.begin(), msg.data.end(), '\n');
	// std::cout << "Num of lines: " << n << std::endl;
	// std::cout << "-----------" << std::endl;
	// input = std::to_string(msg.data);

	//Breaking message into multiple parts:
	std::istringstream iss{msg.data};
	std::string a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, r ,s;
	if (iss >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l >> m >> n >> o >> p >> r >> s) {
		std::string synonym = a + b + c + d;
		std::cout  << h  << e << std::endl;
	} else
		std::cerr << "The QR message has a wrong format \n";

	// if (e == "R") std::cout << "I have the first type of command " << std::endl;

	if (g == "DR" && e == "R:") {
		std::cout << "I have the first type of command " << std::endl;
		
		//Power
		std::string power = getNumber(b);
		//Energy
		std::string energy = getNumber(d);
		//Converting intiger to a double
		double pwrNum = std::stod( power );
		double enrNum = std::stod( energy );

		//Calculating wait time:
		double waitTime = enrNum/pwrNum;

		// std::cout << "Robot has to wait " <<   waitTime <<  "seconds" <<std::endl;

		//Couting the number of rooms to disenfect:
		std::string::difference_type numOfRooms = std::count(f.begin(), f.end(), ',');
		numOfRooms++;

		//Seperating rooms with a space instead of commas
		std::replace( f.begin(), f.end(), ',', ' '); 

		//Concating all the peaces of info together to send it to the topic
		std::string topicString = "1 " + std::to_string(waitTime) + " " + std::to_string(numOfRooms) + " " + f;
		// std::cout << "Topic string is: " << topicString << std::endl;	

		//ros string msg type:
		std_msgs::String message;

		//Converting topicString into char
		char arr[topicString.length() + 1]; 
		//Copying char into array which is later pushed to the data key of ros string message
	    strcpy(arr, topicString.c_str());
		//Adding the char to the message data type
		message.data = arr;
		//Publishig message to a topic channel
		qr_pub.publish(message);


	} else if (g == "FW:" && e == "R:") {
		std::cout << "I have the third type of command" << std::endl;
		
		//Power
		std::string power = getNumber(b);
		//Energy
		std::string energy = getNumber(d);
		//Converting intiger to a double
		double pwrNum = std::stod( power );
		double enrNum = std::stod( energy );

		//Calculating wait time:
		double waitTime = enrNum/pwrNum;

		std::string::difference_type numOfRooms = std::count(f.begin(), f.end(), ',');
		numOfRooms++;

		std::replace( f.begin(), f.end(), ',', ' '); 

		//Concating all the peaces of info together to send it to the topic
		std::string topicString = "3 " + std::to_string(waitTime) + " " + std::to_string(numOfRooms) + " " + f;

	} else if(e == "FWY"){
		std::cout << "I have the second type of command" << std::endl;

		//Power
		std::string power = getNumber(b);
		//Energy
		std::string energy = getNumber(d);
		//Converting intiger to a double
		double pwrNum = std::stod( power );
		double enrNum = std::stod( energy );

		//Calculating wait time:
		double waitTime = enrNum/pwrNum;

		// std::cout << "Robot has to wait " <<   waitTime <<  "seconds" <<std::endl;

		//Couting the number of rooms to disenfect:
		std::string::difference_type numOfCoord = std::count(msg.data.begin(), msg.data.end(), '\n');
		numOfCoord = numOfCoord-2;
		std::cout << "Num of coordinates: " << numOfCoord << std::endl;

		//Concating all the peaces of info together to send it to the topic j, k, l, m, n, o, p, r ,s
		std::string topicString = "2 " + std::to_string(waitTime) + " " + std::to_string(numOfCoord) + f + g + h + i + j + k + l;

		std::cout << "COncated string:" << std::endl;
		std::cout << topicString << std::endl;
		// std::cout << "Topic string is: " << topicString << std::endl;	
		//Replacing coordinate () - bracekets with a space 
		std::replace( topicString.begin(), topicString.end(), '(', ' '); 
		std::replace( topicString.begin(), topicString.end(), ')', ' '); 
		//Replacing coordinate ,-commas with a space 
		std::replace( topicString.begin(), topicString.end(), ',', ' '); 

		//ros string msg type:
		std_msgs::String message;

		//Converting topicString into char
		char arr[topicString.length() + 1]; 
		//Copying char into array which is later pushed to the data key of ros string message
	    strcpy(arr, topicString.c_str());
		//Adding the char to the message data type
		message.data = arr;
		//Puvlishig message to a topic channel
		qr_pub.publish(message);
	}
	


   is_there_new_artwork = true;

   oldMsg = msg.data;
   

}

void display(cv::Mat &im, cv::Mat &bbox)
{
  int n = bbox.rows;
  for(int i = 0 ; i < n ; i++)
  {
    line(im, cv::Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), cv::Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), cv::Scalar(255,0,0), 3);
  }
  imshow("Current Image", im);
}

void cameraCallback(const sensor_msgs::CompressedImageConstPtr& msg){
	try{
		cv::Mat color_img = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);

       if (!is_there_new_artwork){
           cv::Mat disp_img;
		   //Resizing imae for display putposes
           cv::resize(color_img, disp_img, cv::Size(0, 0), 0.25, 0.25, cv::INTER_LINEAR);
           cv::imshow("Current Image", disp_img);
           cv::waitKey(1);                        
           return;
       }

       is_there_new_artwork = false;
       
	   //Converting image to grayscale:
       cv::Mat gray_img;
       cv::cvtColor(color_img, gray_img, cv::COLOR_RGB2GRAY);      

	   //Detecting blobs:
       cv::SimpleBlobDetector::Params params;
       params.filterByColor = true;
       params.minThreshold = 0;
       params.maxThreshold = 200;
	   params.filterByCircularity = true;
	   params.minCircularity = 0.1;
	//    params.filterByArea = true;
	//    params.minArea = 700;

       cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
        
       new_keypoints.clear();
       detector->detect(gray_img, new_keypoints);
       cv::Mat  marked_img;

       if (new_keypoints.size()>0){
		//We draw red color on keypoints
           cv::drawKeypoints(color_img, new_keypoints, marked_img, cv::Scalar(36,156,255)); // , cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS

       }

       imshow("Current Image", marked_img);

	
	

	cv::waitKey(1);
	}
	
	catch(cv::Exception& e){
		ROS_ERROR("Error converting image, %s", e.what());
	}
}


int main(int argc, char **argv) {
	ros::init(argc, argv, "reading_image"); 
	ros::NodeHandle nh;

	ros::Subscriber subs_barcode = nh.subscribe("/barcode", 1, barcodeCallback);

	ros::Subscriber subs_camera = nh.subscribe("/camera/rgb/image_raw/compressed", 1, cameraCallback);


	qr_pub = nh.advertise<std_msgs::String>("qrComm", 1000);
	

	ros::Rate rate(10);
	while(ros::ok()){
		ros::spinOnce();
		rate.sleep();
	}
}