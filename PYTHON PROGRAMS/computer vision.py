# -*- coding: utf-8 -*-
"""
Created on Sun Apr  2 14:30:03 2023

@author: saids
"""

import cv2
import dlib #to download this module we need visual studio and c make and "shape_predictor_68_face_landmarks.dat"
#from math import hypot
#import numpy as np
from Eye_Control import Eye_tracker
import time

################################################################################################
camera=cv2.VideoCapture(0)                                #0 means acces the laptop camera if we want to acces a video file just write the name of file'file.mp4'
detector=dlib.get_frontal_face_detector()
predictor=dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
font=cv2.FONT_HERSHEY_SIMPLEX

while True:
    ret,frame=camera.read()                                #read frame image one by one
    gray=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)            #make the gray frame
    faces=detector(gray)
    for face in faces :
        
        blink=Eye_tracker.detect_blink(gray,face,frame,predictor)
        #Eye_tracker.detect_face(face,frame)
        left_gaze_ratio=Eye_tracker.detect_gaze([42,43,44,45,46,47],gray,face,predictor,frame)           #https://b2633864.smushcdn.com/2633864/wp-content/uploads/2017/04/facial_landmarks_68markup.jpg?size=630x508&lossy=1&strip=1&webp=1
        right_gaze_ratio=Eye_tracker.detect_gaze([36,37,38,39,40,41],gray,face,predictor,frame)         # you can find the 68 facial landmark coordinates from this address
        gaze_ratio=(left_gaze_ratio+right_gaze_ratio)/2
        print(gaze_ratio)
       # eye=frame[min_y:max_y,min_x:max_x]
        #gray_eye=cv2.cvtColor(eye,cv2.COLOR_BGR2GRAY)       #make the eye in gray
        #_,threshold_eye=cv2.threshold(gray_eye,100,255,cv2.THRESH_BINARY)#to detect the blcak part of eye
     
    
    #threshold_eye=cv2.resize(threshold_eye,None,fx=3,fy=3)
    #cv2.imshow('THRESHOLD',threshold_eye)      
    #cv2.imshow('eye',eye)               #display the video 
        if blink == True:
            cv2.putText(frame,"BLINKING",(50,150),font,3,(255,0,0))
            y="BLINKING"
        else:
            if gaze_ratio>1.1:
                 cv2.putText(frame,"RIGHT",(50,150),font,2,(0,0,255))
                 y="RIGHT"
            elif gaze_ratio<0.50:
                cv2.putText(frame,"LEFT",(50,150),font,2,(0,0,255))
                y="lefT"
            elif .5<gaze_ratio<1.1:
                cv2.putText(frame,"CENTER",(50,150),font,2,(0,0,255))
                y="center"
        
   
        
    
    cv2.imshow('frame',frame)           #display the video
    time.sleep(.25)
    
    
    key=cv2.waitKey(1)                   #wait for a key press every 1 ms
    if key ==ord("z"):
        break

        


camera.release()                          #release video capture
cv2.destroyAllWindows()    
    


