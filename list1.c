#include "shell.h"
/**
 * add_node - ...
 * @head: ...
 * @str: ..
 * @n: ...
 * Return: ...
 */
link_l *add_node(link_l **head, const char *str, int n)
{
	link_l *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(link_l));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(link_l));
	new->n = n;
	if (str)
	{
		new->s = _strdup(str);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = (*head);
	*head = new;
	return (new);
}
/**
 * add_node_end - ...
 * @head: ...
 * @str: ...
 * @n: int
 * Return: ...
 */
link_l *add_node_end(link_l **head, const char *str, int n)
{
	link_l *new, *node;

	if (!head)
		return (NULL);
	node = *head;
	new = malloc(sizeof(link_l));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(link_l));
	new->n = n;
	if (str)
	{
		new->s = _strdup(str);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);
}
/**
 * print_list_str - ...
 * @h: ...
 * Return: ...
 */
size_t print_list_str(const link_l *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		s++;
	}
	return (s);
}
/**
 * delete_node_at_index - ....
 * @head: ...
 * @index: ...
 * Return: ....
 */
int delete_node_at_index(link_l **head, unsigned int index)
{
	link_l *node, *prev;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		prev = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - ...
 * @head_p: ...
 * Return: ...
 */
void free_list(link_l **head_p)
{
	link_l *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->s);
		free(node);
		node = next_node;
	}
	*head_p = NULL;
}
