#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct		s_forks {
	int				*fork;
	struct s_forks	*next;
} 					t_forks;

typedef struct s_philo{
	char			**args;
	int				*ind;
	t_forks 		*esq;
	t_forks 		*dir;
	pthread_mutex_t	*mt;
}					t_philo;

void printforks(t_forks *lst);
t_forks *getfork(t_forks *lst, int n);
void buildforks(t_forks **lst, int n);
void	crono_thread(t_forks **forks);
t_forks *ft_lstnew(int *content);
void	ft_lstadd_back(t_forks **lst, t_forks *new);
void	ft_lstfront(t_forks **lst, t_forks *new);
void *fThread_Timer(void *forks);

#endif