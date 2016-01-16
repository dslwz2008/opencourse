# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com

import cv2
import numpy as np
from matplotlib import pyplot as plt

minThreshold = 100
maxThreshold = 200

img = cv2.imread('data/lena512gray.jpg',cv2.IMREAD_GRAYSCALE)

while(1):
    edges = cv2.Canny(img,minThreshold,maxThreshold)
    cv2.imshow('Edge Detection', edges)

    k = cv2.waitKey(1) & 0xFF
    if k == ord('m'):
        maxThreshold += 5
    elif k==ord('j'):
        maxThreshold -= 5
    elif k==ord('n'):
        minThreshold+=5
    elif k==ord('h'):
        minThreshold-=5
    elif k == 27:
        break
    print(minThreshold,maxThreshold)

cv2.destroyAllWindows()
