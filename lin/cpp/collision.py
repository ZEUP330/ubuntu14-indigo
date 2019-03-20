import rospy
import moveit_ros_planning
import moveit_msgs
 
if __name__=='__main__':
    rospy.init_node('check_disco')
    plan=moveit_ros_planning
    moveit_msgs.msg.collision