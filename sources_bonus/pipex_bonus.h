/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:23 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/14 15:43:07 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <stdio.h> // perror
# include <fcntl.h> // open, close
# include <sys/wait.h> // wait, waitpid

# define READ 0
# define WRITE 1
# define ERR_CMD_NOT_FOUND 2
# define ERR_IO_FILE 3
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

typedef struct s_data {
	int		argc;
	char	**argv;
	char	**envp;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
	int		here_doc;
	char	*limiter;
	int		cmd_count;
	int		offset;
	char	**cmds;
	char	***args;
	int		**pipe_fd;
	pid_t	*pid;
	int		exit_value;
	int		child_exit_status;
}	t_data;

void	ft_init_data(t_data *data, int argc, char **argv, char **envp);
void	ft_init_here_doc(t_data *data, int argc, char **argv, char **envp);
void	ft_init_exec(t_data *data);
void	ft_argument_parser(t_data *data);
void	ft_free_pipex(t_data *data);
void	ft_init_pipe(t_data *data);
void	ft_init_pid(t_data *data);
int		ft_set_perror(t_data *data, int error_id, char *str);

#endif /* PIPEX_BONUS_H */
