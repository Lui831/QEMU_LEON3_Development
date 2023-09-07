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
# Definição de funções importantes ao código


def TCPtoSerial(socket,serialComn):
    # Desc: função que recebe string da porta TCP e a envia para porta serial.
    # Return: (-).
    # Parameters: socket --> Objeto da classe socket que representa a porta TCP conectada.
    #             serialComn --> Objeto da classe serial que representa a porta serial conectada.

    while True:

       string = strReadSocket(socket)

       print("Mensagem recebida da Porta TCP: '%s'. \n" % string)

       writeSerial(serialComn, string)


def SerialToTCP(socket,serialComn):
    # Desc: função que recebe string da porta serial e a envia para porta TCP.
    # Return: (-).
    # Parameters: socket --> Objeto da classe socket que representa a porta TCP conectada.
    #             serialComn --> Objeto da classe serial que representa a porta serial conectada.

    while True:

       string = strReadSerial("numBytes", serialComn, '', 1)

       print("Mensagem recebida da Porta Serial: '%s'. \n" % string)

       writeSocket(socket, string)


###################################################################################################################################################################################
###################################################################################################################################################################################
# Parte principal do código

print("Bem vindo ao programa TCP&SerialConnection! \n")

# Estabelece conexão com portas TCP e Serial

socket = serialSocketConnect("socket")

serialComn = serialSocketConnect("serial")

# Configura e starta threads que simulam a conexão entre porta TCP e porta serial

thread1 = threading.Thread(target = TCPtoSerial, args = [socket, serialComn])
thread2 = threading.Thread(target = SerialToTCP, args = [socket, serialComn])

thread1.start()
thread2.start()



