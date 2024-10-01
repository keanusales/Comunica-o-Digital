def transfer(data: int, gen: int):
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
  res = transfer(data, gen)
  print(f"Resposta: {bin(res)}")
  res = receiver(res, gen)
  print(f"Checagem: {bin(res)}")

if __name__ == "__main__": main()