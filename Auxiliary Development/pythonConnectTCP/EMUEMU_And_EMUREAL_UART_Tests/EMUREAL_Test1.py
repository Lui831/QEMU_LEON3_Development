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

def bConectSerial():

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