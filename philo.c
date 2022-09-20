/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:27:22 by arakhurs          #+#    #+#             */
/*   Updated: 2022/09/04 18:27:35 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fill_philo(t_philo **philo, int i, struct s_state *s, \
		pthread_mutex_t *thinking)
{
	philo[i] = (t_philo *)malloc(sizeof(t_philo));
	if (philo[i] == 0)
		return (0);
	philo[i]->id = i;
	philo[i]->eat_count = 0;
	philo[i]->last_meal = 0;
	philo[i]->is_dead = 0;
	philo[i]->born_time = -1;
	philo[i]->left_fork = i;
	philo[i]->right_fork = (i + 1) % s->nb;
	philo[i]->thinking = thinking;
	philo[i]->state = s;
	if (pthread_mutex_init(&(s->fork[i]), NULL))
		ft_error("❌ Mutex not initialized❗️");
	return (1);
}

t_philo	**philosophers(struct s_state *s)
{
	int				i;
	t_philo			**philo;
	pthread_mutex_t	waiting;

	philo = (t_philo **)malloc(sizeof(t_philo) * (s->nb + 1));
	s->fork = malloc(sizeof(pthread_mutex_t) * s->nb);
	if (!philo || !(s->fork))
		exit(0);
	philo[s->nb] = 0;
	if (pthread_mutex_init(&waiting, NULL) != 0)
		ft_error("❌ Mutex not initialized ⚠️");
	i = -1;
	while (++i < s->nb)
		if (fill_philo(philo, i, s, &waiting) == 0)
			return (0);
	return (philo);
}

void	*death_check(void *args)
{
	int		i;
	int		eat_finish;
	t_philo	**philo;

	philo = (t_philo **)args;
	usleep(15000);
	while (1)
	{
		eat_finish = 0;
		i = -1;
		while (++i < philo[0]->state->nb)
		{
			if (((timeset() - philo[i]->last_meal) > \
				philo[0]->state->time_to_die) && philo[i]->born_time > 0)
			{
				dead(philo[i], &eat_finish);
				break ;
			}
			all_ate(&eat_finish, philo, i);
		}
		if (eat_finish == philo[0]->state->nb || eat_finish == -1)
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct s_state	state;
	t_philo			**philo;

	if (args(ac, av, &state) == 0)
	{
		philo = philosophers(&state);
		if (philo == 0)
			return (0);
		thread(&state, philo);
	}
	return (0);
}
