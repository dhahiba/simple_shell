#include "shell.h"
/**
 * find_path - ..
 * @f: ...
 * @p: ...
 * @c: ...
 * Return: ...
 */
char *find_path(inf_t *f, char *p, char *c)
{
	char *ps;
	int i, cp;

	if (!p)
		return (NULL);
	if ((_strlen(c) > 2) && starts_with(c, "./"))
	{
		if (is_cmd(f, c))
			return (c);
	}
	cp = 0;
	i = 0;
	while (1)
	{
		if (!p[i] || p[i] == ':')
		{
			ps = dup_chars(p, cp, i);
			if (!*ps)
				_strcat(ps, c);
			else
			{
				_strcat(ps, "/");
				_strcat(ps, c);
			}
			if (is_cmd(f, ps))
				return (ps);
			if (!p[i])
				break;
			cp = i;
		}
		i++;
	}
	return (NULL);
}
/**
 * dup_chars - ...
 * @p: ...
 * @s: ....
 * @t: ...
 * Return: ...
 */
char *dup_chars(char *p, int s, int t)
{
	int i, k;
	static char b[1024];

	for (k = 0, i = s; i < t; i++)
	{
		if (p[i] != ':')
			b[k++] = p[i];
	}
	b[k] = 0;
	return (b);
}
/**
 * is_cmd - ...
 * @f: ...
 * @p: ...
 * Return: ...
 */
int is_cmd(inf_t *f, char *p)
{
	struct stat s;

	(void)f;
	if (!p || stat(p, &s))
		return (0);
	if (s.st_mode & S_IFREG)
		return (1);
	return (0);
}
/**
 * _myalias - ...
 * @f: ...
 * Return: ...
 */
int _myalias(inf_t *f)
{
	link_l *n = NULL;
	char *p = NULL;
	int k = 0;

	if (f->argc == 1)
	{
		n = f->alias;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (k = 1; f->argv[k]; k++)
	{
		p = _strchr(f->argv[k], '=');
		if (p)
			set_alias(f, f->argv[k]);
		else
			print_alias(node_starts_with(f->alias, f->argv[k], '='));
	}
	return (0);
}
/**
 * print_alias - ...
 * @n: ...
 * Return: ...
 */
int print_alias(link_l *n)
{
	char *a = NULL, *p = NULL;

	if (n)
	{
		p = _strchr(n->s, '=');
		for (a = n->s; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
