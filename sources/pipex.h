/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 02:17:23 by maolivei          #+#    #+#             */
/*   Updated: 2022/06/06 22:44:27 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <stdio.h> // perror
# include <sys/wait.h> // wait, waitpid

# define READ 0
# define WRITE 1
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

char	*ft_parse_env_path(char *envp[], char *cmd);

#endif /* PIPEX_H */
