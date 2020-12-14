// This is a node that publishes the number of keys 
// pressed in the last second, and the last character entered

// Include ROS functions
#include <ros/ros.h>

// Allow printing to terminal
#include <iostream>

int main(int argc, char ** argv){

    // Initialise the node
    ros::init(argc, argv, "keyPresses");

    // Start the node
    ros::NodeHandle nh;

    // Tell master that we will be publishing on a topic
    // Creates an object 'key_press' that can be used to publish to the topic
    ros::Publisher key_press = n.advertise<std_msgs::String>(key_presses_topic, 100);
    
    // Need to subscribe to topic
    // Create variable for topic to subscribe to
    std::string keyboard_topic;

    // Get name of topic to subscribe from param server
    n.getParam("Keyboard_topic", keyboard_topic);

    // create subscriber
    ros::Subscriber sub = 

    // loop rate (1hz, 1 per second)
    ros::Rate loop_rate(1);



}