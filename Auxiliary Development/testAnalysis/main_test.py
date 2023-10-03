from testAnalysisLibrary import *

(oDb, oDbCur) = csvToDb("textLog_1000_4_EMUREALUARTs.csv")

addDeltaT(oDb,oDbCur)