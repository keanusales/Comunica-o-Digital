from crc import transfer, receiver
from timeit import timeit

def main():
  data, gen = 0b1101011011, 0b10011
  res = transfer(data, gen)
  if res := receiver(res, gen):
    raise BufferError(f"{res} != 0")

if __name__ == "__main__":
  reps = 1_000_000
  time = timeit(main, number = reps)
  print(f"Média: {time / reps}")
  print(f"Total: {time}")