# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com
# Load two images

import numpy as np
import cv2

img1 = cv2.imread('data/messi5.jpg')
img2 = cv2.imread('data/opencv_logo.png')
img3 = cv2.imread('data/2.png')
# print(img3.dtype)
img3Small = cv2.resize(img3, (100,100))
# print(img3Small.shape)
# cv2.imshow('resize', img2)

# # I want to put logo on top-left corner, So I create a ROI
# rows,cols,channels = img2.shape
# print(rows,cols,channels)
# roi = img1[0:rows, 0:cols ]
#
# # Now create a mask of logo and create its inverse mask also
# img2gray = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
# cv2.imshow('gray', img2gray)
#
# # 黑底白字
# ret, mask = cv2.threshold(img2gray, 10, 255, cv2.THRESH_BINARY)
# cv2.imshow('mask',mask)
#
# # 白底黑字
# mask_inv = cv2.bitwise_not(mask)
# cv2.imshow('mask_inv',mask_inv)
#
# # Now black-out the area of logo in ROI
# img1_bg = cv2.bitwise_or(roi,roi,mask = mask_inv)
# # img1_bg = cv2.bitwise_and(roi,roi,mask = mask_inv)
# cv2.imshow('img1_bg',img1_bg)
#
# # Take only region of logo from logo image.
# img2_fg = cv2.bitwise_or(img2,img2,mask = mask)
# cv2.imshow('img2_fg',img2_fg)
#
# # Put logo in ROI and modify the main image
# dst = cv2.add(img1_bg,img2_fg)
# cv2.imshow('dst',dst)
#
# img1[0:rows, 0:cols ] = dst
# cv2.imshow('img1',img1)

def overlayPng(img, png, posx, posy):
    rows,cols,channels = png.shape
    print(rows,cols,channels)
    roi = img[posx:(posx+rows), posy:(posy+cols)]
    png2gray = cv2.cvtColor(png, cv2.COLOR_BGR2GRAY)

    # 黑底
    ret, mask = cv2.threshold(png2gray, 10, 255, cv2.THRESH_BINARY)
    # 白底
    mask_inv = cv2.bitwise_not(mask)
    # 挖空ROI中的overlay中的非透明区域
    roiBg = cv2.bitwise_or(roi, roi, mask=mask_inv)
    # and和or的操作是一样的
    # roiBg = cv2.bitwise_and(roi,roi,mask = mask_inv)
    # png图片取出非透明区域
    pngFg = cv2.bitwise_or(png, png, mask=mask)

    # Put logo in ROI and modify the main image
    dst = cv2.add(roiBg, pngFg)
    img[posx:(posx+rows), posy:(posy+cols)] = dst

overlayPng(img1, img3Small, 100, 100)
cv2.imshow('dest', img1)
cv2.waitKey(0)
cv2.destroyAllWindows()