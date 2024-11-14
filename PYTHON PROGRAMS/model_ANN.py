# -*- coding: utf-8 -*-
"""
Created on Mon Jan 30 02:54:43 2023

@author: Amany_Ibrahim
"""

import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
import keras
import tensorflow as tf
from keras.models import Sequential
from keras.layers import Dense
from keras.optimizers import SGD
from tensorflow.keras import regularizers


df = pd.read_csv("saedrandom.csv")
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
x_train, x_test, y_train, y_test = train_test_split(No_outliers_dataset, direction, test_size = 0.1, random_state = 0)
'''
from sklearn.decomposition import PCA

pca = PCA(n_components=4)

x_training = pca.fit_transform(x_train)
'''

#%%

model=tf.keras.Sequential([tf.keras.layers.Dense(254,activation='relu',input_dim=10, kernel_initializer = 'uniform'),
                          tf.keras.layers.Dense(254,activation='relu', kernel_initializer = 'uniform'),
                          tf.keras.layers.Dense(64,activation='relu', kernel_initializer = 'uniform'),
                          tf.keras.layers.Dense(8,activation='relu', kernel_initializer = 'uniform'),
                          tf.keras.layers.Dense(4,activation='softmax', kernel_initializer = 'uniform')   ])
                          
'''
model  = Sequential()

# Adding the input layer and the first hidden layer
model .add(Dense(units = 254,kernel_initializer = 'uniform', input_dim=10, activation='relu')) 
#model .add(Dense(12,kernel_initializer = 'uniform', input_dim=9, activation='relu'))
# Adding the second hidden layer
model .add(Dense(units = 254,kernel_initializer = 'uniform', activation='relu') )
#model .add(Dense(12,kernel_initializer = 'uniform', activation='relu'))
# Adding the output layer
model .add(Dense(units = 8,kernel_initializer = 'uniform', activation='relu'))
#model .add(Dense(1, activation = 'sigmoid'))
model .add(Dense(4, activation = 'softmax'))

'''

# Compiling the ANN
#model .compile(optimizer = 'adam', loss = 'binary_cross entropy', metrics = ['accuracy'])
opt = SGD(lr= 0.00001, momentum = 0.99)
model .compile(optimizer = opt , loss = 'sparse_categorical_crossentropy', metrics = ['accuracy'])

# adam
# 'sparse_categorical_crossentropy'
#binary_crossentropy
#'mean_squared_error'
model.fit(x_train, y_train, validation_split = 0.1, verbose = 2,epochs = 2000, batch_size=2)

#%%
y_pred = model.predict(x_test)
#print(y_pred)
#%%y_pred = (y_pred> 0.5)

#%%
#model.save(r"D:\BCI\BCI\model_ANN.h5")
test_loss,test_acc = model.evaluate(x_test,y_test, verbose =1)

#%%
from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix
acc1 = confusion_matrix(y_test, np.argmax(y_pred, axis=1))
acc = accuracy_score(y_test, np.argmax(y_pred, axis=1))

#%%
#y_pred[0].argmax()

print(acc1)
print(acc)
print(test_acc)
