# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com

import cv2
import numpy as np
from matplotlib import pyplot as plt
# import scipy.misc
#
# img = scipy.misc.lena()
# cv2.imwrite("lena.jpg",img)

img = cv2.imread('data/lena512gray.jpg',cv2.IMREAD_GRAYSCALE)

# convert to float to display gray image
# img = img/255.0

# laplacian = cv2.Laplacian(img,cv2.CV_64F)
# laplacian3 = cv2.Laplacian(img,cv2.CV_64F,ksize=3)
# laplacian5 = cv2.Laplacian(img,cv2.CV_64F,ksize=5)

# cv2.imshow('lap',laplacian)
# cv2.imshow('lap3',laplacian3)
# cv2.imshow('lap5',laplacian5)

# sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)
# sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=5)
#
# cv2.imshow('sobelx',sobelx)
# cv2.imshow('sobely',sobely)

#
# plt.subplot(2,2,1),plt.imshow(img/255.0,cmap = 'gray')
# plt.title('Original'), plt.xticks([]), plt.yticks([])
# plt.subplot(2,2,2),plt.imshow(laplacian/255.0,cmap = 'gray')
# plt.title('Laplacian'), plt.xticks([]), plt.yticks([])
# plt.subplot(2,2,3),plt.imshow(sobelx/255.0,cmap = 'gray')
# plt.title('Sobel X'), plt.xticks([]), plt.yticks([])
# plt.subplot(2,2,4),plt.imshow(sobely/255.0,cmap = 'gray')
# plt.title('Sobel Y'), plt.xticks([]), plt.yticks([])
#
# plt.show()

img = cv2.imread('data/bwbox.png',cv2.IMREAD_GRAYSCALE)

# Output dtype = cv2.CV_8U
sobelx8u = cv2.Sobel(img,cv2.CV_8U,1,0,ksize=5)

# Output dtype = cv2.CV_64F. Then take its absolute and convert to cv2.CV_8U
sobelx64f = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)
abs_sobel64f = np.absolute(sobelx64f)
sobel_8u = np.uint8(abs_sobel64f)

cv2.imshow('8u',sobelx8u)
cv2.imshow('64f',sobel_8u)

cv2.waitKey(0)
cv2.destroyAllWindows()
