#include <contacts.h>
#include <form.h>
#include <form_handler.h>
#include <string.h>
#include <utils.h>

struct field_settings {
  int max;
  char *name;
};

const struct field_settings opts[] = {
    {MAX_NAME, "Name: "},        {MAX_NUMBERS, "Phone number: "},
    {MAX_EMAIL, "Email: "},      {MAX_BIRTHDAY, "Birthday: "},
    {MAX_ADDRESS, "Adress 1: "}, {MAX_ADDRESS, "Adress 2: "},
};

void init_fields(FIELD *fields[], int num, int w_lines) {
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

void set_field_buffers(person *p, FIELD *fields[]) {
  int i = 0;
  char *buffers[] = {
      p->name, p->numbers, p->email, p->birthday, p->address, p->address2,
  };
  while (fields[i] != NULL) {
    set_field_buffer(fields[i], 0, buffers[i]);
    i++;
  }
}

void free_fields(FIELD *fields[]) {
  int i;
  for (i = 0; fields[i] != NULL; i++) {
    free_field(fields[i]);
  }
}

void draw_field_names(WINDOW *subwindow, int num, int w_lines) {
  int i;
  int y = 2;
  for (i = 0; i < num - 1; i++) {
    mvwprintw(subwindow, y, 0, "%s", opts[i].name);
    y += (w_lines) / num;
  }
}

void set_person_from_field(FIELD *fields[], person *p) {
  char *buffers[] = {
      p->name, p->numbers, p->email, p->birthday, p->address, p->address2,
  };
  int i = 0;
  while (fields[i] != NULL) {
    strcpy(buffers[i], rtrim(field_buffer(fields[i], 0)));
    i++;
  }
}

void init_form(FORM *form, WINDOW *win, WINDOW *subwindow) {
  set_form_win(form, win);
  set_form_sub(form, subwindow);
}

void do_form_key(FORM *form, int c) {
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
