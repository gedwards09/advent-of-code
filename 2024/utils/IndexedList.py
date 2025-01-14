from utils.List import List

class IndexedList(List):

    def __init__(self, sRawText, cDelim):
        super().__init__(sRawText, cDelim)
        self._pIndex = self._initIndex(self._pArray)

    def _initIndex(self, pArray):
        pIndex = {}
        for i in range(self._iLength):
            el = self._pArray[i]
            if el in pIndex:
                pIndex[el].append(i)
            pIndex[el] = [i]
        return pIndex
    
    def iterateIndices(self, el):
        if not self.contains(el):
            raise Exception('IndexedArray.py:Element not found in index')
        for idx in self._pIndex[el]:
            yield idx

    def contains(self, el):
        return el in self._pIndex
    
    def getFirstIndex(self, element):
        if self.contains(element):
            return self._pIndex[element][0]
        
    def swap(self, i: int, j: int):
        super().swap(i, j)
        self._updateIndex(self._pArray[j], i, j)
        self._updateIndex(self._pArray[i], j, i)

    def _updateIndex(self, element, oldIdx, newIdx):
        pIndex = self._pIndex[element]
        for idx in range(len(pIndex)):
            if pIndex[idx] == oldIdx:
                pIndex[idx] = newIdx

    def print(self):
        print(self.toString())

    def toString(self):
        return ','.join(self._pArray)

