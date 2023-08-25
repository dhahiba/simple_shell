#include "shell.h"
/**
 * _myunsetenv - ...
 * @f: ...
 * Return: ...
 */
int _myunsetenv(inf_t *f)
{
	int k = 0;

	if (f->argc == 1)
	{
		_eputs("Too few argements.\n");
		return (1);
	}
	for (k = 1; k <= f->argc; k++)
		_unsetenv(f, f->argv[k]);
	return (0);
}
/**
 * _mysetenv - ....
 * @f: ....
 * Return: ...
 */
int _mysetenv(inf_t *f)
{
	if (f->argc != 3)
	{
		_eputs("incorrect number\n");
		return (1);
	}
	if (_setenv(f, f->argv[1], f->argv[2]))
		return (0);
	return (1);
}
/**
 * _myenv - ...
 * @f: ...
 * Return: ...
 */
int _myenv(inf_t *f)
{
	print_list_str(f->env);
	return (0);
}
/**
 * _getenv - ...
 * @f: ...
 * @n: ...
 * Return: ...
 */
char *_getenv(inf_t *f, const char *n)
{
	char *s;
	link_l *nd = f->env;

	while (nd)
	{
		s = starts_with(nd->s, n);
		if (s && *s)
			return (s);
		nd = nd->next;
	}
	return (NULL);
}
/**
 * get_environ - ...
 * @f: ...
 * Return: ...
 */
char **get_environ(inf_t *f)
{
	if (!f->environ || f->env_changed)
	{
		f->environ = list_to_strings(f->env);
		f->env_changed = 0;
	}
	return (f->environ);
}
