#include "main.h"

/**
 * _printf - prints anything according to a format
 * @format: the format string
 * Return: number of bytes printed
 */
int _printf(const char *format, ...)
{
	int sum = 0;
	va_list ap;
	char *k, *start;
	params_t params = PARAMS_INIT;

	va_start(ap, format);

	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (k = (char *)format; *k; k++)
	{
		init_params(&params, ap);
		if (*k != '%')
		{
			sum += _putchar(*k);
			continue;
		}
		start = k;
		k++;
		while (get_flag(k, &params)) /* while char at k is flag char */
		{
			k++; /* next char */
		}
		k = get_width(k, &params, ap);
		k = get_precision(k, &params, ap);
		if (get_modifier(k, &params))
			k++;
		if (!get_specifier(k))
			sum += print_from_to(start, k,
				params.l_modifier || params.h_modifier ? k - 1 : 0);
		else
			sum += get_print_func(k, ap, &params);
	}
	_putchar(BUF_FLUSH);
	va_end(ap);
	return (sum);
}
