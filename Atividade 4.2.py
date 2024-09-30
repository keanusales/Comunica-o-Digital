from timeit import timeit

def sender(data: int, gen: int):
  orddt = data.bit_length() - 1
  ordgn = gen.bit_length() - 1
  sumord = orddt + ordgn
  send = temp = data << ordgn
  for i in range(orddt + 1):
    if temp & (1 << (sumord - i)):
      temp ^= gen << (orddt - i)
  return send ^ temp

def receiver(data: int, gen: int):
  orddt = data.bit_length() - 1
  ordgn = gen.bit_length() - 1
  sumord = orddt + ordgn
  for i in range(orddt + 1):
    if data & (1 << (sumord - i)):
      data ^= gen << (orddt - i)
  return data

def main():
  data, gen = 0b1101011011, 0b10011
  res = sender(data, gen)
  if res := receiver(res, gen):
    raise BufferError(f"{res} != 0")

if __name__ == "__main__":
  reps = 1_000_000
  ttime = timeit(main, number = reps)
  print(ttime / reps)