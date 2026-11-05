// gen.cpp — generator testów: ./gen.e <ziarno> [nmax] [tmax]
#include <cstdio>
#include <cstdlib>
#include <random>
using namespace std;

mt19937 rng;
int losuj(int a, int b) {  // liczba z [a, b]
  return uniform_int_distribution<int>(a, b)(rng);
}

int main(int argc, char **argv) {
  rng.seed(argc > 1 ? atoi(argv[1]) : 0);            // jawne ziarno = powtarzalny test
  int nmax = argc > 2 ? atoi(argv[2]) : 8;           // małe n — kontrtest da się policzyć
  int tmax = argc > 3 ? atoi(argv[3]) : 1000000000;  // zakres czasów
  // --- od tej linii: format wejścia konkretnego zadania (tu: par) ---
  int n = losuj(1, nmax);
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    int w = losuj(0, tmax - 1);
    printf("%d %d\n", w, losuj(w + 1, tmax));  // w < o
  }
}