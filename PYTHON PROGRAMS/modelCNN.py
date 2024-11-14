# -*- coding: utf-8 -*-
"""
Created on Sun Feb  5 18:53:16 2023

@author: saids
"""

import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import keras
import tensorflow as tf
from keras.models import Sequential
from keras.layers import Dense
from keras.optimizers import SGD
from tensorflow.keras import regularizers


df = pd.read_csv("saed.csv")
dataset=df.iloc[:,3:13]
direction=df.iloc[:,2]

Q1=dataset.quantile(0.25)                                   #Q1 at 25% of the features values
Q3=dataset.quantile(0.75)
IQR=Q3-Q1
Lower_Limit=Q1-1.5*IQR
Upper_Limit=Q3+1.5*IQR
#dataset after replacing every outlier with 'nan'
No_outliers_dataset=dataset[(dataset>Lower_Limit)&(dataset<Upper_Limit)]  #dataset without outliers
#No_outliers_dataset.drop('blinkStrength',inplace=True,axis=1)             #dataset after removing blinkstrenth coloumn

# Feature Scaling
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
No_outliers_dataset = sc.fit_transform(No_outliers_dataset)

'''
#normalization of dataset
from sklearn.preprocessing import MinMaxScaler
sc = MinMaxScaler()
No_outliers_dataset = sc.fit_transform(No_outliers_dataset)
'''

#imputation to impute outliers
from sklearn.preprocessing import Imputer
mean_imputer = Imputer(missing_values='NaN', strategy='median', axis=0)
No_outliers_dataset[:] = mean_imputer.fit_transform(No_outliers_dataset)  #impute the missing values ,[:] is used so it returns dataframe not numpy array



#splitting the data into train data and test data
from sklearn.model_selection import train_test_split
X_train, X_test, Y_train, Y_test = train_test_split(No_outliers_dataset, direction, test_size = 0.2, random_state = 0)


#RESHAPING THE DATA
print(X_train.shape)
print(X_train[0].shape)
print(X_train[0])

x_train=X_train.reshape(2866,10,1)
x_test=X_test.reshape(717,10,1)


print(x_train.shape)
print(x_train[0].shape)
print(x_train[0])

#%%

model=Sequential([
              
tf.keras.layers.Conv1D(filters=5,kernel_size=3,strides=1,activation='relu',input_shape=(10,1)),#1
tf.keras.layers.Conv1D(filters=2,kernel_size=3,strides=1,activation='relu'),#1
tf.keras.layers.Flatten(),
#tf.keras.layers.Dense(254,activation='relu', kernel_initializer = 'uniform'),
tf.keras.layers.Dense(127,activation='relu', kernel_initializer = 'uniform'),
tf.keras.layers.Dense(127,activation='relu', kernel_initializer = 'uniform'),
tf.keras.layers.Dense(64,activation='relu', kernel_initializer = 'uniform'),
tf.keras.layers.Dense(64,activation='relu', kernel_initializer = 'uniform'),
tf.keras.layers.Dense(8,activation='relu', kernel_initializer = 'uniform'),
tf.keras.layers.Dense(4,activation='softmax')

])

#print(model.summary())
opt = SGD(lr= 0.00001, momentum = 0.99)
model .compile(optimizer ='adam'  , loss = 'sparse_categorical_crossentropy', metrics = ['accuracy'])


model.fit(x_train, Y_train, validation_split = 0.1, verbose = 2,epochs = 100)

test_loss,test_acc = model.evaluate(x_test,Y_test, verbose =1)
y_pred = model.predict(x_test)

#%%
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
acc1 = confusion_matrix(Y_test, np.argmax(y_pred, axis=1))
acc = accuracy_score(Y_test, np.argmax(y_pred, axis=1))

#%%
#y_pred[0].argmax()

print(acc1)
print(acc)
print(test_acc)


'''
tf.keras.layers.BatchNormalization(),
tf.keras.layers.LeakyReLU(),
tf.keras.layers.MaxPooling1D(pool_size=2,strides=2),
tf.keras.layers.Conv1D(filters=1,kernel_size=3,strides=1,activation='relu'),
tf.keras.layers.LeakyReLU(),
tf.keras.layers.MaxPooling1D(pool_size=2,strides=2),
tf.keras.layers.Dropout(.5),
tf.keras.layers.Conv1D(filters=1,kernel_size=3,strides=1,activation='relu'),
tf.keras.layers.LeakyReLU(),
tf.keras.layers.AveragePooling1D(pool_size=2,strides=2),
tf.keras.layers.Conv1D(filters=5,kernel_size=3,strides=1,activation='relu'),
tf.keras.layers.LeakyReLU(),
tf.keras.layers.GlobalAveragePooling1D(),
'''






