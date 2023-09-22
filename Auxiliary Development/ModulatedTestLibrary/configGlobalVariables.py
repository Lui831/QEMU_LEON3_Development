# Declaração das variáveis globais

strCntrl = ""
strData = ""

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