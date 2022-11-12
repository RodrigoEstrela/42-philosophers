#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

// philo is thinking
# define BLUE "\033[0;34m"
// philo died
# define RED "\033[1;31m"
// philo is eating
# define GREEN "\033[0;32m"
// philo has taken a fork
# define YELLOW "\033[0;33m"
// philo is sleeping
# define CYAN "\033[0;36m"
// timer
# define PURPLE "\033[0;35m"
# define RESET "\033[0m"

typedef struct		s_lst {
	int				*q;
	struct s_lst	*next;
} 					t_lst;


typedef struct s_philo{
	char		**args;
	int			*ind;
	t_lst		*x;
	t_lst 		*esq;
	t_lst 		*dir;
	pthread_mutex_t	*mt;
}					t_philo;

t_lst	*get_item(t_lst *lst, int n, int flag);
void	buildlst(t_lst **lst, int n);
t_lst	*ft_lstnew(int *content);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstfront(t_lst **lst, t_lst *new);
void	*fThread_Timer(void *forks);

void	printforks(t_lst *lst);
void	crono_thread(t_lst **forks);

#endif
