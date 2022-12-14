/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/02 13:50:49 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/13 13:47:41 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

int  error(char *str);

typedef struct  s_data
{
    char    **path_vars;
    char    *path;
    char    **cmd1;
    char    *cmd2;
    int     fd[2];
}               t_data;


int parse_path(t_data *data, char **argv, char **envp);

int child_process(t_data *data, int fd1, char **cmd);

// int parent_process()

#endif