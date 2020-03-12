
#include "../../includes/com.h"

char			*freesplit()
{
	int	i;

	i = 0;
	while (g_tkn_last->op_args[i] != NULL)
	{
		free(g_tkn_last->op_args[i]);
		i++;
	}
	free(g_tkn_last->op_args);//???
	return (NULL);
}

void	free_token()
{
	t_token	*tmp;

	if (!g_tkn_first)
		return ;
	while (g_tkn_first != NULL)
	{
		tmp = g_tkn_first;
		g_tkn_first = (g_tkn_first)->next;
		if (tmp->op_args)
			freesplit();
		free(tmp);
	}
}

void	free_label()
{
	t_lbl_lst	*temp;

	if (g_label_first == NULL)
		return ;
	while (g_label_first != NULL)
	{
		temp = g_label_first;
		g_label_first = g_label_first->next;
		free(temp);
	}
}

void		free_data(void)
{
	/*if (g_buf)
		free(g_buf);*/
	if (g_data)
	{
		if (g_data->fd_s)
			close(g_data->fd_s);
		free(g_data->head);
		free(g_data);
	}
	if (g_tkn_first)
		free_token();
	if (g_label_first)
		free_label();
	exit(0);
}
