#pragma once
#include <stdlib.h>
#ifndef _CONTACTS_H_
#define _CONTACTS_H_
#include <stdio.h>

extern char *FILENAME;

#define MAX_NAME 30
#define MAX_NUMBERS 20
#define MAX_BIRTHDAY 20
#define MAX_ADDRESS 50
#define MAX_EMAIL 20

typedef struct person {
  char name[MAX_NAME];
  char numbers[MAX_NUMBERS];
  char email[MAX_EMAIL];
  char birthday[MAX_BIRTHDAY];
  char address[MAX_ADDRESS];
  char address2[MAX_ADDRESS];
} person;

typedef struct namepair {
  char name[MAX_NAME];
  char numbers[MAX_NUMBERS];
} namepair;

void addContact(person *p);
void deleteContact(person *p);
person *searchContact(const char *name);
void editContact(person *o, person *n);
int readContact(namepair *p, FILE *fp);
void initContact(void);
void endContact(void);

#endif
