#include "com.h"

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

void	solve_res(char *s, char **s_op, int a)
{
  int		lbllen;
  char	*pnt;
  char	*op;

  printf("##########SOLVE_RES##############\n");

  if(a == -1)
  {
    printf("a==-1 => invalid option ");
    return ;
  }
  else
    op = s_op[a];

  printf("s =%s__op =%s\n",s,op);

  if (*s != '\0' && (op == NULL || op != &(s[0])))
  {
    lbllen = 0;
    while (is_lblchar(s[lbllen]))
    {
      printf("lblchr_%c\n",s[lbllen]);
      lbllen++;
    }
    if (s[lbllen] == ':')
    {
      add_token(&(s[0]), lbllen, LABEL, -1);
      //printf("after add_token(LABEL) = %s\n",s);
    }
    else
    {
      printf("where label_:_???\n");
      error();
    }
    pnt = skip_space(&(s[lbllen + 1]));
    //printf("pnt = %s\n",pnt);
    if (pnt == op)
    {
      add_token(op, 0, INSTRUCTION, a);
      printf("after add_token(INSTR) = %s\n",s);
    }
    else
    {
      printf("wtf after label:???\n");
      error();
    }
  }
  else if (op == &(s[0]) && a > 0)
  {
    add_token(op, 0, INSTRUCTION, a);
    printf("after add_token(INSTR) = %s\n",s);
  }
}

void search_op(char *s)
{
  int		a;
  char	*op[16];

  printf("search_op = %s\n",s);
  a = -1;
  (op[0] = ft_strstr(s, "live")) != NULL ? a = 0 : -1;
  (op[1] = ft_strstr(s, "ld")) != NULL ? a = 1 : -1;
  (op[2] = ft_strstr(s, "st")) != NULL ? a = 2 : -1;
  (op[3] = ft_strstr(s, "add")) != NULL ? a = 3 : -1;
  (op[4] = ft_strstr(s, "sub")) != NULL ? a = 4 : -1;
  (op[5] = ft_strstr(s, "and")) != NULL ? a = 5 : -1;
  (op[6] = ft_strstr(s, "or")) != NULL ? a = 6 : -1;
  (op[7] = ft_strstr(s, "xor")) != NULL ? a = 7 : -1;
  (op[8] = ft_strstr(s, "zjmp")) != NULL ? a = 8 : -1;
  (op[9] = ft_strstr(s, "ldi")) != NULL ? a = 9 : -1;
  (op[10] = ft_strstr(s, "sti")) != NULL ? a = 10 : -1;
  (op[11] = ft_strstr(s, "fork")) != NULL ? a = 11 : -1;
  (op[12] = ft_strstr(s, "lld")) != NULL ? a = 12 : -1;
  (op[13] = ft_strstr(s, "lldi")) != NULL ? a = 13 : -1;
  (op[14] = ft_strstr(s, "lfork")) != NULL ? a = 14 : -1;
  (op[15] = ft_strstr(s, "aff")) != NULL ? a = 15 : -1;
//	printf("a = %d\nop = %s\n", a, op[a]);
  solve_res(s, op, a);
}
