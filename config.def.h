#pragma once
#ifndef _CONFIG_H_
#define _CONFIG_H_

// USAGE: Enable the usage of XDG paths if defined as 1 (defualts to
// ~/.local/share/pbook/.
#define USE_XDG 1

// USAGE: Defines the name and path of the detabase file.
// NOTE: Do not use ~ or $HOME in the path it will be added itself
// defenition.
#define DBFILE "/.contacts.pbook"

#endif
