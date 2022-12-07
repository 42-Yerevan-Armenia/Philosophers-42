# Philosophers-42

<p align="center">
    <img src="https://i.redd.it/ob3wlk4d7du31.png">
</p>

<strong><i>The dining philosophers problem</i></strong> is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

The Dining Philosopher Problem states that N philosophers seated around a circular table with a large bowl of spaghetti and one fork between each pair of philosopher. Each philosopher is doing one of the three things: eating, sleeping, thinking. While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping. I should state that philosophers aren’t aware of other philosophers status.



The goal here is to create a program that simulate the 3 states of philosophers and log print any change of status as follow:

- **timestamp_in_ms** X has taken a fork (left/right)
- **timestamp_in_ms** X is eating
- **timestamp_in_ms** X is sleeping
- **timestamp_in_ms** X is thinking
- **timestamp_in_ms** X died

The program need 5 arguments which are:

- **number_of_philosophers[nop]**: is the number of philosophers and also the number of forks.
- **time_to_die[ttd]**: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.
- **time_to_eat[tte]**: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
- **time_to_sleep[tts]**: is in milliseconds and is the time the philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat**: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
A philosopher may eat if he can pick up the two forks adjacent to him. One fork may be picked up by any one of its adjacent followers but not both as it would result in a problem that we will discuss forthcoming.

<p align="center">
  <a href="https://adit.io/posts/2013-05-11-The-Dining-Philosophers-Problem-With-Ron-Swanson.html#deadlock">
    <img src="https://adit.io/imgs/dining_philosophers/at_the_table.png">
  </a>
</p>

## Something about coding

pthread_create(1, 2, 3, 4)
- 1 -> t1 variable &pointer
- 2 -> atrubuts, default NULL
- 3 -> &function that will be "executed"
- 4 -> arguments in &function(), default NULL

pthread_join(1, 2) -> finish "execution"
- 1 -> t1 actual struct
- 2 -> pointer for result, default NULL

------------------------------------

### Processes vs threads

2 dif id	  2 same id

Process can contain multiple threads and NOT multiple processes is a single thread. In forking we are duping all the vars to child process
- All vars in the same threads
- All threads can access all vars

------------------------------------

### Race Conditions

| Proces | t1 | t2 |
| :---------: | :---: | :---: |
| read emails | 23 | 24 |
| increment | 23 | 24 |
| write emails | 24 | 25 |

Multiple times in the same thread for (int i = 0; i < 100; i++) {emails++;}

| Proces | t1 | t2 |
| :---------: | :---: | :---: |
| read emails | 23 | 23 -> wait t1 |
| increment | 23 |
| write emails | 24 |
| ... | ... | ... |
| read emails | 24 | 23 -> wait t1 |
| increment | 24 |
| write emails | 25 |
| ... | (7 times) | ... |
| read emails | 29 | 23 |
| increment | 29 | 30 |
| write emails | 30 | 24 |

------------------------------------

### Mutex

int	lock = 0;

lock = 1, start t1, wait until lock = 0
| Proces | t1 | t2 |
| :---------: | :---: | :---: |
| read emails | 23 | wait |
| increment | 23 | wait |
| write emails | 24 | wait |

lock = 0, finish t1, start t2

For savty work use
- pthread_mutex_t	mutex; (in function)
- pthread_mutex_lock(&mutex);
- function ...
- pthread_mutex_unlock(&mutex);

In main
- pthread_mutex_init(&mutex, NULL);
- trades ...
- pthread_mutex_destroy(&mutex);

It will solve Race Conditions problem - Mutex protect your code that executes t1 from others t

------------------------------------

Get return value

In <strong><i>void</i></strong> function we need allocate(deallocate) our result by malloc

------------------------------------

### Pass arguments to threads
| Proces | t1 | t2 |
| :---------: | :---: | :---: |
| i = 0 | created | created | 
| i = 1 | i is 0 | i is 1 |
| | print 2 | print 3 |

If t2 started right after t1
| Proces | t1 | t2 |
| :---------: | :---: | :---: |
| i = 0 | created | created | 
| i = 1 | i is 1 | i is 1 |
| | print 3 | print 3 |

------------------------------------

### Trylock and lock

- **mutex_trylock** - if can't lock go to next thraed, process continiue if it can't lock
- **mutex_lock** - always waiting until mutex unlock, process stops if it can't unlock'
- **mutex_unlock** - to gontiniue process

------------------------------------

### Condition variables

- **pthread_mutex_unlock(&mutex)** - wait for pthread_cond_signal(&cond) in t1 
- **pthread_mutex_lock(&mutex)** - start pthread_cond_wait(&cond) in t2
