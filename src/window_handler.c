#include <ncurses.h>
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
