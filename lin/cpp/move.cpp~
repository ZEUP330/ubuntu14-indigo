// 包含miveit的API头文件#include <ros/ros.h>
#include <stdio.h>
#include<unistd.h>
// 包含moveit的API
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/kinematic_constraints/utils.h>
#include <eigen_conversions/eigen_msg.h>
#include <moveit/move_group_interface/move_group.h>
int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle; 
  ros::AsyncSpinner spinner(1);
  spinner.start();
 
  moveit::planning_interface::MoveGroup group("arm");
 
  // 设置机器人终端的目标位置
  geometry_msgs::Pose target_pose1;
  target_pose1.orientation.w = 0.726282;
  target_pose1.orientation.x= 4.04423e-07;
  target_pose1.orientation.y = -0.687396;
  target_pose1.orientation.z = 4.81813e-07;
 
  target_pose1.position.x = 0.2;
  target_pose1.position.y = 0.37;
  target_pose1.position.z = 1;
  group.setPoseTarget(target_pose1);
 
 
  // 进行运动规划，计算机器人移动到目标的运动轨迹，此时只是计算出轨迹，并不会控制机械臂运动
  moveit::planning_interface::MoveGroup::Plan my_plan;
  bool success = group.plan(my_plan);
  
  ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");   
  //让机械臂按照规划的轨迹开始运动。
  if(success){
      group.execute(my_plan);
      printf("seccss");}
  else{printf("fail");}
  ros::shutdown(); 
  return 0;
}
