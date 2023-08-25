#include "shell.h"
/**
 * print_d - ...
 * @n: ...
 * @f: ...
 * Return: ....
 */
int print_d(int n, int f)
{
	unsigned int _abc_, c;
	int i, cn = 0;
	int (*__putchar)(char) = _putchar;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (n < 0)
	{
		_abc_ = -n;
		__putchar('-');
		cn++;
	}
	else
		_abc_ = n;
	c = _abc_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abc_ / i)
		{
			__putchar('0' + c / i);
			cn++;
		}
		c %= i;
	}
	__putchar('0' + c);
	cn++;
	return (cn);
}
/**
* _erratoi - ...
* @s: ...
* Return: ...
*/
int _erratoi(char *s)
{
	unsigned long int r = 0;
	int i = 0;

	if (*s == '+')
		s++; /*TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			r *= 10;
			r += (s[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (r);
}
/**
 * remove_comments - ...
 * @b: ...
 */
void remove_comments(char *b)
{
	int i;

	for (i = 0; b[i] != '\0'; i++)
		if (b[i] == '#' && (!i || b[i - 1] == ' '))
		{
			b[i] = '\0';
			break;
		}
}
/**
 * convert_number - ...
 * @n: ..
 * @b: ...
 * @f: ..
 * Return: ...
 */
char *convert_number(long int n, int b, int f)
{
	char *p;
	char s = 0;
	static char bf[50];
	static char *a;
	unsigned long nn = n;

	if (n < 0 && !(f & CONVERT_UNSIGNED))
	{
		nn = -n;
		s = '-';
	}
	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &bf[49];
	*p = '\0';
	do {
		*--p = a[nn % b];
		nn = nn / b;
	} while (nn != 0);
	if (s)
		*--p = s;
	return (p);
}
