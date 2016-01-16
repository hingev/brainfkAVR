
#ifndef _PARSE_OPTS_H
#define _PARSE_OPTS_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <sysexits.h>

struct CmdParams {
  char* in_file;
  char* out_file;
};

void error (const char *str, int code) {
  fprintf (stderr, "Error: %s\n", str);
  exit (code);
}

void parse_opts (int argc, char *argv[], struct CmdParams *params) {
  size_t i;

  for (i=1; i < argc; ++i) {
    // printf ("Opt[%d] = %s\n", i, argv[i]);
    if (strcmp ("-o", argv[i]) == 0) {
      if (i + 1 >= argc)
	error ("-o takes one argument, none given", EX_USAGE);
      params->out_file = argv[++i];
    } else {
      params->in_file = argv[i];
    }
  }

}

#endif
