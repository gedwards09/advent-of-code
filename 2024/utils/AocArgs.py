class AocArgs:

    g_sFormatException = 'format:./day-NUMBER.py INPUT [1|2; default=2]'

    def __init__(self, argv):
        self._argc = len(argv)
        if self._argc > 3:
            raise Exception(AocArgs.g_sFormatException)
        self.InputFileName = argv[1]
        self.PartNumber = AocArgs._initPartNumber(argv)

    def _initPartNumber(argv):
        if len(argv) == 3:
            if argv[2] == '1' or argv[2] == '2':
                return int(argv[2])
            else:
                raise Exception(AocArgs.g_sFormatException)
        else:
            return 1
