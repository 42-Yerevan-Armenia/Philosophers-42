/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:31:22 by arakhurs          #+#    #+#             */
/*   Updated: 2022/09/20 16:31:23 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
		if (!str[0])
			return (0);
	while (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

void	ft_error(char *str)
{
	if (str && *str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * j);
}

int	args(int ac, char **av, struct s_state *s)
{
	if (ac < 5 || ac > 6)
		ft_error("❌ ./philo 4️⃣  or 5️⃣  arguments");
	s->nb = ft_atoi(av[1]);
	if (s->nb < 1 || s->nb > 200)
		ft_error("❌ Wrong number of philosophers 🏛");
	s->time_to_die = ft_atoi(av[2]);
	if (s->time_to_die <= 0)
		ft_error("❌ Time to die ☠️");
	s->time_to_eat = ft_atoi(av[3]);
	if (s->time_to_eat <= 0)
		ft_error("❌ Time to eat 🍽");
	s->time_to_sleep = ft_atoi (av[4]);
	if (s->time_to_sleep <= 0)
		ft_error("❌ Time to sleep 💤");
	if (ac == 6)
	{
		s->nb_eat = ft_atoi(av[5]);
		if (s->nb_eat <= 0)
			ft_error("Wrong number of fruits");
	}
	else
		s->nb_eat = -1;
	return (0);
}
