#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
import cv2
import time
import sys
import os
import numpy as np

bridge = CvBridge()

fn_haar = '/home/buddha/opencv/data/haarcascades/haarcascade_frontalface_default.xml'
fn_dir = '/home/buddha/catkin_ws/src/python/scripts/att_faces'
fn_name= sys.argv[1]
path = os.path.join(fn_dir, fn_name)

if not os.path.isdir(path):
	try:	
		os.mkdir(path)
		print("New Person Created")
	except OSError as e:
		if e.errno == 17:
			os.chmod(path, 0777);


	


(im_width, im_height)=(130,100)
face_cascade = cv2.CascadeClassifier(fn_haar)


def image_callback(msg):
	try:
		im = bridge.imgmsg_to_cv2(msg,"bgr8")
		
	
	except CvBridgeError, e:
		print(e)


	count = 1
	while count < 30:
	
		
		gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
		faces = face_cascade.detectMultiScale(gray,1.3, 5)
		for(x,y,w,h) in faces:
			cv2.rectangle(im,(x,y),(x+w,y+h),(0,255,0),2)
			face = gray[y:y+h, x:x+w]
			face_resize = cv2.resize(face,(im_width, im_height))
			cv2.imwrite('%s/%s.png' % (path,count),face_resize)
		count += 1
	
		cv2.imshow('Opencv', im)
		key = cv2.waitKey(5)
		if key == 27:
			break
	print("Updated!")

def main():
	rospy.init_node('image_create_train')

	image_topic = "/camera/color/image_raw"
	rospy.Subscriber(image_topic, Image, image_callback)

	try:
        	rospy.spin()
    	except KeyboardInterrupt:
        	print "Shutting down ROS Image feature detector module"
    	cv2.destroyAllWindows()


if __name__ == '__main__':
	main()
