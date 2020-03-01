#include "../includes/com.h"

void	parse_op(char *op)
{
	char	**lex;

	printf("args_op =%s\n",op);
	lex = ft_strsplit(op,  SEPARATOR_CHAR);
	if (lex ==NULL)
	{
		printf("split error-\n");
		error();
	}
	int i = 0;
	while (lex[i] != NULL)
	{
		printf("lex[%d] = %s\n", i, lex[i]);
		i++;
	}
	printf("---------------%s_\n",(g_op_tab[1]).name);
}
