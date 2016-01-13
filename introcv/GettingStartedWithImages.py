# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com
import numpy as np
import cv2


def main():
    img = cv2.imread('data/messi5.jpg',cv2.IMREAD_UNCHANGED)
    noise = img.copy()
    cv2.randn(noise,30,10)
    imgNoised = img + noise

    cv2.namedWindow('raw', cv2.WINDOW_NORMAL)
    cv2.imshow('raw', img)
    cv2.namedWindow('test', cv2.WINDOW_NORMAL)
    cv2.imshow('test', imgNoised)

    k = cv2.waitKey(0)
    if k == 27:         # wait for ESC key to exit
        cv2.destroyAllWindows()
    elif k == ord('s'): # wait for 's' key to save and exit
        cv2.imwrite('test.png',img)
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
