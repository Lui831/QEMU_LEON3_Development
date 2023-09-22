from modulatedTestLibrary import *
import threading

setStrCntrl("start")
setStrData("")

ArrayComn = oCicleInit()

print(ArrayComn)

# Configura threads

threadTest = threading.Thread(target = TestMaker, args = [0, 5])
threadIO = threading.Thread(target = IOWork, args = [ArrayComn, 5])

threadTest.start()
threadIO.start()