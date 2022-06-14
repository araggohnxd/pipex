/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:11:12 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/14 19:52:00 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_here_doc(t_data *data, int argc, char **argv, char **envp)
{
	data->here_doc = 1;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = NULL;
	data->outfile = argv[argc - 1];
	data->cmds = NULL;
	data->args = NULL;
	data->pipe_fd = NULL;
	data->pid = NULL;
	data->cmd_count = argc - 4;
	data->limiter = argv[2];
	data->offset = 3;
	data->exit_value = 0;
	data->infile_fd = -1;
	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->outfile_fd < 0)
		ft_set_perror(data, ERR_IO_FILE, data->outfile);
}

void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->here_doc = 0;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->cmds = NULL;
	data->args = NULL;
	data->pipe_fd = NULL;
	data->pid = NULL;
	data->cmd_count = argc - 3;
	data->limiter = NULL;
	data->offset = 2;
	data->exit_value = 0;
	data->infile_fd = open(data->infile, O_RDONLY);
	if (data->infile_fd < 0)
		ft_set_perror(data, ERR_IO_FILE, data->infile);
	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		ft_set_perror(data, ERR_IO_FILE, data->outfile);
}
