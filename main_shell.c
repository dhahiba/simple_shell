#include "shell.h"
/**
 * main_shell - ..
 * @f: ..
 * @s: ...
 * Return: ...
 */
int main_shell(inf_t *f, char **s)
{
	ssize_t r = 0;
	int b = 0;

	while (r != -1 && b != -2)
	{
		clear_info(f);
		if (_inter(f))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(f);
		if (r != -1)
		{
			set_info(f, s);
			b = find_b(f);
			if (b == -1)
				f_cmd(f);
		}
		else if (_inter(f))
			_putchar('\n');
		free_inf(f, 0);
	}
	write_h(f);
	free_inf(f, 1);
	if (!_inter(f) && f->status)
		exit(f->status);
	if (b == -2)
	{
		if (f->err_num == -1)
			exit(f->status);
		exit(f->err_num);
	}
	return (b);
}
/**
 * free_inf - ...
 * @f: ...
 * @l: ..
 */
void free_inf(inf_t *f, int l)
{
	ffree(f->argv);
	f->argv = NULL;
	f->path = NULL;
	if (l)
	{
		if (f->history)
			free_list(&(f->history));
		if (f->env)
			free_list(&(f->env));
		if (f->alias)
			free_list(&(f->alias));

		if (!f->cmd_buf)
			free(f->arg);
		ffree(f->environ);
		f->environ = NULL;
		bfree((void **)f->cmd_buf);
		if (f->readfd > 2)
			close(f->readfd);
		_putchar(BUF_FLUSH);
	}
}
/**
 * clear_info - ....
 * @f: ...
 */
void clear_info(inf_t *f)
{
	f->argc = 0;
	f->path = NULL;
	f->arg = NULL;
	f->argv = NULL;

}
/**
 * set_info - ...
 * @f: ...
 * @a: ...
 */
void set_info(inf_t *f, char **a)
{
	int i;

	f->fname = a[0];
	if (f->arg)
	{
		f->argv = strtow(f->arg, " \t");
		if (!f->argv)
		{
			f->argv = malloc(sizeof(char *) * 2);
			if (f->argv)
			{
				f->argv[0] = _strdup(f->arg);
				f->argv[1] = NULL;
			}
		}
		for (i = 0; f->argv && f->argv[i]; i++)
			;
		f->argc = i;
		replace_alias(f);
		replace_vars(f);
	}
}
