#include <contacts.h>
#include <menu.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ui.h>
#include <utils.h>

void init_ui(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
}

// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO
// with modification
static void middlePrint(WINDOW *win, int starty, int startx, int width,
                        const char *string) {
  int length, x, y;
  int temp;

  if (win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if (startx != 0)
    x = startx;
  if (starty != 0)
    y = starty;
  if (width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length) / 2;
  x = startx + (int)temp;
  mvwprintw(win, y, x, "%s", string);
  refresh();
}

void draw_menu(void) {
  ITEM **items;
  MENU *menu;
  WINDOW *win;

  int lines = lineNumber(FILENAME);

  items = malloc(sizeof(ITEM *) * lines + 1);

  FILE *fp = fopen(FILENAME, "r");
  namepair *np = malloc(sizeof(namepair) * lines);

  int i = 0;
  while (readContact(&np[i], fp) != EOF) {
    items[i] = new_item(np[i].name, np[i].numbers);
    i++;
  }
  fclose(fp);
  items[i] = NULL;

  win = newwin(LINES - 2, COLS, 1, 0);
  menu = new_menu(items);
  keypad(win, TRUE);

  int w_lines = LINES - 2;
  int w_cols = COLS;

  set_menu_win(menu, win);
  set_menu_sub(menu, derwin(win, w_lines - 3, w_cols - 1, 3, 1));
  set_menu_format(menu, w_lines - 4, 1);

  set_menu_mark(menu, "* ");
  box(win, 0, 0);
  post_menu(menu);
  refresh();

  mvwaddch(win, 2, 0, ACS_LTEE);
  mvwhline(win, 2, 1, ACS_HLINE, w_cols - 2);
  mvwaddch(win, 2, w_cols - 1, ACS_RTEE);
  middlePrint(win, 1, 0, w_cols, "CONTACTS");
  wrefresh(win);

  int c = 0;

  while ((c = wgetch(win)) != 'q') {
    switch (c) {
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    case 10:
      middlePrint(win, 1, 0, w_cols - 3, item_name(current_item(menu)));
    }
    wrefresh(win);
  }

  unpost_menu(menu);
  free_menu(menu);
  for (int i = 0; i < lines; i++) {
    free_item(items[i]);
  }
  free(np);
}

void draw_title(void) {
  const char *title = "pbook - a simple phonebook for TUI lovers";
  attron(A_REVERSE);
  mvprintw(0, 0, "%s", title);
  for (int i = strlen(title); i < COLS; i++) {
    mvprintw(0, i, " ");
  }
  attron(A_REVERSE);
  refresh();
}

void draw_help(void) {
  mvprintw(LINES - 1, 0, "Press 'q' to quit");
  refresh();
}

void end_ui(void) { endwin(); }
