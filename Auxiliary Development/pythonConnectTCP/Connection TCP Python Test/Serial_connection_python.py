import socket

HOST = 'localhost'  # Endereço IP ou hostname do servidor
PORT = 5050  # Porta do servidor

# Cria um socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Associa o socket ao endereço e porta
sock.connect((HOST, PORT))

# Coloca o socket em modo de escuta

# Aceita uma conexão do cliente
a = 1



while a!='x':
    a = input("Valor: ")
    sock.send(a.encode())

sock.close()