#include <contacts.h>
#include <menu.h>
#include <menu_handler.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

namepair *init_items(ITEM ***items) {
  int lines = lineNumber(FILENAME);

  free(*items);
  *items = malloc(sizeof(ITEM *) * (lines + 1));

  FILE *fp = fopen(FILENAME, "r");
  namepair *np = malloc(sizeof(namepair) * lines);

  int i = 0;
  while (readContact(&np[i], fp) != EOF) {
    (*items)[i] = new_item(np[i].name, np[i].numbers);
    i++;
  }
  fclose(fp);
  items[i] = NULL;
  return np;
}

void free_items(ITEM *items[]) {
  int i;
  for (i = 0; items[i] != NULL; i++) {
    free_item(items[i]);
  }
}
