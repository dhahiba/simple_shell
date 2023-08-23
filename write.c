#include "shell.h"
/**
 * write_h - ...
 * @f: ....
 * Return: ...
 */
int write_h(inf_t *f)
{
ssize_t fd;
char *fn = get_history_file(f);
link_l *node = NULL;

if (!fn)
return (-1);
fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(fn);
if (fd == -1)
return (-1);
node = f->history;
while (node)
{
_putsfd(node->s, fd);
_putfd('\n', fd);
node = node->next;
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
 * _mycd - ...
 * @f: ..
 * Return: ..
 */
int _mycd(inf_t *f)
{
int i;
char *d, *s, b[1024];

s = getcwd(b, 1024);
if (!s)
_puts ("TODO:>>getcwd failure emsg here<<\n");
printf("mucd");
if (!f->argv[1])
{
d = _getenv(f, "HOME=");
if (!d)
i = chdir((d = _getenv(f, "PWD=")) ? d : "/");
else
i = chdir(d);
}
else if (_strcmp(f->argv[1], "-") == 0)
{
if (!_getenv(f, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(f, "OLDPWD="));
_putchar('\n');
i = chdir((d = _getenv(f, "OLDPWD=")) ? d : "/");
}
else
i = chdir(f->argv[1]);
if (i == -1)
{
print_error(f, "can't cd to");
_eputs(f->argv[1]);
_eputchar('\n');
}
else
{
_setenv(f, "OLDPWD", _getenv(f, "PWD="));
_setenv(f, "PWD", getcwd(b, 1024));
}
return (0);
}
/**
* _getline - ...
* @f: ...
* @pr: ...
* @l: ...
* Return: ..
*/
int _getline(inf_t *f, char **pr, size_t *l)
{
static size_t j, i;
ssize_t r = 0, s = 0;
size_t k;
char *c, *p = NULL, *np = NULL;
static char b[READ_BUF_SIZE];

p = *pr;
if (l && p)
s = *l;
if (j == i)
{
i = 0;
j = 0;
}
r = read_buf(f, b, &j);
if (r == -1 || (r == 0 && j == 0))
return (-1);
c = _strchr(b + i, '\n');
k = c ? 1 + (unsigned int) (c - b) : j;
np = _realloc(p, s, s ? s + k : k + 1);
if (!np)
return (p ? free(p), -1 : -1);
if (s)
_strncat(np, b + i, k - i);
else
_strncpy(np, b + i, k - i + 1);
s = s + k - 1;
i = k;
p = np;
if (l)
*l = s;
*pr = p;
return (s);
}
/**
* read_buf - ...
* @f: ...
* @b: ..
* @n: ..
* Return: ...
*/
ssize_t read_buf(inf_t *f, char *b, size_t *n)
{
ssize_t r = 0;

if (*n)
return (0);
r = read(f->readfd, b, READ_BUF_SIZE);
if (r >= 0)
*n = r;
return (r);
}
/**
* sigintHandler - ...
* @s: ...
*/
void sigintHandler(__attribute__((unused))int s)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
