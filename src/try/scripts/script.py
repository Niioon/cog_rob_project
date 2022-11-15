#!/usr/bin/env python3

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib>

import time

import rospy
from actionlib_msgs.msg import GoalStatusArray
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import PoseWithCovarianceStamped
from move_base_msgs.msg import MoveBaseActionFeedback
from std_msgs.msg import Float64

current_pos = [0, 0]
moving_status = 0

def publishMethod(goalsX, goalsY, pub):
    # params & variables
    goalMsg = PoseStamped()
    goalMsg.header.frame_id = "base_link"
    goalMsg.pose.orientation.z = 0.0
    goalMsg.pose.orientation.w = 1.0
    # Publish the first goal
    goalMsg.header.stamp = rospy.get_rostime()
    global current_pos
    X = goalsX - current_pos[0]
    Y = goalsY - current_pos[1]
    goalMsg.pose.position.x = X
    goalMsg.pose.position.y = Y
    pub.publish(goalMsg)
    current_pos = [goalsX, goalsY]


def subscriberCallback(data):
    global moving_status
    moving_status = data.status_list[0].status
    print(moving_status)

def main():
    rospy.init_node('navControl', anonymous=True)
    global moving_status
    rospy.Subscriber("move_base/status", GoalStatusArray, subscriberCallback)
    pub = rospy.Publisher('move_base_simple/goal', PoseStamped, queue_size=10)
    goals_X = [1, -1, 0]
    goals_Y = [1, 1, 1]
    for i in range(len(goals_X)):
        publishMethod(goals_X[i], goals_Y[i], pub)
        while moving_status == 1:
            time.sleep(1)
        time.sleep(1)
        

if __name__ == '__main__':
    try:
        main()     
    except rospy.ROSInterruptException:
        pass
