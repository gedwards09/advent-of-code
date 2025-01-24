from utils.LinkedList.LinkedListNode import LinkedListNode

class LinkedList:

    def __init__(self):
        self._iSz = 0
        self._pHead = None
        self._pTail = None

    def getHead(self):
        return self._pHead
    
    def size(self):
        return self._iSz
    
    # protected
    def _makeNode(self, vData):
        return LinkedListNode(vData)
    
    def addToFront(self, vData):
        pNode = self._makeNode(vData)
        pNode.setNext(self._pHead)
        self._pHead = pNode
        if self._iSz == 0:
            self._pTail = pNode
        self._iSz += 1

    def addToBack(self, vData):
        pNode = self._makeNode(vData)
        if self._iSz == 0:
            self._pHead = pNode
            self._pTail = pNode
        else:
            self._pTail.setNext(pNode)
            self._pTail = pNode
        self._iSz += 1

    def removeFromFront(self):
        if self._pHead == None:
            raise Exception("LinkedList.py:removeFromFront:Attempt to remove from empty list")
        
        vData = self._pHead.getData()
        self._pHead = self._pHead.getNext()
        if self._pHead == None:
            self._pTail = None
        return vData
    
    def print(self):
        pNode = self._pHead
        while pNode != None:
            pNode.getData().print()
            pNode = pNode.getNext()
