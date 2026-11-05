#!/bin/bash

# 1. Definicja kolorów
GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color


# 2. Odczyt argumentów (z wartościami domyślnymi)
mode=${1:-default} # Jesli nie podano użyj standardowej wersji make
wzor=${2:-wzor}   # Jesli nie podano pliku użyj wzor.e
brut=${3:-brut}   
gen=${4:-gen}

# 3. Dobór flag kompilacji na podstawie trybu
case "$mode" in
    fast)
        FLAGS="-std=c++20 -O3 -Wall -Wextra"
        ;;
    test)
        FLAGS="-std=c++20 -O2 -Wall -Wextra -Werror -fsanitize=address,undefined -D_GLIBCXX_DEBUG -g"
        ;;
    *)
        mode="default"
        FLAGS="-std=c++20 -Og -Wall -Wextra -Werror -fsanitize=address,undefined -D_GLIBCXX_DEBUG -g"
        ;;
esac


# 4. Kompilacja plikow
echo -e "${CYAN}==> Kompilacja w trybie:  ${YELLOW}$mode...${NC}"

# Odpalamy kompilacje współbieżnie w tle (&) i zapisujemy ich PID-y ($!)
g++ $FLAGS "$wzor.cpp" -o "$wzor" & PID_WZOR=$!
g++ $FLAGS "$brut.cpp" -o "$brut" & PID_BRUT=$!
g++ -std=c++20 -O3 "$gen.cpp" -o "$gen" & PID_GEN=$!

# Czekamy na zakończenie każdego z procesów i sprawdzamy status
wait $PID_WZOR || { echo -e "${RED}Błąd kompilacji $wzor.cpp${NC}"; exit 1; }
echo -e "${GREEN} Skompilowano: ${NC}$wzor.cpp"

wait $PID_BRUT || { echo -e "${RED}Błąd kompilacji $brut.cpp${NC}"; exit 1; }
echo -e "${GREEN} Skompilowano: ${NC}$brut.cpp"

wait $PID_GEN || { echo -e "${RED}Błąd kompilacji $gen.cpp${NC}"; exit 1; }
echo -e "${GREEN} Skompilowano: ${NC}$gen.cpp"

echo -e "${GREEN}==> Kompilacja zakonczona sukcesem! Rozpoczynam testy...${NC}\n"

# Sprzątanie plików tymczasowych przy wyjściu
trap 'rm -f t.in wzor.out brut.out' EXIT


# 5. Pętla testująca
for i in $(seq 1 100); do
    echo -ne "\r${CYAN}Test ${YELLOW}#$i${NC}... \033[K"


    ./$gen $i > t.in
    ./$wzor < t.in > wzor.out
    ./$brut < t.in > brut.out

    if ! diff -wq wzor.out brut.out > /dev/null; then
        # Podajemy numer błędnej linii
        LINE_NUM=$(LC_ALL=C cmp wzor.out brut.out | awk -F'line ' '{print $2}')


        echo -e "\n\n${RED}BŁĄD!, ${CYAN}ziarno = $i${NC}\n"
        echo -e "${RED}Pierwsza różnica w linii nr: ${YELLOW}$LINE_NUM${NC}\n"
        echo -e "${CYAN}======Wejście (t.in)======${NC}"
        cat t.in
        echo -e "\n${RED}-----Otrzymano: ($wzor)-----"
        cat wzor.out
        
        echo -e "\n${GREEN}-----Oczekiwano: ($brut)-----"
        cat brut.out
        exit 1
    fi
done
echo "${GREEN} Wszystkie testy zaliczone pomyślnie!${NC}"