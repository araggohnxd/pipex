/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:22:12 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/14 15:42:37 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_close_and_wait(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->cmd_count && data->pid[index])
	{
		close(data->pipe_fd[index][READ]);
		close(data->pipe_fd[index][WRITE]);
		waitpid(data->pid[index], &data->child_exit_status, 0);
		data->exit_value = WEXITSTATUS(data->child_exit_status);
	}
	if (!data->cmds[data->cmd_count - 1])
			data->exit_value = 127;
}

static void	ft_exec_nth_cmd(t_data *data, int index)
{
	int	i;

	if (dup2(data->pipe_fd[index][READ], STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[index][WRITE], STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	i = -1;
	while (++i < data->cmd_count)
	{
		close(data->pipe_fd[i][READ]);
		close(data->pipe_fd[i][WRITE]);
	}
	if (execve(data->cmds[index], data->args[index], data->envp) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error during execve execution");
}

void	ft_init_exec(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->cmd_count)
	{
		if (!data->cmds[index])
			ft_set_perror(data, ERR_CMD_NOT_FOUND, data->args[index][0]);
		else
		{
			data->pid[index] = fork();
			if (data->pid[index] < 0)
				ft_set_perror(data, EXIT_FAILURE, "error creating fork");
			else if (data->pid[index] == 0)
				ft_exec_nth_cmd(data, index);
		}
	}
	ft_close_and_wait(data);
}
