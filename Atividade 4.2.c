#include <stdio.h>

typedef unsigned long long uint64;
typedef unsigned char uint8;

uint8 order(uint64 data) {
  uint8 bits = 0;
  while (data >>= 1) bits++;
  return bits;
}

uint64 transfer(uint64 data, uint64 gen) {
  uint8 odata = order(data);
  uint8 orgen = order(gen);
  uint8 smord = odata + orgen;
  uint64 send = data << orgen;
  uint64 rest = send;
  for (uint8 i = 0; i <= odata; i++)
    if (rest & (1ull << (smord - i)))
      rest ^= gen << (odata - i);
  return send ^ rest;
}

uint64 receiver(uint64 data, uint64 gen) {
  uint8 odata = order(data);
  uint8 smord = odata - order(gen);
  for (uint8 i = 0; i <= smord; i++)
    if (data & (1ull << (odata - i)))
      data ^= gen << (smord - i);
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