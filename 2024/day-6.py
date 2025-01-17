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
    pVisited = initVisited()
    _ = _doesObstructedPathLoop(pMap, pStartingCoordinate, pVisited)
    return pVisited

def initVisited():
    return {}

def _doesObstructedPathLoop(pMap: Map2D, pStartingCoordinate, pVisited, pObstruction=None):
    pCoordinate = copyCoordinate(pStartingCoordinate)
    while pMap.isValid(pCoordinate['iRow'], pCoordinate['iCol'])\
            and not detectLoop(pVisited, pCoordinate):
        pVisited = updateVisitedCoordinate(pVisited, pCoordinate)
        pCoordinate = advanceCoordinate(pMap, pCoordinate, pVisited, pObstruction)
    return detectLoop(pVisited, pCoordinate)

def copyCoordinate(pCoordinate):
    return {key: pCoordinate[key] for key in pCoordinate}

def detectLoop(pVisited, pCoordinate):
    return (pCoordinate['iRow'], pCoordinate['iCol']) in pVisited\
        and pVisited[(pCoordinate['iRow'], pCoordinate['iCol'])] & pCoordinate['bDirFlag'] != 0

def updateVisitedCoordinate(pVisited, pCoordinate):
    return updateVisited(pVisited, pCoordinate['iRow'], pCoordinate['iCol'], pCoordinate['bDirFlag'])

def updateVisited(pVisited, iRow, iCol, bDirFlag):
    if (iRow, iCol) not in pVisited:
        pVisited[(iRow, iCol)] = bDirFlag
    else:
        pVisited[(iRow, iCol)] |= bDirFlag
    return pVisited
            
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
        pVisited = updateVisited(pVisited, iRow, iCol, pCoordinate['bDirFlag'])
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
    pVisited = initVisited()
    return _doesObstructedPathLoop(pMap, pStartingCoordinate, pVisited, pObstruction)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()