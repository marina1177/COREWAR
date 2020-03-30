
#include "../../includes/com.h"

char			*freesplit(t_token	*tmp)
{
	unsigned int	i;

	i = 0;
	while (i < (tmp)->op->args_num)
	{
		free(tmp->args[i]->arg);
		free(tmp->args[i]);
		++i;
	}
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
		freesplit(tmp);
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
		free(temp->label);
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
