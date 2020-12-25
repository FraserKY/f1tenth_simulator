// ROS Node that captures and publishes the keys that are pressed once every second

// Include ROS functions
#include <ros/ros.h>
#include <std_msgs/String.h>

class key_tracker(){

public:
// Variable to store pressed keys in
std::string keys;

// Variable to store subscriber topic
std::string keyboard_topic;

// Variables to store last and number of keys pressed
int length = 0;
char last;

void start() {

    // Initialise Node
    ros::init(argc, argv, "key_tracker");

    // Create a handle
    ros::NodeHandle nh;

    // Get topic name from parameter file
    nh.getParam("keyboard_topic", keyboard_topic);

    // Set up subscriber
    ros::subscriber sub = nh.subscribe(keyboard_topic, 10, key_tracker);

    // Set up publisher
    ros::publisher pub = nh.advertise("key_press_info", 3);

    //ros::Rate(1);
}

void key_tracker(const std_msgs::String &msg) {

    // Store key pressed in keys string
    keys.append(msg.data);
}

void key_info_publish() {

    // Get the number of keys pressed, and the last key
    length = keys.size();
    last = keys.back();

    std_msgs:
    String result = "The number of keys pressed: " + std::to_string(length) + ". The last key pressed "
                                                                              "was" + last;

    // Publish Message
    pub.publish(result);

    ROSINFO("%s", result.c_str());

    length = 0;
    last.clear()
    keys.clear()
}

}

int main(int argc, char ** argv){

    // Create object
    key_tracker JetBot;

    JetBot.start();

    ros::Rate(1)

    while(ros::ok()){
        // Publish key press information
        JetBot.key_info_publish();

        // Process Callbacks?
        ros::spinOnce();
        r.sleep();
    }

}