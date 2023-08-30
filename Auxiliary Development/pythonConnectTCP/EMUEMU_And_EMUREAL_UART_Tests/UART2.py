from socket import *
import threading

def main():

    ADDR2 = ("localhost", 4321)
    
    uart2 = socket(AF_INET6, SOCK_STREAM)
    uart2.bind(ADDR2)

    try:

        uart2.listen()

    except:

        print("Não foi possível estabelecer conexão com UART1 \n")

    comn2 , addr = uart2.accept()
    print("UART2 conectada ao endereço:", addr)

    thread1 = threading.Thread(target=receiveMessage, args=[comn2])
    thread2 = threading.Thread(target=sendMessage, args=[comn2])

    thread1.start()
    thread2.start()

    
def receiveMessage(uart2):

    while True:

        try:

            msg = uart2.recv(1024).decode()
            print("Mensagem recebida da UART1: '%s'. \n" % msg)

        except:

            pass

def sendMessage(uart2):

    while True:



            msg = input("\n")
            uart2.send(msg.encode("utf-8"))



main()