# -*- coding: utf-8 -*-
"""
Created on Fri Dec  2 08:47:27 2022

@author: Amany_Ibrahim
"""


import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import sys
import json
import time
from telnetlib import Telnet
import serial
import keras

#from keras.utils import to_categorical

def Merge (dict1, dict2):  
    res = {**dict1,**dict2}
    return res

# Feature Scaling
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
#imputation to impute outliers
from sklearn.preprocessing import Imputer
mean_imputer = Imputer(missing_values='NaN', strategy='median', axis=0)

from joblib import load
model = load(r"D:\BCI\BCI\Data\model_ANN.joblib") 
#reconstructed_model = keras.models.load_model(r"D:\BCI\BCI\Data\model_CNN.h5")
#%%
def Send(y_predict):
    #direction =0
    Stop =0
    Forward =1
    Right =2
    Left =3
    Bring = 4
    
    port_name = "COM6"  # the name / address we found for our device
    
    ser = serial.Serial(
        port=port_name,
        baudrate=9600,          #115200,
        bytesize=serial.EIGHTBITS,  # set this to the amount of data you want to send
        )
    
    # the information we want to send: 8 bits = 1 byte
    if y_predict == Stop:
         byte_to_send = str.encode('2')  # send a "2"
         return ser.write(byte_to_send)
         #time.sleep(0.5)
    if y_predict == Forward:
        byte_to_send = str.encode('1')  # send a "1"
        return ser.write(byte_to_send)
        #time.sleep(0.5)
    if y_predict == Right:
        byte_to_send = str.encode('3')  # send a "3"
        return ser.write(byte_to_send)
        #time.sleep(0.5)
    if y_predict == Left:
        byte_to_send = str.encode('4')  # send a "4"
        return ser.write(byte_to_send)
        #time.sleep(0.5)
    if y_predict == Bring:
        byte_to_send = str.encode('5')  # send a "5"
        return ser.write(byte_to_send)
        #time.sleep(0.5)
    # After measurements are done, close the connection 
    #ser.close();
#%%
def Differ(St,For,Rt,Lt):
        out = 0
        Stop =0
        Forward =1
        Right =2
        Left =3
        
        if (St>For)&(St>Rt)&(St>Lt):
             out = Stop
             return out
        elif (For>St)&(For>Rt)&(For>Lt):
             out = Forward
             return out
        elif (Rt>For)&(Rt>St)&(Rt>Lt):
             out = Right
             return out
        elif (Lt>For)&(Lt>Rt)&(Lt>St):
             out = Left
             return out 
        else:
             #waiting for the next signal
             pass


#%%
Stop =0
Forward =1
Right =2
Left =3
Bring =4
direction_values = [ ]


attention_values = np.array([])
meditation_values = np.array([])
delta_values = np.array([])
theta_values = np.array([])
lowAlpha_values = np.array([])
highAlpha_values = np.array([])
lowBeta_values = np.array([])
highBeta_values = np.array([])
lowGamma_values = np.array([])
highGamma_values = np.array([])
time_array = np.array([])

tn=Telnet('localhost',13854);

start=time.process_time();

i=0;
tn.write(str.encode('{"enableRawOutput": true, "format": "Json"}'));


outfile="null";
if len(sys.argv)>1:
	outfile=sys.argv[len(sys.argv)-1];
	outfptr=open(outfile,'w');

eSenseDict={'attention':0, 'meditation':0};
waveDict={'lowGamma':0, 'highGamma':0, 'highAlpha':0, 'delta':0, 'highBeta':0, 'lowAlpha':0, 'lowBeta':0, 'theta':0};
signalLevel=0;
count = 0
i = 9
c =0
s =0
f =0
r =0
l =0

while time.process_time() - start < 15:
	line=tn.read_until(b'\r');
	if len(line) > 20:	
		timediff=time.process_time()-start;
		dict=json.loads((line));
		if "poorSignalLevel" in dict:
			signalLevel=dict['poorSignalLevel'];
		if "blinkStrength" in dict:
			blinkStrength=dict['blinkStrength'];
		if "eegPower" in dict:
			waveDict=dict['eegPower'];
			eSenseDict=dict['eSense'];
		outputstr=str(timediff)+ ", " + str(eSenseDict['attention']) + ", " + str(eSenseDict['meditation']) + ", "+str(waveDict['lowGamma'])+", " + str(waveDict['highGamma'])+", "+ str(waveDict['highAlpha'])+", "+str(waveDict['delta'])+", "+ str(waveDict['highBeta'])+", "+str(waveDict['lowAlpha'])+", "+str(waveDict['lowBeta'])+ ", "+str(waveDict['theta']);
		time_array = np.append(time_array, [timediff]);
		lowGamma_values = np.append(lowGamma_values, [waveDict['lowGamma']]);
		highGamma_values = np.append(highGamma_values, [waveDict['highGamma']]);
		highAlpha_values = np.append(highAlpha_values, [waveDict['highAlpha']]);
		delta_values = np.append(delta_values, [waveDict['delta']]);
		lowBeta_values = np.append(lowBeta_values, [waveDict['lowBeta']]);
		highBeta_values = np.append(highBeta_values, [waveDict['highBeta']]);
		theta_values = np.append(theta_values, [waveDict['theta']]);
		lowAlpha_values = np.append(lowAlpha_values, [waveDict['lowAlpha']]);
		attention_values = np.append(attention_values, [eSenseDict['attention']]);
		meditation_values = np.append(meditation_values, [eSenseDict['meditation']]);
		count = count+1
		if count == i :
             #Signal = Merge(eSenseDict,waveDict)
    		 Signal = [attention_values[i-9:i],delta_values[i-9:i],highAlpha_values[i-9:i],highBeta_values[i-9:i],highGamma_values[i-9:i],lowAlpha_values[i-9:i],lowBeta_values[i-9:i],lowGamma_values[i-9:i],meditation_values[i-9:i]]
    		 Signal= np.array(Signal).T
    		 Q1=np.quantile(Signal,0.25)                                   #Q1 at 25% of the features values
    		 Q2=np.quantile(Signal,0.75)
    		 IQR=Q2-Q1
    		 Lower_Limit= Q1-1.5*IQR
    		 Upper_Limit= Q2+1.5*IQR
    		 No_outliers_datarow=Signal[(Signal>Lower_Limit)&(Signal<Upper_Limit)]
    		 data_row  = pd.DataFrame(Signal) #, columns=['attention', 'meditation', 'delta', 'theta', 'lowAlpha', 'highAlpha', 'lowBeta', 'highBeta',
                           #  'lowGamma', 'highGamma'])                  
    		 data_row = sc.fit_transform(data_row)
    		 No_outliers_datarow = sc.fit_transform(data_row)
    		 mean_imputer = Imputer(missing_values='NaN', strategy='median', axis=0)
    		 No_outliers_datarow[:] = mean_imputer.fit_transform(data_row) 
    		 out_predict=model.predict(No_outliers_datarow)
    		 for data in out_predict[:]:
                  print('data is %s' %data)
                  out_class = Differ(out_predict[c][0],out_predict[c][1],out_predict[c][2],out_predict[c][3])
                  c = c+1
                  if out_class == Stop :
                  	 s = s+1
                  	 print('s is %s' %s)
                  elif out_class == Forward:
                  	 f = f+1
                  	 print('f is %s' %f)
                  elif out_class == Right :
                  	 r = r+1
                  	 print('r is %s' %r)
                  elif out_class == Left:
                  	 l = l+1
                  	 print('l is %s' %l)
                  out_data = Differ(s,f,r,l)
                  
    		 #out_predict=regressor.predict(data_row)     
    		 print( out_predict)
    		 print( out_data)
    		 print(str(timediff))
    		 i=i+9
    		 c = 0
    		 s =0
    		 f =0
    		 r =0
    		 l =0
    		 if out_data == Stop :
    		     Send(out_data)
    		     print('Stop')
    		 elif out_data == Forward:
    			 Send(out_data)
    			 print('Forward')
    		 elif out_data == Right :
    			 Send(out_data)
    			 print('Right')
    		 elif out_data == Left:
    			 Send(out_data)
    			 print('Left')
    		 elif out_data == Bring:
    			 Send(out_data)
    			 print('Bring')
             
#%%    

tn.close();

