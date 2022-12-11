#! /usr/bin/env python 

import rospy
import roslaunch
from std_msgs.msg import String
import nav_msgs
from nav_msgs.srv import GetPlan


finished_instructions = False
### JUST A TEMPLATE SO FAR, IGNORE PLS

def callback(data):
    # topic gets called when instructions are fulfilled
    global finished_instructions
    finished_instructions = True


def main():


    rospy.init_node('navigation_control')


    locations = rospy.get_param("/locations")

    print(locations[0])

    ## Plan optimal ord er of visting locations
    goal = locations[0]
    # rospy.wait_for_service('make_plan')
    make_plan = rospy.ServiceProxy('make_plan',GetPlan)
    try:
        plan = make_plan(goal[0], goal[1])
    except rospy.ServiceException as exc:
        print("Service did not process request: " + str(exc))    

    print(plan)


    rate = rospy.Rate(1)

    

     

    # done, shutdown nodes



if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass

