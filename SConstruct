# -*- coding: utf-8 -*-

import os
import re
import pprint

# Edytowalne ustawienia

Debug = 1 # Od tego zależą flagi kompilacji i linkowania, patrz niżej
MainDirectory = "." # Plików źródłowych z main() spodziewamy się w lokalnym katalogu
ClassesDirectories = ["proZPRd"] # Katalogi w których ma poszukiwać plików źródłowych klas.

# Koniec edytowalnych ustawień

if os.name == 'nt':
	E = Environment(tools = ['mingw'])
	MinGwPathFileName = "MinGwPath.txt"
	
	if os.path.exists(MinGwPathFileName):
		MinGwPath = open(MinGwPathFileName).read()
		print(MinGwPath)
	else:
		print(MinGwPathFileName + " not found")
		exit(1)
	
	E['ENV']['PATH'] += ';' + MinGwPath
else:
	E = Environment()
	
E.Append(CXXFLAGS = "-Wall -Wextra -std=c++11 -march=native -fdata-sections -ffunction-sections")
E.Append(LINKFLAGS = "-pthread -Wl,--gc-sections")

BinDirectory = "Bin"
if Debug:
	BinDirectory = os.path.join(BinDirectory, "Debug")
	E.Append(CXXFLAGS = "-g")
else:
	BinDirectory = os.path.join(BinDirectory, "Release")
	E.Append(CXXFLAGS = "-O2")
	E.Append(LINKFLAGS = "-s")

if os.name == 'nt':
	E.Append(LINKFLAGS = "-static")
	

# Stwórz katalog BinDirectory
if not os.path.exists(BinDirectory):
	os.makedirs(BinDirectory)

# Funkcja która stworzy nazwę pliku o, który pojawi się w katalogu bin.	
def EscapePath(Path):
	Path = os.path.join(BinDirectory, re.sub(r"[^a-zA-Z0-9\.]+", '_', Path))
	return Path

# Pliki Main, to te które zawierają funkcję main() i będą zlinkowane z obiektami, każdy do pliku .exe
MainPairs = []

# Pliki źródłowe obiektów, każdy z nich stworzy odpowiedni plik .o
ClassesPairs = []

# Znajdź wszystkie pliki .cpp w lokalnym katalogu i przygotuj dla nich nazwy obiektów. Zakłada sie, że są to pliki zawierające funkcję main() i każdy z nich będzie zlinkowany ze wszystkimi klasami
for MainSourceFile in os.listdir(MainDirectory):
	if os.path.isfile(MainSourceFile):
		if MainSourceFile.endswith(".cpp"):
			ObjectName = EscapePath(os.path.splitext(MainSourceFile)[0]) + ".o"
			MainPairs.append([MainSourceFile, ObjectName])

# Znajdź wszystkie pozostałe pliki .cpp (w katalogach wg ClassesDirectories) i przygotuj dla nich obiekty
for ClassesDirectory in ClassesDirectories:
	for DirPath, DirNames, FileNames in os.walk(ClassesDirectory):
		for FileName in FileNames:
			FilePath = os.path.join(DirPath, FileName)
			if(FilePath.endswith(".cpp")):
				ObjectName = EscapePath(os.path.splitext(FilePath)[0]) + ".o"
				ClassesPairs.append([FilePath, ObjectName])

# W tej liście będą przechowane bezpośrednio nazwy obiektów do zlinkowania. E.Program przyjmuje jako parametr listę obiektów do zlinkowania - potrzebna jest lista zawierająca tylko te obiekty.
AllObjects = []
for SourceFile, ObjectFile in ClassesPairs:
	AllObjects.append(ObjectFile)

# Skompiluj wszystkie obiekty z obu list
for SourceFile, ObjectFile in MainPairs + ClassesPairs:
	E.Object(ObjectFile, SourceFile)

# Dla każdego pliku z main() zlinkuj wszystkie obiekty klas z obiektem tego pliku main
for MainSourceFile, MainObjectFile in MainPairs:
	ExecutableFile = os.path.join(BinDirectory, os.path.splitext(MainSourceFile)[0]) # Nazwa pliki exe
	E.Program(ExecutableFile, [MainObjectFile] + AllObjects)






