import roslib
import cv2
import rospy
import sys
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError   

from __future__ import print_function

def callback(data):

    bridge = CvBridge()
    
    cv_image = bridge.imgmsg_to_cv2(data, "bgr8")

    cv2.imshow("Color Image", cv_image)
    cv2.waitKey(0)

def listener():
    rospy.init_node('ColorImage', anonymous=True)

    rospy.Subscriber("/camera/color/image_raw",Image,callback)

    rospy.spin()

if __name__ == '__main__':
    listener()
