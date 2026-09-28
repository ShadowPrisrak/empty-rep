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
    for (size_t j = 0; j<n; ++j) {
      newMtx[j][i] = mtx[i][j];
    }
  }
  return newMtx;
}

void printMtx(int ** mtx, size_t m, size_t n) {
  for (size_t i = 0; i<m; ++i) {
    for (size_t j = 0; j<n; ++j) {
      std::cout << mtx[i][j] << (j + 1 == n ? "" : " ");
    }
    std::cout << '\n';
  }
}



int main() {
  size_t m = 0;
  size_t n = 0;

  if (!(std::cin >> m >> n) || m==0 || n==0) {
    return 1;
  }

  int ** mtx = nullptr;
  int ** tMtx = nullptr;

  try {
    mtx = makeMtx(m,n);
  } catch (const std::bad_alloc &) {
    return 2;
  }

  for (size_t i = 0; i<m; ++i) {
    for (size_t j = 0: j<n; ++j) {
      if (!(std::cin >> mtx[i][j])) {
        rmMtx(mtx, m);
        return 1;
      }
    }
  }

  try {
    tMtx = transpose(mtx,m,n);
  } catch (const std::bad_alloc &) {
    rmMtx(mtx,m);
    return 2;
  }

  printMtx(tMtx, n, m);

  rmMtx(mtx, m);
  rmMtx(mtx, n);

  return 0;

}
