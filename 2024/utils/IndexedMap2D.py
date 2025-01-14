from utils.Map2D import Map2D

class IndexedMap2D(Map2D):

    def __init__(self, sFileName='', sRawText='', cDelim=''):
        super().__init__(sFileName, sRawText, cDelim)
        self._pIndex = self._initIndex()

    def _initIndex(self):
        pIndex = {}
        for iRowNum in range(self.getYLength()):
            pRow = self._map[iRowNum]
            for iColNum in range(self.getXLength()):
                pc = pRow[iColNum]
                if pc not in pIndex:
                    pIndex[pc] = [(iRowNum, iColNum)]
                else:
                    pIndex[pc].append((iRowNum, iColNum))
        return pIndex
    
    def iterateCoordinates(self, element):
        if not self.contains(element):
            raise Exception('IndexedMap2d.py:iterateCoordinates:element not found in index')
        for coordinate in self._pIndex[element]:
            yield coordinate

    def contains(self, element):
        return element in self._pIndex
