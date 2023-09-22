from testLibrary import *
import threading

setStrCntrl("start")
setStrData("")

ArrayComn = oCicleInit()

print(ArrayComn)

# Configura threads

threadTest = threading.Thread(target = oTestMaker, args = [1, 5])
threadIO = threading.Thread(target = SerialIO, args = [ArrayComn, 5])

threadTest.start()
threadIO.start()