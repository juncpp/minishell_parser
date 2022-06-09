#include "minishell.h"

int	create_command(t_command **command, char *date, int flag)
{
	t_command	*tmp1;
	t_command	*tmp2;

	tmp1 = *command;
	tmp2 = (t_command *)malloc(sizeof(t_command));
	if (tmp2 == NULL)
		return (0);
	tmp2->next = NULL;
	tmp2->str = date;
	tmp2->flag = 1;
	if (flag == 0)
			tmp2->flag = 0;
	if (tmp1 == NULL)
		*command = tmp2;
	else
	{
		while (tmp1->next != NULL)
			tmp1 = tmp1->next;
		tmp1->next = tmp2;
	}
	return (1);
}

char	*str_command(char *p, int tmp, int i, int flag)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (i - tmp + 1));
	if (!str)
		return (NULL);
	if (flag == 1)
	{
		while (is_token(p[tmp]) == WORD)
			str[j++] = p[tmp++];
	}
	else if (flag == 2)
		str[j++] = p[tmp];
	else if (flag == 3)
	{
		str[j++] = p[tmp++];
		str[j++] = p[tmp++];
	}
	str[j] = '\0';
	return (str);
}

int	in_str_token(int token, char *p, t_command **command, int *i)
{
	int	tmp;

	tmp = *i;
	if (token == 0)
	{
		while (is_token(p[*i]) == SEP)
			(*i)++;
	}
	else if (token == 1)
	{
		while (is_token(p[*i]) == WORD)
			++*i;
		tmp = create_command(command, str_command(p, tmp, *i, 1), 1);
		if (tmp == 0)
			return (tmp);
	}
	return (tmp);
}

char	*str_command_fields(char *p, int tmp, int i)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (i - tmp - 1));
	if (!str)
		return (NULL);
	++tmp;
	while (tmp < i - 1)
		str[j++] = p[tmp++];
	str[j] = '\0';
	return (str);
}

int	run_str(int token, char *p, t_command **command, int *i)
{
	int			tmp;

	tmp = *i;
	if (token == 0 || token == 1)
		tmp = in_str_token(token, p, command, i);
	else if (token == 8 || (token >= 4 && token <= 5))
		tmp = create_command(command, str_command(p, tmp, ++*i, 2), 0);
	else if (token == 6 || token == 7)
	{
		tmp = create_command(command, str_command(p, tmp, *i + 2, 3), 0);
		*i = *i + 2;
	}
	else
	{
		++*i;
		while (is_token(p[*i]) != token && p[*i])
			(*i)++;
		if (is_token(p[*i]) == token)
			++*i;
		tmp = create_command(command, str_command_fields(p, tmp, *i), token % 2);
	}
	return (tmp);
}