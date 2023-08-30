import threading
from socket import *


def main():

    ADDR1 = ("localhost", 5051)
    ADDR2 = ("localhost", 5052)

    sock1 = socket(AF_INET6, SOCK_STREAM)
    sock2 = socket(AF_INET6, SOCK_STREAM)

    try:
        sock1.connect(ADDR1)
 
        print("UART1 conectada! \n")

    except:
        print("Não foi possível se conectar à primeira UART. \n")

    try:
        sock2.connect(ADDR2)

        print("UART2 conectada! \n")

    except:
        print("Não foi possível se conectar à segunda UART. \n")

    flyback1 = threading.Thread(target=flybackMessage1,args=[sock1,sock2])
    flyback2 = threading.Thread(target=flybackMessage2,args=[sock1,sock2])

    flyback1.start()
    flyback2.start()


def flybackMessage1(sock1,sock2):

    while True:

        try:

           msg = sock1.recv(1024)

           if msg.decode() != "":
               
               print("Mensagem recebida da UART1: '%s'." % msg.decode())

           sock2.send(msg)

        except:
           
           pass
        
def flybackMessage2(sock1,sock2):

    while True:

        try:
           
           msg = sock2.recv(1024)

           if msg.decode() != "":
               
               print("Mensagem recebida da UART2: '%s'." % msg.decode())

           sock1.send(msg)

        except:
           
           pass
        
main()