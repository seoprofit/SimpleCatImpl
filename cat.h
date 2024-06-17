#include <getopt.h>

#ifndef S21_CAT_IMPL
#define S21_CAT_IMPL 1

struct OptionObject {
  int b;
  int E;
  int n;
  int s;
  int v;
  int T;
};

struct option const LONG_OPTIONS[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {"T", 0, 0, 't'},
    {"E", 0, 0, 'e'},
    {0, 0, 0, 0},
};

const char SHORT_OPTIONS[] = "bEensvTt";
struct OptionObject options = {0};
int pars_command_line(int argc, char *const *argv, const char *SHORT_OPTIONS,
                      struct option const *LONG_OPTIONS,
                      struct OptionObject *options);
void parse_files(int files_count, char *const files[],
                 struct OptionObject *options);
void show_file_content(char *name, struct OptionObject *const options,
                       int *index);
void show_error_message(const char *const file);

void show_character(int c, char *prev, struct OptionObject *const options,
                    int *index, int *yet_printed);

#endif