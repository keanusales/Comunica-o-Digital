#include <stdint.h>
#include <stdio.h>

uint8_t order(uint64_t data) {
  uint8_t bits = 0;
  while (data >>= 1) bits++;
  return bits;
}

uint64_t transfer(uint64_t data, uint64_t gen) {
  const uint8_t orddt = order(data);
  const uint8_t ordgn = order(gen);
  const uint8_t sumord = orddt + ordgn;
  uint64_t temp = data << ordgn;
  const uint64_t send = temp;
  for (uint8_t i = 0; i <= orddt; i++)
    if (temp & (1ull << (sumord - i)))
      temp ^= gen << (orddt - i);
  return send ^ temp;
}

uint64_t receiver(uint64_t data, uint64_t gen) {
  const uint8_t orddt = order(data);
  const uint8_t ordgn = order(gen);
  const uint8_t sumord = orddt + ordgn;
  for (uint8_t i = 0; i <= orddt; i++)
    if (data & (1ull << (sumord - i)))
      data ^= gen << (orddt - i);
  return data;
}

int main() {
  uint64_t res;
  const uint64_t gen = 0b10011;
  const uint64_t data = 0b1101011011;
  res = transfer(data, gen);
  printf("Resposta: %llu\n", res);
  res = receiver(res, gen);
  printf("Checagem: %llu\n", res);
  return 0;
}