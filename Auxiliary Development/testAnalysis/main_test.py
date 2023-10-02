from testAnalysisLibrary import *

(oDb, oDbCur) = csvToDb("textLog.csv")

addDeltaT(oDb,oDbCur)