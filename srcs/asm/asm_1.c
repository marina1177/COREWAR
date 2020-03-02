#include "com.h"


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


void	save_head(char *p, t_4b type_h, t_4b *flg, unsigned long *len )
{
	while (*p != '\"' && *p != '\0')
	{
		if ((type_h == 0 && *len > 128)
			|| (type_h == 1 && *len > 2048))
		{
			printf("error PROG_NAME_LENGTH\n");
			error();
		}
		if (type_h == 0)
			g_data->head->prog_name[*len] = *p;
		else if (type_h == 1)
			g_data->head->comment[*len] = *p;
		p++;
		(*len)++;
	}
	printf("*p_end = %c\n", *p);
	if (*p == '\0')
		return ;
	else if (*p == '\"')
	{
		*flg -= 1;
		printf("flg = %d\n",*flg);
	}
}

char	*init_headdata(char *p, t_4b *flg)
{
	*flg += 1;
	p = skip_space(p);
	//printf("2_p =%s\n",p);
	if (*p != '\"' )
	{
		printf("what's in front of the name???\n");
		exit(0);
	}
	p++;
	//printf("3_p =%s\n",p);
	return(p);
}

void	add_header(char *s)
{
	char	*p;

	if ((p = ft_strstr(s, NAME_CMD_STRING)) != NULL
		 && p == s && g_data->name_f == 0 && g_data->namelen == 0)
	{
		p += ft_strlen(NAME_CMD_STRING);
		save_head(init_headdata(p,&(g_data->name_f)), 0, &(g_data->name_f), &(g_data->namelen));
	}
	else if(g_data->name_f == 1)
		save_head(s, 0, &(g_data->name_f), &(g_data->namelen));
	else if((p = ft_strstr(s, COMMENT_CMD_STRING))!= NULL && p == s
			 && g_data->comm_f == 0 && g_data->commlen == 0)
	{
		p += ft_strlen(COMMENT_CMD_STRING);
		save_head(init_headdata(p,&(g_data->comm_f)), 1, &(g_data->comm_f), &(g_data->commlen));
	}
	else if(g_data->comm_f == 1)
		save_head(s, 1, &(g_data->comm_f), &(g_data->commlen));
	else if (g_data->namelen != 0 && g_data->commlen != 0)
	{
		printf("ERROR header already exists\n");
	}
	/*else
	{
		printf("prog_name =%s\ncomment=%s\n", g_data->head->prog_name, g_data->head->comment);
		return ;
	}*/
	printf("prog_name =%s\ncomment=%s\n", g_data->head->prog_name, g_data->head->comment);

}

void		parse_str(char **buf)
{
	char	*pnt;

	pnt = skip_comment(*buf);
	if (*pnt != '\0')
	{
		if (*pnt == '.' || g_data->name_f != 0 || g_data->comm_f != 0)
		{
			printf("add_header\n");
			add_header(pnt);
			//return ;
		}
		else
		{
			pnt = skip_space(*buf);
			search_op(pnt);
		}
	}
	else
		return ;
	printf("---------------%s\n",(g_op_tab[1]).name);

}
