import serial
import threading
import serial.tools.list_ports
import time
import os
from socket import *

# Cria a função main de execução principal

def main():
    port_antigo = [] 
    while True:
        portList = []
        ports = serial.tools.list_ports.comports() # Armazena todas as portas seriais conectadas na lista 'ports'
        for n in ports:
            portList.append(str(n)) # Para cada porta serial armazenada na lista 'ports', a altera e a armazena na lista portList
        if portList != port_antigo:
            port_antigo=portList # Para cada lista adicionada, altera a lista port_antigo
            os.system('cls') 
            i = 0
            print("Portas conectáveis:") # Printa todas as portas conectadas e disponíveis
            for n in portList:
                print(f"{i} -> {n}")
                i+=1
            select_port = input("\nSelecione uma porta com base no numero: ") # Selecionar uma das portas disponíveis
            try:
                os.system('cls')
                ADDR2 = ("localhost", 4322) # Cria um socket para porta virtual no enredeço selecionado
                uart2 = socket(AF_INET6, SOCK_STREAM) # Configura o socket para comuncação TCP/IP
                uart2.connect(ADDR2) # Conecta o canal de comunicação no servidor criado pela UART
                print(f"Porta conectada: {portList[int(select_port)][:5]}")
                print("Conectado ao UART-PC")
                print("=============================\n")

                serialInst = serial.Serial() # Cria uma classe serial
                serialInst.baudrate = 9600 # Seta a taxa de transmissão do serial
                serialInst.port = portList[int(select_port)][:5] # Escolhe a porta serial com base no input fornecido pelo usuário
                serialInst.open()            
                
                thread1 = threading.Thread(target=receiveMessage, args=[uart2,serialInst]) # Inicializa as threads de recebimento e transmissão de mensagens
                thread2 = threading.Thread(target=sendMessage, args=[uart2,serialInst])

                thread1.start()
                thread2.start()
                
     
            except:
                os.system('cls')
                print("Error connecting...")
                print(f"Porta número {select_port} não existe ou UART emulada não está configurada...")
                time.sleep(1.5)
                main()

            # Caso dê errado, entra nessa rotina


def receiveMessage(uart2,serialInst): # Recebe mensagens da uart virtual e manda para a entrada serial
    while True:
        msg = uart2.recv(1024).decode()
        print("Mensagem recebida da UART Emulada: '%s'. \n" % msg)
        serialInst.write(msg.encode())

def sendMessage(uart2,serialInst): # Recebe mensagens da entrada serial e manda para a uart real
    while True:
        msg = serialInst.read().decode('utf')
        print("Mensagem recebida da UART Real: '%s'. \n" % msg)
        uart2.send(msg.encode("utf-8"))

if __name__ == "__main__": # Executa a função main definida anteriormente
    main()
