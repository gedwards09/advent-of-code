class BinaryTreeNode:

    def __init__(self, vData):
        self._vData = vData
        self._pLeft = None
        self._pRight = None
        self._pParent = None

    def getData(self):
        return self._vData

    def getLeft(self):
        return self._pLeft
    
    def getRight(self):
        return self._pRight
    
    def getParent(self):
        return self._pParent
    
    def setData(self, vData):
        self._vData = vData
    
    def setLeft(self, pNode):
        self._pLeft = pNode
        pNode._setParent(self)

    def setRight(self, pNode):
        self._pRight = pNode
        pNode._setParent(self)

    # internal
    def _setParent(self, pNode):
        self._pParent = pNode

    def hasLeft(self):
        return self._pLeft == None
    
    def hasRight(self):
        return self._pRight == None