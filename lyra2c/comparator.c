#include <stdio.h>
#include "./Sponge.h"
#include "./Sponge.c"
#include <inttypes.h>

/**
 * Funcoes uteis para printing
 * 
 * */
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define OCT_BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

// Printa uint64_t em binario
void print64ulong (uint64_t pica) {
  printf("Dec: %"PRIu64"\n", pica);
  printf("Hex: %016llX\n", pica);
  printf("Bin: "OCT_BYTE_TO_BINARY_PATTERN"\n\n", BYTE_TO_BINARY(pica>>56), BYTE_TO_BINARY(pica>>48), BYTE_TO_BINARY(pica>>40), BYTE_TO_BINARY(pica>>32), BYTE_TO_BINARY(pica>>24), BYTE_TO_BINARY(pica>>16), BYTE_TO_BINARY(pica>>8), BYTE_TO_BINARY(pica));
}

void printState(uint64_t state[]) {
  printf("Estado\n");
  printf("Hex[00]: %016llX\n", state[0]);
  printf("Hex[01]: %016llX\n", state[1]);
  printf("Hex[02]: %016llX\n", state[2]);
  printf("Hex[03]: %016llX\n", state[3]);
  printf("Hex[04]: %016llX\n", state[4]);
  printf("Hex[05]: %016llX\n", state[5]);
  printf("Hex[06]: %016llX\n", state[6]);
  printf("Hex[07]: %016llX\n", state[7]);
  printf("Hex[08]: %016llX\n", state[8]);
  printf("Hex[09]: %016llX\n", state[9]);
  printf("Hex[10]: %016llX\n", state[10]);
  printf("Hex[11]: %016llX\n", state[11]);
  printf("Hex[12]: %016llX\n", state[12]);
  printf("Hex[13]: %016llX\n", state[13]);
  printf("Hex[14]: %016llX\n", state[14]);
  printf("Hex[15]: %016llX\n\n", state[15]);
}

/*
Converte string para int
*/
int my_getnbr(char *str)
{
  int result;
  int puiss;

  result = 0;
  puiss = 1;
  while (('-' == (*str)) || ((*str) == '+'))
  {
      if (*str == '-')
        puiss = puiss * -1;
      str++;
  }
  while ((*str >= '0') && (*str <= '9'))
  {
      result = (result * 10) + ((*str) - '0');
      str++;
  }
  return (result * puiss);
}

// Declaracao de variaveis de teste
uint64_t ref[8] =
{
  0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
  0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
  0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
  0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
};

/**
 * "Testes" 
 * */

void testInitState(uint64_t state[]) {
  printState(state);
}

void testRotr64() {
  uint64_t rot5 = rotr64(ref[0], 5);
  print64ulong(rot5);
}

void testblake2bG(uint64_t state[]) {
  G(0, 1, state[10], state[11], state[12], state[13]);
  printState(state);
}

void testRoundLyra(uint64_t state[]) {
  ROUND_LYRA(0, state);
  printState(state);
}

void testSpongeLyra(uint64_t state[]) {
  spongeLyra(state);
  printState(state);
}

void testAbsorbColumn(uint64_t state[]) {
  uint64_t columns[12] = {
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL
  };
  absorbColumn(state, columns);
  printState(state);
}

void testAbsorbBlockBlake2Safe(uint64_t state[]) {
  uint64_t columns[12] = {
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL
  };
  absorbBlockBlake2Safe(state, columns);
  printState(state);
}

int main (int argc, char **argv) {
  int functionBeingTesting = 0;  
  uint64_t state[16];
  uint64_t column = 0x1f83d9aCDbAAbd6bULL;
  uint64_t columns[12] = {
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL
  };

  if (argc >= 2) {
    functionBeingTesting = my_getnbr(argv[1]);
  }

  printf("Function being tested: %d\n", functionBeingTesting);

  initState(state);

  switch(functionBeingTesting) {
    case 0: // initState
      printf("Test initState()\n");
      testInitState(state);
      break;
    case 1: // rotr64()
      printf("Test rotr64()\n");
      testRotr64();
      break;
    case 2: // blake2bG()
      printf("Test blake2bG()\n");
      testblake2bG(state);
      break;
    case 3: // ROUND_LYRA
      printf("Test ROUND_LYRA()\n");
      testRoundLyra(state);
      break;
    case 4: // SpongeLyra
      printf("Test SpongeLyra()\n");
      testSpongeLyra(state);
      break;
    case 5:
      printf("Test absorbColumn()\n");
      testAbsorbColumn(state);
      break;
    case 6:
      printf("Test absorbBlockBlake2Safe()\n");
      testAbsorbBlockBlake2Safe(state);
      break;    
    default:
      break;
  }

  printf("\n\n");
  return 0;
};