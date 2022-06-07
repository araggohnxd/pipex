/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:38:58 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/07 15:39:26 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(t_data *data, char *envp[])
{
	close(data->infile);
	close(data->outfile);
	close(data->pipe_fd[READ]);
	close(data->pipe_fd[WRITE]);
	execve(data->cmd, data->args, envp);
}

void	ft_write_outfile(t_data *data, char *arg, char *envp[])
{
	ft_get_arguments(data, arg, envp);
	data->child_pid_2 = fork();
	if (data->child_pid_2 < 0)
		ft_set_error(2, "fork");
	else if (data->child_pid_2 == 0)
	{
		dup2(data->pipe_fd[READ], STDIN);
		dup2(data->outfile, STDOUT);
		ft_execute(data, envp);
	}
	ft_free_split(&data->args);
	ft_memfree((void *) &data->cmd);
}

void	ft_read_infile(t_data *data, char *arg, char *envp[])
{
	ft_get_arguments(data, arg, envp);
	data->child_pid_1 = fork();
	if (data->child_pid_1 < 0)
		ft_set_error(2, "fork");
	else if (data->child_pid_1 == 0)
	{
		dup2(data->infile, STDIN);
		dup2(data->pipe_fd[WRITE], STDOUT);
		ft_execute(data, envp);
	}
	ft_free_split(&data->args);
	ft_memfree((void *) &data->cmd);
}
