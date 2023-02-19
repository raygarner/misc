#define SEPARATE '\n'
#define MAXLEN 64

enum { FALSE, TRUE };

int dict_len(const char *dictnamee);
char *get_random_word(int max, const char *dictname);
