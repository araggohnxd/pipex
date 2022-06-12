/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/12 14:54:53 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_init_exec(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->cmd_count)
	{
		data->pid[index] = fork();
		if (data->pid[index] < 0)
			ft_set_perror(data, EXIT_FAILURE, "error creating fork");
		else if (data->pid[index] == 0)
			ft_exec_nth_cmd(data, index);
	}
	index = -1;
	while (++index < data->cmd_count)
	{
		close(data->pipe_fd[index][READ]);
		close(data->pipe_fd[index][WRITE]);
		waitpid(data->pid[index], &data->child_exit_status, 0);
		data->exit_value = WEXITSTATUS(data->child_exit_status);
	}
}

static void	ft_init_here_doc(t_data *data, int argc, char **argv, char **envp)
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
		ft_set_perror(data, EXIT_FAILURE, data->outfile);
}

static void	ft_init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->here_doc = 0;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->infile_fd = open(data->infile, O_RDONLY);
	data->cmds = NULL;
	data->args = NULL;
	data->pipe_fd = NULL;
	data->pid = NULL;
	data->cmd_count = argc - 3;
	data->limiter = NULL;
	data->offset = 2;
	data->exit_value = 0;
	if (data->infile_fd < 0)
		ft_set_perror(data, EXIT_FAILURE, data->infile);
	data->outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile_fd < 0)
		ft_set_perror(data, EXIT_FAILURE, data->outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		ft_putendl_fd("pipex: Too few arguments", STDERR);
		ft_putendl_fd(
			"Usage: ./pipex <infile> <cmd1> <cmd2>...<cmdn> <outfile>",
			STDERR);
		ft_putendl_fd(
			"      ./pipex here_doc <LIMITER> <cmd1> <cmd2>...<cmdn> <outfile>",
			STDERR);
		exit(EXIT_FAILURE);
	}
	else if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		ft_init_here_doc(&data, argc, argv, envp);
	else
		ft_init_data(&data, argc, argv, envp);
	ft_argument_parser(&data);
	ft_init_pipe(&data);
	ft_init_pid(&data);
	ft_init_exec(&data);
	ft_free_pipex(&data);
	return (data.exit_value);
}
