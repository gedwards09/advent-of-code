from utils.Map2D.Map2D import Map2D

class MazeMap(Map2D):

    g_cStartSprite = 'S'
    g_cEndSprite = 'E'
    g_cWallSprite = '#'

    def __init__(self, sFileName='', sRawText=''):
        super().__init__(sFileName=sFileName, sRawText=sRawText)
        tStart, tEnd = self._initStartAndEndPositions()
        self._tStart = tStart
        self._tEnd = tEnd
    
    def _initStartAndEndPositions(self):
        tStart = None
        tEnd = None
        for iRow in range(self.getYLength()):
            sRow = self.getRow(iRow)
            for iCol in range(self.getXLength()):
                if sRow[iCol] == MazeMap.g_cStartSprite:
                    tStart = (iRow, iCol)
                    if tEnd != None:
                        return tStart, tEnd
                elif sRow[iCol] == MazeMap.g_cEndSprite:
                    tEnd = (iRow, iCol)
                    if tStart != None:
                        return tStart, tEnd
                    
    def getStart(self):
        return self._tStart
    
    def getEnd(self):
        return self._tEnd
    
    def GetWallSprite():
        return MazeMap.g_cWallSprite
    
    def GetEndSprite():
        return MazeMap.g_cEndSprite