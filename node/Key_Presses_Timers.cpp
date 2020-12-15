// This is a node that publishes the number of keys pressed in the last second, 
// and the last character entered. Uses Timers to allow aysnchronous
// reading and publishing

#include <ros/ros.h>

class KeyRecorder
{
// Public is an access specifier, makes functions accessible outside of the class
public:
    // Function to initialise object
    key_recorder_start()
    {
        // advertise to master we will be publishing to a topic, returns object that can be used to publish
        ros::Publisher key_press = n.advertise<std_msgs::String>(key_presses_topic, 100);

    }


    // Function to read key presses
    char read_keys()
    {

    }

    // Function to publish to topic
    void publish_info()
    {


    }

private:
    // Character array



};

int main(int argc, char **argv)
{
    // Initialise the Node and start it
    ros::init(argc, argv, "key_presses");
    ros::NodeHandle nh;

    // create an instance of the keyRecorder class (pass the address of nh)
    KeyRecorder keyrecorder(&nh);

    // Create a ROS timer for reading data
    // createTimer requires a 'callback trigger' and a 'callback function
    // Reads 10 times a second
    ros::Timer timerReadfromkeyboard_topic = 
                    nh.createTimer(ros::Rate(10), std:bind(&KeyRecorder::read_keys));


    // Create a Ros timer for publishing the key presses
    ros::Timer timerPublishToTopic = 
                    nh.createTimer(ros::Rate(1), std:bind(&KeyRecorder::publish_info));

    // Causes the code to loop 
    ros::spin();

}