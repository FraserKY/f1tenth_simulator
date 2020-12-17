#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/String.h>
#include <string>
#include <iostream>

using namespace std;

class jetbotDriveCmd
{
private:
    // NodeHandle starts a node, with name 'n'
    ros::NodeHandle n;

    ros::Subscriber key_sub;

    ros::Publisher diff_drive_pub;

    double prev_key_velocity = 0.0;
    double keyboard_max_speed = 1.0;
    double rotationWheelSpeedScale;
    double leftWheelSpeed = 0;
    double rightWheelSpeed = 0;
    unsigned int mode = 2;
    double speed_increment, wheel_track;

public:
    jetbotDriveCmd()
    {
        n = ros::NodeHandle("~");

        // Create variables for parameters
        std::string diff_drive_topic, mux_topic, joy_topic, key_topic;
        // Get parameters from parameter Server dictionary'getParam(<key>, <storage variable>)'
	    n.getParam("diff_drive_topic", diff_drive_topic);
        n.getParam("keyboard_topic", key_topic);
        n.getParam("jetbot_rotation_wheel_speed_scale", rotationWheelSpeedScale);
        n.getParam("jetbot_width", wheel_track);
        n.getParam("speed_increment", speed_increment);


        // Advertise tells ROS master you want to publish information on a given topic (diff_drive_topic), 
        // Returns a publisher object that allows you to publish to the topic, using the .publish command
        // the number refers to the size of the buffer, ie how many messages to store, if messages are arriving more
        // quickly than they can be sent
        diff_drive_pub = n.advertise<std_msgs::Float64MultiArray>(diff_drive_topic, 10);

        // Subscribes to the key_topic topic, then calls the key_callback function whenever a message arrives.
        // The 2nd argument is the queue size.
        key_sub = n.subscribe(key_topic, 1, &jetbotDriveCmd::key_callback, this);

    }


    void publish_to_diff_drive(double rightWheelTrq,double leftWheelTrq)
    {
        // Creates an array 
        std_msgs::Float64MultiArray diffDriveMsg;
        // clears the array
	    diffDriveMsg.data.clear();
        // Adds rightWheelTrq to the end of the array
	    diffDriveMsg.data.push_back(rightWheelTrq);
	    diffDriveMsg.data.push_back(leftWheelTrq);
        // Publishes array
        diff_drive_pub.publish(diffDriveMsg);
    }

    void key_callback(const std_msgs::String & msg){

        bool publish = true;

        // Mode swap
        if (msg.data == "m"){
            // If in increase mode, swap to constant
            if (mode == 2){
                mode = 1;
                cout << "Constant Speed Mode" << endl;
                // else swap to increase
            }else{
                mode = 2;
                cout << "Game Mode" << endl;
            }
        }

        if (msg.data == "w"){
            // s_const mode
            if (mode == 1){
                leftWheelSpeed = 1.0;
                rightWheelSpeed = 1.0;
            }else{
                // speed increase mode
                leftWheelSpeed = leftWheelSpeed + speed_increment;
                rightWheelSpeed = rightWheelSpeed + speed_increment; 
            }

        }else if (msg.data == "c"){
            double tc_radius = 4;
            double wheel_d_inside = 2 * 3.14 * tc_radius;
            double wheel_d_outside = 2 * 3.14 * (tc_radius + wheel_track);
            double ratio = wheel_d_outside / wheel_d_inside;
            leftWheelSpeed = 0.5;
            rightWheelSpeed = leftWheelSpeed * ratio;

        }else if(msg.data=="s"){

            if (mode == 1){
                leftWheelSpeed = -1.0;
                rightWheelSpeed = -1.0;
            }else{
                // speed decrease mode
                leftWheelSpeed = leftWheelSpeed - speed_increment;
                rightWheelSpeed = rightWheelSpeed - speed_increment;
            }

        }else if(msg.data == "a"){
            leftWheelSpeed = -1.0*rotationWheelSpeedScale;
            rightWheelSpeed = 1.0*rotationWheelSpeedScale;

        }else if(msg.data == "d") {
            leftWheelSpeed = 1.0*rotationWheelSpeedScale;
            rightWheelSpeed = -1.0*rotationWheelSpeedScale;
        }else if (msg.data ==" "){
            leftWheelSpeed = 0.0;
            rightWheelSpeed = 0.0;
        }else {
            publish = false;
        }
        if (publish){
            publish_to_diff_drive(rightWheelSpeed , leftWheelSpeed);
        }
    }

};
int main(int argc, char ** argv){

    //
    ros::init(argc, argv, "jetbotDriveCmd");

    // 
    jetbotDriveCmd jetDriver;

    // spin() causes the code to loop
    ros::spin();
    
    return 0;
}


