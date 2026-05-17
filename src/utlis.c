t_path	*ft_lstnew(char *str)
{
	t_path	*path;

	path = ft_malloc(sizeof (t_path));
	if (!path)
		return (NULL);
	path->path = str;
    lstat(str, &path->stat);
	path->next = NULL;
	return (path);
}

int	ft_lstadd_alpha(t_list **lst, char *str)
{
	t_list	*path;
	t_list	*tmp;

    path = ft_lstnew(str);
    if (!path)
        return (1);
	if (!*lst || ft_strcmp((*lst)->path, str) > 0)
	{
		path->next = *lst;
        *lst = path;
    }
    else
    {
        tmp = *lst;
        while (tmp->next && ft_strcmp(tmp->next->path, str) < 0)
            tmp = tmp->next;
        path->next = tmp->next;
        tmp->next = path;
    }
    return (0);
}