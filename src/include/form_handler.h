#pragma once
#ifndef _FORM_HANDLER_H_
#define _FORM_HANDLER_H_

#include <contacts.h>
#include <form.h>

void init_fields(FIELD *fields[], int num, int w_lines);
void set_field_buffers(person *p, FIELD *fields[]);
void free_fields(FIELD *fields[]);
void draw_field_names(WINDOW *subwindow, int num, int w_lines);
void set_person_from_field(FIELD *fields[], person *p);
void init_form(FORM *form, WINDOW *win, WINDOW *subwindow);
void do_form_key(FORM *form, int c);

#endif
