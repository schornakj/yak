/*
 * ros_rgbd_camera.h
 *
 *  Created on: Jun 2, 2015
 *      Author: mklingen
 */

#ifndef ROS_RGBD_CAMERA_H_
#define ROS_RGBD_CAMERA_H_

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <image_transport/camera_subscriber.h>
#include <cv_bridge/cv_bridge.h>
#include <kfusion/types.hpp>

namespace kfusion
{
    class RosRGBDCamera
    {
        public:
            RosRGBDCamera(const ros::NodeHandle& handle);
            virtual ~RosRGBDCamera();

            void SubscribeDepth(const std::string& topic);
            void SubscribeRGB(const std::string& topic);

            void DepthCallback(const sensor_msgs::ImageConstPtr& image, const sensor_msgs::CameraInfoConstPtr& cameraInfo);
            void RGBCallback(const sensor_msgs::ImageConstPtr& image, const sensor_msgs::CameraInfoConstPtr& cameraInfo);

            bool Grab(cv::Mat& depth, cv::Mat& image);

            kfusion::Intr GetDepthIntrinsics();

            inline int GetDepthWidth()
            {
                return lastDepthInfo->width;
            }
            inline int GetDepthHeight()
            {
                return lastDepthInfo->height;
            }

            ros::NodeHandle nodeHandle;

            image_transport::ImageTransport transport;
            image_transport::CameraSubscriber depthSubscriber;
            image_transport::CameraSubscriber rgbSubscriber;

            sensor_msgs::ImageConstPtr lastDepthImage;
            sensor_msgs::CameraInfoConstPtr lastDepthInfo;
            sensor_msgs::ImageConstPtr lastRGBImage;
            sensor_msgs::CameraInfoConstPtr lastRGBInfo;

            bool hasNewDepth;
            bool hasNewRGB;
            bool subscribedDepth;
            bool subscribedRGB;

            ros::Time lastImageTime;
    };

} /* namespace kfusion */
#endif /* ROS_RGBD_CAMERA_H_ */
