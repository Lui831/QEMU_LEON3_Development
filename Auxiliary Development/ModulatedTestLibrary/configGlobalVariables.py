# Declaração das variáveis globais

strCntrl = ""
strData = ""
iTime = 0

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