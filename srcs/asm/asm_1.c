#include "../includes/com.h"


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
		printf("a==-1 =>invalid option ");
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

void	save_head(char *p, t_4b type_h, t_4b flg, unsigned long len )
{
	while (*p != '\"' && *p != '\0')
	{
		printf("start\n");
		printf("*p = %c\n", *p);
		//printf("g_data->head->prog_name =%s\n", g_data->head->prog_name);
		(g_data->head)->prog_name[len] = *p;
		p++;
		len++;
		printf("len = %ld\n", len);
	//	exit(0);
		if ((type_h == 0 && len > 128)
			|| (type_h == 1 && len > 2048))
		{
			printf("error PROG_NAME_LENGTH\n");
			error();
		}/*
		if (type_h == 0)
		{
			printf("1_p=%s\n",p);
			g_data->head->prog_name[len] = *p;
			printf("1_p=%s\ng_data->head->prog_name[%ld] =%c", p,len, g_data->head->prog_name[len]);
		}
		else if (type_h == 1)
			g_data->head->comment[len] = *p;
		len++;
		p++;
	//	printf("len = %ld, *p = %c\n", len, *p);*/
	}
	printf("*p_end = %c\n", *p);
	if (*p == '\0')
		return ;
	else if (*p == '\"')
	{
		flg -= 1;
		printf("flg = %d\n",flg);
		/*if (type_h == 0)
			//g_data->head->prog_name[len] = '\0';
		else if (type_h == 1)
			//g_data->head->comment[len] = '\0';*/
	}
}

char	*init_headdata(char *p, t_4b flg)
{
	flg += 1;
	p = skip_space(p);
	printf("2_p =%s\n",p);
	if (*p != '\"' )
	{
		printf("what's in front of the name???\n");
		exit(0);
	}
	p++;
	printf("3_p =%s\n",p);
	return(p);
	//len = 0;
}

void	add_header(char *s)
{
	char	*p;
	printf("p =%s\n", s);

	if ((p = ft_strstr(s, NAME_CMD_STRING)) != NULL
		 && p == s++ && g_data->name_f == 0 && g_data->namelen == 0)
	{
		printf("_1_\n");
		p += ft_strlen(NAME_CMD_STRING);
		printf("1_p =%s\n",p);
		save_head(init_headdata(p,g_data->name_f), 0, g_data->name_f, g_data->namelen);
	}
	else if(g_data->name_f == 1)
	{
		printf("_2_\n");
		save_head(p, 0, g_data->name_f, g_data->namelen);
	}
	else if((p = ft_strstr(s, COMMENT_CMD_STRING))!= NULL && p == &(s[1])
			 && g_data->comm_f == 0 && g_data->commlen == 0)
	{
		printf("_3_\n");
		p += ft_strlen(COMMENT_CMD_STRING);
		init_headdata(p,g_data->comm_f);
		save_head(p, 1, g_data->comm_f, g_data->commlen);
	}
	else if(g_data->comm_f == 1)
	{
		printf("_4_\n");
		save_head(p, 1, g_data->comm_f, g_data->commlen);
	}

	else
	{
		printf("ERROR HEADER\n");
		error();
	}

}

void		parse_str(char **buf)
{
	char	*pnt;

	pnt = skip_comment(*buf);
	pnt = skip_space(*buf);

	if (*pnt != '\0')
	{
		if (*pnt == '.')
		{
			printf("add_header\n");
			//add_header(pnt);
			//return ;
		}
		else
			search_op(pnt);
	}
	else
		return ;
	printf("---------------%s\n",(g_op_tab[1]).name);

}
