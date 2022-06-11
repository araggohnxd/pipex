/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:45:44 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 03:59:30 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_parse_env_path(char *envp[], char *cmd)
{
	size_t	i;
	char	**split;
	char	*current_path;
	char	*bin;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
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
		if (access(current_path, X_OK) == 0)
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
		if (ft_strchr("\"'", s[i++]))
		{
			while (!ft_strchr("\"'", s[i]))
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

	ft_replace_quoted_arg(&cmd, ' ', 1);
	split = ft_split(cmd, ' ');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		ft_replace_quoted_arg(&split[i++], 1, ' ');
	return (split);
}

void	ft_argument_parser(t_data *data)
{
	data->args = (char ***) ft_calloc(3, sizeof(char **));
	data->args[0] = ft_parse_cmd_args(data->argv[2]);
	data->args[1] = ft_parse_cmd_args(data->argv[3]);
	data->cmds = (char **) ft_calloc(3, sizeof(char *));
	data->cmds[0] = ft_parse_env_path(data->envp, *(data->args[0]));
	data->cmds[1] = ft_parse_env_path(data->envp, *(data->args[1]));
}
