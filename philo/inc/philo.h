/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PHILOSOPHERS                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
// timestamp
# define PURPLE "\033[0;35m"
# define RESET "\033[0m"

typedef struct s_lst{
	int				*q;
	struct s_lst	*next;
}					t_lst;

typedef struct s_philo{
	t_lst		*esq;
	t_lst		*dir;
	int			*phn;
	int			*status;
	int 		*ecnt;
}					t_philo;

typedef struct s_master
{
	pthread_mutex_t	*mt1;
	pthread_mutex_t	*mt2;
	pthread_mutex_t	*mt3;
	int				*ph_n;
	int				*die_t;
	int				*eat_t;
	int				*sleep_t;
	t_lst			**forks;
	t_philo			**b;
	pthread_t		th[124535];
}				t_master;

void			*f_thread(void *m);
t_lst			*get_item(t_lst *lst, int index, int flag);
void			buildlst(t_lst **lst, int n, int cnt);
t_lst			*ft_lstnew(int *content);
void			ft_lstadd_back(t_lst **lst, t_lst *new);
void			ft_lstfront(t_lst **lst, t_lst *new);
void			deletelist(t_lst **lst);
int				ft_atoi(const char *str);
long long int	get_time(struct timeval start);
int				me_dead(int dtime, long long int etime, struct timeval s);
int				ft_isnumber(const char *str);
int				inputcheck(int ac, char **av);
void			masterbuilder(t_master *m, char **av);
void			threaddoer(t_master *m, char **av);
void			masterdestroyer(t_master *m);
#endif
