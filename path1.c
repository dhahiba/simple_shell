#include "shell.h"
/**
 * set_alias - ...
 * @f: ...
 * @s: ...
 * Return: ....
 */
int set_alias(inf_t *f, char *s)
{
char *ch;

ch = _strchr(s, '=');
if (!ch)
return (1);
if (!*++ch)
return (unset_alias(f, s));
unset_alias(f, s);
return (add_node_end(&(f->alias), s, 0) == NULL);
}
/**
 * unset_alias - ...
 * @f: ....
 * @s: ...
 * Return: ...
 */
int unset_alias(inf_t *f, char *s)
{
int i;
char *p, c;

p = _strchr(s, '=');
if (!p)
return (1);
c = *p;
*p = 0;
i = delete_node_at_index(&(f->alias),
		get_node_index(f->alias, node_starts_with(f->alias, s, -1)));
*p = c;
return (i);
}
/**
 * _myhistory - ...
 * @f: ....
 * Return: ...
 */
int _myhistory(inf_t *f)
{
print_listint(f->history);
return (0);
}
/**
 * _myhelp - ....
 * @f: ...
 * Return: ...
 */
int _myhelp(inf_t *f)
{
char **a;

a = f->argv;
_puts("help\n");
if (0)
_puts(*a);
return (0);
}
/**
 * _myexit - ...
 * @f: ...
 * Return: ...
 */
int _myexit(inf_t *f)
{
int i;
if (f->argv[1])
{
i = _erratoi(f->argv[1]);
if (i == -1)
{
f->status = 2;
print_error(f, "number illegal");
_eputs(f->argv[1]);
_eputchar('\n');
return (1);
}
f->err_num = _erratoi(f->argv[1]);
return (-2);
}
f->err_num = -1;
return (-2);
}
