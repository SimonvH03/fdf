#include <stdio.h>

int	round_double(double x)
{
	short	sign;

	sign = 1;
	if (x < 0)
	{
		x = -x;
		sign = -sign;
	}
	double	ones = (int)x;
	double	decimal = x - ones;
	if (decimal >= 0.5)
		return (ones + 1) * sign;
	return ones * sign;
}

int	main()
{
	double	x = -3.5;
	printf("Result: %i\n", round_double(x));
}