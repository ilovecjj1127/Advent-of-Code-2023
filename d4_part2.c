#include "libft/libft.h"

int	call = 0;

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
	return (count);
}

void	find_card(int i, char **cards)
{
	char	**sets, **wins, **win, **set;
	int		point;
	int		j = 1;

	call++;
	if (!cards[i + 1])
		return ;
	sets = ft_split(cards[i], '|');
	wins = ft_split(sets[0], ':');
	set = ft_split(sets[1], ' ');
	win = ft_split(wins[1], ' ');
	point = get_points(win, set);
	free_arr(sets);
	free_arr(wins);
	free_arr(set);
	free_arr(win);
	while (j <= point && cards[i + j])
	{
		find_card(i + j, cards);
		j++;
	}
}

int main(int argc, char **argv)
{
	char	*tab, *buffer;
	char	**cards;
	int 	fd;
	int		bytesread;

	fd = open(argv[argc - 1], O_RDONLY);
	buffer = (char *)malloc(101);
	tab = NULL;
	while ((bytesread = read(fd, buffer, 100)) > 0)
	{
		buffer[bytesread] = '\0';
		tab = ft_strjoin(tab, buffer);
	}
	cards = ft_split(tab, '\n');
	int	i = -1;
	while (cards[++i])
		find_card(i, cards);
	free(buffer);
	free(tab);
	free_arr(cards);
	printf("%d\n", call);
	return (0);
}

		// sets = ft_split(line, '|');
		// wins = ft_split(sets[0], ':');
		// sets[1] = ft_strtrim(sets[1], "\n");
		// set = ft_split(sets[1], ' ');
		// win = ft_split(wins[1], ' ');
		// sum += get_points(win, set);
		// free(line);
		// free_arr(sets);
		// free_arr(wins);
		// free_arr(set);
		// free_arr(win);
		// line = get_next_line(fd);