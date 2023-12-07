
##################################################################################################################################################################################
##################################################################################################################################################################################

# ahbramTestLibrary

# Desc: biblioteca para a elaboração de funções (a serem implementadas como threads) que realizem os testes de validação da ahbram.
# Functions: testMaker --> função responsável pela geração de dados e validação dos dados recebidos.
#            IOWork --> função responsável pela comunicação e transferência de dados com a máquina emulada.
#            strDataGenerator --> função responsável pela geração de dados a serem enviados para a máquina emulada.
#            oCicleInit --> função destinada ao início e configuração do ciclo de testes.
# Libraries: SerialSocketLibrary (e afins), configGlobalVariables

##################################################################################################################################################################################
##################################################################################################################################################################################
# Import de bibliotecas necessárias

from serialSocketLibrary import *
from configGlobalVariables import *

##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de funções principais

def strDataGenerator(numData):
   # Desc: Função destinada à geração a de uma string de letras e números aleatórios, segundo um determinado parâmetro size.
   # Return: String a ser formada.
   # Paramaters: numData --> Número de bytes a ser formada a string.

   string = ""
   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   sizeCharacters = len(characters)

   for i in range (0,numData):
      
      string = string + characters[randint(0,sizeCharacters - 1)]

   return string


def oCicleInit():
   # Desc: Função destinada ao início e configuração do ciclo de testes.
   # Return: Lista de nomes de dispositivos e suas respectivas estruturas de comunicação.
   # Parameters: (-)

   arrayComn = []
   oConfig = {}

   print("Bem vindo ao programa de testes cíclicos de ahbrams! \n")

   # Testerá-se somente uma ahbram por vez
   iDev = 1

   # Ciclo de preenchimento para cada dispositivo
   for iContDev in range(0, iDev):

      strTypeDev = str(input("O dispositivo comunica-se por meio de uma porta TCP ou serial? (TCP/serial): "))

      if strTypeDev == "TCP":

         socket = serialSocketConnect("socket")
         arrayComn.append(["TCP", socket])


      elif strTypeDev == "serial":

         serialComn = serialSocketConnect("serial")
         arrayComn.append(["Serial", serialComn])

   # Configurações gerais do teste com base nos inputs do usuário

   oConfig["iNumOffset"] = int(input("Qual o offset de início de implementação da ahbram (em decimal): "))
   oConfig["iNumSize"] = int(input("Qual o tamanho (em bytes, decimal) da ahbram: "))
   oConfig["iNumData"] = int(input("Quantos bytes de dados serão transferidos na comunicação: "))
   oConfig["iNumTest"] = (oConfig["iNumSize"] / oConfig["iNumData"] - 2) * iDev 

   setOConfig(oConfig)

   # Geração do arquivo .csv de output do teste
   initOFile()

   # Gravação do tempo de início dos testes

   setITime(time.time())
   
   print("\nIniciando o ciclo de testes.....\n")
   
   return (arrayComn)


def IOWork(ArrayComn):
   # Desc: Função relacionada com o envio e recebimento de dados para os testes
   # Return: (-)
   # Parameters: ArrayComn --> Array que contém as estruturas de comunicação dos dispositivos conectados.
   #             strData (global variable) --> Variável para transferência de dados inter-threads.
   #             iCntrl (global variable) --> Variável para indicação de ação.

   iComnCont = 0
   
   # Enquanto o bit de control não se encontra em halt
   while(readStrCntrl() != "halt"):

      # Para o caso de control em send
      if readStrCntrl() == "send":

         # Grava um item no log, de TX
         info = [str(readIContTest()*2), ArrayComn[iComnCont][0] + str(iComnCont), "TX", readStrData(), str(time.time() - readITime()), str(readOConfig()["iNumData"]), ""]
         appendOFile(",".join(info) + "\n")


         # Se o dispositivo for do tipo TCP
         if ArrayComn[iComnCont][0] == "TCP":

            # Envia a string por meio do socket e grava timestamp
            writeSocket(ArrayComn[iComnCont][1], readStrData())

         # Se o dispositivo for do tipo serial
         elif ArrayComn[iComnCont][0] == "Serial":

            # Envia a string por meio da serial
            writeSerial(ArrayComn[iComnCont][1], readStrData())

         # Passa para o estado de receive
         setStrCntrl("receive")

      # Para o caso de control em receive
      elif readStrCntrl() == "receive":

         # Começa gravação de novo item no log, de RX
         info = [str(readIContTest()*2 + 1), ArrayComn[iComnCont][0] + str(iComnCont)]
         appendOFile(",".join(info) + ",")

         # Se o dispositivo for do tipo TCP
         if ArrayComn[iComnCont][0] == "TCP":

            # Recebe a string por meio do socket
            setStrData(strReadSocket(ArrayComn[iComnCont][1], readOConfig()["iNumData"]))

         # Se o dispositivo for do tipo serial
         elif ArrayComn[iComnCont][0] == "Serial":

            # Recebe a string por meio da serial
            setStrData(strReadSerial("numBytes", ArrayComn[iComnCont][1], '', readOConfig()["iNumData"]))

         iComnCont = (iComnCont + 1) % len(ArrayComn) # Aumenta o contador do dispositivo
         setStrCntrl("validate") # Passa para o estado de validate


def TestMaker():
   # Desc: Função destinada unicamente ao recebimento, validação e output de dados (sob a ótica de um teste de comunicação)
   # Return: (-)
   # Parameters: iOffset --> Variável determinante no offset da Cifra de César.
   #             iNumData --> Número de bytes a serem gerados inicialmente.
   #             strData (global variable) --> Variável para transferência de dados inter-threads.
   #             iCntrl (global variable) --> Variável para indicação de ação.


   # Enquanto o bit de control não se encontra em halt
   while (readStrCntrl() != "halt"):

      # Para o caso do control em scan
      if readStrCntrl() == "scan":

         setStrData(str(readIContTest() + readOConfig()["iNumOffset"]) + "!" + strDataGenerator(readOConfig()["iNumData"]) + "!") # Cria uma string aleatória nova
         strTestString = readStrData(); # Lê a string de dados anterior;
         setStrCntrl("send")

      # Para o caso do control em validate
      elif readStrCntrl() == "validate":

         # Printa o resultado do teste atual e armazena na string de log
         print("Resultado do Teste -> Status: %s, Tempo de processamento: %.2f [s]" % (strTestString == readStrData(), time.time() - readITime()))
         info = ["RX", readStrData(),str(time.time() - readITime()), str(readOConfig()["iNumData"]), str(strTestString == readStrData())]
         appendOFile(",".join(info) + "\n")

         # Se o número de testes ainda estiver no limite, vai para scan
         if readIContTest() <= readOConfig()["iNumTest"]:
            setIContTest(readIContTest() + 1)
            setStrCntrl("scan")

         # Se não, vai para halt
         else:

            setStrCntrl("halt")
            print("\nFinalizando teste....")
            closeOFile()

         # Se a string recebida for diferente da esperada, continua com a esperada

         if strTestString != readStrData():

            setStrData(strTestString)