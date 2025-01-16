import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

g_cDownSprite = 'v'
g_cLeftSprite = '>'
g_cObstructionSprite = '#'
g_cRightSprite = '<'
g_cUpSprite = '^'
g_cStartingSprite = g_cUpSprite

def Alg1(sFileName):
    pMap = Map2D(sFileName)
    pStartingCoordinate = getStartingCoordinate(pMap)
    pVisited = traceSinglePath(pMap, pStartingCoordinate)
    return getVisitedPositionCount(pVisited)

def getStartingCoordinate(pMap: Map2D):
    for iRow in range(pMap.getYLength()):
        for iCol in range(pMap.getXLength()):
            if pMap.get(iRow, iCol) == g_cStartingSprite:
                return {'iRow': iRow, 'iCol': iCol, 'cDir': '^'}
    return None

def initVisited(pCoordinate):
    return {(pCoordinate['iRow'], pCoordinate['iCol']): pCoordinate['cDir']}

def traceSinglePath(pMap, pStartingCoordinate):
    pCoordinate = copyCoordinate(pStartingCoordinate)
    pVisited = initVisited(pCoordinate)
    while pMap.isValid(pCoordinate['iRow'], pCoordinate['iCol']):
        pCoordinate = advanceCoordinate(pMap, pCoordinate, pVisited)
    return pVisited

def copyCoordinate(pCoordinate):
    return {key: pCoordinate[key] for key in pCoordinate}
            
# advance position in a straight line until we hit an obstacle or leave the map
def advanceCoordinate(map: Map2D, pCoordinate, pVisited, pObstruction=None):
    if pObstruction == None:
        pObstruction = {'iRow': None, 'iCol': None}
    iRow = pCoordinate['iRow']
    iCol = pCoordinate['iCol']
    iRowChange, iColChange = getCoordinateChange(pCoordinate['cDir'])
    while map.isValid(iRow + iRowChange,\
                      iCol + iColChange)\
        and map.get(iRow + iRowChange,\
                    iCol + iColChange) != g_cObstructionSprite\
        and not (iRow + iRowChange == pObstruction['iRow']\
                 and iCol + iColChange == pObstruction['iCol']):
        iRow += iRowChange
        iCol += iColChange
        pVisited = updateVisited(pVisited, iRow, iCol, pCoordinate['cDir'])
    if not map.isValid(iRow + iRowChange,
                       iCol + iColChange):
        # we're done
        # increment coords off the map
        # don't record this as new position visited
        iRow += iRowChange
        iCol += iColChange
    else:
        pCoordinate['cDir'] = getNextDirection(pCoordinate['cDir'])
    pCoordinate['iRow'] = iRow
    pCoordinate['iCol'] = iCol
    return pCoordinate

def getCoordinateChange(cDirection: str):
    iRow = 0
    iCol = 0
    if cDirection == g_cDownSprite:
        iRow = 1
    elif cDirection == g_cLeftSprite:
        iCol = -1
    elif cDirection == g_cRightSprite:
        iCol = 1
    elif cDirection == g_cUpSprite:
        iRow = -1
    return iRow, iCol

def updateVisited(pVisited, iRow, iCol, cDir):
    if (iRow, iCol) not in pVisited:
        pVisited[(iRow, iCol)] = cDir
    else:
        pVisited[(iRow, iCol)] += cDir
    return pVisited

def getNextDirection(cDirection: str):
    if cDirection == g_cDownSprite:
        return g_cLeftSprite
    elif cDirection == g_cLeftSprite:
        return g_cUpSprite
    elif cDirection == g_cRightSprite:
        return g_cDownSprite
    elif cDirection == g_cUpSprite:
        return g_cRightSprite
    else:
        return cDirection

def getVisitedPositionCount(pVisited):
    iSum = 0
    for key in pVisited.keys():
        iSum += 1
    return iSum

def Alg2(sFileName):
    pMap = Map2D(sFileName)
    pStartingCoordinate = getStartingCoordinate(pMap)
    pVisited = traceSinglePath(pMap, pStartingCoordinate)
    iCount = 0
    for key in pVisited:
        pObstruction = {'iRow': key[0], 'iCol': key[1]}
        if doesPathLoopWithObstruction(pMap, pStartingCoordinate, pObstruction):
            iCount += 1
    return iCount

def doesPathLoopWithObstruction(pMap, pStartingCoordinate, pObstruction):
    pCoordinate = copyCoordinate(pStartingCoordinate)
    pVisited = initVisited(pCoordinate)
    while pMap.isValid(pCoordinate['iRow'], pCoordinate['iCol'])\
        and not detectLoop(pCoordinate, pVisited):
        pCoordinate = advanceCoordinate(pMap, pCoordinate, pVisited, pObstruction=pObstruction)
    # we detected a loop if and only if current coordinate is valid
    return pMap.isValid(pCoordinate['iRow'], pCoordinate['iCol'])

def detectLoop(pCoordinate, pVisited):
    s = pVisited[(pCoordinate['iRow'], pCoordinate['iCol'])]
    dir = {}
    for c in s:
        if c in dir:
            return True
        dir[c] = ''
    return False

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()