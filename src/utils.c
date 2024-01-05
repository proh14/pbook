#include <stdio.h>
#include <utils.h>

int lineNumber(char *filename) {
  FILE *fp = fopen(filename, "r");
  int lines = 0;
  int ch = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      lines++;
    }
  }

  fclose(fp);
  return lines;
}
