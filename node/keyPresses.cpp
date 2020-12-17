// This is a node that publishes the number of keys pressed in the last second, 
// and the last character entered.

// Include ROS functions
#include <ros/ros.h>

// Allow printing to terminal
#include <iostream>

//Declare functions
void key_tracker(const std_msgs::String & msg);
string num_and_last_key(string * keys_pressed)

int main(int argc, char ** argv){

    // Initialise the node
    ros::init(argc, argv, "key_presses");

    // Start the node
    ros::NodeHandle nh;

    // Tell master that we will be publishing on a topic
    // Creates an object 'key_press' that can be used to publish to the topic
    ros::Publisher key_press_info = nh.advertise<std_msgs::string>(key_presses_topic(), 100);
    
    // Need to subscribe to topic
    // Create variable for topic to subscribe to
    std::string keyboard_topic;

    // Get name of topic to subscribe from param server
    nh.getParam("keyboard_topic", keyboard_topic);

    // create subscriber, subscibes to topic stored in var keyboard_topic
    // sets a queue size, and then the function to be called when a message
    // is recieved
    ros::Subscriber sub = nh.subscribe(keyboard_topic, 10, key_tracker())

    // create an array to store characters in
    std::string keys_pressed;

    // need a loop that publishes the length of keys_pressed, and the last character
    // then resets contents of keys_pressed every second. Needs to allow tracking function to be called
    // whenever a new key is pressed
    
    // 
    ros::Rate(1);

    //Call publish function
    while(ros::ok())
    {
        //function that returns number of characters and final character
        message = num_and_last_key(keys_pressed);

        //publish to topic 
        key_press_info.publish(message);
        ROS_INFO("%s", message.c_str());

        // Clear string
        key_presses.clear();

        ros::Spin();
    }

}

// A function to keep track of keys pressed..
void key_tracker(const std_msgs::string & msg){

    // Add new key to end of string
    keys_pressed.append(msg.data);

}

string num_and_last_key(string * keys_pressed){
    //  Get length
    int length = keys_pressed.size();
    std::string last = keys_pressed.back();

    result = "The number of keys pressed: " + to_string(length) + ". The last key pressed was" + last;

    return result; 
}