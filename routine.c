/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:20:09 by arakhurs          #+#    #+#             */
/*   Updated: 2022/09/05 17:20:10 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		usleep(20000);//sleep microseconds
	while (1)
	{
		if (eating(philo) == 1)
			break ;
		printf("\033[0;36m");
		status(philo, "is sleeping 💤");
		pthread_mutex_unlock(&(philo->state->fork[philo->left_fork]));
		pthread_mutex_unlock(&(philo->state->fork[philo->right_fork]));
		sleeping(philo->state->time_to_sleep, philo->state);
		printf("\033[0;33m");
		status(philo, "is thinking 🧠");
	}
	return (NULL);
}

int	thread(struct s_state *s, t_philo **philo)
{
	int			i;
	pthread_t	dead;

	i = -1;
//	pthread_create(1, 2, 3, 4)
//	1->t1 variable &pointer
//	2->atrubuts, default NULL
//	3->&function that will be "executed"
//	4->arguments in &function(), default NULL
	pthread_create(&dead, NULL, death_check, (void *)philo);
	while (philo[++i] != 0)
	{
		philo[i]->born_time = timeset();
		philo[i]->last_meal = timeset();
		if (pthread_create(&(philo[i]->thread), 0, routine, (void *)(philo[i])))
			return (1);
	}
//	pthread_join(1, 2) -> finish "execution"
//	1->t1 actual struct
//	2->pointer for result, default NULL
	pthread_join(dead, NULL);
	i = -1;
	while (++i < s->nb)
		pthread_mutex_destroy(&(s->fork[i]));
	pthread_mutex_destroy(philo[0]->thinking);
	return (0);
}

long long	timeset(void)
{
	struct timeval	t;//
	//			time, timezone
	gettimeofday(&t, NULL);// Jun1 1970 00:00:00
	//timeval sec from start  ⬆️ microsec from start 
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	status(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->thinking);//microsec, philo nb, text
	printf("%lld %d %s\n", timeset() - philo->born_time, philo->id + 1, str);
	pthread_mutex_unlock(philo->thinking);
}
