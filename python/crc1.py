from timeit import timeit

def transfer(data: int, gen: int):
  odata = data.bit_length() - 1
  orgen = gen.bit_length() - 1
  order = odata + orgen
  send = rest = data << orgen
  for i in range(odata + 1):
    if rest & (1 << (order - i)):
      rest ^= gen << (odata - i)
  return send ^ rest

def receiver(data: int, gen: int):
  odata = data.bit_length() - 1
  orgen = gen.bit_length() - 1
  order = odata - orgen
  for i in range(order + 1):
    if data & (1 << (odata - i)):
      data ^= gen << (order - i)
  return data

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