import sys
from utils.AocController import AocController
from utils.Map2D.Map2D import Map2D
from utils.UnionFind.UnionFind import UnionFind

class XRegion(object):

    def __init__(self, sName):
        self._sName = sName
        self._iArea = 0
        self._iPerimeter = 0

    def getName(self):
        return self._sName
    
    def getArea(self):
        return self._iArea
    
    def getPerimeter(self):
        return self._iPerimeter
    
    def incrementArea(self):
        self._iArea += 1

    def incrementPerimeter(self):
        self._iPerimeter += 1

    def getPrice(self):
        return self._iArea * self._iPerimeter
    
    def merge(self, pOther):
        if not isinstance(pOther, XRegion):
            raise Exception("XRegion:merge:Cannot merge XRegion object with (object Object)")
        if self._sName != pOther.getName():
            raise Exception("XRegion:merge:Cannot merge XRegion objects with different name")
        self._iArea += pOther.getArea()
        self._iPerimeter += pOther.getPerimeter()

class XRegionIndex(object):

    def __init__(self):
        self._pIndex = {}
        self._pUnionFind = UnionFind()

    def addNewArea(self, sName, iRow, iCol):
        parentKey = self._getOrCreateRegionParentKey(sName, iRow, iCol)
        self._pIndex[sName][parentKey].incrementArea()

    def _getOrCreateRegionParentKey(self, sName, iRow, iCol):
        if sName == None:
            return
        if not self._pUnionFind.Exists((iRow, iCol)):
            self._pUnionFind.Append((iRow, iCol))
        if sName not in self._pIndex:
            self._pIndex[sName] = {}
        parentKey = self.__getParentKey((iRow, iCol))
        if parentKey not in self._pIndex[sName]:
            self._pIndex[sName][parentKey] = self._makeRegion(sName)
        return parentKey
    
    def __getParentKey(self, key):
        return self._pUnionFind.Find(key)
    
    def _makeRegion(self, sName):
        return XRegion(sName)

    def addPerimeter(self, sName, iRow, iCol):
        parentKey = self._getOrCreateRegionParentKey(sName, iRow, iCol)
        self._pIndex[sName][parentKey].incrementPerimeter()

    def addFence(self, sName, iRow, iCol, sNeighborName, iNeighborRow, iNeighborCol):
        if sName != None:
            self.addPerimeter(sName, iRow, iCol)
        if sNeighborName != None:
            self.addPerimeter(sNeighborName, iNeighborRow, iNeighborCol)

    def getTotalPrice(self):
        iSum = 0
        for sName in self._pIndex.keys():
            pRegionKeys = {}
            for key in self._pIndex[sName].keys():
                parentKey = self._pUnionFind.Find(key)
                if parentKey not in pRegionKeys:
                    pRegionKeys[parentKey] = ''
                    iSum += self._pIndex[sName][parentKey].getPrice()
        return iSum
    
    def union(self, sName, iRow, iCol, iOtherRow, iOtherCol):
        parentKey = self.__getParentKey((iRow, iCol))
        otherParentKey = self.__getParentKey((iOtherRow, iOtherCol))
        self._pUnionFind.Union((iRow, iCol), (iOtherRow, iOtherCol))
        self.__mergeToParent(sName, parentKey)
        self.__mergeToParent(sName, otherParentKey)

    def __mergeToParent(self, sName, key):
        parentKey = self.__getParentKey(key)
        if parentKey != key:
            pParentRegion = self._pIndex[sName][parentKey]
            pChildRegion = self._pIndex[sName][key]
            pParentRegion.merge(pChildRegion)
            self._pIndex[sName][key] = None

def Alg1(sFileName):
    pMap = Map2D(sFileName)
    pRegionIndex = XRegionIndex()
    return countRegions(pMap, pRegionIndex)

def countRegions(pMap:Map2D, pRegionIndex: XRegionIndex):
    cWestNeighborName = None
    sNorthNeighborRow = None
    iSzRow = pMap.getXLength()
    for iRow in range(pMap.getYLength() + 1):
        sRow = pMap.getRow(iRow) if iRow < pMap.getYLength() else None
        for iCol in range(iSzRow + 1):
            cName = sRow[iCol] if iCol < iSzRow and sRow != None else None
            if cName != None:
                pRegionIndex.addNewArea(cName, iRow, iCol)
            cNorthNeighborName = sNorthNeighborRow[iCol] if iCol < iSzRow and sNorthNeighborRow != None else None
            addNorthNeighbor(pRegionIndex, cName, iRow, iCol, cNorthNeighborName)
            addWestNeighbor(pRegionIndex, cName, iRow, iCol, cWestNeighborName)
            cWestNeighborName = cName
        sNorthNeighborRow = sRow
    return pRegionIndex.getTotalPrice()

def addNorthNeighbor(pRegionIndex, cName, iRow, iCol, cNeighborName):
    addNeighbor(pRegionIndex, cName, iRow, iCol, cNeighborName, iRow - 1, iCol)

def addWestNeighbor(pRegionIndex, cName, iRow, iCol, cNeighborName):
    addNeighbor(pRegionIndex, cName, iRow, iCol, cNeighborName, iRow, iCol - 1)

def addNeighbor(pRegionIndex, cName, iRow, iCol, cNeighborName, iNeighborRow, iNeighborCol):
    if cName == None and cNeighborName == None:
        return
    elif cName == cNeighborName:
        pRegionIndex.union(cName, iRow, iCol, iNeighborRow, iNeighborCol)
    else:
        pRegionIndex.addFence(cName, iRow, iCol, cNeighborName, iNeighborRow, iNeighborCol)

class XDiscountRegion(XRegion):

    def __init__(self, sName):
        super().__init__(sName)
        self._pSideUnionFind = UnionFind()

    # Override
    def getPrice(self):
        return self.getArea() * self.getSideCount()
    
    def getSideCount(self):
        iCount = 0
        for key in self._pSideUnionFind.IterateSets():
            iCount += 1
        return iCount

    def addSide(self, iRow, iCol, iRowDiff, iColDiff):
        bIsVerticalEdge = self.__isVerticalEdge(iRowDiff, iColDiff)
        bIsPositiveBind = self.__isPositiveBind(iRowDiff, iColDiff)
        if iRowDiff > 0:
            iRow += 1
        if iColDiff > 0:
            iCol += 1
        self.__addSide(iRow, iCol, bIsVerticalEdge, bIsPositiveBind)
        
    # Private
    def __isVerticalEdge(self, iRowDiff, iColDiff):
        if iRowDiff != 0 and iColDiff == 0:
            return False
        elif iRowDiff == 0 and iColDiff != 0:
            return True
        else:
            raise Exception("XDiscountRegion:__isVerticalEdge:Row and column offset cannot be both zero or both non-zero")
        
    # Private
    def __isPositiveBind(self, iRowDiff, iColDiff):
        return iRowDiff > 0 or iColDiff > 0
        
    # Private
    def __addSide(self, iRow, iCol, bIsVerticalEdge, bPositiveBind):
        key = self.__getKey(iRow, iCol, bIsVerticalEdge, bPositiveBind)
        if not self._pSideUnionFind.Exists(key):
            self._pSideUnionFind.Append(key)
        self.__mergeKeys(key, iRow, iCol, bIsVerticalEdge, bPositiveBind)

    # Private
    def __getKey(self, iRow, iCol, bIsVerticalEdge, bPositiveBind):
        if bIsVerticalEdge:
            if bPositiveBind:
                return (iRow, iCol, '|+')
            else:
                return (iRow, iCol, '|-')
        else:
            if bPositiveBind:
                return (iRow, iCol, '-+')
            else:
                return (iRow, iCol, '--')

    # Private
    def __mergeKeys(self, key, iRow, iCol, bIsVerticalEdge, bPositiveBind):
        mergeKey = self.__getUpperMergeKey(iRow, iCol, bIsVerticalEdge, bPositiveBind)
        if self._pSideUnionFind.Exists(mergeKey):
            self._pSideUnionFind.Union(key, mergeKey)
        mergeKey = self.__getLowerMergeKey(iRow, iCol, bIsVerticalEdge, bPositiveBind)
        if self._pSideUnionFind.Exists(mergeKey):
            self._pSideUnionFind.Union(mergeKey, key)

    # Private
    def __getUpperMergeKey(self, iRow, iCol, bIsVerticalEdge, bPositiveBind):
        if bIsVerticalEdge:
            return self.__getKey(iRow + 1, iCol, bIsVerticalEdge, bPositiveBind)
        else:
            return self.__getKey(iRow, iCol + 1, bIsVerticalEdge, bPositiveBind)

    # Private
    def __getLowerMergeKey(self, iRow, iCol, bIsVerticalEdge, bPositiveBind):
        if bIsVerticalEdge:
            return self.__getKey(iRow - 1, iCol, bIsVerticalEdge, bPositiveBind)
        else:
            return self.__getKey(iRow, iCol - 1, bIsVerticalEdge, bPositiveBind)

     # Override   
    def merge(self, pOther):
        if not isinstance(pOther, XDiscountRegion):
            raise Exception("XRegion:merge:Cannot merge XDiscountRegion object with (object Object)")
        super().merge(pOther)
        for key, value in pOther.__iterateKeys():
            if not self._pSideUnionFind.Exists(value):
                self.__addSideKey(value)
            if not self._pSideUnionFind.Exists(key):
                self.__addSideKey(key)
            self._pSideUnionFind.Union(value, key)

    # Private
    def __iterateKeys(self):
        for key in self._pSideUnionFind.iterateKeys():
            yield key, self._pSideUnionFind.Find(key)

    # Private
    def __addSideKey(self, key):
        self.__addSide(key[0], key[1], key[2][0] == '|', key[2][1] == '+')

class XDiscountRegionIndex(XRegionIndex):

    def __init__(self):
        super().__init__()

    # Override
    def _makeRegion(self, sName):
        return XDiscountRegion(sName)

    def addFence(self, sName, iRow, iCol, sNeighborName, iNeighborRow, iNeighborCol):
        super().addFence(sName, iRow, iCol, sNeighborName, iNeighborRow, iNeighborCol)
        if sName != None:
            self.addSide(sName, iRow, iCol, iNeighborRow - iRow, iNeighborCol - iCol)
        if sNeighborName != None:
            self.addSide(sNeighborName, iNeighborRow, iNeighborCol, iRow - iNeighborRow, iCol - iNeighborCol)
    
    def addSide(self, sName, iRow, iCol, iRowDiff, iColDiff):
        parentKey = self._getOrCreateRegionParentKey(sName, iRow, iCol)
        self._pIndex[sName][parentKey].addSide(iRow, iCol, iRowDiff, iColDiff)

def Alg2(sFileName):
    pMap = Map2D(sFileName)
    pRegionIndex = XDiscountRegionIndex()
    return countRegions(pMap, pRegionIndex)

def __main__():
    c = AocController(sys.argv, Alg1, Alg2)
    c.Execute()

if __name__ == "__main__":
    __main__()