import sys
from utils.AocController import AocController

class XRobot:

    def __init__(self, sRawConfigText):
        pConfig = self.__parse(sRawConfigText)
        self._iXInit = pConfig[0][0]
        self._iYInit = pConfig[0][1]
        self._iXCoord = self._iXInit
        self._iYCoord = self._iYInit
        self._tVelocity = pConfig[1]

    def __parse(self, sConfigText):
        pArray = sConfigText.split(' ')
        return [[int(s) for s in XRobot.__splitPiece(pPiece)] for pPiece in pArray]
    
    def __splitPiece(pPiece):
        return pPiece.split('=')[1].split(',')
    
    def getPosition(self):
        return (self._iXCoord, self._iYCoord)
    
    def Reset(self):
        self._iXCoord = self._iXInit
        self._iYCoord = self._iYInit
    
    def Advance(self, iSteps, iXBound=None, iYBound=None):
        self._iXCoord += iSteps * self._tVelocity[0]
        self._iYCoord += iSteps * self._tVelocity[1]
        self._iXCoord %= iXBound
        self._iYCoord %= iYBound
    

class XFloorSpace:

    g_iNumberOfSteps = 100

    def __init__(self, sFileName):
        with open(sFileName, 'r') as f:
            pLines = f.read().split('\n')
        pBounds = self.__initBounds(pLines[0])
        self._iXLength = pBounds[0]
        self._iYLength = pBounds[1]
        self._pRobots = self.__initRobots(pLines[1:])
        self._pPositions = self.__initPositions()

    def __initBounds(self, sLine):
        return [int(s) for s in sLine.split(',')]

    def __initRobots(self, pLines):
        return [XRobot(sLine) for sLine in pLines]
    
    def __initPositions(self):
        pPositions = {}
        for pRobot in self._pRobots:
            pPositions[pRobot.getPosition()] = ''
        return pPositions
    
    def Reset(self):
        for pRobot in self._pRobots:
            pRobot.Reset()
        
    def AdvanceRobots(self, iSteps=None):
        if iSteps == None:
            iSteps = XFloorSpace.__getNumberOfSteps()
        pPositions = {}
        for pRobot in self._pRobots:
            pRobot.Advance(iSteps, iXBound = self._iXLength, iYBound = self._iYLength)
            pPositions[pRobot.getPosition()] = ''
        self._pPositions = pPositions

    def __getNumberOfSteps():
        return XFloorSpace.g_iNumberOfSteps
    
    def GetRobotQuadrantCountProduct(self):
        iProduct = 1
        for iCount in self.__getRobotQuadrantCount():
            iProduct *= iCount
        return iProduct
    
    def __getRobotQuadrantCount(self):
        pQuadrantCount = [0 for _ in range(4)]
        for pRobot in self._pRobots:
            tCoord = pRobot.getPosition()
            iQuadrantId = self.__getQuadrantId(tCoord)
            if iQuadrantId != None:
                pQuadrantCount[iQuadrantId] += 1
        return pQuadrantCount

    # Quadrant ID: 0 | 1
    #              - | -
    #              2 | 3
    def __getQuadrantId(self, tCoord):
        iTwiceX = 2 * tCoord[0]
        iTwiceY = 2 * tCoord[1]
        if iTwiceX == self._iXLength - 1 or iTwiceY == self._iYLength - 1:
            return None
        return 1 * (2 * tCoord[0]  > self._iXLength) + 2 * (2 * tCoord[1] > self._iYLength)
    
    def Print(self):
        for iRow in range(self._iYLength):
            s = ''.join(['#' if (iCol, iRow) in self._pPositions else ' ' for iCol in range(self._iXLength)])
            print(s)

    def GetMaxConnectivityStepNumber(self, bPrint=False):
        iMaxConnectivity = 0
        iMaxStepNumber = 0
        for iStep in range(self._iXLength * self._iYLength):
            iConnectivity = self.__getConnectivityRating()
            if iConnectivity > iMaxConnectivity:
                iMaxConnectivity = iConnectivity
                iMaxStepNumber = iStep
            self.AdvanceRobots(iSteps=1)
        if bPrint:
            self.Reset()
            self.AdvanceRobots(iSteps=iMaxStepNumber)
            self.Print()
        return iMaxStepNumber


    def __getConnectivityRating(self):
        iRating = 0
        for tCoord in self._pPositions.keys():
            for tNeighborCoord in XFloorSpace.__iterateNeighborCoords(tCoord):
                if tNeighborCoord in self._pPositions:
                    iRating += 1
        return iRating

    def __iterateNeighborCoords(tCoord):
        for iRowDiff in range(-1, 2):
            for iColDiff in range (-1, 2):
                if iRowDiff == 0 and iColDiff == 0:
                    continue
                yield (tCoord[0] + iColDiff, tCoord[1] + iRowDiff)


def Alg1(sFileName):
    pFloorSpace = XFloorSpace(sFileName)
    pFloorSpace.AdvanceRobots()
    return pFloorSpace.GetRobotQuadrantCountProduct()

def Alg2(sFileName):
    pFloorSpace = XFloorSpace(sFileName)
    return pFloorSpace.GetMaxConnectivityStepNumber(bPrint=False)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()