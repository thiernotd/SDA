RED='\033[0;31m'
NC='\033[0m' # No Color


# Compilation et exécution en C:
echo "${RED} Compilation du code source en C ${NC}"
cd p/

make

echo "${RED} Exécution des benchmarks en C ${NC}"
./main.exe 250000
./main.exe 200000
./main.exe 150000
./main.exe 100000

echo "${RED} Nettoyage ${NC}"
make clean
