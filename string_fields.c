#include "main.h"

/**
 * get_precision - function that gets the precision from the format string
 * @p: the format string
 * @params: the parameters struct
 * @ap: the argument pointer
 * Return: new pointer
 */

char *get_precision(char *p, params_t *params, va_list ap)
{
int a = 0;

if (*p != '.')
return (p);
p++;
if (*p == '*')
{
a = va_arg(ap, int);
if (a < 0)
params->precision = -1;  /* negative precision means no precision */
else
params->precision = a;
p++;
}
else
{
if (*p == '0')
{
params->precision = 0;
p++;
}
else
{
while (_isdigit(*p))
a = a * 10 + (*p++ - '0');
params->precision = a;
}
}
return (p);
}
