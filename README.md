# Házi feladat

- Mali Bence (ZA2ENI)

# A kész feladat

A feladat a specifikációnak megfelelő, viszont a specifikációban nem szereplő parancssorozat végrehajtást (&&) is megvalósítottam.
Az elkészült feladat bemutató videója [itt](https://odysee.com/linuxproghf:9?r=9Zr5PeXA4NpFRBXK9qucmmAmFtMRJheU) található.

# Specifikáció
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

