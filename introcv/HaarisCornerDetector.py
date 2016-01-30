# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com

import cv2
import numpy as np

filename = 'data/chessboard.jpg'
img = cv2.imread(filename)
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

gray = np.float32(gray)
dst = cv2.cornerHarris(gray,2,3,0.04)

#result is dilated for marking the corners, not important
dst = cv2.dilate(dst,None)
print(0.01*dst.max())
print(dst>0.01*dst.max())
# Threshold for an optimal value, it may vary depending on the image.
img[dst>0.01*dst.max()]=[0,0,255]

cv2.imshow('dst',dst)
cv2.imshow('img',img)
if cv2.waitKey(0) & 0xff == 27:
    cv2.destroyAllWindows()
