# Házi feladat

Név/Nevek NEPTUN kóddal:
- Mali Bence (ZA2ENI)

# Feladat
A tervezett feladat egy linux shell, más ismert shellekhez hasonló működéssel.

A program az alábbi funkciókkal fog rendelkezni:
* Néhány alapvető shell builtin (exit, cd, echo)
* Programok elindítása argumentumokkal (pl: ~$ ps aux)
* Programok bemenetének, kimenetének átirányítása (>, <, >>)
* Programok között pipeolás (pl: ~$ ls -hal | grep thread)

A használni kívánt (nem triviális) linux syscallok/utilityk:
* fork()
* execvp()
* wait()
* getenv()
* pipe()
* dup2()
* freopen()
* chdir()
