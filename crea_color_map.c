#include "libft/ft_printf.h"

void	crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) + 1);
	map[0] = ft_multi_strdup(4, ft_itoa(heith), " ", ft_itoa(width), " 1 1 "); 
	ft_printf("s = {%s}\n", map[0]);
	map[1] = ft_multi_strdup(2, "b c #", color);
	ft_printf("s = {%s}\n", map[1]);
	i = 1;
	while (++i < heith + 2)
	{
		j = -1;
		map[i] = ft_strnew(width - 1);
		while (++j < width)
			map[i][j] = 'b';
		ft_printf("s = {%s}\n", map[i]);
	}
	//map[i] = NULL;
	ft_printf("s = {%s}\n", "Hello");
}

int main(void)
{
	crea_color_map(13, 34, "BF2956");
	return (0);
}
