#include <ncurses.h>
#include <string.h>
#include <window_handler.h>

void init_window(WINDOW **win, WINDOW **subwindow, int *rows, int *cols) {
  *cols = COLS / 2;
  *rows = LINES - 1;

  *win = newwin(*rows, *cols, 1, 0);
  keypad(*win, TRUE);

  *subwindow = derwin(*win, *rows - 3, *cols - 1, 3, 1);
}

void delete_window(WINDOW *win, WINDOW *subwindow) {
  delwin(subwindow);
  delwin(win);
}

void reformat(WINDOW *win, int w_cols) {
  box(win, 0, 0);
  mvwaddch(win, 2, 0, ACS_LTEE);
  mvwaddch(win, 2, w_cols - 1, ACS_RTEE);
  mvwhline(win, 2, 1, ACS_HLINE, w_cols - 2);
  wrefresh(win);
}

// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO
// with modification
void middlePrint(WINDOW *win, int starty, int startx, int width,
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
