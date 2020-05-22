
#include "asm.h"

int32_t		ft_atoi_cor(const char *str, u_int8_t size)
{
	int				neg;
	int				i;
	int64_t			num;

	i = 0;
	neg = 0;
	num = 0;
	while ((str[i]) == ' ' || (str[i]) == '	')
		i++;
	if (str[i] == '-')
		neg = 1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += ((int)str[i] - 48);
		i++;
	}
	num = (neg == 1 ? -num : num);
	size == 1 ? (num = (u_int8_t)num) : 1;
	size == 2 ? (num = (int16_t)num) : 1;
	size == 4 ? (num = (int32_t)num) : 1;
	return (num);
}

int			is_lblchar(char c)
{
	char	*ptr;

	ptr = LABEL_CHARS;
	while (*ptr != '\0')
	{
		if (*ptr == c)
			return (1);
		ptr++;
	}
	return (0);
}

void		skip_space(char *s)
{
	if (!(&(s[g_mdata->x])) || s[g_mdata->x] == '\0')
		return ;
	while (s[g_mdata->x] == ' ' || s[g_mdata->x] == '	')
		g_mdata->x++;
}

void		skip_comment(char *line)
{
	while (*line && *line != COMMENT_CHAR && *line != COMMENT_CHAR_ALT)
		++line;
	*line = 0;
}

void		check_new_line(char *line, int f)
{
	if (!(&(line[g_mdata->x])) || line[g_mdata->x] == '\0')
		return ;
	if (line[g_mdata->x] == '\n')
	{
		if (f == 2)
		{
			if (g_tkn_last)
				g_tkn_last->new_line += 1;
		}
		if (f == 1)
		{
			if (g_label_last)
				g_label_last->new_line += 1;
		}
		if (f == 0)
		{
			if (g_tkn_last)
				g_tkn_last->new_line += 1;
			else if (g_label_last)
				g_label_last->new_line += 1;
		}
		g_mdata->x++;
	}
}
