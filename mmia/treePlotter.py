# -*-coding:utf-8-*-
# Author: Shen Shen
# Email: dslwz2002@163.com
__author__ = 'Shen Shen'

import matplotlib.pyplot as plt

decisionNode = dict(boxstyle='sawtooth', fc='0.8')
leafNode = dict(boxstyle='sawtooth', fc='0.8')
arrow_args = dict(arrowstyle='<-')
ax1 = None
plotTreeTotalW = 0.0
plotTreeTotalD = 0.0
plotTreeXOff = 0.0
plotTreeYOff = 0.0


def set_ch():
    from pylab import mpl
    mpl.rcParams['font.sans-serif'] = ['FangSong']  # 指定默认字体
    mpl.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题


def getNumLeafs(myTree):
    numLeafs = 0
    firstStr = myTree.keys()[0]
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[
                    key]).__name__ == 'dict':  # test to see if the nodes are dictonaires, if not they are leaf nodes
            numLeafs += getNumLeafs(secondDict[key])
        else:
            numLeafs += 1
    return numLeafs


def getTreeDepth(myTree):
    maxDepth = 0
    firstStr = myTree.keys()[0]
    secondDict = myTree[firstStr]
    for key in secondDict.keys():
        if type(secondDict[
                    key]).__name__ == 'dict':  # test to see if the nodes are dictonaires, if not they are leaf nodes
            thisDepth = 1 + getTreeDepth(secondDict[key])
        else:
            thisDepth = 1
        if thisDepth > maxDepth: maxDepth = thisDepth
    return maxDepth


def plotNode(nodeTxt, centerPt, parentPt, nodeType):
    global ax1
    ax1.annotate(nodeTxt, xy=parentPt, xycoords='axes fraction',
                            xytext=centerPt, textcoords='axes fraction',
                            va="center", ha="center", bbox=nodeType, arrowprops=arrow_args)


def plotMidText(cntrPt, parentPt, txtString):
    global ax1
    xMid = (parentPt[0] - cntrPt[0]) / 2.0 + cntrPt[0]
    yMid = (parentPt[1] - cntrPt[1]) / 2.0 + cntrPt[1]
    ax1.text(xMid, yMid, txtString, va="center", ha="center", rotation=30)


def plotTree(myTree, parentPt, nodeTxt):  # if the first key tells you what feat was split on
    global plotTreeTotalW
    global plotTreeTotalD
    global plotTreeXOff
    global plotTreeYOff
    numLeafs = getNumLeafs(myTree)  # this determines the x width of this tree
    depth = getTreeDepth(myTree)
    firstStr = myTree.keys()[0]  # the text label for this node should be this
    cntrPt = (plotTreeXOff + (1.0 + float(numLeafs)) / 2.0 / plotTreeTotalW, plotTreeYOff)
    plotMidText(cntrPt, parentPt, nodeTxt)
    plotNode(firstStr, cntrPt, parentPt, decisionNode)
    secondDict = myTree[firstStr]
    plotTreeYOff = plotTreeYOff - 1.0 / plotTreeTotalD
    for key in secondDict.keys():
        if type(secondDict[
                    key]).__name__ == 'dict':  # test to see if the nodes are dictonaires, if not they are leaf nodes
            plotTree(secondDict[key], cntrPt, str(key))  # recursion
        else:  # it's a leaf node print the leaf node
            plotTreeXOff = plotTreeXOff + 1.0 / plotTreeTotalW
            plotNode(secondDict[key], (plotTreeXOff, plotTreeYOff), cntrPt, leafNode)
            plotMidText((plotTreeXOff, plotTreeYOff), cntrPt, str(key))
    plotTreeYOff = plotTreeYOff + 1.0 / plotTreeTotalD


# if you do get a dictonary you know it's a tree, and the first element will be another dict

def createPlot(inTree):
    global plotTreeTotalW
    global plotTreeTotalD
    global plotTreeXOff
    global plotTreeYOff
    global ax1
    fig = plt.figure(1, facecolor='white')
    fig.clf()
    axprops = dict(xticks=[], yticks=[])
    ax1 = plt.subplot(111, frameon=False, **axprops)  # no ticks
    # createPlot.ax1 = plt.subplot(111, frameon=False) #ticks for demo puropses
    plotTreeTotalW = float(getNumLeafs(inTree))
    plotTreeTotalD = float(getTreeDepth(inTree))
    plotTreeXOff = -0.5 / plotTreeTotalW
    plotTreeYOff = 1.0
    plotTree(inTree, (0.5, 1.0), '')
    plt.show()

# def createPlot():
#    fig = plt.figure(1, facecolor='white')
#    fig.clf()
#    createPlot.ax1 = plt.subplot(111, frameon=False) #ticks for demo puropses
#    plotNode('a decision node', (0.5, 0.1), (0.1, 0.5), decisionNode)
#    plotNode('a leaf node', (0.8, 0.1), (0.3, 0.8), leafNode)
#    plt.show()

def retrieveTree(i):
    listOfTrees = [{'no surfacing': {0: 'no', 1: {'flippers': {0: 'no', 1: 'yes'}}}},
                   {'no surfacing': {0: 'no', 1: {'flippers': {0: {'head': {0: 'no', 1: 'yes'}}, 1: 'no'}}}}
                   ]
    return listOfTrees[i]

def testLenseDataset():
    from trees import createTree
    fr=open('lenses.txt')
    lenses=[inst.strip().split('\t') for inst in fr.readlines()]
    lensesLabels=['age','prescript','astigmatic','tearRate']
    lensesTree=createTree(lenses,lensesLabels)
    createPlot(lensesTree)

if __name__ == '__main__':
    set_ch()
    # createPlot(retrieveTree(0))
    testLenseDataset()
