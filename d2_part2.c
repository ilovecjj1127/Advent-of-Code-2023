#include "libft/libft.h"

int	get_amount(char **cubes, char c)
{
	int	i = -1;

	while (cubes[++i])
	{
		if (ft_strchr(cubes[i], c))
			return (ft_atoi(cubes[i]));
	}
	return (1);
}

/* 12 red 13 green 14 blue*/
int	calculate_bag(char **bags)
{
	int 	i = -1;
	int		r = 0, g = 0, b = 0;
	char	**cubes;

	while (bags[++i])
	{
		cubes = ft_split(bags[i], ','); 
		r = ft_max(r, get_amount(cubes, 'd'));
		g = ft_max(g, get_amount(cubes, 'g'));
		b = ft_max(b, get_amount(cubes, 'b'));
		free(cubes);
	}
	return (r * g * b);
}


int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char 	**temp;
	char 	**bags;
	int		sum = 0;

	fd = open(argv[argc - 1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_split(line, ':');
		bags = ft_split(temp[1],';');
		sum += calculate_bag(bags);
		free_arr(bags);
		free_arr(temp);
		free(line);
		line = get_next_line(fd);
	}
	printf("%d\n", sum);
}