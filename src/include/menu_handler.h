#pragma once
#ifndef _MENU_HANDLER_H_
#define _MENU_HANDLER_H_

#include <contacts.h>
#include <menu.h>

namepair *init_items(ITEM ***items);
void free_items(ITEM *items[]);
void init_menu(MENU *menu, WINDOW *win, WINDOW *subwindow, int w_lines);

#endif
