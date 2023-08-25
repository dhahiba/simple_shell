#include "shell.h"

/**
 * is_chain - ..
 * @f: ...
 * @b: ...
 * @p: ...
 * Return: ...
 */
int is_chain(inf_t *f, char *b, size_t *p)
{
	size_t k = *p;

	if (b[k] == '&' && b[k + 1] == '&')
	{
		b[k] = 0;
		k++;
		f->cmd_buf_type = CMD_AND;
	}
	else if (b[k] == ';')
	{
		b[k] = 0;
		f->cmd_buf_type = CMD_CHAIN;
	}
	else if (b[k] == '|' && b[k + 1] == '|')
	{
		b[k] = 0;
		k++;
		f->cmd_buf_type = CMD_OR;
	}
	else
		return (0);
	*p = k;
	return (1);
}
/**
 * strtow - ..
 * @s: ...
 * @d: ...
 * Return: ..
 */
char **strtow(char *s, char *d)
{
	int i, j, k, m, num = 0;
	char **ch;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_delim(s[i], d) && (is_delim(s[i + 1], d) || !s[i + 1]))
			num++;
	if (num == 0)
		return (NULL);
	ch = malloc((1 + num) * (sizeof(char *)));
	if (!ch)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delim(s[i], d))
			i++;
		k = 0;
		while (!is_delim(s[i + k], d) && s[i + k])
			k++;
		ch[j] = malloc((k + 1) * sizeof(char));
		if (!ch[j])
		{
			for (k = 0; k < j; k++)
				free(ch[k]);
			free(ch);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ch[j][m] = s[i++];
		ch[j][m] = 0;
	}
	ch[j] = NULL;
	return (ch);
}
/**
 * strtow2 - ....
 * @s: ....
 * @d: ...
 * Return: ...
 */
char **strtow2(char *s, char d)
{
	int i, j, k, m, num = 0;
	char **ch;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != d  && s[i + 1] == d)
				|| (s[i] != d  && !s[i + 1]) || s[i + 1] == d)
			num++;
	if (num == 0)
		return (NULL);
	ch = malloc((1 + num) * (sizeof(char *)));
	if (!ch)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (s[i] == d && s[i] != d)
			i++;
		k = 0;
		while (s[i + k] != d && s[i + k] && s[i + k] != d)
			k++;
		ch[j] = malloc((k + 1) * sizeof(char));
		if (!ch[j])
		{
			for (k = 0; k < j; k++)
				free(ch[k]);
			free(ch);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ch[j][m] = s[i++];
		ch[j][m] = 0;
	}
	ch[j] = NULL;
	return (ch);
}
