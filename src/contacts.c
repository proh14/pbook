#include <config.def.h>
#include <contacts.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *FILENAME;

bool contactMatch(person *p1, person *p2) {
  if (strcmp(p1->name, p2->name) != 0)
    return false;
  if (strcmp(p1->email, p2->email) != 0)
    return false;
  if (strcmp(p1->numbers, p2->numbers) != 0)
    return false;
  if (strcmp(p1->address, p2->address) != 0)
    return false;
  if (strcmp(p1->address2, p2->address2) != 0)
    return false;
  if (strcmp(p1->birthday, p2->birthday) != 0)
    return false;
  return true;
}

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
  int file_size = 15;
  char *home = getenv("HOME");
  if (home == NULL) {
    printf("HOME not set.\n");
    exit(1);
  }

#if USE_XDG == 0
  const char *path = "/.contacts.pbook";
#else
  const char *path = "/.local/share/pbook/contacts.pbook";
  file_size = 14;
#endif
  FILENAME = malloc(strlen(home) + strlen(path) + 1);
  strcpy(FILENAME, home);
  strcat(FILENAME, path);
  FILENAME[strlen(path) + strlen(home) - file_size] = '\0';
  struct stat st = {0};
  if (stat(FILENAME, &st) == -1) {
    mkdir(FILENAME, 0700);
  }
  FILENAME[strlen(path) + strlen(home) - file_size] =
      (file_size == 15) ? '.' : 'c';
  FILE *fp = fopen(FILENAME, "ab+");
  fclose(fp);
}

void endContact(void) { free(FILENAME); }
