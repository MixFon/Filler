

#include "filler.h"

int main(int ac, char **av)
{
	char *line;

	while(1)
	{
		get_next_line(0, &line);
		write(2, line, ft_strlen(line));
		write(2, "\n", 1);
		ft_putstr("19");
		ft_putstr(" ");
		ft_putstr("32");
		ft_putstr("\n");
	}
	//exit(1);
	ft_printf("19 32\n");
	write(2, "Hello\n", 6);
	return (0);
}
