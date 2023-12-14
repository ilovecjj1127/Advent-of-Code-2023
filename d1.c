#include "libft/libft.h"

const char	*nums[9] = {
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int	find_number(char *str)
{
	for (int i = 0; i < 9; i++)
	{
		if (ft_strncmp(str, nums[i], ft_strlen(nums[i])) == 0)
			return (i + 1);
	}
	return (0);
}

int	first_digit(char *str)
{
	int i;
	int	num;

	i = -1;
	while (str[++i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			return (str[i] - '0');
		if ((num = find_number(&str[i])) > 0)
			return (num);
	}
	return (0);
}

int	last_digit(char *str)
{
	int i;
	int num;

	i = ft_strlen(str);
	while (--i >= 0)
	{
		if (str[i] <= '9' && str[i] >= '0')
			return (str[i] - '0');
		if ((num = find_number(&str[i])) > 0)
			return (num);
	}
	return (0);
}
int main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		sum;

	fd = open(argv[argc - 1], O_RDONLY);
	line = get_next_line(fd);
	sum = 0;
	while (line)
	{
		sum += first_digit(line) * 10 + last_digit(line);
		line = get_next_line(fd);
	}
	printf("%d\n", sum);
	return (0);
}