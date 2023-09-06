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


##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de funções úteis ao código

def serialConnectSerial():

   listStrPort = []
   i = 0

   listPort = serial.tools.list_ports.comports()
      
   for port in listPort:

      listStrPort.append(str(port))

   for n in listStrPort:
                
     print(f"{i} -> {n}")
                
     i+=1
            
   select_port = input("\nSelecione uma porta com base no número: ")

   try:
      
      serialComn = serial.Serial()

      serialComn.baudrate = 9600

      serialComn.port = listStrPort[int(select_port)][:5]

      serialComn.open()

      print("Sistema conectado à porta serial '%s'. \n" % serialComn.port)

      return serialComn

   except:

      print("Não foi possível conectar à porta desejada...")

      return False
   

def sendSerial(serialComn,string):
   # Responsável por enviar uma string de dados pela conexão serial
   
   serialComn.write(string.encode())

   return


def strReceiveSerial(serialComn,stopByte,numBytes):
   # Responsável por receber uma mensagem a partir da conexão serial, retorna a string recebida.
   # Para numBytes = 0, recebimento de string é delimitado por stopByte.
   # Para numBytes = 1, recebimento de string é delimitado pelo próprio numBytes.

   string = ""

   if(numBytes == 0):
      
      byteAdd = serialComn.read().decode("utf-8")

      while(byteAdd != stopByte):

        string = string + byteAdd
        byteAdd = serialComn.read().decode("utf-8")

   else:

      for i in range(1,numBytes):

         string = string + serialComn.read().decode("utf-8")

   return string


def strDataGenerator(numData):
   # Função destinada à geração a de uma string de letras e números aleatórios, segundo um determinado parâmetro size.

   string = ""
   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   sizeCharacters = len(characters)

   for i in range (1,numData):
      
      string = string + characters[randint(0,sizeCharacters - 1)]

   return string


def strCipherCaesar(string, numOffset):

   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   
   strCipher = ""

   for chr in string:

      posChr = characters.find(chr)
      posChr = (posChr + numOffset) % (len(characters) - 1)
      strCipher = strCipher + characters[posChr]

   return strCipher

def bTestMaker(serialComn, numData, numOffset, stopByte, numBytes):
   # Função responsável pela realização individual de testes, aguardando e validando segundo a cifra de César escolhida.
   # Retorna True se o teste for validado corretamente, e retorna False se o teste falhar

   strSend = strDataGenerator(numData)

   sendSerial(serialComn, strSend)

   strReceive = strReceiveSerial(serialComn,stopByte,numBytes)

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

serialComn = serialConnectSerial()

numTest = int(input("Digite o número de testes a serem realizados: "))

numData = int(input("Digite o número de bytes a serem recebidos / enviados por teste: "))

os.system("cls")

print("Iniciando os testes...")
time.sleep(1.5)

for i in range(0, numTest - 1):

   print("TESTE %i" % i)
   
   if bTestMaker(serialComn, numData, 25, '', 10) == True:

      print("Sucesso!\n")
      okTests += 1

   else:

      print("Falha!\n")
      failTests += 1




























