// This is a node that publishes the number of keys pressed in the last second, 
// and the last character entered.

// Include ROS functions
#include <ros/ros.h>

// Allow printing to terminal
#include <iostream>

int main(int argc, char ** argv){

    // Initialise the node
    ros::init(argc, argv, "key_presses");

    // Start the node
    ros::NodeHandle nh;

    // Tell master that we will be publishing on a topic
    // Creates an object 'key_press' that can be used to publish to the topic
    ros::Publisher key_press = n.advertise<std_msgs::String>(key_presses_topic, 100);
    
    // Need to subscribe to topic
    // Create variable for topic to subscribe to
    std::string keyboard_topic;

    // Get name of topic to subscribe from param server
    nh.getParam("keyboard_topic", keyboard_topic);

    // create subscriber, subscibes to topic stored in var keyboard_topic
    // sets a queue size, and then the function to be called when a message
    // is recieved
    ros::Subscriber sub = nh.subscribe(keyboard_topic, 10, key_tracker)

    // create an array to store characters in
    std::string keys_pressed;

    // loop rate (1hz, 1 per second)
    ros::Rate loop_rate(1);

    // need a loop that publishes the length of keys_pressed, and the last character
    // then resets contents of keys_pressed every second. Needs to allow tracking function to be called
    // whenever a new key is pressed



}

// A function to keep track of keys pressed..
void key_tracker(const std_msgs::String & msg){

    // Add new key to end of string
    keys_pressed.append(msg.data);

}
