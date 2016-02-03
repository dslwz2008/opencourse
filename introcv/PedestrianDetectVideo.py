# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com


from imutils.object_detection import non_max_suppression
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

hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())
# hog.setSVMDetector(cv2.HOGDescriptor_getDaimlerPeopleDetector())

cap = cv2.VideoCapture('data/768x576.avi')

while(cap.isOpened()):
    ret, frame = cap.read()

    if ret == False or frame is None:
        break

    # detect people in the image
    (rects, weights) = hog.detectMultiScale(frame, winStride=(2, 2),
                                            padding=(8, 8), scale=1.05)

    # apply non-maxima suppression to the bounding boxes using a
    # fairly large overlap threshold to try to maintain overlapping
    # boxes that are still people
    rects = np.array([[x, y, x + w, y + h] for (x, y, w, h) in rects])
    # picks = non_max_suppression(rects, probs=None, overlapThresh=0.65)

    # draw the final bounding boxes
    # for (xA, yA, xB, yB) in picks:
    for (xA, yA, xB, yB) in rects:
        cv2.rectangle(frame, (xA, yA), (xB, yB), (0, 255, 0), 2)

    # show some information on the number of bounding boxes
    # print("[INFO]: {} original boxes, {} after suppression".format(len(rects), len(picks)))
    print("[INFO]: {} original boxes".format(len(rects)))
    cv2.imshow('detect', frame)
    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
