/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:22:12 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/11 19:37:18 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_first_cmd(t_data *data)
{
	data->infile_fd = open(data->infile, O_RDONLY);
	if (data->infile_fd < 0)
		ft_set_perror(data, EXIT_FAILURE, data->infile);
	if (dup2(data->infile_fd, STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[WRITE], STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	close(data->pipe_fd[READ]);
	close(data->pipe_fd[WRITE]);
	close(data->infile_fd);
	if (!data->cmds[0] || execve(data->cmds[0], data->args[0], data->envp) < 0)
		ft_set_perror(data, 127, ft_strjoin(CMD_404, data->args[0][0]));
}

void	ft_exec_last_cmd(t_data *data)
{
	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		ft_set_perror(data, EXIT_FAILURE, data->outfile);
	if (dup2(data->outfile_fd, STDOUT) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	if (dup2(data->pipe_fd[READ], STDIN) < 0)
		ft_set_perror(data, EXIT_FAILURE, "error duping file descriptors");
	close(data->pipe_fd[READ]);
	close(data->pipe_fd[WRITE]);
	close(data->outfile_fd);
	if (!data->cmds[1] || execve(data->cmds[1], data->args[1], data->envp) < 0)
		ft_set_perror(data, 127, ft_strjoin(CMD_404, data->args[1][0]));
}
