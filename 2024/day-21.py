import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D

class XKeypadADT:

    g_cAcceptSprite = 'A'
    g_cDownSprite = 'v'
    g_cLeftSprite = '<'
    g_cRightSprite = '>'
    g_cUpSprite = '^'
    g_cWallSprite = ' '

    def __init__(self):
        self._pMap = self._mapArray()
        self._tPosition = self._initPosition()
        self._pPositionIndex = self._initPositionIndex()
        self._pInstructionCache = {}
        self._fpPathMetric = self._initPathMetric()

    def _initPosition(self):
        pass
    
    def _mapArray(self) -> Map2D:
        pass
    
    def _initPositionIndex(self):
        pIndex = {}
        for iRow in range(self._pMap.getYLength()):
            sRow = self._pMap.getRow(iRow)
            for iCol in range(self._pMap.getXLength()):
                c = sRow[iCol]
                if c == ' ':
                    continue
                pIndex[c] = (iRow, iCol)
        return pIndex
    
    def _initPathMetric(self):
        return XKeypadADT.__fpDefaultPathMetric
    
    def __fpDefaultPathMetric(sPath):
        return 0
    
    def SetPathMetric(self, fpPathMetric):
        self._fpPathMetric = fpPathMetric
    
    def Reset(self):
        self._tPosition = self._initPosition()

    def Navigate(self, sCode):
        sOut = ''
        cCurSprite = XKeypadADT.g_cAcceptSprite
        for cNextSprite in sCode:
            sOut += self._navigate(cCurSprite, cNextSprite)
            cCurSprite = cNextSprite
        return sOut

    def _navigate(self, cCurrentSprite, cNextSprite):
        sKey = cCurrentSprite + cNextSprite
        tNextPosition = self._pPositionIndex[cNextSprite]
        if sKey not in self._pInstructionCache:
            self._pInstructionCache[sKey] = self._getInstructions(self._tPosition, tNextPosition)
        self._tPosition = tNextPosition
        return self._pInstructionCache[sKey]
    
    def _getInstructions(self, tCurrentPosition, tNextPosition):
        pAllPaths = self._getAllPaths(tCurrentPosition, tNextPosition)
        iMinScore = -1
        sMinPath = ''
        for sPath in pAllPaths:
            iScore = self._fpPathMetric(sPath)
            if iMinScore == -1 or iScore < iMinScore:
                iMinScore = iScore
                sMinPath = sPath
        return sMinPath + XKeypadADT.AcceptSprite()

    def _getAllPaths(self, tStartPosition, tEndPosition):
        pVisited = {}
        pOutput = []
        pQueue = [(tStartPosition, '')]
        while len(pQueue) > 0:
            tCoord, sPath = pQueue.pop(0)
            pVisited[tCoord] = ''
            iRow, iCol = tCoord
            for iNextRow, iNextCol, cSprite in self._pMap.iterateNeighbors(iRow, iCol):
                if cSprite == XKeypadADT.g_cWallSprite:
                    continue
                if self.__skipNeighbor(iRow, iCol, tStartPosition, tEndPosition):
                    continue
                tNext = (iNextRow, iNextCol)
                if tNext in pVisited:
                    continue
                sNextPath = sPath + XKeypadADT.getSprite(iNextRow - iRow, iNextCol - iCol)
                if tNext == tEndPosition:
                    pOutput.append(sNextPath)
                else:
                    pQueue.append((tNext, sNextPath))
        return pOutput

    def __skipNeighbor(self, iRow, iCol, tStart, tEnd):
        return (iRow > tStart[0] and iRow > tEnd[0])\
        or (iRow < tStart[0] and iRow < tEnd[0])\
        or (iCol < tStart[1] and iCol < tEnd[1])\
        or (iCol > tStart[1] and iCol > tEnd[1])
        
    def getSprite(iRowDiff, iColDiff):
        if iRowDiff > 0:
            return XKeypadADT.g_cDownSprite
        elif iColDiff < 0:
            return XKeypadADT.g_cLeftSprite
        elif iColDiff > 0:
            return XKeypadADT.g_cRightSprite
        elif iRowDiff < 0:
            return XKeypadADT.g_cUpSprite

    def AcceptSprite():
        return XKeypadADT.g_cAcceptSprite
    
    def DownSprite():
        return XKeypadADT.g_cDownSprite
    
    def LeftSprite():
        return XKeypadADT.g_cLeftSprite
    
    def RightSprite():
        return XKeypadADT.g_cRightSprite
    
    def UpSprite():
        return XKeypadADT.g_cUpSprite

class XNumpad(XKeypadADT):

    g_sMapArray = "789\n456\n123\n 0A"
    g_tInitialPosition = (3,2)

    # Override
    def _initPosition(self):
        return XNumpad.g_tInitialPosition
    
    # Override
    def _mapArray(self):
        return Map2D(sRawText=XNumpad.g_sMapArray)
    
class XDPad(XKeypadADT):

    g_sConfig = "Av<>^"
    g_sMapArray = " ^A\n<v>"
    g_tInitialPosition = (0,2)

    def __init__(self):
        super().__init__()
        self._pPairPathLengths = self.__initPairPathLengths()

    def __initPairPathLengths(self):
        sConfig = XDPad.g_sConfig
        pPathCache = {}
        pPairPathLengths = self.__getPairPathLengths(pPathCache)
        
        pPathIndex = {}
        for cStartSprite in sConfig:
            for cEndSprite in sConfig:
                sKey = cStartSprite + cEndSprite
                pAllPaths = pPathCache[sKey]
                if len(pAllPaths) == 0:
                    pPathIndex[sKey] = 1
                    continue
                iMinScore = -1
                for sPath in pAllPaths:
                    iScore = XDPad.__fpPathMetric(sPath, pPairPathLengths)
                    if iMinScore == -1 or iScore < iMinScore:
                        iMinScore = iScore
                        sMinPath = sPath
                pPathIndex[sKey] = iMinScore
        return pPathIndex
    
    def __getPairPathLengths(self, pPathCache):
        pPathLengths = {}
        sConfig = XDPad.g_sConfig
        for cStartSprite in sConfig:
            for cEndSprite in sConfig:
                tStartPosition = self._pPositionIndex[cStartSprite]
                tEndPosition = self._pPositionIndex[cEndSprite]
                pAllPaths = self._getAllPaths(tStartPosition, tEndPosition)
                sKey = cStartSprite + cEndSprite
                pPathCache[sKey] = pAllPaths
                if len(pAllPaths) > 0:
                    pPathLengths[sKey] = 1 + len(pAllPaths[0])
                else:
                    pPathLengths[sKey] = 1
        return pPathLengths
    
    # Override
    def _initPosition(self):
        return XDPad.g_tInitialPosition
    
    # Override
    def _mapArray(self):
        return Map2D(sRawText=XDPad.g_sMapArray)
    
    # Override
    def _initPathMetric(self):
        return self.PathMetric
    
    def PathMetric(self, sPath):
        return XDPad.__fpPathMetric(sPath, self._pPairPathLengths)

    def __fpPathMetric(sPath, pPairPathLengths):
        iScore = 0
        for iIdx in range(len(sPath)):
            if iIdx + 1 < len(sPath):
                sPair = sPath[iIdx:iIdx+2]
            else:
                sPair = sPath[iIdx] + XKeypadADT.AcceptSprite()
            iScore += pPairPathLengths[sPair]
        return iScore
    
class XLayerDirPad(XDPad):

    def __init__(self, iTimes):
        super().__init__()
        self._iTimes = iTimes
        self._pCache = {}
        self._pIndex = {}

    # Override
    def Navigate(self, sCode):
        sOut = ''
        for sPart in self.iterateParts(sCode):
            if sPart not in self._pCache:
                self._pCache[sPart] = super().Navigate(sPart)
            sOut += self._pCache[sPart]
        return sOut

    def GetNavigationLength(self, sCode, iTimes):
        iSum = 0
        for sPart in self.iterateParts(sCode):
            iSum += self.__rGetNavigationLength(sPart, iTimes)
        return iSum

    def __rGetNavigationLength(self, sCode, iTimes):
        if sCode not in self._pIndex:
            self._pIndex[sCode] = self.__initIndexList(sCode)
        sLevelCode = self.Navigate(sCode)
        for iIdx in range(iTimes):
            iSum = 0
            for sPart in self.iterateParts(sLevelCode):
                if sPart in self._pIndex and self._pIndex[sPart][iIdx] != None:
                    iSum += self._pIndex[sPart][iIdx]
                else:
                    iSum += self.__rGetNavigationLength(sPart, iIdx)
            self._pIndex[sCode][iIdx+1] = iSum
        return self._pIndex[sCode][iTimes]

    def iterateParts(self, sCode):
        sOut = ''
        iStartIdx = 0
        iEndIdx = 0
        while iStartIdx < len(sCode):
            while iEndIdx < len(sCode) and sCode[iEndIdx] != XKeypadADT.AcceptSprite():
                iEndIdx += 1
            yield sCode[iStartIdx:iEndIdx+1]
            iEndIdx += 1
            iStartIdx = iEndIdx
        return sOut

    def __initIndexList(self, sCode):
        pList = [None for _ in range(self._iTimes+1)]
        pList[0] = len(sCode)
        return pList

def Alg1(sFileName):
    pCodes = getCodes(sFileName)
    pNumpad = XNumpad()
    pControlpad = XDPad()
    pNumpad.SetPathMetric(pControlpad.PathMetric)
    iTotal = 0
    for sCode in pCodes:
        iNumeric = getNumeric(sCode)
        sCode = pNumpad.Navigate(sCode)
        print(sCode)
        pNumpad.Reset()
        for _ in range(2):
            sCode = pControlpad.Navigate(sCode)
            pControlpad.Reset()
        print(sCode, len(sCode))
        iTotal += iNumeric * len(sCode)
    return iTotal

def getCodes(sFileName):
    with open(sFileName, 'r') as f:
        return f.read().split('\n')
    
def getNumeric(sCode):
    return int(sCode[:-1])

def Alg2(sFileName):
    pCodes = getCodes(sFileName)
    pNumpad = XNumpad()
    pControlpad = XLayerDirPad(iTimes = 25)
    pNumpad.SetPathMetric(pControlpad.PathMetric)
    iTotal = 0
    for sCode in pCodes:
        iNumeric = getNumeric(sCode)
        sCode = pNumpad.Navigate(sCode)
        pNumpad.Reset()
        iLen = pControlpad.GetNavigationLength(sCode, 25)
        pControlpad.Reset()
        iTotal += iNumeric * iLen
    return iTotal

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()