#include "../../includes/com.h"

void	save_head(char *p, t_4b type_h, t_4b *flg, unsigned long *len )
{
	if (*p == '\0')
	{
		if (type_h == 0)
			g_data->head->prog_name[*len] = '\n';
		else if (type_h == 1)
			g_data->head->comment[*len] = '\n';
	}
	while (*p != '\"' && *p != '\0')
	{
		if ((type_h == 0 && *len > 128))
			error_event(ERR_CHNAME_LEN);
		else if (type_h == 1 && *len > 2048)
			error_event(ERR_CHCOMM_LEN);
		if (type_h == 0)
			g_data->head->prog_name[*len] = *p;
		else if (type_h == 1)
			g_data->head->comment[*len] = *p;
		p++;
		(*len)++;
	}
	if (*p == '\0')
		return ;
	else if (*p == '\"')
		*flg += 1;
}

char	*init_headdata(char *p, t_4b *flg)
{
	p = skip_space(p);
	if (*p != '\"' )
	{
		error_event(ERR_NAMECOM);
		//printf("what's in front of the name???\n");
	}
	else
	{
		*flg += 1;
	}
	p++;
	return(p);
}

void	add_header(char *s)
{
	char	*p;

	if ((p = ft_strstr(s, NAME_CMD_STRING)) != NULL
		 && p == s && g_data->name_f == 0 && g_data->namelen == 0)
	{
		p += ft_strlen(NAME_CMD_STRING);
		save_head(init_headdata(p, &(g_data->name_f)), 0, &(g_data->name_f), &(g_data->namelen));
	}
	else if(g_data->name_f == 1)
		save_head(s, 0, &(g_data->name_f), &(g_data->namelen));
	else if((p = ft_strstr(s, COMMENT_CMD_STRING))!= NULL && p == s
			 && g_data->comm_f == 0)
	{
		p += ft_strlen(COMMENT_CMD_STRING);
		save_head(init_headdata(p,&(g_data->comm_f)), 1, &(g_data->comm_f), &(g_data->commlen));
	}
	else if(g_data->comm_f == 1)
		save_head(s, 1, &(g_data->comm_f), &(g_data->commlen));
	else if (g_data->name_f == 2 && g_data->comm_f == 2)
	{
		//printf("ERROR header already exists\n");
		error_event(ERR_NAMECOM);
	}
	printf("prog_name =%s\ncomment=%s\n", g_data->head->prog_name, g_data->head->comment);
}


