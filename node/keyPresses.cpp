// This is a node that publishes the number of keys pressed in the last second, 
// and the last character entered.

// Include ROS functions
#include <ros/ros.h>

// Allow printing to terminal
#include <iostream>
#include <std_msgs/String.h>
#include <ros/console.h>

//Declare functions
void key_reciever(const std_msgs::String & msg);
std::string num_and_last_key(std::string keys_pressed);

int main(int argc, char ** argv){

    // Initialise the node
    ros::init(argc, argv, "key_presses");
    ROS_INFO("keyPresses Node Initialised\n");

    // Start the node
    ros::NodeHandle nh;

    // Tell master that we will be publishing on a topic
    // Creates an object 'key_press' that can be used to publish to the topic
    ros::Publisher key_press_info = nh.advertise<std_msgs::String>("key_press_info", 3);
    ROS_INFO("Publisher Created\n");

    // Need to subscribe to topic
    // Create variable for topic to subscribe to
    std::string keyboard_topic;

    // Get name of topic to subscribe from param server
    nh.getParam("keyboard_topic", keyboard_topic);

    // create an array to store characters in
    std::string keys_pressed;

    // create subscriber, subscribes to topic stored in var keyboard_topic
    // sets a queue size, and then the function to be called when a message
    // is received
    ros::Subscriber sub = nh.subscribe(keyboard_topic, 10, key_reciever);


    // need a loop that publishes the length of keys_pressed, and the last character
    // then resets contents of keys_pressed every second. Needs to allow tracking function to be called
    // whenever a new key is pressed
    
    // 
    ros::Rate(1);

    //Call publish function
    while(ros::ok())
    {
        //function that returns number of characters and final character
        std_msgs::String message;
        message.data = num_and_last_key(keys_pressed);
        ROS_INFO("Entered while loop keyPresses.cpp\n");

        //publish to topic 
        key_press_info.publish(message);
        ROS_INFO("%s", message.data.c_str());

        // Clear string
        keys_pressed.clear();

        ros::spin();
    }

}

// A function to keep track of keys pressed..
// I think i need a function to get the key when the subscriber function is called
// then i need to pass it back into main?, this way I can then add it to main
void key_reciever(const std_msgs::String & msg){

    // Add new key to end of string
    //keys_pressed.append(msg.data);
    ROS_INFO("%s", msg.data.c_str());

    //return keys_pressed;
}

std::string num_and_last_key(std::string keys_pressed){
    //  Get length
    int length = keys_pressed.size();
    char last = keys_pressed.back();

    std::string result = "The number of keys pressed: " + std::to_string(length) + ". The last key pressed was" + last;

    ROS_INFO("%s", result.c_str());

    return result;
}