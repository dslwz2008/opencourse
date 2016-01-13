# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com

import cv2
import numpy as np

img = cv2.imread('data/test.png',0)
f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)
magnitude = 20*np.log(np.abs(fshift))
magntShow = cv2.convertScaleAbs(magnitude)

print img.dtype
print magnitude.dtype
print magntShow.dtype

cv2.imshow('Input', img)
cv2.imshow('Magnitude', magntShow)

cv2.waitKey(0)
cv2.destroyAllWindows()
