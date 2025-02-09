import sys
from utils.AocController import AocController

class XNumberGenerator:

    g_iPruneConstant = 0xFFFFFF

    def Generate(iInt, iTimes = 1):
        for _ in range(iTimes):
            iInt = XNumberGenerator.GetNextInt(iInt)
        return iInt

    def GetNextInt(iInt):
        iInt = XNumberGenerator.Step1(iInt)
        iInt = XNumberGenerator.Step2(iInt)
        iInt = XNumberGenerator.Step3(iInt)
        return iInt

    def Step1(iInt):
        iInt = XNumberGenerator.Mix(iInt, iInt << 6)
        return XNumberGenerator.Prune(iInt)
    
    def Step2(iInt):
        iInt = XNumberGenerator.Mix(iInt, iInt >> 5)
        return XNumberGenerator.Prune(iInt)
    
    def Step3(iInt):
        iInt = XNumberGenerator.Mix(iInt, iInt << 11)
        return XNumberGenerator.Prune(iInt)

    def Mix(iInt, iVal):
        return iInt ^ iVal
    
    def Prune(iInt):
        return iInt & XNumberGenerator.g_iPruneConstant
    
class XPriceMaximizer:

    g_iSzQueue = 4

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            self._pNumbers = [int(iInt) for iInt in f.read().split('\n')]
        self._pBananaCache = {}

    def Solve(self, iTimes=2000):
        for iInt in self._pNumbers:
            self.__generateSequences(iInt, iTimes)
        return self.__getMaxBananas()

    def __generateSequences(self, iInt, iTimes):
        iStartIdx = -(XPriceMaximizer.g_iSzQueue)
        pQueue = self.__initQueue(iTimes)
        pUsed = {}
        iPrice = self.__getPrice(iInt)
        for _ in range(iTimes):
            iNew = XNumberGenerator.GetNextInt(iInt)
            iNewPrice = self.__getPrice(iNew)
            pQueue[iStartIdx+4] = str(iNewPrice - iPrice)
            iStartIdx += 1
            if iStartIdx >= 0:
                sKey = self.__makeKey(pQueue, iStartIdx)
                if sKey not in pUsed:
                    self.__addBananas(sKey, iNewPrice)
                    pUsed[sKey] = ''
            iInt = iNew
            iPrice = iNewPrice

    def __initQueue(self, iTimes):
        return [None for _ in range(iTimes)]

    def __getPrice(self, iInt):
        return iInt % 10

    def __makeKey(self, pQueue, iStartIdx):
        return ','.join(pQueue[iStartIdx:iStartIdx+XPriceMaximizer.g_iSzQueue])
    
    def __addBananas(self, sKey, iPrice):
        if sKey not in self._pBananaCache:
            self._pBananaCache[sKey] = iPrice
        else:
            self._pBananaCache[sKey] += iPrice

    def __getMaxBananas(self):
        iMax = 0
        for sKey in self._pBananaCache:
            iCur = self._pBananaCache[sKey]
            if iCur > iMax:
                iMax = iCur
        return iMax

def Alg1(sFileName):
    iSum = 0
    with open(sFileName, 'r') as f:
        for sLine in f.read().split('\n'):
            iInt = int(sLine)
            iSum += XNumberGenerator.Generate(iInt, 2000)
    return iSum

def Alg2(sFileName):
    priceMaximizer = XPriceMaximizer(sFileName)
    return priceMaximizer.Solve()

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()