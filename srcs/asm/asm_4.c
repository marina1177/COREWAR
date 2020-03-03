#include "com.h"


int is_reg(char *line)
{
  int i;
  int len;

  len = ft_strlen(line);
  i = 0;
  if (/*(2 == len || len == 3) &&*/ line[i++] == 'r')
  {
    while (ft_isdigit(line[i]) && i < len)
      i++;
    return (i == len && ft_atoi(&line[1]) > 0);
  }
  return (0);
}

int		is_lblchar(char c)
{
  char	*ptr;

  ptr = LABEL_CHARS;
  while(*ptr != '\0')
  {
    if (*ptr == c)
      return (1);
    ptr++;
  }
  return (0);
}
//