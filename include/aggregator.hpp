#ifndef AGGREGATOR_HPP
#define AGGREGATOR_HPP

#include <cstdio>

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/header.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "sensor_msgs/msg/point_field.hpp"

#include "ringbuffer.hpp"

namespace pointcloud2
{

class Pointcloud2_Aggregator: public rclcpp::Node 
{

    public:
        Pointcloud2_Aggregator(const rclcpp::NodeOptions& options);

    private:

        void pointcloud2_sub_callback(const sensor_msgs::msg::PointCloud2& msg);
        void timer_callback();
        void insert_msg_into_buffer();

        double publish_frequency;
        std::string topic_name;
        std::string topic_name_agg;
        std::shared_ptr<rclcpp::Duration> time_window;
        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud2_sub;

        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr aggregator_pub;

        std::shared_ptr<ring<sensor_msgs::msg::PointCloud2::SharedPtr>> buffer;

        rclcpp::TimerBase::SharedPtr receive_timer;
        rclcpp::TimerBase::SharedPtr aggregated_publish_timer;

        sensor_msgs::msg::PointCloud2::SharedPtr pointcloud_template;
        sensor_msgs::msg::PointCloud2::SharedPtr latest_msg;
        
};
}

#endif