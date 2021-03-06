//首先要包含API的头文件
#include <stdio.h>
#include <moveit/move_group_interface/move_group.h>
int main(int argc, char **argv)
{
  printf("OK!");
  ros::init(argc, argv, "move_group_interface_demo", ros::init_options::AnonymousName);
  // 创建一个异步的自旋线程（spinning thread）
  ros::AsyncSpinner spinner(1);
  spinner.start();
  // 连接move_group节点中的机械臂实例组，这里的组名arm是我们之前在setup assistant中设置的
  move_group_interface::MoveGroup group("arm");
  
  
  
  // 随机产生一个目标位置
  group.setRandomTarget();
  // 开始运动规划，并且让机械臂移动到目标位置
  group.move();
  ros::waitForShutdown();
}
