/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaron <vkaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:12:02 by vkaron            #+#    #+#             */
/*   Updated: 2020/02/05 16:39:54 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFF_SIZE 10000

size_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strdup2(const char *s1);
char	*ft_strndup(char *str, size_t n);
char	*ft_strrdup(char *str, size_t n);
char	*ft_strmcat(char *s1, char *s2);
size_t	ft_strfind(char *str, char sym);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	**ft_strsplit(char const *s, char c);
int		get_next_line(const int fd, char **line);
void	ft_swap(int *n1, int *n2);
int		ft_atoi(char *str);
int		ft_atoi_16(char *str);
int		ft_isspace(int c);
char	*ft_itoa(int nbr);
void	ft_pad_left(char *s, char c, unsigned int len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memalloc(size_t size);
void	*ft_memset(void *dest, int n, size_t size);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);

#endif
