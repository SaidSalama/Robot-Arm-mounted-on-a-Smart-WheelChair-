# -*- coding: utf-8 -*-
"""
Created on Sun Apr 23 17:56:42 2023

@author: saids
"""

import cv2
#import dlib
from math import hypot
import numpy as np

class Eye_tracker:
    
    def mid_point(p1,p2):
        return int((p1.x+p2.x)/2),int((p1.y+p2.y)/2)
    def get_blinking_ratio(eye_points,facial_landmarks):    # a function used to get the distance between an upper landmark and lower one to decide whether there is a blink or not 
        left_point=(facial_landmarks.part(eye_points[0]).x,facial_landmarks.part(eye_points[0]).y)
        right_point=(facial_landmarks.part(eye_points[3]).x,facial_landmarks.part(eye_points[3]).y)
        center_top=Eye_tracker.mid_point(facial_landmarks.part(eye_points[1]),facial_landmarks.part(eye_points[2]))
        center_bottom=Eye_tracker.mid_point(facial_landmarks.part(eye_points[5]),facial_landmarks.part(eye_points[4]))
        
       # horline=cv2.line(frame,left_point,right_point,(0,255,0),2)
        #verline=cv2.line(frame,center_top,center_bottom,(0,255,0),2)
        
        horline_lenght=hypot((left_point[0]-right_point[0]),(left_point[1]-right_point[1]))
        verline_lenth=hypot((center_top[0]-center_bottom[0]),(center_top[1]-center_bottom[1]))
    
        ratio=(horline_lenght/verline_lenth)
        return ratio
    
    def detect_blink(gray,face,frame,predictor):  # a function used to detect if the useb blinks or not 
        #predictor=dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
        #font=cv2.FONT_HERSHEY_SIMPLEX
        landmarks=predictor(gray,face)
        right_eye_ratio=Eye_tracker.get_blinking_ratio([36,37,38,39,40,41],landmarks)       # the numbers given to the function are the landmarks of eye according to the photo
        left_eye_ratio=Eye_tracker.get_blinking_ratio([42,43,44,45,46,47],landmarks)
        blinking_ratio=(right_eye_ratio+left_eye_ratio)/2
        
        if blinking_ratio>5:
            #cv2.putText(frame,"BLINKING",(50,150),font,3,(255,0,0))
            return True
            
    def detect_gaze(eye_points,gray,face,predictor,frame):                 # this function detect the gaze and dtermines how many black pixels are in right side and left side and returns the ratio between them  
        #predictor=dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")
        landmark=predictor(gray,face)
        eye_region=np.array([(landmark.part(eye_points[0]).x,landmark.part(eye_points[0]).y),
                                 (landmark.part(eye_points[1]).x,landmark.part(eye_points[1]).y),
                                 (landmark.part(eye_points[2]).x,landmark.part(eye_points[2]).y),
                                 (landmark.part(eye_points[3]).x,landmark.part(eye_points[3]).y),
                                 (landmark.part(eye_points[4]).x,landmark.part(eye_points[4]).y),
                                 (landmark.part(eye_points[5]).x,landmark.part(eye_points[5]).y)])
        #cv2.polylines(frame,[left_eye_region],True,(0,0,255),2)
        max_x=np.max(eye_region[:,0])                      #get the max x position of the eye
        min_x=np.min(eye_region[:,0])                  #get the min x position of the eye
        max_y=np.max(eye_region[:,1])                  #get the max y position of the eye
        min_y=np.min(eye_region[:,1])
        
        height,width=gray.shape
        mask=np.zeros((height,width),np.uint8)                       # a mask is a black backgound on which we analyze the eye motion
        cv2.polylines(mask,[eye_region],True,255,2)    #draw the polygone of the eye on the mask
        cv2.fillPoly(mask,[eye_region],255)
        eye_on_mask=np.array([])
        eye_on_mask=cv2.bitwise_and(gray,gray,mask=mask)
        eye=eye_on_mask[min_y:max_y,min_x:max_x]
        _,threshold_eye=cv2.threshold(eye,50,255,cv2.THRESH_BINARY)   
        threshold_eye=cv2.resize(threshold_eye,None,fx=5,fy=5)
       
        height,width=threshold_eye.shape
        left_side_threshold=threshold_eye[0:height,0:int(width/2)]          #int to avoid float numbers
        left_side_white=cv2.countNonZero(left_side_threshold)               #count how many non black pixels are there where 0 is for black
        right_side_threshold=threshold_eye[0:height,int(width/2):width]
        right_side_white=cv2.countNonZero(right_side_threshold) 
        
        if left_side_white==0:                  #if there is no non black pixels it means if all the left side is black 
            gaze_ratio=.5                       #the user is looking left
        else:
            gaze_ratio=right_side_white/left_side_white
        
        
        #cv2.imshow('left',left_side_threshold)
        #cv2.imshow('right',right_side_threshold)    
        #cv2.imshow('left_eye_on_mask',threshold_eye)
        return gaze_ratio
    
    def detect_face(face,frame):
            x,y=face.left(),face.top()
            x1,y1=face.right(),face.bottom()
            cv2.rectangle(frame,(x,y),(x1,y1),(0,255,0),2)   # we got (x,y)the top left point and (x1,y1) the right bottom point then draw a rectangle through these 2 points

            
        
'''
def mid_point(p1,p2):
    return int((p1.x+p2.x)/2),int((p1.y+p2.y)/2)


def get_blinking_ratio(eye_points,facial_landmarks):
    left_point=(facial_landmarks.part(eye_points[0]).x,facial_landmarks.part(eye_points[0]).y)
    right_point=(facial_landmarks.part(eye_points[3]).x,facial_landmarks.part(eye_points[3]).y)
    center_top=mid_point(facial_landmarks.part(eye_points[1]),facial_landmarks.part(eye_points[2]))
    center_bottom=mid_point(facial_landmarks.part(eye_points[5]),facial_landmarks.part(eye_points[4]))
    
   # horline=cv2.line(frame,left_point,right_point,(0,255,0),2)
    #verline=cv2.line(frame,center_top,center_bottom,(0,255,0),2)
    
    horline_lenght=hypot((left_point[0]-right_point[0]),(left_point[1]-right_point[1]))
    verline_lenth=hypot((center_top[0]-center_bottom[0]),(center_top[1]-center_bottom[1]))

    ratio=(horline_lenght/verline_lenth)
    return ratio

def detect_blink(gray,face,frame):
        landmarks=predictor(gray,face)
        right_eye_ratio=get_blinking_ratio([36,37,38,39,40,41],landmarks)       # the numbers given to the function are the landmarks of eye according to the photo
        left_eye_ratio=get_blinking_ratio([42,43,44,45,46,47],landmarks)
        blinking_ratio=(right_eye_ratio+left_eye_ratio)/2
        
        if blinking_ratio>5.3:
            cv2.putText(frame,"BLINKING",(50,150),font,3,(255,0,0))

def detect_gaze(eye_points,gray,face):                 # this function draws a polygone around the eye
    landmark=predictor(gray,face)
    eye_region=np.array([(landmark.part(eye_points[0]).x,landmark.part(eye_points[0]).y),
                             (landmark.part(eye_points[1]).x,landmark.part(eye_points[1]).y),
                             (landmark.part(eye_points[2]).x,landmark.part(eye_points[2]).y),
                             (landmark.part(eye_points[3]).x,landmark.part(eye_points[3]).y),
                             (landmark.part(eye_points[4]).x,landmark.part(eye_points[4]).y),
                             (landmark.part(eye_points[5]).x,landmark.part(eye_points[5]).y)])
   # cv2.polylines(frame,[left_eye_region],True,(0,0,255),2)
    max_x=np.max(eye_region[:,0])                      #get the max x position of the eye
    min_x=np.min(eye_region[:,0])                  #get the min x position of the eye
    max_y=np.max(eye_region[:,1])                  #get the max y position of the eye
    min_y=np.min(eye_region[:,1])
    
    height,width=gray.shape
    mask=np.zeros((height,width),np.uint8)                       # a mask is a black backgound on which we analyze the eye motion
    cv2.polylines(mask,[eye_region],True,255,2)    #draw the polygone of the eye on the mask
    cv2.fillPoly(mask,[eye_region],255)
    eye_on_mask=np.array([])
    eye_on_mask=cv2.bitwise_and(gray,gray,mask=mask)
    eye=eye_on_mask[min_y:max_y,min_x:max_x]
    _,threshold_eye=cv2.threshold(eye,50,255,cv2.THRESH_BINARY)   
    threshold_eye=cv2.resize(threshold_eye,None,fx=5,fy=5)
   
    height,width=threshold_eye.shape
    left_side_threshold=threshold_eye[0:height,0:int(width/2)]          #int to avoid float numbers
    left_side_white=cv2.countNonZero(left_side_threshold)               #count how many non black pixels are there where 0 is for black
    right_side_threshold=threshold_eye[0:height,int(width/2):width]
    right_side_white=cv2.countNonZero(right_side_threshold) 
    
    if left_side_white==0:                  #if there is no non black pixels it means if all the left side is black 
        gaze_ratio=.5                       #the user is looking left
    else:
        gaze_ratio=right_side_white/left_side_white
    
    
    #cv2.imshow('left',left_side_threshold)
    #cv2.imshow('right',right_side_threshold)    
    #cv2.imshow('left_eye_on_mask',threshold_eye)
    return gaze_ratio

def detect_face(face):
            x,y=face.left(),face.top()
            x1,y1=face.right(),face.bottom()
            cv2.rectangle(frame,(x,y),(x1,y1),(0,255,0),2)   # we got (x,y)the top left point and (x1,y1) the right bottom point then draw a rectangle through these 2 points
'''    

