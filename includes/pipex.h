/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 13:50:49 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/14 16:05:57 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

int  error(char *str);

typedef struct s_data
{
    char    **path_vars;
    char    **argv;
    char    **envp;
    char    *path;
    char    **cmd1;
    char    *cmd2;
    int     IN_FILE;
    int     OUT_FILE;
    int     end[2];
}               t_data;

int open_fd(t_data *data, char **argv);

int parse_path(t_data *data, char **argv, char **envp);

int child_process(t_data *data);

int pipex(t_data *data);

// int parent_process()

#endif