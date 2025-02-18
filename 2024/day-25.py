import sys
from utils.AocController import AocController

class XKeyMaster:
   
    def __init__(self, sRawText):
        pKeys = {}
        pLocks = {}
        self.__initKeyMaster(sRawText, pKeys, pLocks)
        self._pKeys = pKeys
        self._pLocks = pLocks
       
    def __initKeyMaster(self, sRawText, pKeys, pLocks):
        for sConfig in sRawText.split('\n\n'):
            self.__addConfig(sConfig, pKeys, pLocks)
   
    def __addConfig(self, sConfig, pKeys, pLocks):
        pLines = sConfig.split('\n')
        iSzLines = len(pLines)
        bIsLock = pLines[0] == '#####'
        iStartIdx = 1
        iEndIdx = iSzLines - 1
        iOutput = 0
        iBaseFlag = 0x1
        for sLine in pLines[iStartIdx:iEndIdx]:
            iFlag = iBaseFlag
            for cSprite in sLine:
                if cSprite == '#':
                    iOutput |= iFlag
                iFlag <<= iSzLines
            iBaseFlag <<= 1
        if bIsLock:
            pLocks[iOutput] = ''
        else:
            pKeys[iOutput] = ''
           
    def CountPairs(self):
        iCount = 0
        for iKey in self._pKeys:
            for iLock in self._pLocks:
                iCount += 1 if iKey & iLock == 0 else 0
        return iCount

def Alg1(sFileName):
    with open(sFileName, 'r') as f:
        sRawText = f.read()
    pKeyMaster = XKeyMaster(sRawText=sRawText)
    return pKeyMaster.CountPairs()

def Alg2(sFileName):
    pass

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()