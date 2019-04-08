
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include <stdio.h>

int main (void)
{
	char	*line;
	int		i;

	i = -1;
	while (1)
	{
		i = get_next_line(0, &line);
		printf("i = %d line %s\n",i,  line);
	}
	return (0);
}
