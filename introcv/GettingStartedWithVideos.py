# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com

import numpy as np
import cv2

# CODEC = cv.CV_FOURCC('D','I','V','3') # MPEG 4.3
# CODEC = cv.CV_FOURCC('M','P','4','2') # MPEG 4.2
# CODEC = cv.CV_FOURCC('M','J','P','G') # Motion Jpeg
# CODEC = cv.CV_FOURCC('U','2','6','3') # H263
# CODEC = cv.CV_FOURCC('I','2','6','3') # H263I
# CODEC = cv.CV_FOURCC('F','L','V','1') # FLV
CODEC = cv2.VideoWriter_fourcc('P','I','M','1') # MPEG-1
CODEC = cv2.VideoWriter_fourcc('D','I','V','X') # MPEG-4 = MPEG-1

cap = cv2.VideoCapture('data/768x576.avi')

# Define the codec and create VideoWriter object
# fourcc = cv2.VideoWriter_fourcc(*'DIVX')
# out = cv2.VideoWriter('output.avi',fourcc, 20.0, (640,480))
out = cv2.VideoWriter('output.avi',CODEC, 20.0, (768,576))

while(cap.isOpened()):
    ret, frame = cap.read()

    if ret == False or frame is None:
        break

    frame = cv2.flip(frame,0)
    out.write(frame)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('frame',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
out.release()
cv2.destroyAllWindows()

