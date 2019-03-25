#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy, sys
import moveit_commander
from moveit_commander import MoveGroupCommander, PlanningSceneInterface
from moveit_msgs.msg import PlanningScene, ObjectColor
from geometry_msgs.msg import PoseStamped, Pose


class MoveItObstaclesDemo:

    def __init__(self, pose):
        self.check_collision = False

        # 初始化move_group的API
        moveit_commander.roscpp_initialize(sys.argv)

        # 初始化ROS节点
        rospy.init_node('moveit_obstacles_demo')

        # 初始化场景对象
        scene = PlanningSceneInterface()

        # 创建一个发布场景变化信息的发布者
        self.scene_pub = rospy.Publisher('planning_scene', PlanningScene, queue_size=5)

        # 创建一个存储物体颜色的字典对象
        self.colors = dict()

        # 等待场景准备就绪
        rospy.sleep(1)

        # 初始化需要使用move group控制的机械臂中的arm group
        arm = MoveGroupCommander('arm')

        # 获取终端link的名称
        end_effector_link = arm.get_end_effector_link()

        # 设置位置(单位：米)和姿态（单位：弧度）的允许误差
        arm.set_goal_position_tolerance(0.01)
        arm.set_goal_orientation_tolerance(0.05)

        # 当运动规划失败后，允许重新规划
        arm.allow_replanning(True)

        # 设置目标位置所使用的参考坐标系
        reference_frame = 'base_link'
        arm.set_pose_reference_frame(reference_frame)

        # 设置每次运动规划的时间限制：5s
        arm.set_planning_time(5)


        # 将场景中的颜色设置发布
        self.sendColors()
        rospy.sleep(5)

        joint_positions = pose
        arm.set_joint_value_target(joint_positions)

        # 控制机械臂完成运动
        if arm.go():
            pass
        else:
            self.check_collision = True
        rospy.sleep(1)


        # 关闭并退出moveit
        moveit_commander.roscpp_shutdown()
        moveit_commander.os._exit(0)

    # 设置场景物体的颜色
    def setColor(self, name, r, g, b, a=0.9):
        # 初始化moveit颜色对象
        color = ObjectColor()

        # 设置颜色值
        color.id = name
        color.color.r = r
        color.color.g = g
        color.color.b = b
        color.color.a = a

        # 更新颜色字典
        self.colors[name] = color

    # 将颜色设置发送并应用到moveit场景当中
    def sendColors(self):
        # 初始化规划场景对象
        p = PlanningScene()

        # 需要设置规划场景是否有差异
        p.is_diff = True

        # 从颜色字典中取出颜色设置
        for color in self.colors.values():
            p.object_colors.append(color)

        # 发布场景物体颜色设置
        self.scene_pub.publish(p)


if __name__ == "__main__":
    try:
        pass
        #M = MoveItObstaclesDemo([0, 0, 0, 0, 0, 0, 0])
        #print M.check_collision
    except KeyboardInterrupt:
        raise

