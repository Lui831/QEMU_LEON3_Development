##################################################################################################################################################################################
##################################################################################################################################################################################

# Test_main.py

# Desc: programa principal utilizado na execução das threads definidas em modulatedTestLibrary, passo final para a execução dos testes
# Libraries: modulatedTestLibrary (e afins), threading.


##################################################################################################################################################################################
##################################################################################################################################################################################

# Import de bibliotecas necessárias

from modulatedTestLibrary import *
import threading
from configGlobalVariables import *


##################################################################################################################################################################################
##################################################################################################################################################################################
# Configurações iniciais do teste

setStrCntrl("start")

ArrayComn = oCicleInit()

thread1 = threading.Thread(target = IOWork, args = [ArrayComn])
thread2 = threading.Thread(target = TestMaker)

thread1.start()
thread2.start()

while(1):

    if(readStrCntrl() == "halt"):

       file = open("meutexto.txt", "w")
       file.write(readStrLog())
       break


