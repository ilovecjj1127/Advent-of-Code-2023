#include "libft/libft.h"
#include <math.h>

int	is_exist(char *str, char **set)
{
	int	j = -1;

	while (set[++j])
	{
		// printf("%s in %s\n", str, set[j]);
		if (!ft_strncmp(str, set[j], 2))
			return (1);
	}
	return (0);
}

int	get_points(char **win, char **set)
{
	int	count = 0;
	int	i = -1;

	while (set[++i])
		count += is_exist(set[i], win);
	printf("%d\n", count);
	return (pow(2, count - 1));
}

int main(int argc, char **argv)
{
	char	*line;
	char	**sets, **set;
	char	**wins, **win;
	int 	fd;
	int		sum = 0;

	fd = open(argv[argc - 1], O_RDONLY);
	line = get_next_line(fd);
	sum = 0;
	while (line)
	{
		sets = ft_split(line, '|');
		wins = ft_split(sets[0], ':');
		sets[1] = ft_strtrim(sets[1], "\n");
		set = ft_split(sets[1], ' ');
		win = ft_split(wins[1], ' ');
		sum += get_points(win, set);
		free(line);
		free_arr(sets);
		free_arr(wins);
		free_arr(set);
		free_arr(win);
		line = get_next_line(fd);
	}
	printf("%d\n", sum);
	return (0);
}