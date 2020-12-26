// ROS Node that captures and publishes the keys that are pressed once every second

// Include ROS functions
#include <ros/ros.h>
#include <std_msgs/String.h>

class key_tracker {

    public:
    // Variable to store pressed keys in
    std::string keys;

    // Variable to store subscriber topic
    std::string keyboard_topic;

    // Variables to store last and number of keys pressed
    int length = 0;
    char last;

    void start(int argc, char ** argv) {

        // Initialise Node
        ros::init(argc, argv, "key_tracker");

        // Create a handle
        ros::NodeHandle nh;

        // Get topic name from parameter file
        nh.getParam("keyboard_topic", keyboard_topic);

        // Set up subscriber
        ros::Subscriber sub = nh.subscribe(keyboard_topic, 10, key_tracker);

        // Set up publisher
        ros::Publisher pub = nh.advertise("key_press_info", 3);

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

        std::string result = "The number of keys pressed: " + std::to_string(length) + ". The last key pressed "
                                                                                "was" + last;

        // Publish Message
        pub.publish(result);

        ROS_INFO("%s", result.c_str());

        length = 0;
        last = " ";
        keys.clear();
    }

};

int main(int argc, char ** argv){

    // Create object
    key_tracker JetBot;

    JetBot.start(argc, argv);

    ros::Rate(1);

    while(ros::ok()){
        // Publish key press information
        JetBot.key_info_publish();

        // Process Callbacks?
        ros::spinOnce();
        r.sleep();
    }

}