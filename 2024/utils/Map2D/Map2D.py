class Map2D:

    def __init__(self, sFileName = '', sRawText = '', cDelim=None):
        self._map = self._initMap(sFileName, sRawText, cDelim)
        self._iXLength = self._initXLength()
        self._iYLength = self._initYLength()

    def _initMap(self, sFileName, sRawText='', cDelim=None):
        if len(sRawText) == 0 and len(sFileName) == 0:
            raise Exception("Map2D.py:_initMap:Must specify filename or raw text input")
        elif len(sRawText) == 0:
            with open(sFileName, 'r') as file:
                return self._parseRawText(file.read(), cDelim)
        return self._parseRawText(sRawText, cDelim)
            
    def _parseRawText(self, sRawText, cDelim=None):
        if cDelim != None:
            return [line.split(cDelim) for line in sRawText.split('\n')]
        else:
            return sRawText.split('\n')
        
    def _initXLength(self):
        return len(self._map[0])
    
    def _initYLength(self):
        return len(self._map)
    
    def getXLength(self):
        return self._iXLength
    
    def getYLength(self):
        return self._iYLength
    
    def get(self, iRowIndex: int, iColIndex: int):
        if self.isValid(iRowIndex, iColIndex):
            return self._map[iRowIndex][iColIndex]
        else:
            return None
        
    def _getMap(self):
        return self._map
        
    def getRow(self, iRowIndex: int):
        if 0 <= iRowIndex and iRowIndex < self.getYLength():
            return self._map[iRowIndex]
        else:
            return None
    
    def isValid(self, iRowIndex: int, iColIndex: int):
        return 0 <= iRowIndex and iRowIndex < self._iYLength\
            and 0 <= iColIndex and iColIndex < self._iXLength
    
    def Transpose(self):
        self._map =  [[int(self._map[iRowNum][iColNum])\
                         for iRowNum in range(self._iYLength)]\
                        for iColNum in range(self._iXLength)]
        tmp = self._iXLength
        self._iXLength = self._iYLength
        self._iYLength = tmp
        
    def iterateRows(self):
        for line in self._map:
            yield line

    def iterateCols(self):
        for i in range(self._iYLength):
            yield ''.join([line[i] for line in self._map])

    def iterateDiagonals(self):
        # return the center diagonals separately so we don't return them twice
        iBound = min(self._iYLength, self._iXLength)
        # \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        yield ''.join([self._map[i][i] for i in range(iBound)])
        # /////////////////////////////////////////////////////////////
        yield ''.join([self._map[self._iYLength - 1 - i][i] for i in range(iBound)])

        for iColNum in range(1, self._iXLength):
            iBound = min(self._iXLength - iColNum, self._iYLength)
            # \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
            yield ''.join([self._map[i][iColNum + i] for i in range(iBound)])
            # /////////////////////////////////////////////////////////
            yield ''.join([self._map[self._iYLength - 1 - i][iColNum + i] for i in range(iBound)])

        for iRowNum in range(1, self._iYLength - 1):
            iBound = min(self._iYLength - iRowNum, self._iXLength)
            # \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
            yield ''.join([self._map[iRowNum + i][i] for i in range(iBound)])
            # /////////////////////////////////////////////////////////
            iBound = min(iRowNum + 1, self._iXLength)
            yield ''.join([self._map[iRowNum - i][i] for i in range(iBound)])

    def iterateNeighbors(self, iRow, iCol, iStepSize=1):
        for iStep in [-1, 1]:
            if self.isValid(iRow + iStepSize * iStep, iCol):
                yield (iRow + iStepSize * iStep, iCol, self.get(iRow + iStepSize * iStep, iCol))
            if self.isValid(iRow, iCol + iStepSize * iStep):
                yield (iRow, iCol + iStepSize * iStep, self.get(iRow, iCol + iStepSize * iStep))