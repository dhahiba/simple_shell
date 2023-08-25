#include "shell.h"
/**
 * _eputs - ...
 * @s: ...
 * Return: ...
 */
void _eputs(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_eputchar(s[i]);
		i++;
	}
}
/**
 * _eputchar - ...
 * @c: ...
 * Return: ...
 */
int _eputchar(char c)
{
	static char b[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, b, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		b[i++] = c;
	return (1);
}
/**
 * env_list - ...
 * @f: ...
 * Return: ...
 */
int env_list(inf_t *f)
{
	link_l *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&n, environ[i], 0);
	f->env = n;
	return (0);
}
