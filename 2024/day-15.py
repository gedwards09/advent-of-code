import sys
from utils.AocController import AocController
from utils.Map2D.CharMap2D import CharMap2D

class XWarehouse(CharMap2D):

    g_cBoxSprite = 'O'
    g_cDownSprite = 'v'
    g_cEmptySprite = '.'
    g_cLeftSprite = '<'
    g_cRightSprite = '>'
    g_cRobotSprite = '@'
    g_cUpSprite = '^'
    g_cWallSprite = '#'

    def __init__(self, sRawText, sInstructions):
        super().__init__(sRawText=sRawText)
        self._sInstructions = sInstructions
        self._tInitialPosition = self._initInitialPosition()
    
    def _initInitialPosition(self):
        for iRow in range(self.getYLength()):
            sRow = self.getRow(iRow)
            for iCol in range(self.getXLength()):
                c = sRow[iCol]
                if c == XWarehouse.g_cRobotSprite:
                    # self._set(iRow, iCol, '.')
                    return (iRow, iCol)
                
    def Execute(self):
        iRow, iCol = self._tInitialPosition
        for cInstruction in self._sInstructions:
            if cInstruction == '\n':
                continue
            iRowDiff, iColDiff = self.getCoordinateChange(cInstruction)
            if self._moveIfAble(iRow, iCol, iRowDiff, iColDiff):
                self._set(iRow, iCol, XWarehouse.g_cEmptySprite)
                iRow += iRowDiff
                iCol += iColDiff
                self._set(iRow, iCol, XWarehouse.g_cRobotSprite)

    def _moveIfAble(self, iRow, iCol, iRowDiff, iColDiff):
        iStep = 1
        cSprite = self.get(iRow + iStep * iRowDiff, iCol + iStep * iColDiff)
        while cSprite != XWarehouse.g_cEmptySprite and cSprite != XWarehouse.g_cWallSprite:
            iStep += 1
            cSprite = self.get(iRow + iStep * iRowDiff, iCol + iStep * iColDiff)
        if cSprite == XWarehouse.g_cEmptySprite:
            self._doMove(iRow, iCol, iRowDiff, iColDiff, iStep)
        return cSprite == XWarehouse.g_cEmptySprite
    
    def _doMove(self, iRow, iCol, iRowDiff, iColDiff, iSteps):
        if self.get(iRow + iRowDiff, iCol + iColDiff) == XWarehouse.g_cBoxSprite:
            self._set(iRow + iSteps * iRowDiff, iCol + iSteps * iColDiff, XWarehouse.g_cBoxSprite)
            self._set(iRow + iRowDiff, iCol + iColDiff, XWarehouse.g_cEmptySprite)

    def GetPositionChecksum(self):
        iSum = 0
        for iRow in range(self.getYLength()):
            pRow = self.getRow(iRow)
            for iCol in range(self.getXLength()):
                if self._isBoxSprite(pRow[iCol]):
                    iSum += self._getChecksum(iRow, iCol)
        return iSum
    
    def _isBoxSprite(self, cSprite):
        return cSprite == XWarehouse.g_cBoxSprite
    
    def _getChecksum(self, iRow, iCol):
        return 100 * iRow + iCol
    
    def getCoordinateChange(self, cSprite):
        iRow = 0
        iCol = 0
        if cSprite == XWarehouse.g_cDownSprite:
            iRow = 1
        elif cSprite == XWarehouse.g_cLeftSprite:
            iCol = -1
        elif cSprite == XWarehouse.g_cRightSprite:
            iCol = 1
        elif cSprite == XWarehouse.g_cUpSprite:
            iRow = -1
        return iRow, iCol
    
    def Print(self):
        for iRow in range(self.getYLength()):
            print(''.join(self.getRow(iRow)))

    def GetBoxSprite():
        return XWarehouse.g_cBoxSprite
    
    def GetEmptySprite():
        return XWarehouse.g_cEmptySprite
    
    def GetRobotSprite():
        return XWarehouse.g_cRobotSprite

    def GetWallSprite():
        return XWarehouse.g_cWallSprite

class XDoubleWarehouse(XWarehouse):

    g_cLeftBoxSprite = '['
    g_cRightBoxSprite = ']'

    def __init__(self, sRawText, sInstructions):
        sRawText = ''.join([XDoubleWarehouse.__translateSprite(cSprite) for cSprite in sRawText])
        super().__init__(sRawText, sInstructions)

    def __translateSprite(cSprite):
        if cSprite == XWarehouse.GetBoxSprite():
            return XDoubleWarehouse.g_cLeftBoxSprite + XDoubleWarehouse.g_cRightBoxSprite
        elif cSprite == XWarehouse.GetEmptySprite():
            return XWarehouse.GetEmptySprite() + XWarehouse.GetEmptySprite()
        elif cSprite == XWarehouse.GetRobotSprite():
            return XWarehouse.GetRobotSprite() + XWarehouse.GetEmptySprite()
        elif cSprite == XWarehouse.GetWallSprite():
            return XWarehouse.GetWallSprite() + XWarehouse.GetWallSprite()
        else:
            return cSprite

    # Override
    def _moveIfAble(self, iRow, iCol, iRowDiff, iColDiff):
        if iColDiff != 0:
            return super()._moveIfAble(iRow, iCol, iRowDiff, iColDiff)
        
        cSprite = self.get(iRow + iRowDiff, iCol + iColDiff)
        if cSprite == XWarehouse.GetEmptySprite():
            return True 
        elif cSprite == XWarehouse.GetWallSprite():
            return False
        elif cSprite == XDoubleWarehouse.g_cRightBoxSprite:
            # to set column to the left box column
            iColDiff = -1

        if self.__moveBoxIfAbleRow(iRow + iRowDiff, iCol + iColDiff, iRowDiff):
            self._set(iRow, iCol, XWarehouse.GetEmptySprite())
            return True
        return False

    def __moveBoxIfAbleRow(self, iRow, iCol, iRowDiff):
        if self.__rCanMove(iRow, iCol, iRowDiff):
            self.__rDoMove(iRow, iCol, iRowDiff)
            return True
        return False

    def __rCanMove(self, iRow, iCol, iRowDiff):
        # Check Left
        cSprite = self.get(iRow + iRowDiff, iCol)
        if cSprite == XWarehouse.GetWallSprite():
            return False
        elif cSprite == XDoubleWarehouse.g_cLeftBoxSprite and not self.__rCanMove(iRow + iRowDiff, iCol, iRowDiff):
            return False
        elif cSprite == XDoubleWarehouse.g_cRightBoxSprite and not self.__rCanMove(iRow + iRowDiff, iCol - 1, iRowDiff):
            return False
        # Check Right
        cSprite = self.get(iRow + iRowDiff, iCol + 1)
        if cSprite == XWarehouse.GetWallSprite():
            return False
        elif cSprite == XDoubleWarehouse.g_cLeftBoxSprite and not self.__rCanMove(iRow + iRowDiff, iCol + 1, iRowDiff):
            return False
            # No need to check for right box sprite
        # Success
        return True

    def __rDoMove(self, iRow, iCol, iRowDiff):
        # Move Left
        cSprite = self.get(iRow + iRowDiff, iCol)
        if cSprite == XDoubleWarehouse.g_cLeftBoxSprite:
            self.__rDoMove(iRow + iRowDiff, iCol, iRowDiff)
        elif cSprite == XDoubleWarehouse.g_cRightBoxSprite:
            self.__rDoMove(iRow + iRowDiff, iCol - 1, iRowDiff)
        # Move Right
        cSprite = self.get(iRow + iRowDiff, iCol + 1)
        if cSprite == XDoubleWarehouse.g_cLeftBoxSprite:
            self.__rDoMove(iRow + iRowDiff, iCol + 1, iRowDiff)
            # no need to handle right box sprite
        # Do Move
        self._set(iRow + iRowDiff, iCol, XDoubleWarehouse.g_cLeftBoxSprite)
        self._set(iRow + iRowDiff, iCol + 1, XDoubleWarehouse.g_cRightBoxSprite)
        self._set(iRow, iCol, XWarehouse.GetEmptySprite())
        self._set(iRow, iCol + 1, XWarehouse.GetEmptySprite())

    # Override
    def _doMove(self, iRow, iCol, iRowDiff, iColDiff, iSteps):
        for iStep in range(iSteps, 0, -1):
            cSprite = self.get(iRow + (iStep - 1) * iRowDiff, iCol + (iStep - 1) * iColDiff)
            self._set(iRow + iStep * iRowDiff, iCol + iStep * iColDiff, cSprite)
        self._set(iRow, iCol, XWarehouse.GetEmptySprite())

    # Override
    def _isBoxSprite(self, cSprite):
        return cSprite == XDoubleWarehouse.g_cLeftBoxSprite

def Alg1(sFileName):
    with open(sFileName, 'r')as f:
        pPieces = f.read().split('\n\n')
        pWarehouse = XWarehouse(sRawText=pPieces[0], sInstructions=pPieces[1])
    return doAlg(pWarehouse)

def doAlg(pWarehouse):
    pWarehouse.Execute()
    return pWarehouse.GetPositionChecksum()

def Alg2(sFileName):
    with open(sFileName, 'r')as f:
        pPieces = f.read().split('\n\n')
        pWarehouse = XDoubleWarehouse(sRawText=pPieces[0], sInstructions=pPieces[1])
    return doAlg(pWarehouse)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()