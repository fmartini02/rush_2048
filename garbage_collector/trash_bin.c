
#include "trash_bin.h"

void	cleaning(t_list **lis)
{
	ft_lstclear(lis, free);
	*lis = NULL;
}

void	*ft_malloc(size_t size, bool CLEAN)
{
	static t_list	*lis = NULL;
	t_list			*tmp;
	void			*new;

	if (CLEAN)
	{
		cleaning(&lis);
		return (NULL);
	}
	new = malloc(size);
	if (!new)
	{
		cleaning(&lis);
		return (NULL);
	}
	tmp = ft_lstnew(new);
	if (!tmp)
	{
		free(new);
		cleaning(&lis);
		return (NULL);
	}
	ft_lstadd_back(&lis, tmp);
	return (new);
}
