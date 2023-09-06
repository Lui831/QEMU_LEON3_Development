##################################################################################################################################################################################
##################################################################################################################################################################################
# Import de bibliotecas necessárias


import serial
import threading
import serial.tools.list_ports
import time
import os
from socket import *


##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de funções úteis ao código

def serialConectSerial():

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




##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de variáveis e listas


listPortAntigo = []
listPort = []
listStrPort = []
numData = 0
cond = True


##################################################################################################################################################################################
# Inicialização do teste e input de informações


print(bConectSerial().port)