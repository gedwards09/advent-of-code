from utils.Comparable.IComparable import IComparable
from utils.LinkedList.LinkedList import LinkedList

class OrderedLinkedList(LinkedList):

    def insert(self, vData: IComparable, pStartNode=None):
        if pStartNode == None:
            pCurrentNode = self.getHead()
        else:
            pCurrentNode = pStartNode
            
        if pCurrentNode == None:
            self.addToFront(vData)
            return

        if vData.Compare(pCurrentNode.getData()) <= 0:
            self.addToFront(vData)
            return
        
        pNewNode = self._makeNode(vData)
        while pCurrentNode != None and pCurrentNode.getNext() != None:
            vCurrentData = pCurrentNode.getNext().getData()
            if vData.Compare(vCurrentData) <= 0:
                self._putAfter(pCurrentNode, pNewNode)
                break
            pCurrentNode = pCurrentNode.getNext()
        if pCurrentNode.getNext() == None:
            self._addNodeToBack(pNewNode)

    # protected
    def _putAfter(self, pCurrentNode, pNewNode):
        pNewNode.setNext(pCurrentNode.getNext())
        pCurrentNode.setNext(pNewNode)


