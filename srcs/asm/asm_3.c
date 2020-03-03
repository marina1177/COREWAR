#include "com.h"


int valid_label(char *s)
{
  int lbllen;

  lbllen = 0;
  while (is_lblchar(s[lbllen]))
  {
    printf("lblchar_%c\n",s[lbllen]);
    lbllen++;
  }
  if(lbllen == ft_strlen(s))
    return(1);
  return(0);

}

int   valid_args_type(int indx)
{
  char *p;
  int i;
  int len;

  i = 0;

  p = (g_tkn_last->op_args)[indx];
  len = ft_strlen(p);
  if (is_reg(p))
  {
    g_tkn_last->args_type[i] = T_REG;
  }
  if(*p == DIRECT_CHAR)//'%'
  {
    p++;
    len--;
    if(*(p + 1) == LABEL_CHAR && valid_label(p + 2))//":"
    {
      g_tkn_last->args_type[i] = T_DIR_LAB;
    }
    else
    {
      if (*p == '+')
      {
        printf("")
      }



    }

  }

}

void  parse_args_type()
{
  int i = 0;

  g_tkn_last->num_byte_op = 2;//код операции + код типов аргументов
  if (g_tkn_last->op->args_types_code == FALSE)
  {
    g_tkn_last->num_byte_op += g_tkn_last->op->t_dir_size;
    return ;
  }
  while ((g_tkn_last->op_args)[i] != NULL)
  {
    if (i > 3)
    {
      printf("so many arguments for operation\n");
      error();
    }
    printf("op_args[%d] = %s\n", i, (g_tkn_last->op_args)[i]);
    if(!valid_args_type(i))
    {
      printf("--args type error\n");
      error();
    }
    i++;
  }



}

void	parse_op(char *op)
{
	char	**lex;



	printf("args_op =%s\n",op);
	lex = ft_strsplit(op,  SEPARATOR_CHAR);
	if (lex == NULL)
	{
		printf("split error-\n");
		error();
	}

	g_tkn_last->op_args = lex;
	parse_args_type();
	printf("---------------%s_\n",(g_op_tab[1]).name);
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
