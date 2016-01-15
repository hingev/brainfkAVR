
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define VERSION "0.07b"

//TODO: add UART support
//TODO: later, even add SPI, I2C, etc.

//TODO: add option for the working register
//      right now, it will be r16

//TODO: add starting RAM address
//      right now, it will be 300

#include "bfc.h"

uint16_t address = MIN_ADDRESS; // SRAM address
uint16_t inst_addr = 0; // instruction address

#define MAX_STACK 1024
uint16_t stack[MAX_STACK];
size_t sp = 0;

//TODO: add atexit
//TODO: write some definitions in header files -_-

int main (int argc, char* argv) {
  puts ("BFC version " VERSION);
  // TODO: parse the options

  // for simplicity: now tries src.bf as source
  // outputs a .bin file

  char infile[] = "src.bf";
  FILE *in = fopen (infile, "r");
  assert (! (in == NULL));
  printf ("Reading file: %s..\n", infile);

  char outfile[] = "out.bin";
  FILE *out = fopen (outfile, "wb");
  FILE *crt;

  char c, tc1, tc2;

  // TODO: write the 'crt0' to outfile
  // TODO: inst_addr += len (crt0)

  /* fprintf (out, "%c%c", 0x00, 0xe0); // ldi r16, 0 */
  /* fprintf (out, "%c%c%c%c", STS_inst, BYTE (address)); */
  /* inst_addr += 3; */
  crt = fopen ("crt_0.bin", "rb");
  while (1) {
    fscanf (crt, "%c%c", &tc1, &tc2);
    if (feof (crt))
      break;
    fprintf (out, "%c%c", tc1, tc2);
    inst_addr ++;
  }
  fclose (crt);

  // load the starting address into X
  fprintf (out, "%c%c", LDI (26, MIN_ADDRESS & 0xFF));
  fprintf (out, "%c%c", LDI (27, (MIN_ADDRESS >> 8) & 0xFF));
  inst_addr += 2;
  
  printf ("Inst_addr: %u\n", inst_addr);

  FILE* debug = fopen ("debug.txt", "w");
  uint16_t cur_char = 0, cur_line = 0;
  while (! feof (in)) {
    c = fgetc (in);
    cur_char ++;
    if (c == '\n') cur_line ++;
    if (feof (in)) c = '#';
    fprintf (debug, "%c : %02x\n", c, inst_addr * 2);
    // printf ("%c\n", c);
    switch (c) {
    case '+': case '-':
      // fprintf (out, "%c%c%c%c", LDS_inst, BYTE(address));
      fprintf (out, "%c%c", LD(16));
      if (c == '+')
	fprintf (out, "%c%c", INC_inst);
      else
	fprintf (out, "%c%c", DEC_inst);
      // fprintf (out, "%c%c%c%c", STS_inst, BYTE(address));      
      fprintf (out, "%c%c", ST(16));
      inst_addr+=3;
      break;
    case '>':
      fprintf (out, "%c%c", LD_inc (2));
      inst_addr ++;
      if (address == MAX_ADDRESS)
	address = MIN_ADDRESS;
      else
	address ++;
      break;
    case '<':
      fprintf (out, "%c%c", LD_dec (2));
      inst_addr ++;
      if (address == MIN_ADDRESS)
	address = MAX_ADDRESS;
      else
	address --;
      break;
    case '[':
      stack[sp++] = inst_addr;
      // fprintf (out, "%c%c%c%c", LDS_inst, BYTE (address));
      fprintf (out, "%c%c", LD(16));
      fprintf (out, "%c%c", CPI_inst);
      fprintf (out, "%c%c", BRNE_inst);
      fprintf (out, "%c%c%c%c", JMP_inst, BYTE (0x00)); // address appended later
      printf ("Adding to stack: %u\n", stack[sp-1]);
      inst_addr += 5;
      break;
    case ']':
      if (sp == 0) {
	fprintf (stderr, "%s:%u:%u: error: closing bracket, without opening one :(\n",
		 infile, cur_line, cur_char);
	exit (-1);
      }
      // BRNE back
      // fprintf (out, "%c%c%c%c", LDS_inst, BYTE (address));
      fprintf (out, "%c%c", LD(16));
      fprintf (out, "%c%c", CPI_inst);
      /* fprintf (out, "%c%c", IN_SREG_inst); */
      /* fprintf (out, "%c%c", SBRS_inst); */
      fprintf (out, "%c%c", BREQ_inst);
      
      printf ("Pulling from stack: %u\n", stack[sp-1]);
      fprintf (out, "%c%c%c%c", JMP_inst, BYTE (stack[sp-1] + 5));

      inst_addr += 5; // CHANGE

      long f_loc = ftell (out);
      fseek (out, (stack[sp-1] + 4)* 2, SEEK_SET);
      fprintf (out, "%c%c", BYTE (inst_addr));
      fseek (out, f_loc, SEEK_SET);

      sp --;
      break;
    case '.':
      // TEMPERARY solution
      // rewrite UART stuff from crt_t0.bin
      crt = fopen ("crt_t0.bin", "rb");
      // fprintf (out, "%c%c%c%c", LDS_inst, BYTE(address));
      fprintf (out, "%c%c", LD (16));
      inst_addr += 1;
      while (1) {
	fscanf (crt, "%c%c", &tc1, &tc2);
	if (feof (crt))
	  break;
	fprintf (out, "%c%c", tc1, tc2);
	inst_addr ++;
      }
      break;
    default:
      break;
    }
  }

  // cbi	0x05, 0
  fprintf (out, "%c%c", 0x28, 0x98);
  // rjmp -2
  fprintf (out, "%c%c", 0xff, 0xcf);
  // jump 0
  //fprintf (out, "%c%c%c%c", JMP_inst, 0x0, 0x0);

  puts ("Done!..");
  
  fflush (out);
  fflush (debug);
  fclose (debug);
  fclose (out);
  fclose (in);
  
  return 0;
}
