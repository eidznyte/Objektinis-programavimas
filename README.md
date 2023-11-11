# Objektinis-programavimas
## Aprašymas
Ši programa generuoja atsitiktinius skirtingo dydžio studentų sąrašus (1000, 10000, 100000, 1000000, 10000000), juos surūšiuoja į dvi kategorijas pagal galutinio pažymio dydį. Taip pat programa analizuoja, kiek laiko užtrunka sugeneruoti tokio dydžio failus, juos perskaityti ir surašyti į atskirus tekstinius failus. Ši programa skiriasi nuo v0.2 tuo, kad matuoja tiek std::vector konteinerio užtruktą skaičiavimo kiekį, tiek std::list.
## Programos struktūra
* main2.cpp.cpp -> pagrindinis kodo file.
* students2.cpp -> file, kuriame yra visos funkcijos.
* students2.h -> antraštinis file.
* students.txt -> tekstinis duomenų failas.
## Ką daro ši programa
* Sugeneruoja atsitiktinius duomenis
* gali nuskaityti duomenis iš failo
* Duomenis gali įvesti pats vartotojas
* Matuoja funkcijų veikimo laikus
* Surūšiuoja duomenys i dvi kategorijas: "Smart" ir "Dummies"
* Gautus rezultatus pateikia lentelėje tekstiniame faile
* Gali apskaičiuoti tiek medianą, tiek vidurkį
* Palyginą kiek laiko trunka apskaičiuoti laiką vector ir list konteineriuose
