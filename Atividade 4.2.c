#include <stdio.h>

typedef unsigned long long uint64;
typedef unsigned char uint8;

uint8 order(uint64 data) {
  uint8 bits = 0;
  while (data >>= 1) bits++;
  return bits;
}

uint64 transfer(uint64 data, uint64 gen) {
  uint8 orddt = order(data);
  uint8 ordgn = order(gen);
  uint8 sumord = orddt + ordgn;
  uint64 send = data << ordgn;
  uint64 temp = send;
  for (uint8 i = 0; i <= orddt; i++)
    if (temp & (1ull << (sumord - i)))
      temp ^= gen << (orddt - i);
  return send ^ temp;
}

uint64 receiver(uint64 data, uint64 gen) {
  uint8 orddt = order(data);
  uint8 ordgn = order(gen);
  uint8 sumord = orddt + ordgn;
  for (uint8 i = 0; i <= orddt; i++)
    if (data & (1ull << (sumord - i)))
      data ^= gen << (orddt - i);
  return data;
}

void main() {
  uint64 gen = 0b10011;
  uint64 data = 0b1101011011;
  uint64 res1 = transfer(data, gen);
  printf("Resposta: %llu\n", res1);
  uint64 res2 = receiver(res1, gen);
  printf("Checagem: %llu\n", res2);
}