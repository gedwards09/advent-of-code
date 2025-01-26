from utils.UnionFind.IUnionFind import IUnionFind

class UnionFind(IUnionFind):

    def __init__(self):
        self._pSet = {}

    # Override
    def Append(self, vData):
        if not self.Exists(vData):
            self._pSet[vData] = vData

    # Override
    def Exists(self, vData):
        return vData in self._pSet
    
    # Override
    def Find(self, vData):
        vParent = self._pSet[vData]
        if vParent == vData:
                return vData
        self._pSet[vData] = self.Find(vParent)
        return self._pSet[vData]

    # Override
    def Union(self, vData, vOther):
        if not self.Exists(vData) or not self.Exists(vOther):
            raise Exception("UnionFind.py:union:Cannot union elements that are not in the set")
        
        vDataParent = self.Find(vData)
        vOtherParent = self.Find(vOther)

        if vDataParent != vOtherParent:
            self._pSet[vOtherParent] = vDataParent

    def iterateKeys(self):
        for key in self._pSet:
            yield key

    def IterateSets(self):
        pParentKeys = {}
        for key in self._pSet.keys():
            parentKey = self.Find(key)
            if parentKey not in pParentKeys:
                pParentKeys[parentKey] = ''
                yield parentKey
            
    

    