#include <stdio.h>
#include "./Sponge.h"
#include "./Sponge.c"
#include <inttypes.h>

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
  printf("Bin: "OCT_BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(pica>>56), BYTE_TO_BINARY(pica>>48), BYTE_TO_BINARY(pica>>40), BYTE_TO_BINARY(pica>>32), BYTE_TO_BINARY(pica>>24), BYTE_TO_BINARY(pica>>16), BYTE_TO_BINARY(pica>>8), BYTE_TO_BINARY(pica));
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

int main() {

/*Blake2b IV Array*/
  uint64_t ref[8] =
  {
    0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
    0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
    0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
    0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
  };
  // 0x6a09e667f3bcc908ULL
  uint64_t rot5 = rotr64(ref[0], 5);
  uint64_t state[16];

  uint64_t column = 0x1f83d9aCDbAAbd6bULL;

  uint64_t columns[12] = {
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL,
    0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL, 0x1f83d9aCDbAAbd6bULL
  };

  initState(state);

  printf("This will be our comparator file:\n\n\n");

  printf("Sponge.c/h internals:\n\n");

  printf("Referencia: %" PRIu64 "\n", ref[0]);

  printf("\nReferencia em binario:\n");
  print64ulong(ref[0]);

  printf("\nRotaciona 5 vezes:\n");
  print64ulong(rot5);

  printf("\nEstado inicial:\n");
  printState(state);
  
  // printf("\nG 0, 1, 10, 11, 12, 13:\n");
  // G(0, 1, state[10], state[11], state[12], state[13]);
  // printState(state);
  
  // printf("ROUND LYRA: \n");
  // ROUND_LYRA(0, state);
  // printState(state);

  printf("spongeLyra(state)\n");
  spongeLyra(state);
  printState(state);

  // printf("absorbColumn(state, column)\n");
  // absorbColumn(&state, &columns);
  // printState(state);

  printf("absorbBlockBlake2Safe(state, column)\n");
  absorbBlockBlake2Safe(&state, &columns);
  printState(state);

  printf("\n\n");
  return 0;
};