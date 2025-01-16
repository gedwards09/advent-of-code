import sys
from utils.AocController import AocController
from utils.Map2D.IntMap2D import IntMap2D

def Alg1(sFileName):
    arr = IntMap2D(sFileName)
    s = 0
    for iRowNum in range(arr.getYLength()):
        row = arr.getRow(iRowNum)
        if isRowSafe(row):
            s += 1
    return s

def isRowSafe(row):
    last = row[0]
    iIncreasing = None
    for i in range(1, len(row)):
        cur = row[i]
        if last == cur:
            return False
        iSign = 1 if last < cur else -1
        iDiff = abs(cur - last)
        if iDiff > 3:
            return False
        if iIncreasing == None:
            iIncreasing = iSign
        elif iIncreasing * iSign <= 0: # different signs
            return False
        last = cur
    return True

def Alg2(sFileName):
    arr = IntMap2D(sFileName)
    s = 0
    for iRowNum in range(arr.getYLength()):
        row = arr.getRow(iRowNum)
        if isRowDampenerSafe(row):
            # print(' '.join([str(s) for s in row]))
            s += 1
    return s

def isRowDampenerSafe(row):
    iRowLength = len(row)
    iIndex = getUnsafeLevelIndex(row)
    return iIndex == iRowLength\
        or getUnsafeLevelIndex(row, iSkipIndex=iIndex-1) == iRowLength\
        or getUnsafeLevelIndex(row, iSkipIndex=iIndex) == iRowLength\
        or getUnsafeLevelIndex(row, iSkipIndex=iIndex+1) == iRowLength

def getUnsafeLevelIndex(row, iSkipIndex=None):
    iRowLength = len(row)
    iStartIndex = getStartIndexFromSkipIndex(iSkipIndex)
    if iStartIndex < 0:
        return -1
    iIncreasing = None
    last = row[iStartIndex]
    for i in range(iStartIndex + 1, len(row)):
        if i == iSkipIndex:
            continue
        cur = row[i]
        if last == cur:
            return (i - 1)
        iSign = 1 if last < cur else -1
        iDiff = abs(cur - last)
        if iDiff > 3:
            return (i - 1)
        if iIncreasing == None:
            iIncreasing = iSign
        elif iIncreasing * iSign <= 0: # different signs
            return (i - 1)
        last = cur
    return iRowLength

def getStartIndexFromSkipIndex(iSkipIndex):
    if iSkipIndex == None:
        return 0
    elif iSkipIndex < 0:
        return -1
    elif iSkipIndex == 0:
        return 1
    elif iSkipIndex == 1:
        return 0
    else:
        return iSkipIndex - 2

def bruteDampenerSafe(row):
    if isRowSafe(row):
        return True
    iRowLength = len(row)
    for iSkipIndex in range(iRowLength):
        if isRowSafeWithSkip(row, iSkipIndex):
            return True
    return False

def isRowSafeWithSkip(row, iSkipIndex):
    iStartIndex = 0 if iSkipIndex > 0 else 1
    last = row[iStartIndex]
    iIncreasing = None
    for i in range(iStartIndex + 1, len(row)):
        if i == iSkipIndex:
            continue
        cur = row[i]
        if last == cur:
            return False
        iSign = 1 if last < cur else -1
        iDiff = abs(cur - last)
        if iDiff > 3:
            return False
        if iIncreasing == None:
            iIncreasing = iSign
        elif iIncreasing * iSign <= 0: # different signs
            return False
        last = cur
    return True

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()