#include <ctype.h>
#include <stdio.h>
#include <string.h>
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

char *rtrim(char *s) {
  for (int i = strlen(s) - 1; i > 0; i--) {
    if (!isspace(s[i])) {
      break;
    }
    s[i] = '\0';
  }
  return s;
}
