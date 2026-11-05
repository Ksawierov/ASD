// gen.cpp — losowy graf: ./gen.e <ziarno> [nmax] [mmax] [pmax] [cmax]
#include <cstdio>
#include <cstdlib>
#include <random>
using namespace std;

constexpr long long INF = 1e9;

mt19937 rng;
int losuj(int a, int b) {  // liczba z [a, b]
  return uniform_int_distribution<int>(a, b)(rng);
}

int main(int argc, char **argv) {
  rng.seed(argc > 1 ? atoi(argv[1]) : 0);
  int nmax = argc > 2 ? atoi(argv[2]) : 5;
  int mmax = argc > 3 ? atoi(argv[3]) : 15;
  int pmax = argc > 4 ? atoi(argv[4]) : INF;
  int cmax = argc > 5 ? atoi(argv[5]) : INF;
  // --- od tej linii: format wejścia konkretnego zadania (tu: tra) ---
  int n = losuj(2, nmax), m = losuj(n, mmax);
  printf("%d %d\n", n, m);
  for (int i = 0; i < m; i++) {
    int u = losuj(1, n), v = losuj(1, n - 1);
    if (v >= u) v++;  // u != v
    printf("%d %d %d %d\n", u, v, losuj(INF / 2, pmax), losuj(INF / 2, cmax));
  }
}