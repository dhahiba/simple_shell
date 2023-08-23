#include "shell.h"
/**
 * b_history - ...
 * @f: ...
 * @b: ....
 * @l: ...
 * Return: ...
 */
int b_history(inf_t *f, char *b, int l)
{
link_l *node = NULL;

if (f->history)
node = f->history;
add_node_end(&node, b, l);
if (!f->history)
f->history = node;
return (0);
}
/**
 * renumber_history - ...
 * @f: ...
 * Return: ...
 */
int renumber_history(inf_t *f)
{
int j = 0;
link_l *nd = f->history;

while (nd)
{
nd->n = j++;
nd = nd->next;
}
return (f->histcount = j);
}
/**
 * get_history_file - ...
 * @f: ...
 * Return: ...
 */
char *get_history_file(inf_t *f)
{
char *b, *d;

d = _getenv(f, "HOME=");
if (!d)
return (NULL);
b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
if (!b)
return (NULL);
b[0] = 0;
_strcpy(b, d);
_strcat(b, "/");
_strcat(b, HIST_FILE);
return (b);
}
/**
 * _setenv - ...
 * @f: ...
 * @v: ...
 * @vl: ...
 * Return: ...
 */
int _setenv(inf_t *f, char *v, char *vl)
{
char *p;
link_l *n;
char *b = NULL;

if (!v || !vl)
return (0);
b = malloc(_strlen(v) + _strlen(vl) + 2);
if (!b)
return (1);
_strcpy(b, v);
_strcat(b, "=");
_strcat(b, vl);
n = f->env;
while (n)
{
p = starts_with(n->s, v);
if (p && *p == '=')
{
free(n->s);
n->s = b;
f->env_changed = 1;
return (0);
}
n = n->next;
}
add_node_end(&(f->env), b, 0);
free(b);
f->env_changed = 1;
return (0);
}
/**
 * _unsetenv - ...
 * @f: ....
 * @v: ...
 * Return: ...
 */
int _unsetenv(inf_t *f, char *v)
{
char *p;
size_t j = 0;
link_l *n = f->env;

if (!n || !v)
return (0);
while (n)
{
p = starts_with(n->s, v);
if (p && *p == '=')
{
f->env_changed = delete_node_at_index(&(f->env), j);
j = 0;
n = f->env;
continue;
}
n = n->next;
j++;
}
return (f->env_changed);
}
