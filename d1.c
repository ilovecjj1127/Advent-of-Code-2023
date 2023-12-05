#include "get_next_line.h"
const char	*nums[9] = {
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i] || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*p_little;
	char	*p_big;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i + ft_strlen(little) <= len && big + i)
	{
		p_little = (char *)little;
		p_big = (char *)big + i;
		while (*p_big == *p_little && *p_little && *p_big)
		{
			p_little++;
			p_big++;
		}
		if (*p_little == '\0')
			return ((char *)big + i);
		if (*p_big == '\0')
			return (NULL);
		i++;
	}
	return (NULL);
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