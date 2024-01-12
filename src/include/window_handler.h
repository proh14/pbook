#pragma once
#ifndef _WINDOW_HANDLER_H_
#define _WINDOW_HANDLER_H_

#include <ncurses.h>

void init_window(WINDOW **win, WINDOW **subwin, int *rows, int *cols);
void delete_window(WINDOW *win, WINDOW *subwin);
void reformat(WINDOW *win, int w_cols);
void middlePrint(WINDOW *win, int starty, int startx, int width,
                 const char *string);

#endif
