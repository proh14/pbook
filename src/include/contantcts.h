#progama once
#ifndef _CONTACTS_H_
#define _CONTACTS_H_

#define MAX_NAME 20
#define MAX_NUMBERS 20
#define MAX_BIRTHDAY 15
#define MAX_ADDRESS 50
#define MAX_EMAIL 50

typedef struct person {
  char name[MAX_NAME];
  char lastname[MAX_NAME];
  char numbers[MAX_NUMBERS];
  char email[MAX_EMAIL];
  char birthday[MAX_BIRTHDAY];
  char address[MAX_ADDRESS];
  char address2[MAX_ADDRESS];
} person;

void addContact(person *p);
void deleteContact(person *p);
person *searchContact(char *name, char *lastname);
void editContact(person *o, person *n);
void saveContacts(char *filename);
void loadContacts(char *filename);

#endif
