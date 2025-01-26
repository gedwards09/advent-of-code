import sys
from utils.AocController import AocController


class XGame:

    g_iTokenCostButton_A = 3
    g_iTokenCostButton_B = 1

    def __init__(self, sRawConfigurationText):
        pConfiguration = sRawConfigurationText.split('\n')
        self._tButton_A = self._initButton(pConfiguration[0])
        self._tButton_B = self._initButton(pConfiguration[1])
        self._tPrize = self._initPrize(pConfiguration[2])
        # print(self._tButton_A, self._tButton_B, self._tPrize)

    def _initButton(self, sConfiguration):
        return self.__parseButton(sConfiguration)

    def __parseButton(self, sConfiguration):
        sRight = sConfiguration.split(": ")[1]
        sConfig = sRight.split(", ")
        iX = self.__parseIntConfig(sConfig[0], "X", "+")
        iY = self.__parseIntConfig(sConfig[1], "Y", "+")
        return (iX, iY)
    
    def __parseIntConfig(self, sConfig, cName, cSymbol):
        return int(sConfig.split(cName + cSymbol)[1])
    
    def _initPrize(self, sConfig):
        sRight = sConfig.split(": ")[1]
        sConfig = sRight.split(', ')
        iX = self.__parseIntConfig(sConfig[0], "X", "=")
        iY = self.__parseIntConfig(sConfig[1], "Y", "=")
        return (iX, iY)
    
    def getMinimumWinTokens(self):
        iDeterminant = self._getDeterminant()
        if iDeterminant == 0:
            return self.getMinCostLinearDependence()
        else:
            return self.getMinCostLinearIndependent(iDeterminant)

    def _getDeterminant(self):
        tA = self._tButton_A
        tB = self._tButton_B
        return tA[0] * tB[1] - tA[1] * tB[0]
    
    def getMinCostLinearDependence(self):
        raise Exception("XGame:getMinCostLinearDependence:Not Implemented")
    
    def GetCost(tTokens):
        return XGame.g_iTokenCostButton_A * tTokens[0] + XGame.g_iTokenCostButton_B * tTokens[1]
    
    def getMinCostLinearIndependent(self, iDeterminant):
        tTokens = self._getMinTokensLinearIndependent(iDeterminant)
        return XGame.GetCost(tTokens)
    
    def _getMinTokensLinearIndependent(self, iDeterminant):
        tA = self._tButton_A
        tB = self._tButton_B
        tZ = self._tPrize
        iCofactorCoeffButton_A = (tB[1] * tZ[0] - tB[0] * tZ[1])
        iCofactorCoeffButton_B = -(tA[1] * tZ[0] - tA[0] * tZ[1])
        if iCofactorCoeffButton_A % iDeterminant == 0 and iCofactorCoeffButton_B % iDeterminant == 0:
            return (iCofactorCoeffButton_A // iDeterminant, iCofactorCoeffButton_B // iDeterminant)
        return (0, 0)
    
class XGameParser:

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            self._sRawText = f.read()

    def getMinimumWinTokens(self):
        iSum = 0
        for sRawConfigurationText in self._sRawText.split('\n\n'):
            pGame = self.makeGame(sRawConfigurationText)
            iSum += pGame.getMinimumWinTokens()
        return iSum
    
    def makeGame(self, sRawConfigurationText):
        return XGame(sRawConfigurationText)
    
class XExtendedGame(XGame):

    g_iPrizeCoordinateOffset = 10000000000000

    # Override
    def _initPrize(self, sConfig):
        iX, iY = super()._initPrize(sConfig)
        return (iX + XExtendedGame.g_iPrizeCoordinateOffset, iY + XExtendedGame.g_iPrizeCoordinateOffset)
    
class XExtendedGameParser(XGameParser):

    # Override
    def makeGame(self, sRawConfigurationText):
        return XExtendedGame(sRawConfigurationText)

def Alg1(sFileName):
    pGameParser = XGameParser(sFileName)
    return pGameParser.getMinimumWinTokens()

def Alg2(sFileName):
    pGameParser = XExtendedGameParser(sFileName)
    return pGameParser.getMinimumWinTokens()

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()