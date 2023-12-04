#include "libft/libft.h"

int	possible_cube(char **cubes)
{
	int	i = -1;
	int	num;

	while (cubes[++i])
	{
		num = ft_atoi(cubes[i]);
		printf("%s\n", cubes[i]);
		if (num > 12 && ft_strchr(cubes[i], 'd'))
			return (0);
		if (num > 13 && ft_strchr(cubes[i], 'g'))
			return (0);
		if (num > 14 && ft_strchr(cubes[i], 'b'))
			return (0);
	}
	return (1);
}

/* 12 red 13 green 14 blue*/
int	possible_bag(char **bags)
{
	int 	i = -1;
	char	**cubes;

	while (bags[++i])
	{
		cubes = ft_split(bags[i], ',');
		if (!possible_cube(cubes))
		{
			free(cubes);
			return (0);
		}
		free(cubes);
	}
	return (1);
}


int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char 	**temp;
	char 	**bags;
	int		sum = 0;
	int		i = 1;

	fd = open(argv[argc - 1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_split(line, ':');
		bags = ft_split(temp[1],';');
		if (possible_bag(bags))
			sum += i;
		free_arr(bags);
		free_arr(temp);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	printf("%d\n", sum);
}