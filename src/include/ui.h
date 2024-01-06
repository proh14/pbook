#pragma once
#ifndef _UI_H_
#define _UI_H_

#include <contacts.h>

void init_ui(void);
void end_ui(void);

void draw_menu(void);

void draw_form(person *p);

void draw_title(void);

void draw_help(void);

#endif
