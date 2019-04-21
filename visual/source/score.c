
#include "../include/visual.h"

/*
**  Calculete score for input on table.
*/

void	score(char *line, int *score_o, int *score_x)
{
	while (*line != '\0')
	{
		if(*line == 'o')
			*score_o = *score_o + 1;
		if(*line == 'x')
			*score_x = *score_x + 1;
		line++;
	}
}

void	delete_map_square(t_vis *vis)
{
	dell_arr(vis->map_score);
	free(vis->map_score);
	vis->map_score = NULL;
	dell_arr(vis->map_bourd);
	free(vis->map_bourd);
	vis->map_bourd = NULL;
	dell_arr(vis->map_obd);
	free(vis->map_obd);
	vis->map_obd = NULL;
	dell_arr(vis->map_obl);
	free(vis->map_obl);
	vis->map_obl = NULL;
	dell_arr(vis->map_xp);
	free(vis->map_xp);
	vis->map_xp = NULL;
	dell_arr(vis->map_xr);
	free(vis->map_xr);
	vis->map_xr = NULL;
}
