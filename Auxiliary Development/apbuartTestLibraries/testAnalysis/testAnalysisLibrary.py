
##################################################################################################################################################################################
##################################################################################################################################################################################

# testAnalysislibrary

# Desc: biblioteca destinada à análise dos dados provenientes do arquivo .csv gerado a partir dos testes
# Functions: 
# Libraries: sqlite3, pandas


##################################################################################################################################################################################
##################################################################################################################################################################################
# Import de bibliotecas necessárias


import sqlite3 as sql


##################################################################################################################################################################################
##################################################################################################################################################################################
# Definição de funções principais

def csvToDb(strNameOfArchive):

   oDb = sql.connect("testAnalysis.db")

   oDbCur = oDb.cursor()

   with open(strNameOfArchive, "r") as csv:
      
      strLines = csv.readlines()

      for iCont in range(0, len(strLines)):
         
         if iCont == 0:

            oDbCur.execute("CREATE TABLE IF NOT EXISTS testAnalysis(%s)" % (strLines[iCont].strip()))

         else:

            values = tuple(strLines[iCont].strip().split(","))
            oDbCur.execute("INSERT INTO testAnalysis VALUES(%s)" % ",".join(["?" for i in values]) ,values)
            

      oDb.commit()

   return (oDb, oDbCur)

def addDeltaT(oDb,oDbCur):

   iCont = 0
   fTimeList = []
   fTimeDelta = [0]

   # Obtenção de uma lista que contém todas as timestamps
   oDbCur.execute("SELECT fTime from testAnalysis")
   fTimeTuple = oDbCur.fetchall()

   for item in fTimeTuple:

      fTimeList.append(float(item[0]))
      iCont += 1

   # Obtenção de lista que contém todos os DeltaT (primeiro sendo 0)
   for iCont in range(0, len(fTimeList)):

      if iCont != 0:

         fTimeDelta.append(fTimeList[iCont] - fTimeList[iCont - 1])
         iCont += 1

   # Adição da coluna DeltaT ao banco de dados
   oDbCur.execute("ALTER TABLE testAnalysis ADD DeltaT")

   # Adição dos DeltaTs ao banco
   for iCont in range(0, len(fTimeDelta)):
       
       oDbCur.execute("UPDATE testAnalysis SET DeltaT = '%f' WHERE id = '%i'" % (fTimeDelta[iCont], iCont))
       print(iCont)

   oDb.commit()

    

   








