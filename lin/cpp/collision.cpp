#include <ros/ros.h>
#include <stdio.h>
#include<unistd.h>
#include <iostream>
using namespace std;
// 包含moveit的API
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/kinematic_constraints/utils.h>
#include <eigen_conversions/eigen_msg.h>
#include <moveit/move_group_interface/move_group.h>

 
int main(int argc, char **argv)
{
  ros::init (argc, argv, "arm_kinematics");
  ros::AsyncSpinner spinner(1);
  spinner.start();


  //printf("\n加载机器人的运动学模型到情景实例中\n");
  robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
  robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
  planning_scene::PlanningScene planning_scene(kinematic_model);
 
  collision_detection::CollisionRequest collision_request;
  collision_detection::CollisionResult collision_result;
  robot_state::RobotState copied_state = planning_scene.getCurrentState();
  //printf("\n修改允许碰撞矩阵（Allowed Collision Matrix，acm)\n");
  //printf("\n 我们可以通过修改acm来指定机器人是否检测自身碰撞和与障碍物的碰撞，在不检测的状态下，即使发生碰撞，检测结果也会显示未发生碰撞\n");
 
  //printf("\n完整的碰撞检测\n");
  //printf("\n同时检测自身碰撞和与障碍物的碰撞\n");
  planning_scene.checkSelfCollision(collision_request, collision_result);
  while(true){  
    collision_detection::AllowedCollisionMatrix acm = planning_scene.getAllowedCollisionMatrix();
    //printf("\ndddddd\n");
    collision_detection::CollisionResult::ContactMap::const_iterator it2;int i=0;
    for(it2 = collision_result.contacts.begin(); it2 != collision_result.contacts.end(); i++, ++it2)
    {
      acm.setEntry(it2->first.first, it2->first.second, true);
    }
    printf("\n%d\n",i);  
    collision_result.clear();
    planning_scene.checkSelfCollision(collision_request, collision_result, copied_state, acm);
    ROS_INFO_STREAM("Test 5: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");

    collision_result.clear();
    planning_scene.checkCollision(collision_request, collision_result, copied_state, acm);
    sleep(1);
    ROS_INFO_STREAM("6. Full collision Test: "<< (collision_result.collision ? "in" : "not in")
                  << " collision");
  }
  ros::shutdown();
  return 0;
}
