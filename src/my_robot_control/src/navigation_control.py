#! /usr/bin/env python 

import rospy
import roslaunch
import actionlib
from std_msgs.msg import String
import nav_msgs
from nav_msgs.srv import GetPlan, GetPlanRequest
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from geometry_msgs.msg import PoseStamped
import geometry_msgs
import tf_conversions
import numpy as np
from sys import maxsize
from itertools import permutations


qrMsg = ""
splitMsg = []

def movebase_client(goal_pose):

    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
    client.wait_for_server()

    # goal = MoveBaseGoal()
    # goal.target_pose.header.frame_id = "map"
    # goal.target_pose.header.stamp = rospy.Time.now()
    # goal.target_pose.pose.position.x = goalX
    #  #goal.target_pose.pose.position.y = goalY
    # goal.target_pose.pose.orientation = geometry_msgs.msg.Quaternion(*tf_conversions.transformations.quaternion_from_euler(0, 0, goalW))

    client.send_goal(goal_pose)
    wait = client.wait_for_result()
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
        return client.get_result()

def qrCallback(data):
    global qrMsg
    qrMsg = data.data
    rospy.loginfo('Read qr code with following instructions: ' + qrMsg)

def disinfection():
    global qrMsg
    global splitMsg
    splitMsg = qrMsg.split()
    print(splitMsg)
    if(splitMsg[0]=="2"):
        for i in range(int(splitMsg[2])):
            result = 0
            result = movebase_client(float(splitMsg[3+(i*2)]), float(splitMsg[4+(i*2)]), 0)
            time.sleep(1)
            if result:
                time.sleep(float(splitMsg[1]))
                rospy.loginfo('room reached ' + str(i+1))

 

def getPathLength(poses):
    # compute euclidean distance of all poses
    total_dist = 0
    for i in range(len(poses)):
        if i+1 >= len(poses):
            break
        point_1 = np.array((poses[i].pose.position.x, poses[i].pose.position.y))
        point_2 = np.array((poses[i+1].pose.position.x, poses[i+1].pose.position.y))
        total_dist +=  np.linalg.norm(point_1 - point_2)
    return total_dist


 

 # implementation of traveling Salesman Problem
def findShortestPath(graph, s):

    # store all vertex apart from source vertex
    vertices = []
    for i in range(len(graph)):
        if i != s:
            vertices.append(i)
        
    # store minimum weight Hamiltonian Cycle
    min_weight = maxsize
    min_path = None
    next_permutation = permutations(vertices)

    for i in next_permutation:

    # store current Path weight(cost)
        current_pathweight = 0

    # compute current path weight
        k = s
        for j in i:
            current_pathweight += graph[k][j]
            k = j
        # add edge back to the start state
        current_pathweight += graph[k][s]

        # update minimum
        if current_pathweight < min_weight:
            min_weight = current_pathweight
            min_path = i


    return min_path, min_weight




def main():

    rospy.init_node('navigation_control')

    locations = rospy.get_param("/locations")
    rooms = rospy.get_param("/rooms")
    print(rooms)
    # also include starting position
    # start_pos = geometry_msgs.p

    # print(locations)
    pub = rospy.Publisher('plan_info', String, queue_size=10)

    # get starting position
    start_x = rospy.get_param('/amcl/initial_pose_x')
    start_y = rospy.get_param('/amcl/initial_pose_y')
    start_a = rospy.get_param('/amcl/initial_pose_a')

    start_pose = PoseStamped()
    start_pose.header.frame_id = 'map'
    start_pose.pose.position.x = start_x
    start_pose.pose.position.y = start_y
    start_pose.pose.position.z = 0
    start_pose.pose.orientation  = geometry_msgs.msg.Quaternion(*tf_conversions.transformations.quaternion_from_euler(0, 0, start_a))
    # print(start_y, start_x, start_a)
    # print(start_pose)

    # list of pose stamped messages
    goals = [start_pose]
    for loc in locations:
        goal = PoseStamped()
        goal.header.frame_id = 'map'
        goal.pose.position.x = loc[0]
        goal.pose.position.y = loc[1]
        goal.pose.position.z = 0
        goal.pose.orientation  = geometry_msgs.msg.Quaternion(*tf_conversions.transformations.quaternion_from_euler(0, 0, loc[2]))
        goals.append(goal)


    # srv = '/move_base/NavfnROS/make_plan'
    srv = '/move_base/make_plan'

    # create Graph of goals and starting position
    # cost of edges are the euclidean distances of the paths computed by movebase

    goal_pairs = [(a, b) for a in range(len(goals)) for b in range(a+1, len(goals))]
    # print(goal_pairs)

    graph = np.zeros((len(goals), len(goals)))

    rospy.loginfo('Computing optimal order of visiting qr codes')
    for edge in goal_pairs:
        # get path through movebase service
        rospy.wait_for_service(srv)
        make_plan = rospy.ServiceProxy(srv, GetPlan)
        msg = GetPlanRequest()
        msg.start = goals[edge[0]]
        msg.goal = goals[edge[1]]
        msg.tolerance = 0.1
        print('making plan for edge')
        try:
            plan = make_plan(msg)
        except rospy.ServiceException as exc:
            print("Service did not process request: " + str(exc)) 
        # compute cost of edge
        path_len = getPathLength(plan.plan.poses)
        print('path ist long: ' + str(path_len))

        # store edge costs
        graph[edge[0], edge[1]] = path_len
        graph[edge[1], edge[0]] = path_len


    print(graph)
    shortest_path, path_length = findShortestPath(graph=graph, s=0)
    rospy.loginfo(f'Computed optimal order: {shortest_path}')
    print(shortest_path, path_length)


    ### START NAVIGATION


    #rospy.Subscriber("qrComm", String, qrCallback)

    #for i, goal in enumerate(goals):
    #    result = 0
    #    result = movebase_client(goal)
    #    rospy.sleep(1)
    #    if result:
    #        
    #        rospy.loginfo('qr code reached ' + str(i+1))
    #        disinfection()







 
 


    rate = rospy.Rate(1)

    

     

    # done, shutdown nodes



if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass

