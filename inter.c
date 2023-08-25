#include "shell.h"
/**
 * _inter - ...
 * @f: ..
 * Return: ...
 */
int _inter(inf_t *f)
{
	return (isatty(STDIN_FILENO) && f->readfd <= 2);
}
/**
 * is_delim - ...
 * @c: ...
 * @d: ...
 * Return: ...
 */
int is_delim(char c, char *d)
{
	while (*d)
	{
		if (*d++ == c)
			return (1);
	}
	return (0);
}
/**
 * _isalpha - Checks for alphabeic character
 * @c: The character to be checked
 * Return: 1 for alphabetic character or 0 for anything else
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * print_error - ...
 * @f: ...
 * @s: ...
 *
 * Return: ..
 */
void print_error(inf_t *f, char *s)
{
	_eputs(f->fname);
	_eputs(": ");
	print_d(f->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(f->argv[0]);
	_eputs(": ");
	_eputs(s);
}
/**
 * read_h - ..
 * @f: ..
 * Return: ...
 */
int read_h(inf_t *f)
{
	int i, l = 0, lc = 0;
	ssize_t rd, fs = 0, fd;
	struct stat s;
	char *b = NULL, *fn = get_history_file(f);

	if (!fn)
		return (0);
	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &s))
		fs = s.st_size;
	if (fs < 2)
		return (0);
	b = malloc(sizeof(char) * (fs + 1));
	if (!b)
		return (0);
	rd = read(fd, b, fs);
	b[fs] = 0;
	if (rd <= 0)
		return (free(b), 0);
	close(fd);
	for (i = 0; i < fs; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			b_history(f, b + l, lc++);
			l = i + 1;
		}
	if (l != i)
		b_history(f, b + l, lc++);
	free(b);
	f->histcount = lc;
	while (f->histcount-- >= HIST_MAX)
		delete_node_at_index(&(f->history), 0);
	renumber_history(f);
	return (f->histcount);
}
