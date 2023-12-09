#include "libft/libft.h"

int	*get_arr(char *line)
{
	int		*arr;
	char	**tab;
	int		len;
	int		i = -1;

	len = arr_len(line, ' ');
	tab = ft_split(line, ' ');
	arr = (int *)malloc(sizeof(int) * len);
	if (!arr)
		return (NULL);
	while (++i < len)
		arr[i] = ft_atoi(tab[i]);
	free_arr(tab);
	return (arr);
}

int	is_zeros(int arr[], int len)
{
	int	i = -1;

	while (++i < len)
	{
		if (arr[i] != 0)
			return (0);
	}
	return (1);
}

int	prev_value(int arr[], int len)
{
	int	next_arr[len - 1];
	int	i = -1;

	if (is_zeros(arr, len))
		return (arr[0]);
	while (++i < len - 1)
		next_arr[i] = arr[i + 1] - arr[i];
	return (arr[0] - prev_value(next_arr, len - 1));
}

int	main(int argc, char **argv)
{
	int		sum = 0;
	char	*line;
	int		*arr;
	int		fd;

	fd = open(argv[argc - 1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		arr = get_arr(line);
		if (arr)
			sum += prev_value(arr, arr_len(line, ' '));
		free(line);
		free(arr);
		line = get_next_line(fd);
	}
	printf("%d\n", sum);
}