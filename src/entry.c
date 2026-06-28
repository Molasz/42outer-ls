#include "ft_ls.h"

static t_entry	*new_entry(char *name, struct stat *st)
{
	t_entry	*entry;

	entry = malloc(sizeof (t_entry));
	if (!entry)
		return (NULL);
	entry->name = ft_strdup(name);
	if (!entry->name)
	{
		free(entry);
		return (NULL);
	}
	entry->stat = *st;
	entry->next = NULL;
	return (entry);
}

static void	entry_insert_alpha(t_entry **a, t_entry *b, int r_flag)
{
	t_entry *tmp;

	if (!*a || (!r_flag && ft_strcmp((*a)->name, b->name) > 0) || (r_flag && ft_strcmp((*a)->name, b->name) < 0))
	{
		b->next = *a;
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ( (!r_flag && ft_strcmp(tmp->next->name, b->name) < 0) || (r_flag && ft_strcmp(tmp->next->name, b->name) > 0)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

static void	entry_insert_time(t_entry **a, t_entry *b, int r_flag)
{
	t_entry *tmp;

	if (!*a || (!r_flag && (*a)->stat.st_mtime < b->stat.st_mtime) || (r_flag && (*a)->stat.st_mtime >= b->stat.st_mtime))
	{
		b->next = (*a);
		*a = b;
		return ;
	}
	tmp = *a;
	while (tmp->next && ((!r_flag && tmp->next->stat.st_mtime >= b->stat.st_mtime) || (r_flag && tmp->next->stat.st_mtime < b->stat.st_mtime)))
		tmp = tmp->next;
	b->next = tmp->next;
	tmp->next = b;
}

int	add_entry(t_data *data, t_entry **entries, char *path, struct stat *st)
{
	t_entry			*entry;

	entry = new_entry(path, st);
	if (!entry)
		return (1);
	if (data->t_flag)
		entry_insert_time(entries, entry, data->r_flag);
	else
		entry_insert_alpha(entries, entry, data->r_flag);
    return (0);
}