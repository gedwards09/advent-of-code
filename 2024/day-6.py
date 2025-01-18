import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

g_cObstructionSprite = '#'
g_cStartingSprite = '^'

class XCoordinate:

    g_bDownFlag = 1 << 0
    g_bLeftFlag = 1 << 1
    g_bRightFlag = 1 << 2
    g_bUpFlag = 1 << 3
    g_cDownSprite = 'v'
    g_cLeftSprite = '<'
    g_cRightSprite = '>'
    g_cUpSprite = '^'

    def __init__(self, iRow, iCol, cDirSprite=None):
        self.Row = iRow
        self.Col = iCol
        self.DirFlag = XCoordinate.initDirFlag(cDirSprite)
        self._cDirSprite = cDirSprite

    def initDirFlag(cDirSprite):
        if cDirSprite == XCoordinate.g_cDownSprite:
            return XCoordinate.g_bDownFlag
        elif cDirSprite == XCoordinate.g_cLeftSprite:
            return XCoordinate.g_bLeftFlag
        elif cDirSprite == XCoordinate.g_cRightSprite:
            return XCoordinate.g_bRightFlag
        elif cDirSprite == XCoordinate.g_cUpSprite:
            return XCoordinate.g_bUpFlag

    def copy(self):
        return XCoordinate(self.Row, self.Col, self._cDirSprite)

    def getCoordinateChange(self):
        iRow = 0
        iCol = 0
        if self.DirFlag == XCoordinate.g_bDownFlag:
            iRow = 1
        elif self.DirFlag == XCoordinate.g_bLeftFlag:
            iCol = -1
        elif self.DirFlag == XCoordinate.g_bRightFlag:
            iCol = 1
        elif self.DirFlag == XCoordinate.g_bUpFlag:
            iRow = -1
        return iRow, iCol

    def advanceDirection(self):
        self.DirFlag = self._getNextDirection()

    # private
    def _getNextDirection(self):
        if self.DirFlag == XCoordinate.g_bDownFlag:
            return XCoordinate.g_bLeftFlag
        elif self.DirFlag == XCoordinate.g_bLeftFlag:
            return XCoordinate.g_bUpFlag
        elif self.DirFlag == XCoordinate.g_bRightFlag:
            return XCoordinate.g_bDownFlag
        elif self.DirFlag == XCoordinate.g_bUpFlag:
            return XCoordinate.g_bRightFlag
        else:
            return self.DirFlag

def Alg1(sFileName):
    pMap = Map2D(sFileName)
    pStartingCoordinate = getStartingCoordinate(pMap)
    pVisited = traceSinglePath(pMap, pStartingCoordinate)
    return getVisitedPositionCount(pVisited)

def getStartingCoordinate(pMap: Map2D):
    for iRow in range(pMap.getYLength()):
        for iCol in range(pMap.getXLength()):
            if pMap.get(iRow, iCol) == g_cStartingSprite:
                return XCoordinate(iRow, iCol, g_cStartingSprite)
    # starting position not found
    return None

def traceSinglePath(pMap: Map2D, pStartingCoordinate):
    pVisited = initVisited(pStartingCoordinate)
    _ = _doesObstructedPathLoop(pMap, pStartingCoordinate, pVisited=pVisited)
    return pVisited

def initVisited(pCoordinate):
    return {(pCoordinate.Row, pCoordinate.Col): ''}

def _doesObstructedPathLoop(pMap: Map2D, pStartingCoordinate, pVisited=None, pObstruction=None):
    pCoordinate = pStartingCoordinate.copy()
    pLoopChecker = {}
    while pMap.isValid(pCoordinate.Row, pCoordinate.Col)\
            and not detectLoop(pLoopChecker, pCoordinate):
        pLoopChecker = updateLoopChecker(pLoopChecker, pCoordinate)
        pCoordinate = advanceCoordinate(pMap, pCoordinate, pVisited, pObstruction)
    return detectLoop(pLoopChecker, pCoordinate)

def detectLoop(pLoopChecker, pCoordinate):
    return (pCoordinate.Row, pCoordinate.Col) in pLoopChecker\
        and pLoopChecker[(pCoordinate.Row, pCoordinate.Col)] & pCoordinate.DirFlag != 0

def updateLoopChecker(pLoopChecker, pCoordinate):
    if (pCoordinate.Row, pCoordinate.Col) not in pLoopChecker:
        pLoopChecker[(pCoordinate.Row, pCoordinate.Col)] = pCoordinate.DirFlag
    else:
        pLoopChecker[(pCoordinate.Row, pCoordinate.Col)] |= pCoordinate.DirFlag
    return pLoopChecker
            
# advance position in a straight line until we hit an obstacle or leave the map
def advanceCoordinate(map: Map2D, pCoordinate, pVisited, pObstruction=None):
    if pObstruction == None:
        pObstruction = XCoordinate(iRow=None, iCol=None)
    iRow = pCoordinate.Row
    iCol = pCoordinate.Col
    iRowChange, iColChange = pCoordinate.getCoordinateChange()
    while map.isValid(iRow + iRowChange,\
                      iCol + iColChange)\
        and map.get(iRow + iRowChange,\
                    iCol + iColChange) != g_cObstructionSprite\
        and not (iRow + iRowChange == pObstruction.Row\
                and iCol + iColChange == pObstruction.Col):
        iRow += iRowChange
        iCol += iColChange
        if pVisited != None:
            pVisited = updateVisited(pVisited, iRow, iCol)
    if not map.isValid(iRow + iRowChange,
                       iCol + iColChange):
        # we're done
        # increment coords off the map
        # don't record this as new position visited
        iRow += iRowChange
        iCol += iColChange
    else:
        pCoordinate.advanceDirection()
    pCoordinate.Row = iRow
    pCoordinate.Col = iCol
    return pCoordinate

def updateVisited(pVisited, iRow, iCol):
    pVisited[(iRow, iCol)] = None
    return pVisited

def getVisitedPositionCount(pVisited):
    iSum = 0
    for key in pVisited.keys():
        iSum += 1
    return iSum

def Alg2(sFileName):
    pMap = Map2D(sFileName)
    pStartingCoordinate = getStartingCoordinate(pMap)
    pVisited = traceSinglePath(pMap, pStartingCoordinate)
    pObstruction = XCoordinate(iRow=None, iCol=None)
    iCount = 0
    for key in pVisited:
        pObstruction.Row = key[0]
        pObstruction.Col = key[1]
        if doesObstructedPathLoop(pMap, pStartingCoordinate, pObstruction):
            iCount += 1
    return iCount

def doesObstructedPathLoop(pMap: Map2D, pStartingCoordinate, pObstruction):
    return _doesObstructedPathLoop(pMap, pStartingCoordinate, pObstruction=pObstruction)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()