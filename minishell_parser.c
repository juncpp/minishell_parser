#include "minishell.h"

int	skip_field(t_token **token, int x)
{
	if ((*token)->token == x)
	{
		*token = (*token)->next;
		while ((*token)->token != x)
			*token = (*token)->next;
		return (1);
	}
	return (0);
}

int	check_fields(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp != NULL)
	{
		if (tmp->token == FIELD)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->token != FIELD)
				tmp = tmp->next;
		}
		else if (tmp->token == EXP_FIELD)
		{
			tmp = tmp->next;
			while (tmp != NULL && tmp->token != EXP_FIELD)
			{
				tmp = tmp->next;
			}
		}
		if (tmp == NULL)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		count_list(t_command *command)
{
	int	count;

	count = 0;
	while (command != NULL)
	{
		++count;
		command = command->next;
	}
	return (count);
}
char	**parser(t_command **command)
{
	char		**str;
	t_command	*tmp;
	int 	i;

	tmp = *command;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (count_list(tmp) + 1));
	if (!str)
		return (NULL);
	while (i < count_list(*command))
	{
		str[i] = (char *)malloc(sizeof(char) * ft_strlen(tmp->str));
		if (!str[i])
			return (NULL);
		ft_strcopy(str[i], tmp->str);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}