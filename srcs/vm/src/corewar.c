/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscottie <sscottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:25:04 by sscottie          #+#    #+#             */
/*   Updated: 2020/03/14 20:39:17 by sscottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(void)
{
	ft_printf("\033[0;32musage:\nflags: etc\n\033[0m");
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

int		check_magic(unsigned char *magic)
{
	if (magic[0] == 0x0 && magic[1] == 0xea && magic[2] == 0x83 && magic[3] == 0xf3)
		return (0);
	return (1);
}

t_cw	*arg_analize(char **av)
{
	t_cw	*cw;
	int		i;
	int		order;
	int		fd;

	unsigned char buf[4];
	
	i = 1;
	order = 0;
	fd = 0;
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
				fd = open(av[i], O_RDONLY);
				ft_printf("fd = %d\n", fd);
				if (fd == -1)
                	perror("open failed on input file");
				else
				{
					int t = 0;
					while (read(fd, &buf[t], 1) && t < MAGIC_LEN)
					{
						ft_printf("%02x ", buf[t]);
						t++;
					}
					write(1, "\n", 1);
					if (check_magic(buf))
						return (NULL);
					ft_printf("MAGIC GOOD\n");
					close(fd);
				}
				
			}
		} 
		i++;
	}
	return (cw);
}

int		main(int ac, char **av)
{
	t_cw	*cw;

	if (ac == 1)
	{
		print_usage();
		return (0);
	}
	else
	{
		cw = arg_analize(av);
	}
	return (0);
}
