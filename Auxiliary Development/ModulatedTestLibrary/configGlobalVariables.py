# Declaração das variáveis globais

strCntrl = ""
strData = ""
iTime = 0
iContTest = 0
oConfig = {"iNumTest" : 0, "iNumOffset" : 0, "iNumData": 0}

# Funções de leitura e mudança das variáveis globais

def readStrCntrl():
   
   global strCntrl

   return strCntrl

def setStrCntrl(string):

   global strCntrl

   strCntrl = string

def readStrData():

   global strData

   return strData

def setStrData(string):

   global strData

   strData = string

def setITime(time):

   global iTime

   iTime = time

def readITime():

   global iTime

   return iTime

def readOConfig():

   global oConfig

   return oConfig

def setOConfig(dicionario):

   global oConfig

   oConfig = dicionario

def setIContTest(cont):

   global iContTest

   iContTest = cont

def readIContTest():

   global iContTest

   return iContTest



