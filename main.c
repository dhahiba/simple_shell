#include "shell.h"
/**
 * main - ...
 * @argc: ...
 * @argv: ...
 * Return: ...
 */
int main(int argc, char **argv)
{
int fd = 2;
inf_t inf[] = { INFO_INIT };
asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

if (argc == 2)
{
fd = open(argv[1], O_RDONLY);
if (fd == -1)
{
if (errno == ENOENT)
{
_eputs(argv[0]);
_eputs(": 0: Can't open");
_eputs(argv[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
if (errno == EACCES)
exit(126);
return (EXIT_FAILURE);
}
inf->readfd = fd;
}
env_list(inf);
read_h(inf);
main_shell(inf, argv);
return (EXIT_SUCCESS);
}
