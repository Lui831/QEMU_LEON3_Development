# Código executado no QEMU para poder criar um client para poder executar este código:
# ./qemu-system-sparc -nographic -no-reboot -M leon3_generic -m 64M -kernel D:/WORKSPACE/VERITAS/teste_veritas_2/Debug/teste_veritas_2 -serial tcp::5050,server=on,wait=on

import socket
import time

HOST = 'localhost'  # Endereço IP ou hostname do servidor
PORT = 5050  # Porta do servidor
PORT2 = 5051  # Porta 2 do servidor

# Cria um socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#sock2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conecta o socket ao host e porta fornecidos
sock.connect((HOST, PORT))
#sock2.connect((HOST, PORT2))

# Printa o cliente cuja a conexão fora estabelecida
print('\nCliente 1..:', sock)
#print('\nCliente 2..:', sock2)

# Cria uma variável de controle e espera por comunicação TCP

a=1
time.sleep(1)

# Cria o laço de repetição afim de receber e enviar mensagens para o QEMU

while True:
       
       # Recebendo as mensagens através da conexão

       time.sleep(0.5)
       mensagem = sock.recv(8192)
       print('Mensagem.:', mensagem.decode())
       if a == "U":
            break
       a = input("Valor: ")
       sock.send(a.encode())

sock.close()
#sock2.close()