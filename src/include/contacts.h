#pragma once
#ifndef _CONTACTS_H_
#define _CONTACTS_H_

#define FILENAME "~/.contacts.pbook"

#define MAX_NAME 30
#define MAX_NUMBERS 20
#define MAX_BIRTHDAY 15
#define MAX_ADDRESS 50
#define MAX_EMAIL 50

typedef struct person {
  char name[MAX_NAME];
  char numbers[MAX_NUMBERS];
  char email[MAX_EMAIL];
  char birthday[MAX_BIRTHDAY];
  char address[MAX_ADDRESS];
  char address2[MAX_ADDRESS];
} person;

void addContact(person *p);
void deleteContact(person *p);
person *searchContact(char *name);
void editContact(person *o, person *n);

#endif
