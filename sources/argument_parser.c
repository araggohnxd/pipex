/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:45:44 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/07 15:42:19 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_parse_env_path(char *envp[], char *cmd)
{
	size_t	i;
	char	**split;
	char	*current_path;
	char	*bin;
	int		is_accessible;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp || !cmd)
		return (NULL);
	split = ft_split((*envp + 5), ':');
	i = 0;
	while (split[i])
	{
		bin = ft_strdup(cmd);
		current_path = ft_strjoin(split[i++], "/");
		current_path = ft_strjoin_free(&current_path, &bin);
		is_accessible = access(current_path, X_OK);
		if (is_accessible == 0)
			break ;
		ft_memfree((void *) &current_path);
	}
	ft_free_split(&split);
	return (current_path);
}

void	ft_replace_quoted_arg(char **str, char from, char to)
{
	size_t	i;
	char	*s;

	i = 0;
	s = *str;
	while (s[i])
	{
		if (ft_strchr("\'\"", s[i++]))
		{
			while (s[i] != '\'' && s[i] != '\'' && s[i])
				if (s[i++] == from)
					s[i - 1] = to;
			++i;
		}
	}
}

char	**ft_parse_cmd_args(char *cmd)
{
	size_t	i;
	char	**split;

	ft_replace_quoted_arg(&cmd, ' ', '%');
	split = ft_split(cmd, ' ');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		ft_replace_quoted_arg(&split[i++], '%', ' ');
	return (split);
}

void	ft_get_arguments(t_data *data, char *arg, char *envp[])
{
	data->args = ft_parse_cmd_args(arg);
	if (!data->args)
		ft_set_error(1, ERRARG);
	data->cmd = ft_parse_env_path(envp, *(data->args));
	if (!data->cmd)
		ft_set_error(2, *(data->args));
}
