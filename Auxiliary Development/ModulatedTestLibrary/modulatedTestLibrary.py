
##################################################################################################################################################################################
##################################################################################################################################################################################

# modulatedTestLibrary

# Desc: biblioteca destinada à automação de testes com APBUARTS reais e emuladas.
# Functions: strDataGenerator --> Função de formação de uma massa de dados aleatória em formato de string.
#            strCipherCaesar --> Função de transformação de uma string a partir da Cifra de César.
#            TestMaker --> Função destinada unicamente ao recebimento, validação e output de dados (sob a ótica de um teste de comunicação)
#            IOWork --> Função relacionada com o envio e recebimento de dados para os testes
#            oCicleInit --> Função destinada ao início e configuração do ciclo de testes.
# Libraries: SerialSocketLibrary (e afins), configGlobalVariables

# OBS: esta biblioteca baseia-se inteiramente na string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", a qual deve ser configurada junto 
# a outros programas envolvidos no teste.


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


def strCipherCaesar(string, numOffset):
   # Desc: Função destinada à transformação de uma string em outra por meio da Cifra de César.
   # Return: String transformada.
   # Paramaters: string --> String a ser transformada.
   #             numOffset --> Offset a ser utilizado na Cifra de César.

   characters = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
   
   strCipher = ""

   for chr in string:

      if chr != "!":

         posChr = characters.find(chr)
         posChr = (posChr + numOffset) % (len(characters))
         strCipher = strCipher + characters[posChr]

   return strCipher

def TestMaker():
   # Desc: Função destinada unicamente ao recebimento, validação e output de dados (sob a ótica de um teste de comunicação)
   # Return: (-)
   # Parameters: iOffset --> Variável determinante no offset da Cifra de César.
   #             iNumData --> Número de bytes a serem gerados inicialmente.
   #             strData (global variable) --> Variável para transferência de dados inter-threads.
   #             iCntrl (global variable) --> Variável para indicação de ação.


   # Enquanto o bit de control não se encontra em halt
   while (readStrCntrl() != "halt"):

      # Para o caso do control em start
      if readStrCntrl() == "start":

         setStrData(strDataGenerator(readOConfig()["iNumData"])) # Gera uma string de dados de um determinado tamanho
         print("\nIniciando testes...\n")
         setStrCntrl("scan") # Próximo estado de scan

      # Para o caso do control em scan
      elif readStrCntrl() == "scan":

         strTestString = strCipherCaesar(readStrData(), readOConfig()["iNumOffset"]) # Faz a cifra de César aplicada a uma string anterior
         setStrCntrl("send")

      # Para o caso do control em validate
      elif readStrCntrl() == "validate":

         # Printa o resultado do teste atual
         print("Resultado do Teste -> String esperada: %s, String recebida: %s, Status: %s, Tempo de processamento: %.2f [s]" % (strTestString, readStrData(), strTestString == readStrData(), readITime()))

         # Se a validação ocorrer corretamente, vai para scan
         if strTestString == readStrData() and readIContTest() <= readOConfig()["iNumTest"]:
            setIContTest(readIContTest() + 1)
            setStrCntrl("scan")

         # Se a validação não ocorrer corretamente, vai para halt
         else:

            setStrCntrl("halt")
            print("\nFinalizando teste....")

         

def oCicleInit():
   # Desc: Função destinada ao início e configuração do ciclo de testes.
   # Return: Lista de nomes de dispositivos e suas respectivas estruturas de comunicação.
   # Parameters: (-)

   arrayComn = []
   oConfig = {}

   print("Bem vindo ao programa de testes cíclicos de comunicações seriais ou TCP! \n")

   iDev = int(input("Quantos dispositivos de comunicação deseja testar simulteneamente: "))

   print("\nPara preencher os dispositivos, coloque-os na ordem a serem testados.\n")

   for iContDev in range(0, iDev):

      strTypeDev = str(input("O %i° dispositivo comunica-se por meio de uma porta TCP ou serial? (TCP/serial): " % (iContDev + 1)))

      if strTypeDev == "TCP":

         socket = serialSocketConnect("socket")
         arrayComn.append(["TCP", socket])


      elif strTypeDev == "serial":

         serialComn = serialSocketConnect("serial")
         arrayComn.append(["Serial", serialComn])

   oConfig["iNumTest"] = int(input("\nDigite quantos ciclos desejam ser realizados: ")) - 2
   oConfig["iNumOffset"] = int(input("Qual o offset a ser utilizado na transformação: "))
   oConfig["iNumData"] = int(input("Quantos bytes de dados serão transferidos na comunicação: "))

   setOConfig(oConfig)


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

         # Grava time stamp
         setITime(time.time())

         # Se o dispositivo for do tipo TCP
         if ArrayComn[iComnCont][0] == "TCP":

            # Envia a string por meio do socket e grava timestamp
            writeSocket(ArrayComn[iComnCont][1], readStrData() + '!')

         # Se o dispositivo for do tipo serial
         elif ArrayComn[iComnCont][0] == "Serial":

            # Envia a string por meio da serial
            writeSerial(ArrayComn[iComnCont][1], readStrData() + '!')

         # Passa para o estado de receive
         setStrCntrl("receive")

      # Para o caso de control em receive
      elif readStrCntrl() == "receive":

         # Se o dispositivo for do tipo TCP
         if ArrayComn[iComnCont][0] == "TCP":

            # Recebe a string por meio do socket
            setStrData(strReadSocket(ArrayComn[iComnCont][1], readOConfig()["iNumData"]))

         # Se o dispositivo for do tipo serial
         elif ArrayComn[iComnCont][0] == "Serial":

            # Recebe a string por meio da serial
            setStrData(strReadSerial("numBytes", ArrayComn[iComnCont][1], '', readOConfig()["iNumData"]))

         setITime(time.time() - readITime()) # Grava variação das time stamps na variável global iTime
         iComnCont = (iComnCont + 1) % len(ArrayComn) # Aumenta o contador do dispositivo
         setStrCntrl("validate") # Passa para o estado de validate





