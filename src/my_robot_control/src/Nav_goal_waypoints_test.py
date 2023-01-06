#! /usr/bin/env python3
# license removed for brevity

import rospy
import actionlib
import time
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
import tf
import tf_conversions
import geometry_msgs
import math
from std_msgs.msg import String

qrMsg = ""
splitMsg = []
RoomsX = [2.0, 1.5]
RoomsY = [2.0, 4.0]

def movebase_client(goalX, goalY, goalW):

    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    client.wait_for_server()

    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
    goal.target_pose.pose.position.x = goalX
    goal.target_pose.pose.position.y = goalY
    goal.target_pose.pose.orientation = geometry_msgs.msg.Quaternion(*tf_conversions.transformations.quaternion_from_euler(0, 0, goalW))

    client.send_goal(goal)
    wait = client.wait_for_result()
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
        return client.get_result()

def subscriberCallback(data):
    global qrMsg
    qrMsg = data.data
    print(qrMsg) #prints on terminal

def disinfection():
    global qrMsg
    global splitMsg
    global RoomsX
    global RoomsY
    splitMsg = qrMsg.split()
    print(splitMsg)
    if(splitMsg[0]=="1"):
        for i in range(int(splitMsg[2])):
            result = 0
            result = movebase_client(RoomsX[int(splitMsg[i+3])-1], RoomsY[int(splitMsg[i+3])-1], 0)
            time.sleep(1)
            if result:
                time.sleep(float(splitMsg[1]))
                rospy.loginfo('room reached ' + str(i+1))
    elif(splitMsg[0]=="2"):
        for i in range(int(splitMsg[2])):
            result = 0
            result = movebase_client(float(splitMsg[3+(i*2)]), float(splitMsg[4+(i*2)]), 0)
            time.sleep(1)
            if result:
                time.sleep(float(splitMsg[1]))
                rospy.loginfo('room reached ' + str(i+1))


def main():
    rospy.init_node('movebase_client_py')
    rospy.Subscriber("qrComm", String, subscriberCallback)
    goals_X = [-1.65, 2.4, 0]
    goals_Y = [2.15, 0.15, 0]
    goals_W = [0, -math.pi/2, math.pi/2]

    for i in range(len(goals_X)):
        result = 0
        result = movebase_client(goals_X[i], goals_Y[i], goals_W[i])
        time.sleep(1)
        if result:
            
            rospy.loginfo('qr code reached ' + str(i+1))
            disinfection()



if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
