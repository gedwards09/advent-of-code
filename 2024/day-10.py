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
    
    def getAdjacentDigit(self, pMap: Map2D, iRowStep, iColStep):
        cDigit = pMap.get(self._iRow + iRowStep, self._iCol + iColStep)
        if cDigit != None:
            return int(cDigit)
        return None
    
    def getAdjacentTuple(self, iRowStep, iColStep):
        return (self._iRow + iRowStep, self._iCol + iColStep)
    
    def makeAdjacentPosition(self, iRowStep, iColStep, iNextDigit):
        return XPosition(self._iRow + iRowStep, self._iCol + iColStep, iNextDigit)


def Alg1(sFileName):
    pMap = Map2D(sFileName)
    return doAlg1(pMap)

def doAlg1(pMap: Map2D):
    iSum = 0
    for iRow in range(pMap.getYLength()):
        for iCol in range(pMap.getXLength()):
            if pMap.get(iRow, iCol) == '0':
                iSum += getPathCount(pMap, iRow, iCol)
    return iSum

def getPathCount(pMap: Map2D, iRow: int, iCol: int):
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
    for iStep in [-1, 1]:
        if pPosition.getAdjacentDigit(pMap, iStep, 0) == iNextDigit\
            and pPosition.getAdjacentTuple(iStep, 0) not in pVisited:
            yield pPosition.makeAdjacentPosition(iStep, 0, iNextDigit)

        if pPosition.getAdjacentDigit(pMap, 0, iStep) == iNextDigit\
            and pPosition.getAdjacentTuple(0, iStep) not in pVisited:
            yield pPosition.makeAdjacentPosition(0, iStep, iNextDigit)


def Alg2(sFileName):
    return

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()