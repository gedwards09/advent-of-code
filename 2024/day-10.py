import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

class XPosition:

    def __init__(self, iRow, iCol, cDigit):
        self._iRow = iRow
        self._iCol = iCol
        self._iDigit = int(cDigit)

    def getRow(self):
        return self._iRow
    
    def getCol(self):
        return self._iCol
    
    def getDigit(self):
        return self._iDigit

    def tuple(self):
        return (self._iRow, self._iCol)

def Alg1(sFileName):
    pMap = Map2D(sFileName)
    return doAlg(pMap, pathCounterBFS)

def doAlg(pMap: Map2D, fpPathCounter):
    iSum = 0
    for iRow in range(pMap.getYLength()):
        for iCol in range(pMap.getXLength()):
            if pMap.get(iRow, iCol) == '0':
                iSum += fpPathCounter(pMap, iRow, iCol)
    return iSum

def pathCounterBFS(pMap: Map2D, iRow: int, iCol: int):
    iPathCount = 0
    pPosition = XPosition(iRow, iCol, '0')
    pVisited = {pPosition.tuple():''}
    pQueue = [pPosition]
    while len(pQueue) > 0:
        pCurrentPosition = pQueue.pop(0)
        if pCurrentPosition.getDigit() == 9:
            iPathCount += 1
        for pNextPosition in iterateNextPositions(pMap, pVisited, pCurrentPosition):
            pQueue.append(pNextPosition)
            pVisited[pNextPosition.tuple()] = ''
    return iPathCount

def iterateNextPositions(pMap: Map2D, pVisited: dict, pPosition: XPosition):
    iNextDigit = pPosition.getDigit() + 1
    for iRow, iCol, cDigit in pMap.iterateNeighbors(pPosition.getRow(), pPosition.getCol()):
        if int(cDigit) == iNextDigit and (iRow, iCol) not in pVisited:
            yield XPosition(iRow, iCol, cDigit)

def Alg2(sFileName):
    pMap = Map2D(sFileName)
    return doAlg(pMap, pathCounterDistinct)

# same algorithm as BFS but we don't mark a cell as visitied until we have added 
# all its neighbors to the queue
def pathCounterDistinct(pMap: Map2D, iRow: int, iCol: int):
    iPathCount = 0
    pPosition = XPosition(iRow, iCol, '0')
    pVisited = {pPosition.tuple():''}
    pQueue = [pPosition]
    while len(pQueue) > 0:
        pCurrentPosition = pQueue.pop(0)
        if pCurrentPosition.getDigit() == 9:
            iPathCount += 1
        for pNextPosition in iterateNextPositions(pMap, {}, pCurrentPosition):
            pQueue.append(pNextPosition)
        pVisited[pNextPosition.tuple()] = ''
    return iPathCount

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()