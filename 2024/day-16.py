import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D
from utils.VisitorCoordinate.VisitorCoordinate import VisitorCoordinate


class XCoordinate(VisitorCoordinate):

    def __init__(self, iRow, iCol, cDir, iScore):
        super().__init__(iRow, iCol, cDir)
        self._iScore = iScore
    
    def getScore(self):
        return self._iScore
    
    # Override
    def iterateNeighbors(self):
        for iDiff in range(-1, 2, 2):
            yield (self._iRow + iDiff, self._iCol, VisitorCoordinate.GetNeighborDirection(iDiff, 0))
            
            yield (self._iRow, self._iCol + iDiff, VisitorCoordinate.GetNeighborDirection(0, iDiff))
    
class XMazeMap(Map2D):

    g_cStartSprite = 'S'
    g_cEndSprite = 'E'
    g_cWallSprite = '#'

    def __init__(self, sFileName):
        super().__init__(sFileName=sFileName)
        tStart, tEnd = self._initStartAndEndPositions()
        self._tStart = tStart
        self._tEnd = tEnd
    
    def _initStartAndEndPositions(self):
        tStart = None
        tEnd = None
        for iRow in range(self.getYLength()):
            sRow = self.getRow(iRow)
            for iCol in range(self.getXLength()):
                if sRow[iCol] == XMazeMap.g_cStartSprite:
                    tStart = (iRow, iCol)
                    if tEnd != None:
                        return tStart, tEnd
                elif sRow[iCol] == XMazeMap.g_cEndSprite:
                    tEnd = (iRow, iCol)
                    if tStart != None:
                        return tStart, tEnd
                    
    def getStart(self):
        return self._tStart
    
    def getEnd(self):
        return self._tEnd
    
    def GetStartDirection():
        return XCoordinate.GetRightSprite()
    
    def GetWallSprite():
        return XMazeMap.g_cWallSprite
    
    def GetEndSprite():
        return XMazeMap.g_cEndSprite

def Alg1(sFileName):
    pMap = XMazeMap(sFileName)
    return getLowestEndScore(pMap)

def getLowestEndScore(pMap: XMazeMap, pLowestScores = None, pPredecessors = None):
    if pLowestScores == None:
        pLowestScores = {}
    getLowestCoordinateScores(pMap, pLowestScores=pLowestScores, pPredecessors=pPredecessors)
    iMin = 0
    tEndCoord = pMap.getEnd()
    for cDir in XCoordinate.IterateDirectionSprites():
        tKey = (tEndCoord, cDir)
        if tKey in pLowestScores:
            if iMin == 0:
                iMin = pLowestScores[tKey]
            elif pLowestScores[tKey] < iMin:
                iMin = pLowestScores[tKey]
    return iMin

def getLowestCoordinateScores(pMap: Map2D, pLowestScores = None, pPredecessors = None):
    pCoord = buildStartingCoordinate(pMap)
    if pLowestScores == None:
        pLowestScores = {}
    pLowestScores[(pCoord.getCoord(), XMazeMap.GetStartDirection())] = pCoord.getScore()
    pQueue = [pCoord]
    while len(pQueue) > 0:
        pCoord = pQueue.pop(0)
        for iRow, iCol, cDir in pCoord.iterateNeighbors():
            if not pMap.isValid(iRow, iCol):
                continue
            cSprite = pMap.get(iRow, iCol)
            if cSprite == XMazeMap.GetWallSprite():
                continue
            tNextCoord = (iRow, iCol)
            iNextScore = pCoord.getScore() + 1
            if cDir != pCoord.getDir():
                iNextScore += 1000
            tNextKey = (tNextCoord, cDir)
            if tNextKey not in pLowestScores or iNextScore < pLowestScores[tNextKey]:
                pNext = XCoordinate(iRow, iCol, cDir, iNextScore)
                pQueue.append(pNext)
                pLowestScores[tNextKey] = iNextScore
                if pPredecessors != None:
                    pPredecessors[tNextKey] = [(pCoord.getCoord(), pCoord.getDir())]
            elif pPredecessors != None and iNextScore == pLowestScores[tNextKey]:
                    pPredecessors[tNextKey].append((pCoord.getCoord(), pCoord.getDir()))

def buildStartingCoordinate(pMap: XMazeMap):
    tStart = pMap.getStart()
    return XCoordinate(iRow=tStart[0], iCol=tStart[1], cDir=XMazeMap.GetStartDirection(), iScore=0)

def newPredecessorList():
    return [None for _ in range(4)]

def getIndexFromDirection(cDirSprite):
    if cDirSprite == XCoordinate.GetDownSprite():
        return 0
    elif cDirSprite == XCoordinate.GetLeftSprite():
        return 1
    elif cDirSprite == XCoordinate.GetRightSprite():
        return 2
    elif cDirSprite == XCoordinate.GetUpSprite():
        return 3

def Alg2(sFileName):
    pMap = XMazeMap(sFileName)
    return getLowestEndScoreTileCount(pMap)

def getLowestEndScoreTileCount(pMap: XMazeMap):
    pPredecessors = {}
    pLowestScores = {}
    iMin = getLowestEndScore(pMap, pLowestScores=pLowestScores, pPredecessors=pPredecessors)
    pQueue = []
    for cDir in XCoordinate.IterateDirectionSprites():
        tKey = (pMap.getEnd(), cDir)
        if tKey in pLowestScores and iMin == pLowestScores[tKey]:
            pQueue.append(tKey)
    pVisited = {pMap.getEnd(): 0xF}
    iCount = 1
    while len(pQueue) > 0:
        tKey = pQueue.pop(0)
        if tKey not in pPredecessors:
            continue
        for tNextKey in pPredecessors[tKey]:
            tNextCoord, cDir = tNextKey
            bDirFlag = XCoordinate.GetDirFlag(cDir)
            if tNextCoord not in pVisited:
                iCount += 1
            elif pVisited[tNextCoord] & bDirFlag != 0:
                continue
            pQueue.append(tNextKey)
            if tNextCoord not in pVisited:
                pVisited[tNextCoord] = bDirFlag
            else:
                pVisited[tNextCoord] |= bDirFlag
    return iCount


def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()