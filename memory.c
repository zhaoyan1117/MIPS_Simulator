#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

/* Pointer to simulator memory */
uint8_t *mem;

/* Called by program loader to initialize memory. */
uint8_t *init_mem() {
  assert (mem == NULL);
  mem = calloc(MEM_SIZE, sizeof(uint8_t)); // allocate zeroed memory
  return mem;
}

/* Returns 1 if memory access is ok, otherwise 0 */
int access_ok(uint32_t mipsaddr, mem_unit_t size) {

  int mod_result = mipsaddr % size;

  //mipsaddr is outside of range.
  if ( (mipsaddr >= MEM_SIZE) | (mipsaddr < 1) )
	  return 0;

  //mipsaddr is misaligned (not divisible by size).
  if (mod_result != 0)
	  return 0;

  //access is ok.
  return 1;
}

/* Writes size bytes of value into mips memory at mipsaddr */
void store_mem(uint32_t mipsaddr, mem_unit_t size, uint32_t value) {
  if (!access_ok(mipsaddr, size)) {
    fprintf(stderr, "%s: bad write=%08x\n", __FUNCTION__, mipsaddr);
    exit(-1);
  }

  switch (size)
  {

  case SIZE_BYTE:
	mem[mipsaddr] = 0xff & value;
	break;

  case SIZE_HALF_WORD:
	mem[mipsaddr] = 0xff & value;
	value = value >> 8;
	mem[mipsaddr+1] = 0xff & value;
	break;

  case SIZE_WORD:
	mem[mipsaddr] = 0xff & value;
	value = value >> 8;
	mem[mipsaddr+1] = 0xff & value;
	value = value >> 8;
	mem[mipsaddr+2] = 0xff & value;
	value = value >> 8;
	mem[mipsaddr+3] = 0xff & value;
	break;

  default:
	break;
  }

}

/* Returns zero-extended value from mips memory */
uint32_t load_mem(uint32_t mipsaddr, mem_unit_t size) {
  if (!access_ok(mipsaddr, size)) {
    fprintf(stderr, "%s: bad read=%08x\n", __FUNCTION__, mipsaddr);
    exit(-1);
  }

  switch (size)
  {
  case SIZE_WORD:
	return (uint32_t) *(uint32_t*)(mem + mipsaddr);

  case SIZE_HALF_WORD:
	return (uint32_t) *(uint16_t*)(mem + mipsaddr);

  case SIZE_BYTE:
	return (uint32_t) *(uint8_t*)(mem + mipsaddr);

  default:
	return 0x0;
  }

}
