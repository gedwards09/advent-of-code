class Int2DArray:

    def __init__(self, sFileName):
        self._array = Int2DArray._parse(sFileName)
        self._iXLength = len(self._array[0])
        self._iYLength = len(self._array)

    def _parse(sFileName):
        with open(sFileName,'r') as f:
            return [[int(el) for el in line.split()]\
                    for line in f.read().split('\n')]
        
    def getXLength(self):
        return self._iXLength
    
    def getYLength(self):
        return self._iYLength
    
    def get(self, iRowNum, iColNum):
        return self._array[iRowNum][iColNum]
        
    def Transpose(self):
        self._array =  [[int(self._array[iRowNum][iColNum])\
                         for iRowNum in range(self._iYLength)]\
                        for iColNum in range(self._iXLength)]
        tmp = self._iXLength
        self._iXLength = self._iYLength
        self._iYLength = tmp

    def getRow(self, iRowNum):
        return self._array[iRowNum]
