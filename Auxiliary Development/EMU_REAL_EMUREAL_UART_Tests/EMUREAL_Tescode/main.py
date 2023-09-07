##################################################################################################################################################################################
##################################################################################################################################################################################

# main - EMUREAL Test 1

# Desc: programa principal de execução do teste de comunicação entre UART real e emulada.


##################################################################################################################################################################################
##################################################################################################################################################################################
# Import de bibliotecas necessárias


import time
import os
from random import *
from serialSocketLibrary import *
from testLibrary import *



##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de variáveis e listas


numData = 0
numTest = 0
numString = 0
okTests = 0
failTests = 0



##################################################################################################################################################################################
# Estabelecimento de conexão serial e input de informações


print("Bem vindo ao Test Code do Test EMUREAL! \n")

serialComn = serialSocketConnect("serial")

socket = serialSocketConnect("socket")

numTest = int(input("Digite o número de testes a serem realizados: "))

numData = int(input("Digite o número de bytes a serem recebidos / enviados por teste: "))

os.system("cls")

print("Iniciando os testes...")
time.sleep(1.5)


##################################################################################################################################################################################
# Sucessão dos testes, gravando test reports para cada um

for cont in range(0, numTest - 1):

   print("TESTE %i" % cont)
   
   testReport = oSerialSocketTestMaker(socket, serialComn, numData, 0, "numBytes", '')

   if testReport["status"] == True:

      print("Sucesso! Resultados do teste: [strSend -> %s , strReceive -> %s , status -> %s).\n" % (testReport["strSend"], testReport["strReceive"], testReport["status"]))
      okTests += 1

   else:

      print("Falha! Resultados do teste: [strSend -> %s , strReceive -> %s , status -> %s).\n" % (testReport["strSend"], testReport["strReceive"], testReport["status"]))
      failTests += 1


##################################################################################################################################################################################
# Overall dos testes realizados

print("Dos %i testes realizados, foi possível verificar que %i foram sucedidos!" % (numTest, okTests))




























