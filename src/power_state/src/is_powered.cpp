#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <realsense_camera/IsPowered.h>
#include <realsense_camera/SetPower.h>
#include "std_srvs/Empty.h"
#include "std_msgs/Bool.h"
#include <cstdlib>



int main(int argc, char **argv)
{

ros::init(argc, argv, "is_powered");

ros::NodeHandle n;

ros::ServiceClient client = n.serviceClient<realsense_camera::IsPowered>("/camera/driver/is_powered");

realsense_camera::IsPowered srv;


if(client.call(srv))
{
   if((int)srv.response.is_powered == 1){
   ROS_INFO("Status: Power On");
  }
   else{
          ROS_INFO("Status: Power Off");
       }
}
else
{
   ROS_INFO("Status: Power Off");
}


return 0;
}
