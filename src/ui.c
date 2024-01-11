#include <contacts.h>
#include <form.h>
#include <menu.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ui.h>
#include <utils.h>

static WINDOW *win;
static WINDOW *subwindow;
static int w_lines;
static int w_cols;

#define CTRL(k) ((k)&0x1f)

struct field_settings {
  int max;
  char *name;
};

const struct field_settings opts[] = {
    {MAX_NAME, "Name: "},        {MAX_NUMBERS, "Phone number: "},
    {MAX_EMAIL, "Email: "},      {MAX_BIRTHDAY, "Birthday: "},
    {MAX_ADDRESS, "Adress 1: "}, {MAX_ADDRESS, "Adress 2: "},
};

void init_ui(void) {
  initscr();
  cbreak();
  noecho();
  raw();
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

static void init_fields(FIELD *fields[], int num) {
  int i = 0;
  int y = 2;
  while (i < num - 1) {
    fields[i] = new_field(1, 20, y, 15, 0, 0);
    field_opts_off(fields[i], O_STATIC);
    set_max_field(fields[i], opts[i].max);
    set_field_back(fields[i], A_UNDERLINE);
    field_opts_off(fields[i], O_AUTOSKIP);
    y += (w_lines) / num;
    i++;
  }
}

static void set_field_buffers(person *p, FIELD *fields[]) {
  int i = 0;
  char *buffers[] = {
      p->name, p->numbers, p->email, p->birthday, p->address, p->address2,
  };
  while (fields[i] != NULL) {
    set_field_buffer(fields[i], 0, buffers[i]);
    i++;
  }
}

static void free_fields(FIELD *fields[]) {
  int i = 0;
  while (fields[i] != NULL) {
    free_field(fields[i]);
    i++;
  }
}

static void draw_field_names(int num) {
  int i;
  int y = 2;
  for (i = 0; i < num - 1; i++) {
    mvwprintw(subwindow, y, 0, "%s", opts[i].name);
    y += (w_lines) / num;
  }
}

static void set_person_from_field(FIELD *fields[], person *p) {
  char *buffers[] = {
      p->name, p->numbers, p->email, p->birthday, p->address, p->address2,
  };
  int i = 0;
  while (fields[i] != NULL) {
    strcpy(buffers[i], rtrim(field_buffer(fields[i], 0)));
    i++;
  }
}

void draw_form(person *p) {
  curs_set(1);
  FORM *form;
  const int MAX_FIELDS = 7;
  FIELD *fields[MAX_FIELDS];
  for (int i = 0; i < MAX_FIELDS; i++) {
    fields[i] = NULL;
  }
  init_fields(fields, MAX_FIELDS);
  set_field_buffers(p, fields);
  form = new_form(fields);
  set_form_win(form, win);
  set_form_sub(form, subwindow);

  post_form(form);
  box(win, 0, 0);
  mvwaddch(win, 2, 0, ACS_LTEE);
  mvwaddch(win, 2, w_cols - 1, ACS_RTEE);
  draw_field_names(MAX_FIELDS);
  wrefresh(win);
  refresh();

  int c = 0;

  form_driver(form, REQ_END_LINE);
  while ((c = wgetch(win)) != CTRL('q')) {
    switch (c) {
    case KEY_UP:
      form_driver(form, REQ_PREV_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    case KEY_DOWN:
    case 10:
      form_driver(form, REQ_NEXT_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    case KEY_RIGHT:
      form_driver(form, REQ_NEXT_CHAR);
      break;
    case KEY_LEFT:
      form_driver(form, REQ_PREV_CHAR);
      break;
    case 127:
      form_driver(form, REQ_PREV_CHAR);
      form_driver(form, REQ_DEL_CHAR);
      break;
    case KEY_DC:
      form_driver(form, REQ_DEL_CHAR);
      break;
    default:
      form_driver(form, c);
      break;
    }
  }

  set_person_from_field(fields, p);
  unpost_form(form);
  free_form(form);
  free_fields(fields);
  refresh();
  curs_set(0);
}

void draw_menu(void) {
  ITEM **items;
  MENU *menu;

  int lines = lineNumber(FILENAME);

  items = malloc(sizeof(ITEM *) * (lines + 1));

  FILE *fp = fopen(FILENAME, "r");
  namepair *np = malloc(sizeof(namepair) * lines);

  int i = 0;
  while (readContact(&np[i], fp) != EOF) {
    items[i] = new_item(np[i].name, np[i].numbers);
    i++;
  }
  fclose(fp);
  items[i] = NULL;

  w_cols = COLS / 2;
  w_lines = LINES - 1;

  win = newwin(w_lines, w_cols, 1, 0);
  menu = new_menu(items);
  keypad(win, TRUE);

  subwindow = derwin(win, w_lines - 3, w_cols - 1, 3, 1);

  set_menu_win(menu, win);
  set_menu_sub(menu, subwindow);
  set_menu_format(menu, w_lines - 4, 1);

  set_menu_mark(menu, "* ");
  box(win, 0, 0);
  post_menu(menu);
  refresh();

  mvwaddch(win, 2, 0, ACS_LTEE);
  mvwaddch(win, 2, w_cols - 1, ACS_RTEE);
  mvwhline(win, 2, 1, ACS_HLINE, w_cols - 2);
  middlePrint(win, 1, 0, w_cols, "CONTACTS");
  wrefresh(win);

  int c = 0;

  while ((c = wgetch(win)) != CTRL('q')) {
    switch (c) {
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    case 10:
      unpost_menu(menu);
      person *p = searchContact(item_name(current_item(menu)));
      person p2 = *p;
      draw_form(p);
      post_menu(menu);
      editContact(&p2, p);
      free(p);
      box(win, 0, 0);
      mvwaddch(win, 2, 0, ACS_LTEE);
      mvwaddch(win, 2, w_cols - 1, ACS_RTEE);
      wrefresh(win);
      break;
    }
    wrefresh(win);
  }

  unpost_menu(menu);
  for (int i = 0; i <= lines; i++) {
    free_item(items[i]);
  }
  free_menu(menu);
  free(np);
  delwin(win);
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

void end_ui(void) { endwin(); }
