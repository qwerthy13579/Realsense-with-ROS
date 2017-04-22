#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <realsense_camera/IsPowered.h>
#include <realsense_camera/SetPower.h>
#include "std_srvs/Empty.h"
#include "std_msgs/Bool.h"
#include <cstdlib>

int main(int argc, char **argv)
{

ros::init(argc, argv, "set_power");

ros::NodeHandle n;

ros::ServiceClient client = n.serviceClient<realsense_camera::SetPower>("/camera/driver/set_power");

realsense_camera::SetPower srv;

srv.request.power_on = atoll(argv[1]);

if(client.call(srv))
{
   ROS_INFO("Status: %d", srv.response.success);
}
else
{
   ROS_INFO("Failed to call service");
return 1;
}




return 0;
}
