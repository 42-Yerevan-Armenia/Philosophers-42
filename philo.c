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

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 23, 29};

void *routine(void *arg)
{
	int index = *(int *)arg;
	printf("%d ", primes[index]);
	free(arg);
}

int	main(int ac, char **av)
{
	pthread_t th[10];
	int i;
	for (i = 0; i < 10; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0 )
			perror("Faild to create thread");
	}
	for (i = 0; i < 10; i++)
		if (pthread_join(th[i], NULL) != 0 )
			perror("Faild to join thread");
	return (0);
}

/*int	args(int ac, char **av, struct s_state *s)
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

t_philo	**philosofers(struct s_state *s)
{
	return (philo);
}

int	thread(struct s_state *state, t_philo **philo)
{
	return (0);
}

int	main(int ac, char **av)
{
	struct s_state	state;
	t_philo			**philo;

	if (args(ac, av, &state) == 0)
	{
		philo = philosofers(&state);
		if (philo == 0)
			return (0);
		thread(&state, philo);
	}
	return (0);
}*/

/*
Thread N1

pthread_create(1, 2, 3, 4)
1->t1 variable &pointer
2->atrubuts, default NULL
3->&function that will be executed
4->arguments in &function(), default NULL
pthread_join(1, 2) -> finish execution
1->t1 actual struct
2->pointer for result, default NULL

------------------------------------

Processes vs threads N2

2 dif id	  2 same id

Process can contain multiple threads
NOT multiple processes in single thread
In forking we are duping all the vars to child process
All vars in the same threads, all threads can access all vars

------------------------------------

Race Conditions N3
 				t1		t2
read mails		23		24
increment		23		24
write mails		24		25

multiple times in the same thread for (int i = 0; i < 100; i++) {mails++;}
				t1		t2
read mails		23		23 -> wait t1 
increment		23		
write mails		24	
...
read mails		24		23 -> wait t1 
increment		24		
write mails		25		
... (7 times)
read mails		29		23
increment		29		30
write mails		30		24

------------------------------------

Mutex N4

int	lock = 0;
 					t1		t2
lock = 1 start t1			wait until lock = 0
read mails			23
increment			23
write mails			24
lock = 0 finish t1, start t2

for savty work use
pthread_mutex_t	mutex; (in function)
pthread_mutex_lock(&mutex);
function ...
pthread_mutex_unlock(&mutex);

pthread_mutex_init(&mutex, NULL);
trades ...
pthread_mutex_destroy(&mutex);

It will solve Race Conditions problem
Mutex protect your code that executes t1 from others t

------------------------------------

Get return value N6

In void function we need allocate(deallocate) our result by malloc

------------------------------------

Pass arguments to threads N7

Main t			t1			t2
i = 0			created		created 
i = 1			i is 0		i is 1
				print 2		print 3

If t2 started right after t1
Main t			t1			t2
i = 0			created		created 
i = 1			i is 1		i is 1
				print 3		print 3

------------------------------------

N8 - 19
*/
