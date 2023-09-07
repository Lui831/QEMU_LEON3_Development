##################################################################################################################################################################################
##################################################################################################################################################################################
# Import de bibliotecas necessárias


import serial
import threading
import serial.tools.list_ports
import time
import os
from socket import *
from random import *
from SerialSocketLibrary import *


##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de funções úteis ao código

def strDataGenerator(numData):
   # Desc: Função destinada à geração a de uma string de letras e números aleatórios, segundo um determinado parâmetro size.
   # Return: String a ser formada.
   # Paramaters: numData --> Número de bytes a ser formada a string.

   string = ""
   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   sizeCharacters = len(characters)

   for i in range (1,numData):
      
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
      posChr = (posChr + numOffset) % (len(characters) - 1)
      strCipher = strCipher + characters[posChr]

   return strCipher

def bTestMaker(type,cntrl,serialComn, numData, numOffset, stopByte, numBytes):
   # Desc: Função destinada à elaboração e validação de um único teste.
   # Return: Resultado do teste (True --> Teste sucedido e False --> Teste fracassado)
   # Paramaters: type --> 

   strSend = strDataGenerator(numData)

   writeSerial(serialComn, strSend)

   strReceive = strReadSerial(cntrl,serialComn,stopByte,numBytes)

   if strReceive == strCipherCaesar(strSend, numOffset):

      return True
   
   else:

      return False


##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de variáveis e listas


numData = 0
numTest = 0
numString = 0
okTests = 0
failTests = 0


##################################################################################################################################################################################
# Estabelecimento de conexão serial e input de informações


print("Bem vindo ao Test Code do Test 1! \n")

serialComn = serialSocketConnect("serial")

numTest = int(input("Digite o número de testes a serem realizados: "))

numData = int(input("Digite o número de bytes a serem recebidos / enviados por teste: "))

os.system("cls")

print("Iniciando os testes...")
time.sleep(1.5)

for cont in range(0, numTest - 1):

   print("TESTE %i" % cont)
   
   if bTestMaker("numBytes",serialComn, numData, 25, '', 10) == True:

      print("Sucesso!\n")
      okTests += 1

   else:

      print("Falha!\n")
      failTests += 1




























