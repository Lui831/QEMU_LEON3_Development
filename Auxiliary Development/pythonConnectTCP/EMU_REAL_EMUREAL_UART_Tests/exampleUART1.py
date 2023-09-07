from socket import *
import threading

def main():

    ADDR1 = ("localhost", 4322) # Inicia o endereço da primeira UART
    
    # Conecta a primeira UART ao endereço em questão
    uart1 = socket(AF_INET6, SOCK_STREAM)
    uart1.bind(ADDR1)

    try:

        uart1.listen()
    
    except:

        print("Não foi possível estabelecer conexão com UART1 \n")

    comn1 , addr = uart1.accept()
    print("UART1 conectada ao endereço:", addr)

    thread1 = threading.Thread(target=receiveMessage, args=[comn1])
    thread2 = threading.Thread(target=sendMessage, args=[comn1])

    thread1.start()
    thread2.start()

    
def receiveMessage(uart1):

    while True:

        try:

            msg = uart1.recv(1024).decode()
            print("Mensagem recebida da UART2: '%s'. \n" % msg)

        except:

            pass

def sendMessage(uart1):

    while True:

            msg = input("\n")
            uart1.send(msg.encode())

    
main()