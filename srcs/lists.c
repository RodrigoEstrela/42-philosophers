# include "../inc/philo.h"

void	ft_lstfront(t_forks **lst, t_forks *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_forks **lst, t_forks *new)
{
	t_forks *tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp->next = (*lst)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_forks *ft_lstnew(int *content)
{
	t_forks *new;

	new = malloc(sizeof(t_forks));
	if (!new)
		return (NULL);
	new->fork = content;
	new->next = NULL;
	return (new);
}
