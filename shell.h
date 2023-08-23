#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE	1024
#define WRITE_BUF_SIZE	1024
#define BUF_FLUSH	-1

#define CMD_NORM	0
#define CMD_OR	1
#define CMD_AND	2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE	0
#define USE_STRTOK	0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct listt - ...
 * @n: ....
 * @s: ...
 * @next: ...
 */
typedef struct listt
{
	int n;
	char *s;
	struct listt *next;
} link_l;
/**
 * struct pasinfo - ..
 * @arg: ...
 * @argv: ...
 * @path: ...
 * @argc: ...
 * @line_count: ...
 * @err_num: ...
 * @linecount_flag: ..
 * @fname: ...
 * @env: ...
 * @environ: ...
 * @history: ...
 * @alias: ....
 * @env_changed: ...
 * @status: ..
 * @cmd_buf: ...
 * @cmd_buf_type: ...
 * @readfd: ...
 * @histcount: ...
 */
typedef struct pasinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	link_l *env;
	link_l *history;
	link_l *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} inf_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0,\
	NULL, 0, 0, 0}
/**
 * struct built -...
 * @t: ...
 * @f: ...
 */
typedef struct built
{
	char *t;
	int (*f)(inf_t *);
} buil_t;

int env_list(inf_t *f);
int main_shell(inf_t *f, char **s);
int find_b(inf_t *f);
void f_cmd(inf_t *f);
void fork_cmd(inf_t *f);

int is_cmd(inf_t *f, char *p);
char *dup_chars(char *p, int s, int t);
char *find_path(inf_t *f, char *p, char *c);
void _eputs(char *s);
int _eputchar(char c);
int _putfd(char c, int f);
int _putsfd(char *s, int f);

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *ch1, const char *ch2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

char *_strncpy(char *d, char *s, int n);
char *_strncat(char *d, char *s, int n);
char *_strchr(char *s, int ch);
char **strtow(char *s, char *d);
char **strtow2(char *s, char d);

char *_memset(char *s, char b, unsigned int n);
void ffree(char **p);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int bfree(void **p);

int _inter(inf_t *f);
int is_delim(char c, char *d);
int _isalpha(int c);
void print_error(inf_t *f, char *s);
int _atoi(char *s);
int _erratoi(char *s);
int print_d(int n, int f);
char *convert_number(long int n, int b, int f);
void remove_comments(char *b);

int _myexit(inf_t *f);
int _mycd(inf_t *f);
int _myhelp(inf_t *f);
int _myhistory(inf_t *f);
int _myalias(inf_t *f);

ssize_t input_buf(inf_t *f, char **b, size_t *l);
ssize_t get_input(inf_t *f);
int _getline(inf_t *f, char **pr, size_t *l);
void sigintHandler(__attribute__((unused))int s);
void clear_info(inf_t *f);
void set_info(inf_t *f, char **a);
void free_inf(inf_t *f, int l);

char *_getenv(inf_t *f, const char *n);
int _myenv(inf_t *f);
int _mysetenv(inf_t *f);
int _myunsetenv(inf_t *f);
char **get_environ(inf_t *f);
int _unsetenv(inf_t *f, char *v);
int _setenv(inf_t *f, char *v, char *vl);
char *get_history_file(inf_t *f);
int write_h(inf_t *f);
int read_h(inf_t *f);
int b_history(inf_t *f, char *b, int l);

int renumber_history(inf_t *f);
link_l *add_node(link_l **head, const char *str, int n);
link_l *add_node_end(link_l **head, const char *str, int n);
size_t print_list_str(const link_l *h);
int delete_node_at_index(link_l **head, unsigned int index);
void free_list(link_l **head_p);
size_t list_len(const link_l *h);
char **list_to_strings(link_l *h);
size_t print_listint(const link_l *h);
link_l *node_starts_with(link_l *node, char *pr, char c);
ssize_t get_node_index(link_l *h, link_l *n);

int is_chain(inf_t *f, char *b, size_t *p);
void check_chain(inf_t *f, char *b, size_t *p, size_t i, size_t l);
int replace_alias(inf_t *f);
int replace_vars(inf_t *f);
int replace_string(char **ch, char *n);

int set_alias(inf_t *f, char *s);
int unset_alias(inf_t *f, char *s);
ssize_t read_buf(inf_t *f, char *b, size_t *n);
int print_alias(link_l *n);
#endif
