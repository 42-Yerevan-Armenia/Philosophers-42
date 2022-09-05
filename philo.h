/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:28:14 by arakhurs          #+#    #+#             */
/*   Updated: 2022/09/04 18:29:44 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	int				is_dead;
	long long		born_time;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*thinking;
	struct s_state	*state;
}				t_philo;

struct s_state
{
	int				nb;
	int				nb_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*fork;
};

void	ft_error(char *str);
int		ft_atoi(const char *str);

#endif
