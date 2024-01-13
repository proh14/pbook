#include <contacts.h>
#include <ctype.h>
#include <form_handler.h>
#include <menu.h>
#include <menu_handler.h>
#include <ncurses.h>
#include <string.h>
#include <ui.h>
#include <window_handler.h>

static WINDOW *win;
static WINDOW *subwindow;
static int w_lines;
static int w_cols;

#define CTRL(k) ((k)&0x1f)

void init_ui(void) {
  initscr();
  cbreak();
  noecho();
  raw();
  keypad(stdscr, TRUE);
  init_window(&win, &subwindow, &w_lines, &w_cols);
  refresh();
  curs_set(0);
}

void draw_form(person *p) {
  curs_set(1);
  FORM *form;
  const int MAX_FIELDS = 7;
  FIELD *fields[MAX_FIELDS];
  for (int i = 0; i < MAX_FIELDS; i++) {
    fields[i] = NULL;
  }
  init_fields(fields, MAX_FIELDS, w_lines);
  set_field_buffers(p, fields);

  form = new_form(fields);
  init_form(form, win, subwindow);

  post_form(form);
  reformat(win, w_cols);
  draw_field_names(subwindow, MAX_FIELDS, w_lines);

  int c = 0;

  form_driver(form, REQ_END_LINE);
  while ((c = wgetch(win)) != CTRL('q')) {
    do_form_key(form, c);
  }

  set_person_from_field(fields, p);

  unpost_form(form);

  free_form(form);
  free_fields(fields);
  refresh();
  curs_set(0);
}

void draw_menu(void) {
  ITEM **items = {NULL};
  MENU *menu;
  namepair *np = init_items(&items);

  person *p;
  person cp;

  menu = new_menu(items);
  init_menu(menu, win, subwindow, w_lines);

  reformat(win, w_cols);
  middlePrint(win, 1, 0, w_cols, "CONTACTS");

  post_menu(menu);

  int c = 0;

  while (tolower((c = wgetch(win))) != CTRL('q')) {
    switch (c) {
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    case 10:
      unpost_menu(menu);
      p = searchContact(item_name(current_item(menu)));
      if (p == NULL) {
        break;
      }
      cp = *p;
      draw_form(p);
      editContact(&cp, p);
      update_menu(menu, &items, &np);
      post_menu(menu);
      reformat(win, w_cols);
      free(p);
      break;
    case 'd':
      unpost_menu(menu);
      p = searchContact(item_name(current_item(menu)));
      if (p == NULL) {
        break;
      }
      deleteContact(p);
      update_menu(menu, &items, &np);
      reformat(win, w_cols);
      post_menu(menu);
      free(p);
      break;
    case 'a':
      unpost_menu(menu);
      p = malloc(sizeof(person));
      fillContact(p);
      draw_form(p);
      addContact(p);
      update_menu(menu, &items, &np);
      reformat(win, w_cols);
      post_menu(menu);
      free(p);
      break;
    }
    wrefresh(win);
  }

  unpost_menu(menu);
  free_menu(menu);
  free_items(&items);
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

void draw_help(void) { (void)0; }

void end_ui(void) {
  delete_window(win, subwindow);
  endwin();
}
