from testAnalysisLibrary import *

(oDb, oDbCur) = csvToDb("log.txt")

addDeltaT(oDb,oDbCur)