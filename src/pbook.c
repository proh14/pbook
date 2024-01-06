/*
 * This file is part of the pbook distribution
 * (https://github.com/proh14/pbook).
 *
 * Copyright (c) 2024 Hoorad Farrokh.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <contacts.h>
#include <stdio.h>
#include <ui.h>

int main(void) {
  initContact();
  init_ui();
  draw_title();
  draw_help();
  draw_menu();
  end_ui();
  endContact();
  return 0;
}
