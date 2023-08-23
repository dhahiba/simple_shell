#include "shell.h"
/**
 * ffree - ..
 * @p: ...
 */
void ffree(char **p)
{
char **a = p;

if (!p)
return;
while (*p)
free(*p++);
free(a);
}
/**
 * *_realloc - ...
 * @ptr: ...
 * @old_size: ...
 * @new_size: ...
 * Return: ...
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
{
free(ptr);
return (NULL);
}
if (new_size == old_size)
return (ptr);
p = malloc(new_size);
if (!p)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
p[old_size] = ((char *)ptr)[old_size];
free(ptr);
return (p);
}
/**
 * _memset - fills memory with a constant byte
 * @s: starting address of memory to be filled
 * @b: the desired value
 * @n: unsigned int
 * Return: changed array with new value for n bytes
 */
char *_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; n > i; i++)
{
s[i] = b;
}
return (s);
}
/**
 * bfree - ..
 * @p: ..
 * Return: ...
 */
int bfree(void **p)
{
if (p && *p)
{
free(*p);
*p = NULL;
return (1);
}
return (0);
}
