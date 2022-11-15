#! /usr/bin/env python 

import rospy
import roslaunch
from std_msgs.msg import String

finished_instructions = False
### JUST A TEMPLATE SO FAR, IGNORE PLS

def callback(data):
    # topic gets called when instructions are fulfilled
    global finished_instructions
    finished_instructions = True


def main():


    rospy.init_node('navigation_control')

    # subscribe to qr code topic
    rospy.Subscriber("qr_done", String, callback)
    
    rate = rospy.Rate(1)

    # hard code qr code locations here
    qr_codes = []

    for qr_code in qr_codes:

        # navigate to qr code

        
        # call node that exectutes instructions

        global finished_instructions
        while not finished_instructions:
            rate.sleep()

    # done, shutdown nodes



if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass

