from modulatedTestLibrary import *
import threading

setStrCntrl("start")

ArrayComn = oCicleInit()

thread1 = threading.Thread(target = IOWork, args = [ArrayComn, 5])
thread2 = threading.Thread(target = TestMaker, args = [1, 5])

thread1.start()
thread2.start()