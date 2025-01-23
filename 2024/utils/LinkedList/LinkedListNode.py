from utils.Node.Node import Node
class LinkedListNode(Node):

    def __init__(self, vData):
        super().__init__(vData)
        self._pNext = None
    
    def getNext(self):
        return self._pNext

    def setNext(self, pNode):
        self._pNext = pNode