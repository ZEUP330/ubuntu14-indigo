#include <moveit/move_group_interface/move_group.h>
#include <stdio.h>
int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle; 
  ros::AsyncSpinner spinner(1);
  spinner.start();
  printf("\ninit finish\n");
  moveit::planning_interface::MoveGroup group("arm");
  group.setStartState(*group.getCurrentState());
  // 设置机器人终端的目标位置
  geometry_msgs::Pose target_pose1;
  target_pose1.orientation.w = 0.726282;
  target_pose1.orientation.x= 0.6;
  target_pose1.orientation.y = -0.687396;
  target_pose1.orientation.z = 4.81813e-07;
 
  target_pose1.position.x = 0.5;
  target_pose1.position.y = 0.4;
  target_pose1.position.z = 0.7;
  group.setPoseTarget(target_pose1);
 
  printf("\nsetting finish\n");
 
  // 进行运动规划，计算机器人移动到目标的运动轨迹，此时只是计算出轨迹，并不会控制机械臂运动
  moveit::planning_interface::MoveGroup::Plan my_plan;
  bool success = group.plan(my_plan);
  
  printf("\nplanning finish\n");
  ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");   
 
  //让机械臂按照规划的轨迹开始运动。

  printf("\nmove start\n");
  if(success)
      group.execute(my_plan);
 
  ros::shutdown(); 

  printf("\nall down\n");
  return 0;
}
