#define _GNU_SOURCE
#include "cat.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])

{
  if (pars_command_line(argc, argv, SHORT_OPTIONS, LONG_OPTIONS, &options) ==
      0) {
    parse_files(argc - optind, argv + optind, &options);
  }

  return 0;
}

int pars_command_line(int argc, char *const *argv, const char *SHORT_OPTIONS,
                      struct option const *LONG_OPTIONS,
                      struct OptionObject *options) {
  char current_argument;
  int index = 0, flag_succees = 0;
  while ((current_argument = getopt_long(argc, argv, SHORT_OPTIONS,
                                         LONG_OPTIONS, &index)) != -1) {
    switch (current_argument) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->E = 1;
        options->v = 1;
        break;
      case 'E':
        options->E = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'T':
        options->T = 1;
        break;
      case 't':
        options->T = 1;
        options->v = 1;
        break;
      default:
        printf("Try 's21_cat --help' for more information.\n");
        flag_succees = 1;
        break;
    }
  }
  return flag_succees;
}

void parse_files(int files_count, char *const files[],
                 struct OptionObject *options) {
  FILE *file = NULL;
  int index = 0;
  while (files_count > 0) {
    file = fopen(*files, "r");
    if (file != NULL) {
      show_file_content(*files, options, &index);
      fclose(file);
    } else {
      show_error_message(*files);
    }
    files_count--;
    files++;
  }
}

void show_error_message(const char *const file) {
  printf("s21_cat: %s No such file or directory\n", file);
}

void show_file_content(char *name, struct OptionObject *const options,
                       int *index) {
  FILE *file = fopen(name, "r");
  int yet_printed = 0;
  char c, prev = '\n';
  while ((c = fgetc(file)) != -1) {
    show_character(c, &prev, options, index, &yet_printed);
  }
  fclose(file);
}

void show_character(int c, char *prev, struct OptionObject *const options,
                    int *index, int *yet_printed) {
  if (((options->s == 1) && *prev == '\n' && c == '\n' && *yet_printed == 1) ==
      0) {
    if (*prev == '\n' && c == '\n') {
      *yet_printed = 1;
    } else
      *yet_printed = 0;
    if (((options->n == 1 && options->b == 0) ||
         (options->b == 1 && c != '\n')) &&
        *prev == '\n') {
      *index += 1;
      printf("%6d\t", *index);
    }
    if (options->E == 1 && c == '\n') {
      printf("$");
    }
    if (options->T == 1 && c == '\t') {
      printf("^");
      c = '\t' + 64;
    }
    if (options->v == 1) {
      if (c > 127 && c < 160) printf("M-^");
      if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
      if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
        c = c > 126 ? c - 128 + 64 : c + 64;
    }

    putchar(c);
  }
  *prev = c;
}