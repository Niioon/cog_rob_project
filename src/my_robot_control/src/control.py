#! /usr/bin/env python 

import rospy
import roslaunch
from std_msgs.msg import String
from geometry_msgs.msg import Twist
import collections
import numpy as np



# find out how frequntly cmd_vel is published
# vel_publish_rate = 2

# keep track of velocities of last minute
# recent_velocities = collections.deque(np.ones(60*vel_publish_rate), maxlen=60*vel_publish_rate)
#
#def callback(data):
#    x = data.linear.x
#    y = data.linear.y
#    theta = data.angular.z
#
#    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data)
#
#    if x + y +theta == 0:
#        recent_velocities.append(0)
#    else:
#        recent_velocities.append(1)


last_vel_publish = 0

 
def callback(data):
    # if velocity cmds are published reset the timer
    global last_vel_publish
    last_vel_publish = 0



def main():
    # exploration 
    rospy.init_node('robot_control')

    # keeps track of time since last move command
 
    rospy.Subscriber("cmd_vel", Twist, callback)

    rate = rospy.Rate(1)

    robot_moving = True

    # while the robot is still exploring do nothing
    while robot_moving:
        # if sum(recent_velocities) == 0:
        #    robot_moving == False
        # else:
        #    rospy.loginfo("Robot is moving: %s", sum(recent_velocities))

        # count up the timer every second
        global last_vel_publish
        last_vel_publish += 1
        rospy.loginfo("seconds since last velocity cmd: %s", last_vel_publish)
        # stop loop if robot is not moving for 60 seconds
        if last_vel_publish >= 60:
            robot_moving = False
        rate.sleep()
    

    # when robot stops moving for one minute save map
    package = 'map_server'
    executable = 'map_saver'
    node_save_map = roslaunch.core.Node(package, executable, output='log', args='-f /home/nion/cog_rob_project/map/mymap')
    launch = roslaunch.scriptapi.ROSLaunch()
    launch.start()
    process = launch.launch(node_save_map)
    print(process.is_alive())
    rospy.spin()
    # process.stop()

    # find out how to shutdown nodes

    # launch navigation stack


    return 


if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass

    