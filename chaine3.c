#include "shell.h"
/**
 * _strchr - ...
 * @s: ...
 * @ch: ...
 * Return: ...
 */
char *_strchr(char *s, int ch)
{
	do {
		if (*s == ch)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}

/**
 * f_cmd - ...
 * @f: ...
 * Return: ...
 */
void f_cmd(inf_t *f)
{
	int i, j;
	char *p = NULL;

	f->path = f->argv[0];
	if (f->linecount_flag == 1)
	{
		f->linecount_flag = 0;
		f->line_count++;
	}
	for (i = 0, j = 0; f->arg[i]; i++)
		if (!is_delim(f->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	p = find_path(f, _getenv(f, "PATH="), f->argv[0]);
	if (p)
	{
		f->path = p;
		fork_cmd(f);
	}
	else
	{
		if ((_inter(f) || _getenv(f, "PATH=") || f->argv[0][0] == '/')
				&& is_cmd(f, f->argv[0]))
			fork_cmd(f);
		else if (*(f->arg) != '\n')
		{
			f->status = 127;
			print_error(f, "not found\n");
		}
	}
}
/**
 * find_b - ...
 * @f: ...
 * Return: ...
 */
int find_b(inf_t *f)
{
	buil_t b[] = {
		{"history", _myhistory},
		{"alias", _myalias},
		{"exit", _myexit},
		{"help", _myhelp},
		{"cd", _mycd},
		{"setenv", _mysetenv},
		{"env", _myenv},
		{"unsetenv", _myunsetenv},
		{NULL, NULL},
	};
	int i, r = -1;

	for (i = 0; b[i].t; i++)
	{
		if (_strcmp(f->argv[0], b[i].t) == 0)
		{
			f->line_count++;
			r = b[i].f(f);
			break;
		}
	}
	return (r);
}
/**
 * fork_cmd - ...
 * @f: ...
 * Return: ...
 */
void fork_cmd(inf_t *f)
{
	pid_t p;

	p = fork();
	if (p == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (p == 0)
	{
		if (execve(f->path, f->argv, get_environ(f)) == -1)
		{
			free_inf(f, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(f->status));
		if (WIFEXITED(f->status))
		{
			f->status = WEXITSTATUS(f->status);
			if (f->status == 126)
				print_error(f, "Permission denied\n");
		}
	}
}
