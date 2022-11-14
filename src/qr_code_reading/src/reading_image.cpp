#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <codecvt>
#include <boost/algorithm/string.hpp>


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

#include <nlohmann/json.hpp>
using json = nlohmann::json;


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

void barcodeCallback(const std_msgs::String& msg){
//    cout << "Detected a QR Code!";
   	// std::cout << "\n";
    std::cout << msg.data;
	std::string::difference_type n = std::count(msg.data.begin(), msg.data.end(), '\n');
	std::cout << "Num of lines: " << n << std::endl;
	std::cout << "-----------" << std::endl;
	// input = std::to_string(msg.data);

	std::istringstream iss{msg.data};
	std::string a, b, c, d, e, f, g, h, i, j;
	if (iss >> a >> b >> c >> d >> e >> f >> g) {
		std::string synonym = a + b + c + d;
		std::cout << a << b << c << d << e << f << g << std::endl;
	} else
		std::cerr << "your string didn't contain four whitespace separated substrings\n";
	



	// std::string hello = "Hello World"; 
    // std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
    // std::u16string hello_word_u16 = convert.from_bytes(hello); 
    // std::string hello_world_u8 = convert.to_bytes(hello_word_u16);


	//Converting int to string:
	// std::string numOfLines = std::to_string(n);
	// std::cout << "Num of lines:" << numOfLines.substr(0, 1);
	
	// std:cout << n;
	// for (int val = 1; val <= 10; ++val) {

	// }

//    first_two = msg.data.substr(0, 2);
//    std::cout << first_two;

//    cout << msg.data;
//    cout << "\n";
   is_there_new_artwork = true;
   
//    json js = msg.data;
//    auto s2 = js.get<std::string>();

//    cout << js["location1"];


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
		//    cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS
       }
    //    cv::resize(marked_img, marked_img, cv::Size(0, 0), 0.25, 0.25, cv::INTER_LINEAR);
       imshow("Current Image", marked_img);

	// cv::QRCodeDetector qrDecoder = cv::QRCodeDetector();
 
	// cv::Mat bbox, rectifiedImage;
	
	// std::string data = qrDecoder.detectAndDecode(gray_img, bbox, rectifiedImage);

	// if(data.length()>0) {
	// 	display(color_img, bbox);
	// 	// rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
	// 	// imshow("Current Image", rectifiedImage);
	// } else {

	// }
	
	

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

	ros::Subscriber subs_camera = nh.subscribe("/usb_cam/image_raw/compressed", 1, cameraCallback);

	
	

	ros::Rate rate(10);
	while(ros::ok()){
		ros::spinOnce();
		rate.sleep();
	}
}