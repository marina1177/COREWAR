#include "../../includes/com.h"

char *skip_space(char *s)
{
	while(*s == ' ' || *s == '	')
		s++;
	return(s);
}

char *skip_comment(char *s)
{
	char	*pnt;

	pnt = ft_strstr(s, "#");
	if (pnt != NULL)
		*pnt = '\0';
	pnt = ft_strstr(s, ";");
	if (pnt != NULL)
		*pnt = '\0';
	return(s);
}
