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
  int nmax = argc > 2 ? atoi(argv[2]) : 800;           // małe n — kontrtest da się policzyć
  int tmax = argc > 3 ? atoi(argv[3]) : 10000000;  // zakres czasów
  // --- od tej linii: format wejścia konkretnego zadania (tu: par) ---
  int n = losuj(nmax / 2, nmax);
  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    int znak = losuj(0, 1);
    int w = losuj(0, tmax - 1);
    if(znak)
        w *= -1;
    printf("%d ", w);  // w < o
  }
  printf("\n");
}