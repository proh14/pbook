#pragma once
#ifndef _MENU_HANDLER_H_
#define _MENU_HANDLER_H_

#include <contacts.h>
#include <menu.h>

namepair *init_items(ITEM ***items);
void free_items(ITEM *items[]);

#endif
