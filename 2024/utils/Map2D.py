class Map2D:

    def __init__(self, sFileName):
        self._map = self._initMap(sFileName)
        self._iXLength = self._initXLength()
        self._iYLength = self._initYLength()

    def _initMap(self, sFileName):
        with open(sFileName, 'r') as file:
            return [line for line in file.read().split('\n')]
        
    def _initXLength(self):
        return len(self._map[0])
    
    def _initYLength(self):
        return len(self._map)
    
    def getXLength(self):
        return self._iXLength
    
    def getYLength(self):
        return self._iYLength
    
    def get(self, iRowIndex: int, iColIndex: int):
        if self.isCoordValid(iRowIndex, iColIndex):
            return self._map[iRowIndex][iColIndex]
    
    def isCoordValid(self, iRowIndex: int, iColIndex: int):
        return 0 <= iRowIndex and iRowIndex < self._iYLength\
            and 0 <= iColIndex and iColIndex < self._iXLength
        
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