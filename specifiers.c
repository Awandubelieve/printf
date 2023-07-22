#include "main.h"

/**
 * get_specifier - finds the format function
 * @s: the format string
 * Return: the number of bytes printed
 */

int (*get_specifier(char *s))(va_list ap, params_t *params)
{
	specifier_t specifiers[] = {
		{"c", print_char},
		{"d", print_int},
		{"i", print_int},
		{"s", print_string},
		{"%", print_percent},
		{"b", print_binary},
		{"o", print_octal},
		{"u", print_unsigned},
		{"x", print_hex},
		{"X", print_HEX},
		{"p", print_address},
		{"S", print_S},
		{"r", print_rev},
		{"R", print_rot13},
		{NULL, NULL}
	};
	int a = 0;

	while (specifiers[a].specifier)
	{
		if (*s == specifiers[a].specifier[0])
		{
			return (specifiers[a].f);
		}
		a++;
	}
	return (NULL);
}

/**
 * get_print_func - finds the format func
 * @s: the format string
 * @ap: argument pointer
 * @params: the parameters struct
 * Return: the number of bytes printed
 */
int get_print_func(char *s, va_list ap, params_t *params)
{
	int (*f)(va_list, params_t *) = get_specifier(s);

	if (f)
		return (f(ap, params));
	return (0);
}

/**
 * get_flag - finds the flag func
 * @s: the format string
 * @params: the parameters struct
 *
 * Return: if flag was valid
 */
int get_flag(char *s, params_t *params)
{
	int a = 0;

	switch (*s)
	{
		case '+':
			a = params->plus_flag = 1;
			break;
		case ' ':
			a = params->space_flag = 1;
			break;
		case '#':
			a = params->hashtag_flag = 1;
			break;
		case '-':
			a = params->minus_flag = 1;
			break;
		case '0':
			a = params->zero_flag = 1;
			break;
	}
	return (a);
}

/**
 * get_modifier - finds the modifier func
 * @s: the format string
 * @params: the parameters struct
 * Return: if modifier was valid
 */
int get_modifier(char *s, params_t *params)
{
	int a = 0;

	switch (*s)
	{
	case 'h':
		a = params->h_modifier = 1;
		break;
	case 'l':
		a = params->l_modifier = 1;
		break;
	}
	return (a);
}

/**
 * get_width - gets the width from the format string
 * @s: the format string
 * @params: the parameters struct
 * @ap: the argument pointer
 * Return: new pointer
 */
char *get_width(char *s, params_t *params, va_list ap)
/* should this function use char **s and modify the pointer? */
{
	int a = 0;

	if (*s == '*')
	{
		a = va_arg(ap, int);
		s++;
	}
	else
	{
		while (_isdigit(*s))
			a = a * 10 + (*s++ - '0');
	}
	params->width = a;
	return (s);
}
