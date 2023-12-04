#include "libft/libft.h"

static int	count_digit(unsigned int n)
{
	int	digit;

	digit = 0;
	while (n != 0)
	{
		digit++;
		n /= 10;
	}
	return (digit);
}

int	ft_is_valid(char c)
{
	if (c && !ft_isdigit(c) && c != '.')
		return (1);
	return (0);
}

int	horizontal_valid(int start, int end, char *tab)
{
	while(start < end)
	{
		if(ft_is_valid(tab[start]))
			return (1);
		start++;
	}
	return (0);
}

int	is_valid(int i, int j, int digit, char **tabs)
{
	int start;
	int end;

	start = j;
	end = j + digit;
	if (j > 0)
	{
		start--;
		if (ft_is_valid(tabs[i][start]))
			return (1);
	}
	if (tabs[i][j + digit])
	{
		if (ft_is_valid(tabs[i][j + digit]))
			return (1);
		end++;
	}
	if (i > 0)
		if (horizontal_valid(start, end, tabs[i - 1]))
			return (1);
	if (tabs[i + 1])
		if (horizontal_valid(start, end, tabs[i + 1]))
			return (1);
	return (0);
}

int	get_number(char **tabs, char *tab, int i)
{
	int	sum = 0;
	int	j = 0;
	int num;
	int	digit;

	while (tab[j])
	{
		while (tab[j] && !ft_isdigit(tab[j]))
			j++;
		if (ft_isdigit(tab[j]))
		{
			num = ft_atoi(&tab[j]);
			digit = count_digit(num);
			if (is_valid(i, j, digit, tabs))
				sum += num;
			j += digit;
		}
	}
	return (sum);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*lines = NULL;
	char	*buffer;
	int		bytesread;
	int		sum = 0;
	
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
		sum += get_number(tabs, tabs[i], i);
	printf("%d\n", sum);
	free_arr(tabs);
	return (0);
}