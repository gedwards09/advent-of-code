from utils.Node.INode import INode

class Node(INode):

    def __init__(self, vData):
        self._vData = vData

    def getData(self):
        return self._vData

    def setData(self, vData):
        self._vData = vData