# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com
__author__ = 'Shen Shen'

import numpy as np
from scipy import linalg


def transform2D(x, y, p):
    p = np.vstack([p, np.array([1])])
    tmat = np.array([
        [1, 0, x],
        [0, 1, y],
        [0, 0, 1]])
    newp = tmat.dot(p)
    divide = newp / newp[-1]
    return divide[:-1]


def rotate2D(theta, p):
    the = theta * np.pi / 180
    rmat = np.array([
        [np.cos(the), -np.sin(the)],
        [np.sin(the), np.cos(the)]])
    return rmat.dot(p)


if __name__ == '__main__':
    # a = np.array([[0], [0]])
    # x = 2
    # y = 1
    # theta = 143
    # print(rotate2D(theta, transform2D(x, y, a)))
    # print(transform2D(x, y, rotate2D(theta, a)))
    a = np.array([[2],[2]])
    # tmat = np.array([
    #     [np.cos(np.pi*45/180), -np.sin(np.pi*45/180), 1],
    #     [np.sin(np.pi*45/180), np.cos(np.pi*45/180), 1],
    #     [0,0,1]
    # ])
    # print(tmat.dot(a))
    print(rotate2D(-45, transform2D(-1, -1, a)))