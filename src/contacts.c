#include <contacts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *FILENAME;

void addContact(person *p) {
  FILE *fp = fopen(FILENAME, "a");
  fprintf(fp, "%s,%s,%s,%s,%s,%s\n", p->name, p->numbers, p->address,
          p->address2, p->email, p->birthday);
  fclose(fp);
}

void fillContact(person *p) {
  strcpy(p->name, "none");
  strcpy(p->numbers, "none");
  strcpy(p->email, "none");
  strcpy(p->birthday, "none");
  strcpy(p->address, "none");
  strcpy(p->address2, "none");
}

int readContact(namepair *n, FILE *fp) {
  char line[sizeof(person)];
  void *ret = fgets(line, sizeof(line), fp);

  if (!ret) {
    return EOF;
  }

  char *token = strtok(line, ",");
  strcpy(n->name, token);
  token = strtok(NULL, ",");
  strcpy(n->numbers, token);

  return 1;
}

void editContact(person *o, person *p) {
  FILE *fp = fopen(FILENAME, "r");
  FILE *fp2 = fopen("temp.txt", "w");
  char line[sizeof(person)];
  while (fgets(line, sizeof(line), fp)) {
    char *token = strtok(line, ",");
    if (strcmp(token, o->name) == 0) {
      fprintf(fp2, "%s,%s,%s,%s,%s,%s\n", p->name, p->numbers, p->address,
              p->address2, p->email, p->birthday);
    } else {
      line[strlen(token)] = ',';
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
      line[strlen(token)] = ',';
      fprintf(fp2, "%s", line);
    }
  }
  fclose(fp);
  fclose(fp2);
  remove(FILENAME);
  rename("temp.txt", FILENAME);
}

person *searchContact(const char *name) {
  FILE *fp = fopen(FILENAME, "r");
  char line[sizeof(person)];
  while (fgets(line, sizeof(line), fp) != NULL) {
    char *token = strtok(line, ",");
    if (strcmp(token, name) == 0) {
      person *p = malloc(sizeof(person));
      strcpy(p->name, token);
      token = strtok(NULL, ",");
      strcpy(p->numbers, token);
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

void initContact(void) {
  const char *path = "/.contacts.pbook";

  char *home = getenv("HOME");
  if (home == NULL) {
    printf("HOME not set.\n");
    exit(1);
  }

  FILENAME = malloc(strlen(home) + strlen(path) + 1);
  strcpy(FILENAME, home);
  strcat(FILENAME, path);

  FILE *fp = fopen(FILENAME, "ab+");
  fclose(fp);
}

void endContact(void) { free(FILENAME); }
