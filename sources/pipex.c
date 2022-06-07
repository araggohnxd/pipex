/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/06 22:41:30 by maolivei         ###   ########.fr       */
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

	while (*envp && ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (!*envp || !cmd)
		return (NULL);
	(*envp) += 5;
	split = ft_split(*envp, ':');
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

int	main(int argc, char *argv[], char *envp[])
{
	char	*path;

	path = ft_parse_env_path(envp, argv[2]);
	if (!path)
		return (1);
	free(path);
	return (0);
}
