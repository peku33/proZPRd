proZPRd - serwer HTTP
---------------------

Wymagania systemowe:

 - Windows:
	 - Zainstalowany kompilator MinGw z obsługą wątków
	 - Zainstalowany python wraz z scons
 - Linux:
	 - Zainstalowany kompilator c++ z obsługą c++11
	 - Zainstalowany scons

Przygotowanie do kompilacji:

 - Windows: Należy upewnić się, że pliki .bat zawierają prawidłową ścieżkę do pliku scons.bat (tworzonego w trakcie instalacji scons na windows). Należy utworzyć nowy plik `MinGwPath.txt` i umieścić w nim ścieżkę do katalogu bin\ kompilatora MinGw. Aby skompilować należy uruchomić wybrany plik .bat
 - Linux: Nie są wymagane żadne dodatkowe kroki. Aby skompilować program należy uruchomić `scons` z parametrem `DEBUG=1` aby skompilować wersję DEBUG lub bez parametrów, aby skompilować wersję RELEASE

