import sys
from utils.AocController import AocController
from utils.Map2D.CharMap2D import CharMap2D

class XMemMap(CharMap2D):

    g_cCorruptSprite = '#'
    g_cSafeSprite = '.'
    g_tStart = (0, 0)

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            pLines = f.read().split('\n')
        iByteCount = int(pLines[0])
        iSzX, iSzY = XMemMap.__parseLine(pLines[1])
        sRawText = '\n'.join([''.join([XMemMap.g_cSafeSprite for _ in range(iSzX + 1)]) for __ in range(iSzY + 1)])
        super().__init__(sRawText=sRawText, cDelim='\n')
        self._iByteCount = iByteCount
        self._pBytes = [XMemMap.__parseLine(sLine) for sLine in pLines[2:]]
        self._iByteIndex = 0
        self._iSzBytes = len(self._pBytes)
        self._tStart = XMemMap.g_tStart
        self._tEnd = (iSzY, iSzX)
        self._iSzX = iSzX + 1
        self._iSzY = iSzY + 1
        self._pCorruptIndex = {}

    def __parseLine(sLine):
        return [int(s) for s in sLine.split(',')]
    
    def Corrupt(self, iByteCount=None):
        if iByteCount == None:
            self.__corrupt(self._iByteCount)
        else:
            self.__corrupt(iByteCount)
        
    def Uncorrupt(self, iByteCount=None):
        if iByteCount == None:
            self.__uncorrupt(self._iByteCount)
        else:
            self.__uncorrupt(iByteCount)

    def __corrupt(self, iByteCount):
        for iIdx in range(iByteCount):
            iX, iY = self._pBytes[self._iByteIndex]
            if (iX, iY) not in self._pCorruptIndex:
                self._pCorruptIndex[(iX, iY)] = 1
            else:
                self._pCorruptIndex[(iX, iY)] += 1
            if self._pCorruptIndex[(iX, iY)] == 1:
                self._set(iY, iX, XMemMap.g_cCorruptSprite)
            self._iByteIndex += 1
    
    def __uncorrupt(self, iByteCount):
        for _ in range(iByteCount):
            self._iByteIndex -= 1
            iX, iY = self._pBytes[self._iByteIndex]
            self._pCorruptIndex[(iX, iY)] -= 1
            if self._pCorruptIndex[(iX, iY)] == 0:
                self._set(iY, iX, XMemMap.g_cSafeSprite)
                    
    def Solve(self):
        tCoord = self._tStart
        pVisited = {tCoord: 0}
        pQueue = [tCoord]
        while len(pQueue) > 0:
            tCoord = pQueue.pop(0)
            iRow, iCol = tCoord
            for iRow, iCol, cSprite in self.iterateNeighbors(iRow, iCol):
                if cSprite != XMemMap.g_cSafeSprite:
                    continue
                tNext = (iRow, iCol)
                if tNext not in pVisited:
                    pVisited[tNext] = pVisited[tCoord] + 1
                    if tNext == self._tEnd:
                        return pVisited[tNext]
                    pQueue.append(tNext)
        return -1
    
    def Print(self):
        for pRow in self.iterateRows():
            print(''.join(pRow))

    def Search(self):
        iLeft = self._iByteIndex
        iRight = self._iSzBytes
        while iLeft < iRight:
            iNext = (iRight + iLeft) // 2
            iDiff = iNext - self._iByteIndex
            if iDiff > 0:
                self.__corrupt(iDiff)
            elif iDiff < 0:
                self.__uncorrupt(-iDiff)
            iResult = self.Solve()
            if iResult > 0:
                iLeft = self._iByteIndex + 1
            elif iResult < 0:
                iRight = self._iByteIndex
        return ','.join([str(i) for i in self._pBytes[self._iByteIndex]])

def Alg1(sFileName):
    pMap = XMemMap(sFileName)
    pMap.Corrupt()
    return pMap.Solve()

def Alg2(sFileName):
    pMap = XMemMap(sFileName)
    return pMap.Search()

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()