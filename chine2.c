#include "shell.h"
/**
 * _strcmp - ...
 * @s1: ...
 * @s2: ...
 * Return: ...
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - ...
 * @ch1: ...
 * @ch2: ...
 * Return: ...
 */
char *starts_with(const char *ch1, const char *ch2)
{
	while (*ch2)
	{
		if (*ch1++ != *ch2++)
			return (NULL);
	}
	return ((char *)ch1);
}
/**
 * _strcat - ....
 * @dest: ...
 * @src: ...
 * Return: ...
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
/**
 * _strncpy - ...
 * @d: ...
 * @s: .....
 * @n: ...
 * Return: ...
 */
char *_strncpy(char *d, char *s, int n)
{
	int i = 0, j;
	char *str = d;

	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (str);
}
/**
 * _strncat - ...
 * @d: ...
 * @s: ...
 * @n: ...
 * Return: ...
 */
char *_strncat(char *d, char *s, int n)
{
	int i = 0, j = 0;
	char *str = d;

	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < n)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < n)
		d[i] = '\0';
	return (str);
}
