/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:23:07 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 19:31:51 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_set_perror(t_data *data, int error_id, char *str)
{
	ft_putstr_fd("pipex: ", STDERR);
	if (error_id == 127)
	{
		ft_putendl_fd(str, STDERR);
		free(str);
	}
	else
		perror(str);
	if (data->pipe_fd[READ] > 0)
		close(data->pipe_fd[READ]);
	if (data->pipe_fd[WRITE] > 0)
		close(data->pipe_fd[WRITE]);
	ft_free_pipex(data);
	exit(error_id);
}

void	ft_free_pipex(t_data *data)
{
	ft_memfree((void *) &data->cmds[0]);
	ft_memfree((void *) &data->cmds[1]);
	ft_memfree((void *) &data->cmds);
	ft_free_split((void *) &data->args[0]);
	ft_free_split((void *) &data->args[1]);
	ft_memfree((void *) &data->args);
}
