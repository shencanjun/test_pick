#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include "pick_place_bridge/set_pick.h"
#include "pick_place_bridge/set_place.h"
#include "pick_place_bridge/ros_pick_place.h"
#include "pick_place_bridge/ros_freeback.h"
#include "pick_place_bridge/ros_stop.h"

int main(int argc, char** argv)
{
    ros::init(argc,argv,"test_new_pick");
    ros::NodeHandle n;
    ros::ServiceClient client_setpick = n.serviceClient<pick_place_bridge::set_pick>("set_pick_pose");
    ros::ServiceClient client_setplace = n.serviceClient<pick_place_bridge::set_place>("set_place_pose");
    ros::ServiceClient client_pickplace = n.serviceClient<pick_place_bridge::ros_pick_place>("pick_place");
    //ros::ServiceClient client_pickstop = n.serviceClient<pick_place_bridge::ros_stop>("pick_stop");
    //ros::ServiceClient client_freeback = n.serviceClient<pick_place_bridge::ros_freeback>("pick_freeback");

    pick_place_bridge::set_pick set_pick_po;
    pick_place_bridge::set_place set_place_po;
    pick_place_bridge::ros_pick_place pick_place;
   // pick_place_bridge::pick_freeback pf;

    geometry_msgs::Pose pickpos, placepos;

    pickpos.position.x = 0.34;
    pickpos.position.y = -0.23;
    pickpos.position.z = 0.34;
    pickpos.orientation.x = 0.707056;
    pickpos.orientation.y = -2.93083e-05;
    pickpos.orientation.z = -0.707157;
    pickpos.orientation.w = 1.0609e-05;

    placepos.position.x = 0.45;
    placepos.position.y = 0.35;
    placepos.position.z = 0.55;
    placepos.orientation.x = 0;
    placepos.orientation.y = 0;
    placepos.orientation.z = 0;
    placepos.orientation.w = 1;


    set_pick_po.request.pickPos = pickpos;
    set_place_po.request.placePos = placepos;


    if(client_setpick.call(set_pick_po))
       std::cout<<"set_pick succeeful"<<std::endl;
    else
       std::cerr<<"set_pick failed"<<std::endl;

    sleep(3.0);

    if(client_setplace.call(set_place_po))
       std::cout<<"set_place_po succeeful"<<std::endl;
    else
       std::cerr<<"set_place_po failed"<<std::endl;

    sleep(3.0);
    
    if(client_pickplace.call(pick_place))
       std::cout<<"pick_place succeeful"<<std::endl;
    else
       std::cerr<<"pick_place failed"<<std::endl;
}

