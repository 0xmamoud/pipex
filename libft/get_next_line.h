/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kane <kane@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:03:36 by kane              #+#    #+#             */
/*   Updated: 2024/03/20 21:42:56 by kane             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h> 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  1
# endif

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}	t_lst;
char	*get_next_line(int fd);
void	ft_read_fd(int fd, t_lst **lst);
void	ft_lstadd(t_lst **lst, char *buf, int read_bytes);
void	ft_clean_lst(t_lst **lst);
char	*ft_getline(t_lst *lst);
void	ft_free_lst(t_lst *lst);
int		ft_linesize(t_lst *lst);
int		ft_find_newline(t_lst *lst);
t_lst	*ft_lstlast_list(t_lst *lst);

#endif