#include "ft_ls.h"
int main(void)
{
	int i = ft_printf("%*d",5,42);
	int i2 = printf("%*d", 5, 42);
	printf("%d-%d", i, i2);
}
