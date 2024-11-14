# -*- coding: utf-8 -*-
"""
Created on Sun Apr 23 18:28:20 2023

@author: saids
"""
'''
#pip install pipwin 
#pipwin install pocketsphinx
from pocketsphinx import LiveSpeech

for phrase in LiveSpeech(): 
    if phrase =='stop':
        print('stop')
    print(phrase)
'''    
import speech_recognition as sr       # nedded pyaudio library 
r=sr.Recognizer()
'''while True:
    try:
    
        with sr.Microphone() as source:
            r.adjust_for_ambient_noise(source,duration=.2)
            audio=r.listen(source,10,2)
            text=r.recognize_google(audio)
            text=text.lower()
            #print(text)
            if 'go' in text:
                print("go")
            elif 'left' in text:
                print("left")
            elif 'stop' in text:
                print("stop")
                break
    except :
        r=sr.Recognizer()
        continue
'''
class Vocal_Command:
    
    def Get_Direction():
        '''
        It takes user's voice as input
        '''
        Direction='stop'                            #if the voice is not recognized well it will return stop
        r=sr.Recognizer()
        with sr.Microphone() as source:
            print("Listening...")
            r.adjust_for_ambient_noise(source)
            audio=r.listen(source)
    
        try:
            print("Recognizing...")
            Direction = r.recognize_google(audio, language="en-in")
            Direction=Direction.lower()
            print(f"Recognized Command: {Direction}")
        
        except Exception as e:
            print(e)
            print("I didn't recognize what you said please repeat")
            r=sr.Recognizer()
            
        
        return Direction


  
    