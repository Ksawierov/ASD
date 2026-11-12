#include <cstdio>
#include <cstdlib>
#include <random>
using namespace std;

mt19937 rng;
int losuj(int a, int b) {  // liczba z [a, b]
  return uniform_int_distribution<int>(a, b)(rng);
}

int main(int argc, char **argv) {
  rng.seed(argc > 1 ? atoi(argv[1]) : 0);
  int nmax = argc > 2 ? atoi(argv[2]) : 6;
  int amax = argc > 3 ? atoi(argv[3]) : 10;
  int n = losuj(1, nmax);
  printf("%d\n", n);
  for (int i = 0; i < n; i++) printf("%d ", losuj(1, amax));
  printf("\n");
}