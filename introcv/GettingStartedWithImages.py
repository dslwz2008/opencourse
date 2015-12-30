# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com
import numpy as np
import cv2

def gaussianNoise(size, scale):
    return np.random.normal(size=size)


def main():
    img = cv2.imread('data/messi5.jpg',1)
    cropped = img[110:130,10:160]

    cv2.imshow('image',cropped)
    k = cv2.waitKey(0)
    if k == 27:         # wait for ESC key to exit
        cv2.destroyAllWindows()
    elif k == ord('s'): # wait for 's' key to save and exit
        cv2.imwrite('test.png',img)
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
