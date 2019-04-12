#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
	int heith;
	int width;
	int o_x;
	int o_y;
	int x_x;
	int x_y;
	int i;
	int j;

	heith = 0;
	width = 0;
	i = -1;
	if (ac != 7)
	{
		write(2, "Error args\n", 11);
		write(2, "Use:\nheith, width, o_x, o_y, x_x, x_y\n", 38);
		return (0);
	}
	heith = atoi(av[1]);
	width = atoi(av[2]);
	o_x = atoi(av[3]);
	o_y = atoi(av[4]);
	x_x = atoi(av[5]);
	x_y = atoi(av[6]);
	//printf("h = %d, w = %d, o_x = %d, o_y = %d, x_x = %d, x_y = %d\n", heith, width, o_x, o_y, x_x, x_y);
	while (++i < heith)
	{
		j = -1;
		while (++j <= width)
		{
			if (i == o_x && j == o_y)
				write(1, "O", 1);
			else	if (i == x_x && j == x_y)
				write(1, "X", 1);
			else	if (j == width)
				write(1, "\n", 1);
			else
				write(1, ".", 1);
		}
	}
	return (0);
}
