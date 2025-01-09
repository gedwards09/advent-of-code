from utils.AocArgs import AocArgs

class AocController:

    def __init__(self, args, fpAlg1, fpAlg2):
        self._args = AocArgs(args)
        self._fpAlg1 = fpAlg1
        self._fpAlg2 = fpAlg2

    def Execute(self):
        value = self._doAlg()
        self._doCheck(value)

    def _doAlg(self):
        if self._args.getPartNumber() == 1:
            return self._fpAlg1(self._args.getInputFileName())
        elif self._args.getPartNumber() == 2:
            return self._fpAlg2(self._args.getInputFileName())

    def _doCheck(self, value):
        if self._args.isVerbose():
            print(value)
        else:
            assert(value == self._args.getOutput())
            print(self._getPassMessage())

    def _getPassMessage(self):
        return self._args.getScriptFileName() + ' Part ' + str(self._args.getPartNumber()) + ' Passed'