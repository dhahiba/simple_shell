#include "shell.h"
/**
 * _strdup - ...
 * @str: ...
 * Return: ...
 */
char *_strdup(const char *str)
{
size_t	l = 0;
char *ret;

if (str == NULL)
return (NULL);
while (*str++)
l++;
ret = malloc(sizeof(char) * (l + 1));

if (ret == NULL)
return (NULL);
for (l++; l--;)
ret[l] = *--str;
return (ret);
}
/**
 * _strlen - ...
 * @s: ...
 * Return: ...
 */
int _strlen(char *s)
{
int i = 0;

while (*s != '\0')
{
i++;
s++;
}
return (i);
}
/**
 * _strcpy - ...
 * @dest: ...
 * @src: ...
 * Return: ...
 */
char *_strcpy(char *dest, char *src)
{
int i;

if (dest == src || src == 0)
return (dest);
i = 0;
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
/**
 * _putchar - ...
 * @c: ...
 * Return: ...
 */
int _putchar(char c)
{
static int i;
static char b[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, b, i);
i = 0;
}
if (c != BUF_FLUSH)
b[i++] = c;
return (1);
}
/**
 * _puts - ...
 * @str: ...
 */
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}
