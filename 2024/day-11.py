import sys
from utils.AocController import AocController

g_iIterations = 25
g_iBiggerIterations = 75

def Alg1(sFileName):
    return doAlg(sFileName, g_iIterations)

def doAlg(sFileName, iIterations):
    with open(sFileName, 'r') as f:
        arr = [int(i) for i in f.read().split(' ')]
    return getCount(arr, iIterations)

def getCount(arr, iIterations):
    pMemo = {}
    iSum = 0
    for iNum in arr:
        iSum += getOneCount(iNum, iIterations, pMemo)
    return iSum

def getOneCount(iNum, iIterations, pMemo):
    if iIterations == 0:
        return 1
    if (iNum, iIterations) in pMemo:
        return pMemo[(iNum, iIterations)]
    sNum = str(iNum)
    iSzNum = len(sNum)
    if iSzNum % 2 == 0:
        iLeft, iRight = splitInt(sNum, iSzNum)
        iResult = getOneCount(iLeft, iIterations-1, pMemo) + getOneCount(iRight, iIterations-1, pMemo)
    elif iNum == 0:
        iResult = getOneCount(1, iIterations-1, pMemo)
    else: 
        iResult = getOneCount(iNum * 2024, iIterations - 1, pMemo)
    pMemo[(iNum, iIterations)] = iResult
    return iResult

def splitInt(sNum, iSzNum):
    return int(sNum[:iSzNum // 2]), int(sNum[iSzNum // 2:])


def Alg2(sFileName):
    return doAlg(sFileName, g_iBiggerIterations)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()