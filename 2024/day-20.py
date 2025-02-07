import sys
from utils.AocController import AocController
from utils.Map2D.MazeMap import MazeMap

class XRaceMazeMap(MazeMap):

    g_iMaxCheatSteps = 2

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            pRawText = f.read().split('\n', maxsplit=1)
        super().__init__(sRawText=pRawText[1])
        self._iLimit = int(pRawText[0])

    def getLimit(self):
        return self._iLimit
    
    def getMaxCheatStep(self):
        return XRaceMazeMap.g_iMaxCheatSteps
    
class XSuperCheatRaceMazeMap(XRaceMazeMap):

    g_iMaxCheatSteps = 20
    
    # Override
    def iterateNeighbors(self, iRow, iCol, iStepSize=1):
        for iRowStep in range(-iStepSize, iStepSize + 1, 1):
            for iColStep in range(-iStepSize + abs(iRowStep), iStepSize - abs(iRowStep) + 1, 1):
                if iRowStep == 0 and iColStep == 0:
                    continue
                if self.isValid(iRow + iRowStep, iCol + iColStep):
                    yield (iRow + iRowStep, iCol + iColStep, self.get(iRow + iRowStep, iCol + iColStep))

    # Override
    def getMaxCheatStep(self):
        return XSuperCheatRaceMazeMap.g_iMaxCheatSteps
    

def Alg1(sFileName):
    pMap = XRaceMazeMap(sFileName)
    return countCheats(pMap)

def countCheats(pMap: XRaceMazeMap):
    return _countCheats(pMap, pMap.getLimit(), pMap.getMaxCheatStep())

def _countCheats(pMap: MazeMap, iBound: int, iStepSize: int):
    pDistFromEnd = getDistanceFromEnd(pMap)
    iCount = 0
    for tCoord in pDistFromEnd:
        iRow, iCol = tCoord
        iDistFromEnd = pDistFromEnd[tCoord]
        for iNextRow, iNextCol, cNextSprite in pMap.iterateNeighbors(iRow, iCol, iStepSize=iStepSize):
            if cNextSprite == MazeMap.GetWallSprite():
                continue
            if iDistFromEnd - pDistFromEnd[(iNextRow, iNextCol)] - abs(iRow - iNextRow) - abs(iCol - iNextCol) >= iBound:
                iCount += 1
    return iCount

def getDistanceFromEnd(pMap: MazeMap):
    tCoord = pMap.getEnd()
    pDistFromEnd = {tCoord:0}
    pQueue = [tCoord]
    while len(pQueue) > 0:
        tCoord = pQueue.pop(0)
        iRow, iCol = tCoord
        for iNextRow, iNextCol, cNextSprite in pMap.iterateNeighbors(iRow, iCol):
            tNext = (iNextRow, iNextCol)
            if tNext in pDistFromEnd:
                continue
            if cNextSprite == MazeMap.GetWallSprite():
                continue
            pDistFromEnd[tNext] = pDistFromEnd[tCoord] + 1
            pQueue.append(tNext)
    return pDistFromEnd


def Alg2(sFileName):
    pMap = XSuperCheatRaceMazeMap(sFileName)
    return countCheats(pMap)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()