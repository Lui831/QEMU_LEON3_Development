
##################################################################################################################################################################################
##################################################################################################################################################################################

# testLibrary

# Desc: biblioteca destinada à automação de testes com APBUARTS reais e emuladas.
# Functions: strDataGenerator --> Função de formação de uma massa de dados aleatória em formato de string.
#            strCipherCaesar --> Função de transformação de uma string a partir da Cifra de César.
#            oSerialTestMaker --> Função destinada à elaboração e validação de um único teste para uma porta serial.
# Libraries: SerialSocketLibrary (e afins)

# OBS: esta biblioteca baseia-se inteiramente na string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", a qual deve ser configurada junto 
# a outros programas envolvidos no teste.


##################################################################################################################################################################################
##################################################################################################################################################################################
# Import de bibliotecas necessárias


from serialSocketLibrary import *


##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de funções principais


def strDataGenerator(numData):
   # Desc: Função destinada à geração a de uma string de letras e números aleatórios, segundo um determinado parâmetro size.
   # Return: String a ser formada.
   # Paramaters: numData --> Número de bytes a ser formada a string.

   string = ""
   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   sizeCharacters = len(characters)

   for i in range (0,numData):
      
      string = string + characters[randint(0,sizeCharacters - 1)]

   return string


def strCipherCaesar(string, numOffset):
   # Desc: Função destinada à transformação de uma string em outra por meio da Cifra de César.
   # Return: String transformada.
   # Paramaters: string --> String a ser transformada.
   #             numOffset --> Offset a ser utilizado na Cifra de César.

   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   
   strCipher = ""

   for chr in string:

      posChr = characters.find(chr)
      posChr = (posChr + numOffset) % (len(characters))
      strCipher = strCipher + characters[posChr]

   return strCipher


def oSerialTestMaker(serialComn, numData, numOffset,cntrl, stopByte):
   # Desc: Função destinada à elaboração e validação de um único teste a uma porta serial.
   # Return: Resultado do teste baseado em um dicionário testReport (constituído por strSend, strReceive e status)
   # Paramaters: serialComn --> Objeto da classe serial que contém a porta serial conectada.
   #             numData --> Número de bytes a serem enviados e recebidos pela porta serial.
   #             numOffset --> Offset configurado para a Cifra de César.
   #             cntrl --> Se for igual à string "stopByte", programa limita o recebimento da string por meio de stopByte.
   #                       Se for igual à string "numBytes", programa limita o recebimento da string por meio de numBytes.
   #             stopByte --> Char determinante para a limitação de recebimento da string.
   #             numBytes --> Valor inteiro determinante para a limitação de recebimento da string.

   # OBS: esta função deve ser chamada após o programa estar conectado a uma porta serial.

   testReport = {"strSend" : "" , "strReceive" : "", "strExpected" : "" , "status" : False}

   strSend = strDataGenerator(numData)
   testReport["strSend"] = strSend

   writeSerial(serialComn, strSend)

   time.sleep(1.5)

   strReceive = strReadSerial(cntrl,serialComn,stopByte,numData)
   testReport["strReceive"] = strReceive
   testReport["strExpected"] = strCipherCaesar(strSend, numOffset)

   if strReceive == testReport["strExpected"]:

      testReport["status"] = True

      return testReport
   
   else:

      return testReport
   


def oSocketTestMaker(socket, numData, numOffset):
   # Desc: Função destinada à elaboração e validação de um único teste a uma porta serial.
   # Return: Resultado do teste baseado em um dicionário testReport (constituído por strSend, strReceive e status)
   # Paramaters: socket --> Objeto da classe socket que contém a porta TCP conectada.
   #             numData --> Número de bytes a serem enviados e recebidos pela porta serial.
   #             numOffset --> Offset configurado para a Cifra de César.

   # OBS: esta função deve ser chamada após o programa estar conectado a um socket.

   testReport = {"strSend" : "" , "strReceive" : "", "strExpected" : "", "status" : False}

   strSend = strDataGenerator(numData)
   testReport["strSend"] = strSend

   writeSocket(socket, strSend)

   strReceive = strReadSocket(socket)
   testReport["strReceive"] = strReceive
   testReport["strExpected"] = strCipherCaesar(strSend, numOffset)

   if strReceive == testReport["strExpected"]:

      testReport["status"] = True

      return testReport
   
   else:

      return testReport
   

def oSerialSocketTestMaker(socket, serialComn, numData, numOffset, cntrl, stopByte):
   # Desc: Função destinada à elaboração e validação de um único teste a uma porta serial e porta TCP.
   # Return: Resultado do teste baseado em um dicionário testReport (constituído por strSend, strReceive e status)
   # Paramaters: socket --> Objeto da classe socket que contém a porta TCP conectada.
   #             serialComn --> Objeto da classe serial que contém a porta serial conectada.
   #             numData --> Número de bytes a serem enviados e recebidos.
   #             numOffset --> Offset configurado para a Cifra de César.
   #             cntrl --> Se for igual à string "stopByte", programa limita o recebimento da string por meio de stopByte.
   #                       Se for igual à string "numBytes", programa limita o recebimento da string por meio de numBytes.
   #             stopByte --> Char determinante para a limitação de recebimento da string.

   # OBS: esta função deve ser chamada após o programa estar conectado a uma porta serial e a um socket.

   testReport = {"strSend" : "" , "strReceive" : "", "strExpected" : "", "status" : False}

   strSend = strDataGenerator(numData)
   testReport["strSend"] = strSend

   writeSocket(socket, strSend)

   strReceive = strReadSerial("numBytes", serialComn, '', numData)
   testReport["strReceive"] = strReceive
   testReport["strExpected"] = strCipherCaesar(strSend, numOffset)

   if strReceive == testReport["strExpected"]:

      testReport["status"] = True

      return testReport
   
   else:

      return testReport





