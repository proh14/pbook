#include <contacts.h>
#include <menu_handler.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

namepair *init_items(ITEM ***items) {
  int lines = lineNumber(FILENAME);

  *items = malloc(sizeof(ITEM *) * (lines + 1));

  int i = 0;
  for (i = 0; i < lines + 1; i++) {
    (*items)[i] = NULL;
  }

  FILE *fp = fopen(FILENAME, "r");
  namepair *np = malloc(sizeof(namepair) * lines);

  i = 0;
  while (readContact(&np[i], fp) != EOF) {
    (*items)[i] = new_item(np[i].name, np[i].numbers);
    i++;
  }
  fclose(fp);
  return np;
}

void free_items(ITEM ***items) {
  int i;
  for (i = 0; (*items)[i] != NULL; i++) {
    free_item((*items)[i]);
  }
  free_item((*items)[i]);
  free(*items);
}

void init_menu(MENU *menu, WINDOW *win, WINDOW *subwindow, int w_lines) {
  set_menu_win(menu, win);
  set_menu_sub(menu, subwindow);
  set_menu_format(menu, w_lines - 4, 1);

  set_menu_mark(menu, "* ");
}
