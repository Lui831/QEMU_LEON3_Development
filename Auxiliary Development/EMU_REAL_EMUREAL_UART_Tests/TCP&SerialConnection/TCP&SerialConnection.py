###################################################################################################################################################################################
###################################################################################################################################################################################

# TCP&SerialConnection

# Desc: programa que emula uma conexão direta entre uma porta TCP e uma porta serial.

###################################################################################################################################################################################
###################################################################################################################################################################################
# Inclusão de bibliotecas necessárias ao código


import threading
import time
import os
from SerialSocketLibrary import *


###################################################################################################################################################################################
###################################################################################################################################################################################
# Definição de funções importantes ao código (junto à definição da variável global fTime)


fTime = time.time()


def TCPtoSerial(socket,serialComn):
    # Desc: função que recebe string da porta TCP e a envia para porta serial.
    # Return: (-).
    # Parameters: socket --> Objeto da classe socket que representa a porta TCP conectada.
    #             serialComn --> Objeto da classe serial que representa a porta serial conectada.

    while True:

       global fTime

       string = strReadSocket(socket)

       if string != '':

          print("Mensagem recebida da Porta TCP: '%s' (Tempo desde a ocorrência: %.2f). \n" % (string,time.time() - fTime))

          fTime = time.time()

          writeSerial(serialComn, string)


def SerialToTCP(socket,serialComn,numBytes):
    # Desc: função que recebe string da porta serial e a envia para porta TCP.
    # Return: (-).
    # Parameters: socket --> Objeto da classe socket que representa a porta TCP conectada.
    #             serialComn --> Objeto da classe serial que representa a porta serial conectada.

    global fTime

    while True:

       string = ""

       while(len(string) != numBytes):

          chr = strReadSerial("numBytes", serialComn, '', 1)

          if chr != '':
             
             string = string + chr

       print("Mensagem recebida da Porta Serial: '%s' (Tempo desde a ocorrência: %.2f). \n" % (string, time.time() - fTime))

       fTime = time.time()

       writeSocket(socket, string)


###################################################################################################################################################################################
###################################################################################################################################################################################
# Parte principal do código

print("Bem vindo ao programa TCP&SerialConnection! \n")

# Estabelece conexão com portas TCP e Serial

numBytes = int(input("Digite o número de bytes a serem bufferizados na porta Serial (-1 para não bufferização): "))

print("\n**Conexão com a porta TCP**\n")

socket = serialSocketConnect("socket")

print("\n**Conexão com a porta Serial**\n")

serialComn = serialSocketConnect("serial")

# Configura e starta threads que simulam a conexão entre porta TCP e porta serial

thread1 = threading.Thread(target = TCPtoSerial, args = [socket, serialComn])
thread2 = threading.Thread(target = SerialToTCP, args = [socket, serialComn, numBytes])

thread1.start()
thread2.start()



