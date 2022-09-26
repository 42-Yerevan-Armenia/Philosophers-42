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
	int				id;//indexx of philos
	int				eat_count;//for each philo
	int				left_fork;//mutex
	int				right_fork;//mutex
	int				is_dead;//to break process
	long long		born_time;//first appearance
	long long		last_meal;//for each philo
	pthread_t		thread;//routine
	pthread_mutex_t	*thinking;//mutex
	struct s_state	*state;
}				t_philo;

struct s_state//args
{
	int				nb;
	int				nb_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*fork;
};

//Parsing ♻️
int			ft_error(char *str);
int			ft_atoi(const char *str);
int			args(int ac, char **av, struct s_state *s);

//Routine ⚙️
long long	timeset(void);
void		*routine(void *args);
void		*death_check(void *args);
void		status(t_philo *philo, char *str);
int			thread(struct s_state *s, t_philo **philo);

//Actions ⚙️
int			eating(t_philo *philo);
void		dead(t_philo *philo, int *ate);
void		all_ate(int *ate, t_philo **philo, int i);
void		sleeping(long long time, struct s_state *state);

#endif
