#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "autocross_visualizer/Vector2D.hpp"


enum Colour {
    Blue,    // By default, this will be 0
    Yellow,  // This will be 1
};

class MarkerPublisher : public rclcpp::Node
{
public:
    MarkerPublisher() : Node("marker_publisher")
    {

        // marker_pub is the publisher to the topic "visualization_marker"
        marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("visualization_marker", 10);
    
    
        // Read coordinates from file and store in vector
        coordinates_left = read_coordinates_from_file("Left.txt");
        coordinates_right = read_coordinates_from_file("Right.txt");
        timer_ = this->create_wall_timer(std::chrono::milliseconds(0), std::bind(&MarkerPublisher::publish_markers, this));


    }

private:

    std::vector<Vector2D> read_coordinates_from_file(const std::string &filename)
    {
        // This function reads a file, and returns the vector of vectors

        std::vector<Vector2D> coordinates;
        std::ifstream file(filename);

        if (!file.is_open())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open file: %s", filename.c_str());
            return coordinates;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            double x, y;

            // Reading x and y from the line
            ss >> x >> y;

            if (ss.fail())
            {
                RCLCPP_WARN(this->get_logger(), "Failed to parse line: %s", line.c_str());
                continue;
            }

            // Create a Vector2D object and add it to the vector
            coordinates.emplace_back(x, y);
        }

        file.close();
        return coordinates;
    }

    void publish_markers()
    {
        create_and_publish_markers(coordinates_left,coordinates_right);
    }

    void create_and_publish_markers(const std::vector<Vector2D> &coordinatesLeft,const std::vector<Vector2D> &coordinatesRight)
    {
        int id = 0;  // ID to differentiate each marker

        for (const auto& coord : coordinatesLeft)
        {
            auto marker = visualization_msgs::msg::Marker();
            marker.header.frame_id = "map";
            marker.header.stamp = this->get_clock()->now();
            marker.ns = "basic_shapes";
            marker.id = id++;
            
            marker.type = visualization_msgs::msg::Marker::SPHERE;
            marker.action = visualization_msgs::msg::Marker::ADD;

            // Set the position from the Vector2D object
            marker.pose.position.x = coord.x;
            marker.pose.position.y = coord.y;
            marker.pose.position.z = 0.0;  // Assuming z=0 for 2D coordinates
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.scale.x = 0.5;
            marker.scale.y = 0.5;
            marker.scale.z = 0.5;

            marker.color.r = 0.0f;
            marker.color.g = 0.0f;
            marker.color.b = 1.0f;
            marker.color.a = 1.0;
            marker.lifetime = rclcpp::Duration::from_seconds(0); // Marker persists indefinitely

            // Publish the marker
            marker_pub_->publish(marker);
        }


        for (const auto& coord : coordinatesRight)
        {
            auto marker = visualization_msgs::msg::Marker();
            marker.header.frame_id = "map";
            marker.header.stamp = this->get_clock()->now();
            marker.ns = "basic_shapes";
            marker.id = id++;
            
            marker.type = visualization_msgs::msg::Marker::SPHERE;
            marker.action = visualization_msgs::msg::Marker::ADD;

            // Set the position from the Vector2D object
            marker.pose.position.x = coord.x;
            marker.pose.position.y = coord.y;
            marker.pose.position.z = 0.0;  // Assuming z=0 for 2D coordinates
            marker.pose.orientation.x = 0.0;
            marker.pose.orientation.y = 0.0;
            marker.pose.orientation.z = 0.0;
            marker.pose.orientation.w = 1.0;
            marker.scale.x = 0.5;
            marker.scale.y = 0.5;
            marker.scale.z = 0.5;

            marker.color.r = 1.0f;
            marker.color.g = 1.0f;
            marker.color.b = 0.0f;
            marker.color.a = 1.0;
            marker.lifetime = rclcpp::Duration::from_seconds(0); // Marker persists indefinitely

            // Publish the marker
            marker_pub_->publish(marker);
        }
    }

    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<Vector2D> coordinates_left;
    std::vector<Vector2D> coordinates_right;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MarkerPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}