import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

g_bDownFlag = 1 << 0
g_bLeftFlag = 1 << 1
g_bRightFlag = 1 << 2
g_bUpFlag = 1 << 3
g_cObstructionSprite = '#'
g_cStartingSprite = '^'

def Alg1(sFileName):
    pMap = Map2D(sFileName)
    pStartingCoordinate = getStartingCoordinate(pMap)
    pVisited = traceSinglePath(pMap, pStartingCoordinate)
    return getVisitedPositionCount(pVisited)

def getStartingCoordinate(pMap: Map2D):
    for iRow in range(pMap.getYLength()):
        for iCol in range(pMap.getXLength()):
            if pMap.get(iRow, iCol) == g_cStartingSprite:
                return {'iRow': iRow, 'iCol': iCol, 'bDirFlag': g_bUpFlag}
    # starting position not found
    return None

def traceSinglePath(pMap: Map2D, pStartingCoordinate):
    pVisited = initVisited(pStartingCoordinate)
    _ = _doesObstructedPathLoop(pMap, pStartingCoordinate, pVisited=pVisited)
    return pVisited

def initVisited(pCoordinate):
    return {(pCoordinate['iRow'], pCoordinate['iCol']): ''}

def _doesObstructedPathLoop(pMap: Map2D, pStartingCoordinate, pVisited=None, pObstruction=None):
    pCoordinate = copyCoordinate(pStartingCoordinate)
    pLoopChecker = {}
    while pMap.isValid(pCoordinate['iRow'], pCoordinate['iCol'])\
            and not detectLoop(pLoopChecker, pCoordinate):
        pLoopChecker = updateLoopChecker(pLoopChecker, pCoordinate)
        pCoordinate = advanceCoordinate(pMap, pCoordinate, pVisited, pObstruction)
    return detectLoop(pLoopChecker, pCoordinate)

def copyCoordinate(pCoordinate):
    return {key: pCoordinate[key] for key in pCoordinate}

def detectLoop(pLoopChecker, pCoordinate):
    return (pCoordinate['iRow'], pCoordinate['iCol']) in pLoopChecker\
        and pLoopChecker[(pCoordinate['iRow'], pCoordinate['iCol'])] & pCoordinate['bDirFlag'] != 0

def updateLoopChecker(pLoopChecker, pCoordinate):
    if (pCoordinate['iRow'], pCoordinate['iCol']) not in pLoopChecker:
        pLoopChecker[(pCoordinate['iRow'], pCoordinate['iCol'])] = pCoordinate['bDirFlag']
    else:
        pLoopChecker[(pCoordinate['iRow'], pCoordinate['iCol'])] |= pCoordinate['bDirFlag']
    return pLoopChecker
            
# advance position in a straight line until we hit an obstacle or leave the map
def advanceCoordinate(map: Map2D, pCoordinate, pVisited, pObstruction=None):
    if pObstruction == None:
        pObstruction = {'iRow': None, 'iCol': None}
    iRow = pCoordinate['iRow']
    iCol = pCoordinate['iCol']
    iRowChange, iColChange = getCoordinateChange(pCoordinate['bDirFlag'])
    while map.isValid(iRow + iRowChange,\
                      iCol + iColChange)\
        and map.get(iRow + iRowChange,\
                    iCol + iColChange) != g_cObstructionSprite\
        and not (iRow + iRowChange == pObstruction['iRow']\
                and iCol + iColChange == pObstruction['iCol']):
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
        pCoordinate['bDirFlag'] = getNextDirection(pCoordinate['bDirFlag'])
    pCoordinate['iRow'] = iRow
    pCoordinate['iCol'] = iCol
    return pCoordinate

def getCoordinateChange(bDirFlag: int):
    iRow = 0
    iCol = 0
    if bDirFlag == g_bDownFlag:
        iRow = 1
    elif bDirFlag == g_bLeftFlag:
        iCol = -1
    elif bDirFlag == g_bRightFlag:
        iCol = 1
    elif bDirFlag == g_bUpFlag:
        iRow = -1
    return iRow, iCol

def updateVisited(pVisited, iRow, iCol):
    pVisited[(iRow, iCol)] = None
    return pVisited

def getNextDirection(bDirFlag: int):
    if bDirFlag == g_bDownFlag:
        return g_bLeftFlag
    elif bDirFlag == g_bLeftFlag:
        return g_bUpFlag
    elif bDirFlag == g_bRightFlag:
        return g_bDownFlag
    elif bDirFlag == g_bUpFlag:
        return g_bRightFlag
    else:
        return bDirFlag

def getVisitedPositionCount(pVisited):
    iSum = 0
    for key in pVisited.keys():
        iSum += 1
    return iSum

def Alg2(sFileName):
    pMap = Map2D(sFileName)
    pStartingCoordinate = getStartingCoordinate(pMap)
    pVisited = traceSinglePath(pMap, pStartingCoordinate)
    pObstruction = {}
    iCount = 0
    for key in pVisited:
        pObstruction['iRow'] = key[0]
        pObstruction['iCol'] = key[1]
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