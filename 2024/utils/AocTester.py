from utils.AocArgs import AocArgs

class AocTester:

    def test(args: AocArgs, value):
        if args.isVerbose():
            print(value)
        else:
            assert(value == args.getOutput())
            print(args.ScriptFileName + ' Part ' + str(args.PartNumber) + ' Passed')