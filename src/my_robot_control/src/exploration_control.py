#! /usr/bin/env python 

import rospy
import roslaunch
from std_msgs.msg import String
from geometry_msgs.msg import Twist
import collections
import numpy as np
import os


 


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
        # count up the timer every second
        global last_vel_publish
        last_vel_publish += 1
        rospy.loginfo("seconds since last velocity cmd: %s", last_vel_publish)
        # stop loop if robot is not moving for 60 seconds
        if last_vel_publish >= 10:
            robot_moving = False
        rate.sleep()
    

    # when robot stops moving for one minute save map
    package = 'map_server'
    executable = 'map_saver'

    # get the path to the map directory independent of the user
    absolute_path = os.path.dirname(__file__)
    full_path = os.path.realpath(os.path.join(absolute_path, '..', '..', '..', 'map', 'mymap'))
    path_args = '-f ' + full_path
    rospy.loginfo('writing map to: ' + path_args)

    node_save_map = roslaunch.core.Node(package, executable, output='log', args=path_args)
    launch = roslaunch.scriptapi.ROSLaunch()
    launch.start()
    process = launch.launch(node_save_map)
    rospy.spin()
    # process.stop()

    # find out how to shutdown nodes
    return 


if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass

    