/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/15 18:04:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		print_usage(void)
{
	ft_printf("\033[0;32musage:\nflags: etc\n\033[0m");
	exit(0);
	return (1);
}

int		check_name(char *name)
{
	int i;

	i = ft_strlen(name) - 1;
	if (name[i] == 'r' && name[i - 1] == 'o' && name[i - 2] == 'c' && name[i - 3] == '.')
		return (0);
	else
		return (1);
}

t_cw	*arg_analize(char **av)
{
	t_cw	*cw;
	int		i;
	int		order;

	i = 0;
	order = 0;
	if (!(cw = (t_cw *)malloc(sizeof(t_cw))))
		return (NULL);
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			if (ft_strcmp(av[i], "-n") == 0 && av[i + 1])
			{
				if (ft_atoi(av[i + 1]) >= 1 && ft_atoi(av[i + 1]) <= MAX_PLAYERS && av[i + 2])
				{
					if (check_name(av[i + 2]) == 0)
					{
						write(1, "worked\n", 6);
						
					}
				}
			}
		}
		else
		{
			if (check_name(av[i]) == 0)
			{
				write(1, "worked\n", 7);

			}
		} 
		i++;
	}
	return (cw);
}

void	parse_flag_n(t_cw *cw, char *arg)
{
	
	
	
}

static int		check_option_n(char *s_nplayer, t_cwoptions *cwoptions,
	t_player *players)
{
	int		player_n;

	if (!ft_isint(s_nplayer))
		ret_error("Error: failed value for option -n\n", -1);
	player_n = ft_atoi(s_nplayer);
	if (player_n < 1 || player_n > cwoptions->q_players)
		ret_file_error("Error: failed a number of the player for option -n: ",
		s_nplayer, " is less than 1 or more than max quantity of players\n",
		-1);
	if (players[player_n - 1].id != 0)
		ret_file_error("Error: a number of the player #", s_nplayer,
		" is busy\n", -1);
	return (player_n);
}




void	parse_args(t_cw *cw, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-n"))
		{
			parse_flag_n(cw, av[i + 1]);
			i++;
		}
		else if (!ft_strcmp(av[i], "-dump"))
			parse_flag_dump(i + 1, ac, av, cw);	
		else
			parse_players(cw, av[i]);
		i++;
	}
}

int     main(int ac, char **av)
{
	t_cw	*cw;

	ac < 2 ? print_usage() : 0;	
	if (is_valid_args(ac, av))
	{
		cw = t_cw_create();
		parse_args(cw, ac, av);
	}
	return (0);
}