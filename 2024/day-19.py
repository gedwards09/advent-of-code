import sys
from utils.AocController import AocController

class XTowelDesigner:

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            pParts = f.read().split('\n\n')
        self._pTokens = self.__initTokens(pParts[0])
        self._pWords = self.__initWords(pParts[1])

    def __initTokens(self, sPart):
        return sPart.split(', ')
    
    def __initWords(self, sPart):
        return sPart.split('\n')
    
    def CountValidWords(self):
        pDict = self._initDictionary()
        iCount = 0
        for sWord in self._pWords:
            iCount += self._validWordCount(sWord, pDict)
        return iCount

    def _initDictionary(self):
        return {sToken:'' for sToken in self._pTokens}
        
    def _validWordCount(self, sWord, pDict):
        if len(sWord) == 0:
            return 1
        if sWord in pDict:
            return 1
        for iIdx in range(len(sWord)):
            if sWord[:iIdx+1] in pDict and self._validWordCount(sWord[iIdx+1:], pDict) == 1:
                pDict[sWord[iIdx+1:]] = ''
                return 1
        return 0
    
class XTowelComboDesigner(XTowelDesigner):

    # Override
    def CountValidWords(self):
        pTokenDict = super()._initDictionary()
        pCountDict = {}
        for sToken in self._pTokens:
            _ = self.__validWordCount(sToken, pTokenDict, pCountDict)
        iCount = 0
        for sWord in self._pWords:
            iCount += self.__validWordCount(sWord, pTokenDict, pCountDict)
        return iCount

    def __validWordCount(self, sToken, pTokenDict, pCountDict):
        if len(sToken) == 0:
            return 1
        if sToken in pCountDict:
            return pCountDict[sToken]
        iTotal = 0
        for iIdx in range(len(sToken)):
            sLeft = sToken[:iIdx+1]
            sRight = sToken[iIdx+1:]
            if sLeft in pTokenDict:
                iTotal += self.__validWordCount(sRight, pTokenDict, pCountDict)
        pCountDict[sToken] = iTotal
        return iTotal

def Alg1(sFileName):
    pDesigner = XTowelDesigner(sFileName)
    return pDesigner.CountValidWords()

def Alg2(sFileName):
    pDesigner = XTowelComboDesigner(sFileName)
    return pDesigner.CountValidWords()

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()