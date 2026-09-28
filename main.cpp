#include <iostream>
#include <stdexcept>


void rmMtx(int ** mtx, size_t m);

int ** makeMtx(size_t m, size_t n) {
  int ** mtxR = new int * [m];

  for (size_t i = 0; i<m; ++i) {
    mtxR[i] = nullpr;
  }

  try {
    for (size_t i = 0; i<m; ++i) {
      mtxR[i] = new int [n];
    }
    return mtxR;
  catch (const std::bad_alloc & e) {
    rmMtx(mtxR, m);
    throw;
  }
}

void rmMtx(int ** mtx, size_t m) {
  if (!mtx) return;
  for (size_t i = 0; i<m; ++i) {
    delete [] mtx[i];
  }
  delete [] mtx;
}

int ** transpose(int ** mtx, size_t m, size_t n) {
  int ** newMtx = makeMtx(n,m);

  for (size_t i = 0; i<m; ++i) {
    for (size_t j = 0; j<m; ++j) {
      std::cout << mtx[i][j] << (j + 1 == n ? "" : " ");
    }
    std::cout << '\n';
  }
}

















int main() {
    size_t m = 0;
    size_t n = 0;
    std::cin >> m >> n;
    if (!std::cin) {
        return 1;
    }

    int ** mtx =nullptr;
    mtx = makeMtx(mtx,m,n);

    for (size_t i = 0; i<m*n; ++i) {
        std::cin >> mtx[i/m][i%m] = 0;

    }

    if (std::cin.fail()) {
        rmMtx(mtx,m);
    }

    transpose(mtx);


    for (size_t i = 0; i<m*n; ++i) {
        std::cout << mtx[i/m][i%m] = 0;

    }

    rmMtx(mtx,m);

}
