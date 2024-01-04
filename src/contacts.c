#include <contacts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addContact(person *p) {
  FILE *fp = fopen(FILENAME, "a");
  fprintf(fp, "%s,%s,%s,%s,%s\n", p->name, p->address, p->address2, p->email,
          p->birthday);
  fclose(fp);
}

void editContact(person *o, person *p) {
  FILE *fp = fopen(FILENAME, "r");
  FILE *fp2 = fopen("temp.txt", "w");
  char line[sizeof(person)];
  while (fgets(line, sizeof(line), fp)) {
    char *token = strtok(line, ",");
    if (strcmp(token, o->name) == 0) {
      fprintf(fp2, "%s,%s,%s,%s,%s\n", p->name, p->address, p->address2,
              p->email, p->birthday);
    } else {
      fprintf(fp2, "%s", line);
    }
  }
  fclose(fp);
  fclose(fp2);
  remove(FILENAME);
  rename("temp.txt", FILENAME);
}

void deleteContact(person *p) {
  FILE *fp = fopen(FILENAME, "r");
  FILE *fp2 = fopen("temp.txt", "w");
  char line[sizeof(person)];
  while (fgets(line, sizeof(line), fp)) {
    char *token = strtok(line, ",");
    if (strcmp(token, p->name) != 0) {
      fprintf(fp2, "%s", line);
    }
  }
  fclose(fp);
  fclose(fp2);
  remove(FILENAME);
  rename("temp.txt", FILENAME);
}

person *searchContact(char *name) {
  FILE *fp = fopen(FILENAME, "r");
  char line[sizeof(person)];
  while (fscanf(fp, "%s", line) != EOF) {
    char *token = strtok(line, ",");
    if (strcmp(token, name) == 0) {
      person *p = malloc(sizeof(person));
      strcpy(p->name, token);
      token = strtok(NULL, ",");
      strcpy(p->address, token);
      token = strtok(NULL, ",");
      strcpy(p->address2, token);
      token = strtok(NULL, ",");
      strcpy(p->email, token);
      token = strtok(NULL, ",");
      strcpy(p->birthday, token);
      fclose(fp);
      return p;
    }
  }
  fclose(fp);
  return NULL;
}
