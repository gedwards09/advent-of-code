class VisitorCoordinate:

    g_bDownFlag = 1 << 0
    g_bLeftFlag = 1 << 1
    g_bRightFlag = 1 << 2
    g_bUpFlag = 1 << 3
    g_cDownSprite = 'v'
    g_cLeftSprite = '<'
    g_cRightSprite = '>'
    g_cUpSprite = '^'

    def __init__(self, iRow, iCol, cDir):
        self._iRow = iRow
        self._iCol = iCol
        self._cDir = cDir

    def getRow(self):
        return self._iRow
    
    def setRow(self, iRow):
        self._iRow = iRow
    
    def getCol(self):
        return self._iCol
    
    def setCol(self, iCol):
        self._iCol = iCol
    
    def getDir(self):
        return self._cDir
    
    def setDir(self, cDir):
        self._cDir = cDir

    def getCoord(self):
        return (self._iRow, self._iCol)
    
    def iterateNeighbors(self):
        for iDiff in range(-1, 2, 2):
            yield (self._iRow + iDiff, self._iCol)
            
            yield (self._iRow, self._iCol + iDiff)

    def GetNeighborDirection(iRowDiff, iColDiff):
        if iRowDiff == 1:
            return VisitorCoordinate.g_cDownSprite
        elif iColDiff == -1:
            return VisitorCoordinate.g_cLeftSprite
        elif iColDiff == 1:
            return VisitorCoordinate.g_cRightSprite
        elif iRowDiff == -1:
            return VisitorCoordinate.g_cUpSprite
        
    def GetDownSprite():
        return VisitorCoordinate.g_cDownSprite
    
    def GetLeftSprite():
        return VisitorCoordinate.g_cLeftSprite
    
    def GetRightSprite():
        return VisitorCoordinate.g_cRightSprite
    
    def GetUpSprite():
        return VisitorCoordinate.g_cUpSprite
    
    def GetDownFlag():
        return VisitorCoordinate.g_bDownFlag
    
    def GetLeftFlag():
        return VisitorCoordinate.g_bLeftFlag
    
    def GetRightFlag():
        return VisitorCoordinate.g_bRightFlag
    
    def GetUpFlag():
        return VisitorCoordinate.g_bUpFlag
    
    def IterateDirectionSprites():
        for cDir in [VisitorCoordinate.g_cDownSprite,\
                    VisitorCoordinate.g_cLeftSprite,\
                    VisitorCoordinate.g_cRightSprite,\
                    VisitorCoordinate.g_cUpSprite]:
            yield cDir

    def GetDirFlag(cDirSprite):
        if cDirSprite == VisitorCoordinate.g_cDownSprite:
            return VisitorCoordinate.g_bDownFlag
        elif cDirSprite == VisitorCoordinate.g_cLeftSprite:
            return VisitorCoordinate.g_bLeftFlag
        elif cDirSprite == VisitorCoordinate.g_cRightSprite:
            return VisitorCoordinate.g_bRightFlag
        elif cDirSprite == VisitorCoordinate.g_cUpSprite:
            return VisitorCoordinate.g_bUpFlag
        
    def getCoordinateChange(self):
        iRow = 0
        iCol = 0
        if self.DirFlag == VisitorCoordinate.g_bDownFlag:
            iRow = 1
        elif self.DirFlag == VisitorCoordinate.g_bLeftFlag:
            iCol = -1
        elif self.DirFlag == VisitorCoordinate.g_bRightFlag:
            iCol = 1
        elif self.DirFlag == VisitorCoordinate.g_bUpFlag:
            iRow = -1
        return iRow, iCol