class AocArgs:
    
    g_iDefaultPartNumber = 1
    g_sAltFlag = '-a'
    g_sAltInputFileNamePostfix = '-a'
    g_sDayNumberError = 'AocArgs.py:day-<number>.py:Number must be an integer from 1 to 25'
    g_sDefaultPartNumber = str(g_iDefaultPartNumber)
    g_sInputFilePostfix = '.in'
    g_sOutputFilePostfix = '.out'
    g_sPartNumberError = 'AocArgs.py:Part number must be 1 or 2'
    g_sScriptFileNamePrefix = 'day-'
    g_sScriptFileNamePostfix = '.py'
    g_sTestFlag = '-t'
    g_sTestsDirectoryName = './tests/'
    g_sFormatError = 'AocArgs.py:format:./day-NUMBER.py {1|2} ['\
        + g_sTestFlag + '] [' + g_sAltFlag + ']'

    #
    # desc: Handles command line arguments passed to Advent of Code scripts
    # Format: 
    #   ./day-NUMBER.py {1|2} [-t] [-a]
    # params: argv (IN,REQ): array of command line arguments passed to caller.
    #                          ./day-DAYNUMBER.py: Python script name
    #                          {1|2}: Part number 1 or 2
    #                          [-t]: Test flag
    #                          [-a]: Alt flag, use input file: DAYNUMBER-a.in
    #
    def __init__(self, argv):
        argc = len(argv)
        if argc > 3:
            raise Exception(AocArgs.g_sFormatError)
        self._sScriptFileName = AocArgs._initScriptFileName(argv)
        self._iDayNumber = AocArgs._initDayNumber(argv)
        self._iPartNumber = AocArgs._initPartNumber(argv)
        self._bTestFlag = False
        self._bAltFlag = False
        self._initFlags(argv)
        self._sInputFileName = self._initInputFileName()
        self._iOutput = self._initOutput()
        self._bVerbose = self._initVerbose()

    # private
    # static
    def _initScriptFileName(argv):
        return AocArgs._parseScriptFileName(argv)
    
    # private
    # static
    def _parseScriptFileName(argv):
        return argv[0]
    
    # private
    # static
    def _initDayNumber(argv):
        try:
            iDayNumber = int(AocArgs._parseDayNumber(argv))
            if not AocArgs._isValidDayNumber(iDayNumber):
                raise Exception()
        except Exception:
            raise Exception(AocArgs.g_sDayNumberError)
        return iDayNumber
        
    # private
    # static
    def _parseDayNumber(argv):
        return AocArgs._parseScriptFileName(argv)\
            .split('/')[-1]\
            .replace(AocArgs.g_sScriptFileNamePrefix,'')\
            .replace(AocArgs.g_sScriptFileNamePostfix, '')
        
    # private
    # static
    def _isValidDayNumber(iDayNumber):
        return iDayNumber >= 1 and iDayNumber <= 25

    # private
    # static
    def _initPartNumber(argv):
        argc = len(argv)
        try:
            if argc < 2:
                raise Exception()
            iPartNumber = int(argv[1])
            if not AocArgs._isValidPartNumber(iPartNumber):
                raise Exception()
        except Exception:
             raise Exception(AocArgs.g_sPartNumberError)
        return iPartNumber
    
    # private
    # static
    def _isValidPartNumber(iPartNumber):
        return iPartNumber == 1 or iPartNumber == 2
    
    def _initFlags(self, argv):
        for el in argv[2:]:
            if el == AocArgs.g_sTestFlag:
                self._bTestFlag = True
            elif el == AocArgs.g_sAltFlag:
                self._bAltFlag = True
            else:
                raise Exception(AocArgs.g_sFormatError)
    
    # private
    # static
    def _initInputFileName(self):
        if self._bAltFlag:
            s = str(self._iDayNumber) + AocArgs.g_sAltInputFileNamePostfix
        else:
            s = str(self._iDayNumber)
        return AocArgs.makeInputFileName(s)
    
    # private
    # static
    def _initOutput(self):
        if not self._bTestFlag:
            return None
        sDayNumber = str(self._iDayNumber)
        sPartNumber = str(self._iPartNumber)
        sOutputFileName = AocArgs.makeOutputFileName(sDayNumber, sPartNumber)
        with open(sOutputFileName, 'r') as file:
            return int(file.read())
    
    # private
    # static
    def _initVerbose(self):
        return not self._bTestFlag
    
    # public
    def isVerbose(self):
        return self._bVerbose
    
    # public
    def getScriptFileName(self):
        return self._sScriptFileName
    
    # public
    def getDayNumber(self):
        return self._iDayNumber
    
    # public
    def getInputFileName(self):
        return self._sInputFileName
    
    # public
    def getPartNumber(self):
        return self._iPartNumber
    
    # public
    def getOutput(self):
        return self._iOutput
    
    # public
    # static
    def getTestFlag():
        return AocArgs.g_sTestFlag
    
    # public
    # static
    def makeScriptFileName(sDayNumber):
        return './' + AocArgs.g_sScriptFileNamePrefix + sDayNumber\
            + AocArgs.g_sScriptFileNamePostfix
    
    # public
    # static
    def makeInputFileName(sDayNumber):
        return AocArgs.g_sTestsDirectoryName + sDayNumber\
            + AocArgs.g_sInputFilePostfix
    
    # public
    # static
    def makeOutputFileName(sDayNumber, sPartNumber):
        return AocArgs.g_sTestsDirectoryName + sDayNumber + '-' + sPartNumber\
            + AocArgs.g_sOutputFilePostfix