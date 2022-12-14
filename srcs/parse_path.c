/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:57:41 by tklouwer      #+#    #+#                 */
/*   Updated: 2022/12/13 10:22:18 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int arraylen(char **arr)
{
    int i;
    
    i = 0;
    while (arr[i])
    {
        i++;
    }
    return (i);
}

void    command_args(t_data *data, char **argv)
{
    int i = 0;
    char **tmp1;

    tmp1 = ft_split(argv[2], ' ');
    data->cmd1 = ft_calloc((arraylen(tmp1) + 1), sizeof(char *));
    if (!data->cmd1)
        error("MEMORY ALLOCATION ERROR");
    while (tmp1[i])
    {
        data->cmd1[i] = tmp1[i];
        free(tmp1[i]);
        i++;
    }
    data->cmd2 = ft_strdup(argv[3]);
    free(tmp1);
}

void    env_path(t_data *data, char **envp)
{
    while(!data->path)
    {
        if (ft_strnstr(*envp, "PATH=", ft_strlen(*envp)))
            data->path = ft_substr(*envp, 5, ft_strlen(*envp));
        envp++;
    }
}

void    path_vars(t_data *data)
{
    char    **tmp;
    int     i;

    i = 0;
    tmp = ft_split(data->path, ':');
    data->path_vars = ft_calloc((arraylen(tmp) + 1), sizeof(char *));
    if (!data->path_vars)
        error("MEMORY ALLOCATION ERROR");
    while (tmp[i])
    {
        data->path_vars[i] = ft_strjoin(tmp[i], "/");
        free(tmp[i]);
        i++;
    }
    free(tmp);
}

int parse_path(t_data *data, char **argv, char **envp)
{
    env_path(data, envp);
    command_args(data, argv);
    path_vars(data);
    return(EXIT_SUCCESS);
}