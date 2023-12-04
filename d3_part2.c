#include "libft/libft.h"
#include <math.h>

int	get_prenumber(char *tab, int j, int *count)
{
	int num = 0;
	int	i = 0;

	while (j >= 0 && ft_isdigit(tab[j]))
	{
		num += pow(10, i) * (tab[j] - '0');
		i++;
		j--;
	}
	printf("pre %d\n", num);
	(*count)++;
	return (num);
}

int	get_afternumber(char *tab, int j, int *count)
{
	(*count)++;
	printf("after %d\n", ft_atoi(&tab[j]));
	return (ft_atoi(&tab[j]));
}

int	get_upnumber(char *tab, int j, int *count)
{
	int mul = 1;
	
	if (!ft_isdigit(tab[j])) //j not digit
	{
		if (j > 0 && ft_isdigit(tab[j - 1]))
			mul *= get_prenumber(tab, j - 1, count);
		if (tab[j + 1] && ft_isdigit(tab[j + 1]))
			mul *= get_afternumber(tab, j + 1, count);
	}
	else //j digit
	{
		if (tab[j + 1] && !ft_isdigit(tab[j + 1])) //j + 1 not digit
			mul *= get_prenumber(tab, j, count);
		else if (j > 0 && !ft_isdigit(tab[j - 1])) // j + 1 digit j - 1 not
			mul *= get_afternumber(tab, j, count);
		else if (j > 0)
			mul *= get_afternumber(tab, j - 1, count);
	}
	return (mul);
}

int	gear_ratio(char **tabs, int i, int j)
{
	int	mul = 1;
	int count = 0;

	if (j > 0 && ft_isdigit(tabs[i][j - 1]))
		mul *= get_prenumber(tabs[i], j - 1, &count);
	if (tabs[i][j + 1] && ft_isdigit(tabs[i][j + 1]))
		mul *= get_afternumber(tabs[i], j + 1, &count);
	if (i > 0 && count <= 2)
		mul *= get_upnumber(tabs[i - 1], j, &count);
	if (tabs[i + 1] && count <= 2)
		mul *= get_upnumber(tabs[i + 1], j, &count);
	printf("%d: %d, count: %d\n", i, mul, count);
	if (count == 2)
		return (mul);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*lines = NULL;
	char	*buffer;
	int		bytesread;
	int		sum = 0;
	int 	j;
	
	fd = open(argv[argc - 1], O_RDONLY);
	buffer = (char *)malloc(11);
	while ((bytesread = read(fd, buffer, 10)) > 0)
	{
		buffer[bytesread] = '\0';
		char *tmp = ft_strjoin(lines, buffer);
		free(lines);
		lines = tmp;
	}
	free(buffer);
	char **tabs = ft_split(lines, '\n');
	int	i = -1;
	while (tabs[++i])
	{
		j = -1;
		while (tabs[i][++j])
		{
			if (tabs[i][j] == '*')
				sum += gear_ratio(tabs, i, j);
		}
	}
	printf("%d\n", sum);
	free_arr(tabs);
	return (0);
}