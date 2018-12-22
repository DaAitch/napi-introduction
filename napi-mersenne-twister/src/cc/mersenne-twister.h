#ifndef __MERSENNE_TWISTER_H__
#define __MERSENNE_TWISTER_H__
#include <array>

constexpr unsigned long N = 624;
constexpr unsigned long M = 397;
constexpr unsigned long MERSENNE_MULT = 1812433253ul;
constexpr unsigned long DEFAULT_SEED = 5489ul;
constexpr unsigned long A[2] = { 0, 0x9908B0DF };

template<typename T>
class MersenneTwister {
public:
  T Next();

  void SetSeed(T seed) {
    this->seed = seed;
  }

private:
  void Init();
  void Update();

  std::array<T, N> mt;
  int idx = N + 1;
  T seed = DEFAULT_SEED;
};

template<typename T>
void MersenneTwister<T>::Init() {
  for (int i = 0; i < mt.size(); i++) {
    mt[i] = seed;
    seed = MERSENNE_MULT * (seed ^ (seed >> 30)) + (i + 1);
  }
}

template<typename T>
void MersenneTwister<T>::Update() {

  int i = 0;
  for (; i < N-M; i++) {
    mt[i] = mt[i+(M  )] ^ (((mt[i  ] & 0x80000000) | (mt[i+1] & 0x7FFFFFFF)) >> 1) ^ A[mt[i+1] & 1];
  }

  for (; i < N-1; i++) { // ongoing loop on index `i`
    mt[i] = mt[i+(M-N)] ^ (((mt[i  ] & 0x80000000) | (mt[i+1] & 0x7FFFFFFF)) >> 1) ^ A[mt[i+1] & 1];
  }

  mt[N-1] = mt[M-1]     ^ (((mt[N-1] & 0x80000000) | (mt[0  ] & 0x7FFFFFFF)) >> 1) ^ A[mt[0  ] & 1];
}

template<typename T>
T MersenneTwister<T>::Next() {

  if (idx >= N) {
    if (idx > N) {
      Init();
    }

    Update();
    idx = 0;
  }

  T e = mt[idx++];
  e ^= (e >> 11);
  e ^= (e <<  7) & 0x9D2C5680;
  e ^= (e << 15) & 0xEFC60000;
  e ^= (e >> 18);

  return e;
}
#endif