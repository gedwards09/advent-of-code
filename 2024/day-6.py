import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D
from utils.VisitorCoordinate.VisitorCoordinate import VisitorCoordinate

g_cObstructionSprite = '#'
g_cStartingSprite = '^'

class XCoordinate(VisitorCoordinate):

    def __init__(self, iRow, iCol, cDirSprite=None):
        super().__init__(iRow, iCol, cDirSprite)
        self.DirFlag = XCoordinate.initDirFlag(cDirSprite)

    def initDirFlag(cDirSprite):
        return VisitorCoordinate.GetDirFlag(cDirSprite)

    def copy(self):
        return XCoordinate(self.getRow(), self.getCol(), self.getDir())

    def advanceDirection(self):
        self.DirFlag = self._getNextDirection()

    # private
    def _getNextDirection(self):
        if self.DirFlag == VisitorCoordinate.GetDownFlag():
            return VisitorCoordinate.GetLeftFlag()
        elif self.DirFlag == VisitorCoordinate.GetLeftFlag():
            return VisitorCoordinate.GetUpFlag()
        elif self.DirFlag == VisitorCoordinate.GetRightFlag():
            return VisitorCoordinate.GetDownFlag()
        elif self.DirFlag == VisitorCoordinate.GetUpFlag():
            return VisitorCoordinate.GetRightFlag()
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
    return {(pCoordinate.getRow(), pCoordinate.getCol()): ''}

def _doesObstructedPathLoop(pMap: Map2D, pStartingCoordinate, pVisited=None, pObstruction=None):
    pCoordinate = pStartingCoordinate.copy()
    pLoopChecker = {}
    while pMap.isValid(pCoordinate.getRow(), pCoordinate.getCol())\
            and not detectLoop(pLoopChecker, pCoordinate):
        pLoopChecker = updateLoopChecker(pLoopChecker, pCoordinate)
        pCoordinate = advanceCoordinate(pMap, pCoordinate, pVisited, pObstruction)
    return detectLoop(pLoopChecker, pCoordinate)

def detectLoop(pLoopChecker, pCoordinate):
    return (pCoordinate.getRow(), pCoordinate.getCol()) in pLoopChecker\
        and pLoopChecker[(pCoordinate.getRow(), pCoordinate.getCol())] & pCoordinate.DirFlag != 0

def updateLoopChecker(pLoopChecker, pCoordinate):
    if (pCoordinate.getRow(), pCoordinate.getCol()) not in pLoopChecker:
        pLoopChecker[(pCoordinate.getRow(), pCoordinate.getCol())] = pCoordinate.DirFlag
    else:
        pLoopChecker[(pCoordinate.getRow(), pCoordinate.getCol())] |= pCoordinate.DirFlag
    return pLoopChecker
            
# advance position in a straight line until we hit an obstacle or leave the map
def advanceCoordinate(map: Map2D, pCoordinate, pVisited, pObstruction=None):
    if pObstruction == None:
        pObstruction = XCoordinate(iRow=None, iCol=None)
    iRow = pCoordinate.getRow()
    iCol = pCoordinate.getCol()
    iRowChange, iColChange = pCoordinate.getCoordinateChange()
    while map.isValid(iRow + iRowChange,\
                      iCol + iColChange)\
        and map.get(iRow + iRowChange,\
                    iCol + iColChange) != g_cObstructionSprite\
        and not (iRow + iRowChange == pObstruction.getRow()\
                and iCol + iColChange == pObstruction.getCol()):
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
    pCoordinate.setRow(iRow)
    pCoordinate.setCol(iCol)
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
        pObstruction.setRow(key[0])
        pObstruction.setCol(key[1])
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