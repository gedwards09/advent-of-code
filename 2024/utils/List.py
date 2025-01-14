from utils.IList import IList

class List(IList):

    def __init__(self, sRawText, cDelim=','):
        self._pArray = sRawText.split(cDelim)
        self._iLength = len(self._pArray)

    # Override
    def getLength(self):
        return self._iLength
    
    # Override
    def get(self, i: int):
        if self.isValidIndex(i):
            return self._pArray[i]
        
    # Override
    def isValidIndex(self, i: int):
        return 0 <= i and i < self._iLength
    
    # Override
    def swap(self, i: int, j: int):
        if not self.isValidIndex(i) or not self.isValidIndex(j):
            raise Exception('List.py:swap:invalid index encountered.')
        tmp = self._pArray[i]
        self._pArray[i] = self._pArray[j]
        self._pArray[j] = tmp

    # Override
    def iterate(self):
        for el in self._pArray:
            yield el