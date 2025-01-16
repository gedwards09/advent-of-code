from time import time
from utils.AocArgs import AocArgs

class AocController:

    def __init__(self, args, fpAlg1, fpAlg2):
        self._args = AocArgs(args)
        self._fpAlg1 = fpAlg1
        self._fpAlg2 = fpAlg2

    def Execute(self):
        tStart = time()
        value = self._doAlg()
        tTime = time() - tStart
        self._doCheck(value, tTime)

    def _doAlg(self):
        if self._args.getPartNumber() == 1:
            return self._fpAlg1(self._args.getInputFileName())
        elif self._args.getPartNumber() == 2:
            return self._fpAlg2(self._args.getInputFileName())

    def _doCheck(self, value, tTime):
        if self._args.isVerbose():
            print(value)
        else:
            try:
                assert(value == self._args.getOutput())
            except AssertionError:
                exit(1)
            print(self._getPassMessage(tTime))

    def _getPassMessage(self, tTime):
        return self._args.getScriptFileName()\
            + ' Test ' + str(self._args.getTestNumber())\
            + ' Part ' + str(self._args.getPartNumber())\
            + ' Passed ({:.3f} s)'\
            .format(tTime)