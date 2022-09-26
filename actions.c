/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:24:00 by arakhurs          #+#    #+#             */
/*   Updated: 2022/09/20 16:24:05 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->state->fork[philo->left_fork]));
	printf("\033[0;35m");
	status(philo, "has take a left fork 🍴");
	pthread_mutex_lock(&(philo->state->fork[philo->right_fork]));
	if (philo->is_dead == 1)
		return (1);
	printf("\033[0;35m");
	status(philo, "has take a right fork 🍴");
	printf("\033[0;32m");
	status(philo, "is eating 😋");
	philo->last_meal = timeset();
	sleeping(philo->state->time_to_eat, philo->state);
	(philo->eat_count)++;//for each philo
	return (0);
}

void	dead(t_philo *philo, int *ate)
{
	philo->is_dead = 1;
	printf("\033[0;31m");
	status(philo, "💀 Died ⚰️");
	*ate = -1;
}

void	all_ate(int *ate, t_philo **philo, int i)
{
	if (philo[0]->state->nb_eat != -1 && philo[i]->eat_count \
			>= philo[0]->state->nb_eat)
		++(*ate);
}

void	sleeping(long long time, struct s_state *state)
{
	long long	i;

	i = timeset();
	(void)state;
	while (1)
		if ((timeset() - i) >= time)
			break ;
}
