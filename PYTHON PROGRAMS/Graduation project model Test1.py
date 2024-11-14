# -*- coding: utf-8 -*-
"""
Created on Sun Nov 20 10:06:40 2022

@author: Said Salama
"""

# Logistic Regression

# Importing the libraries
import numpy as np
#import matplotlib.pyplot as plt
import pandas as pd
#import seaborn as sns

# Importing the dataset

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
X_train, X_test, y_train, y_test = train_test_split(No_outliers_dataset, direction, test_size = 0.25, random_state = 0)

'''
# Fitting Logistic Regression to the Training set
from sklearn.linear_model import LogisticRegression
classifier = LogisticRegression(random_state = 0)
classifier.fit(X_train, y_train)
'''
'''
# Fitting KNN to the Training set
from sklearn.neighbors import KNeighborsClassifier 
classifier = KNeighborsClassifier(n_neighbors=5, metric='euclidean')
classifier.fit(X_train, y_train)
'''

# Fitting svm  to the Training set
from sklearn.svm import SVC
classifier = SVC()
classifier.fit(X_train, y_train)

# Predicting the Test set results
y_pred = classifier.predict(X_test)

# Making the Confusion Matrix
from sklearn.metrics import confusion_matrix
cm = confusion_matrix(y_test, y_pred)

#accuracy calculation
from sklearn.metrics import accuracy_score
accuracy=accuracy_score(y_test, y_pred)










