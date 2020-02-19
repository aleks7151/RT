/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_figure_materials.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 23:24:29 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/18 19:04:58 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	write_figure1(int fd, t_fig *fig, char *buf)
{
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n7	material: ", fd);
	ft_putstr_fd(fig->mat->name, fd);
	ft_putstr_fd("\n8	uv scale:", fd);
	buf = get_fnbr_to_string(fig->uvt.scale.x);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putchar_fd(' ', fd);
	buf = get_fnbr_to_string(fig->uvt.scale.y);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n9	uv rotation: ", fd);
	buf = get_fnbr_to_string(fig->uvt.rot);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n10	uv move: ", fd);
	buf = get_fnbr_to_string(fig->uvt.move.x);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putchar_fd(' ', fd);
	buf = get_fnbr_to_string(fig->uvt.move.y);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n\n", fd);
}

void	write_figure0(int fd, t_fig *fig, char *buf)
{
	buf = get_thre_float(fig->dir.x, fig->dir.y, fig->dir.z);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n3	rotation:", fd);
	buf = get_thre_float(fig->alpha.x,
		fig->alpha.y, fig->alpha.z);
	ft_putstr_fd(buf, fd);
	ft_putstr_fd("\n4	radius:", fd);
	free(buf);
	buf = get_fnbr_to_string(fig->rad);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n5	angle:", fd);
	buf = get_fnbr_to_string(fig->ang);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n6	limit:", fd);
	buf = get_fnbr_to_string(fig->limit.x);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putchar_fd(' ', fd);
	buf = get_fnbr_to_string(fig->limit.y);
	write_figure1(fd, fig, buf);
}

void	write_figure(int fd, t_lst *lst)
{
	t_fig	*fig;
	char	*buf;

	fig = lst->scn->figs;
	while (fig)
	{
		ft_putstr_fd("[figure]:\n0	type:", fd);
		if (fig->type == sphere)
			ft_putstr_fd("sphere", fd);
		else if (fig->type == cylinder)
			ft_putstr_fd("cylinder", fd);
		else if (fig->type == plane)
			ft_putstr_fd("plane", fd);
		else if (fig->type == conus)
			ft_putstr_fd("conus", fd);
		else if (fig->type == inv_sph)
			ft_putstr_fd("inv_sph", fd);
		ft_putstr_fd("\n1	position:", fd);
		buf = get_thre_float(fig->pos.x, fig->pos.y, fig->pos.z);
		ft_putstr_fd(buf, fd);
		free(buf);
		ft_putstr_fd("\n2	center:", fd);
		write_figure0(fd, fig, buf);
		fig = fig->next;
	}
}

void	write_materials0(int fd, t_mat *mat, char *buf)
{
	buf = get_fnbr_to_string(mat->refl);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n7	refraction: ", fd);
	buf = get_fnbr_to_string(mat->refr);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n8	transpare: ", fd);
	buf = get_fnbr_to_string(mat->transpare);
	ft_putstr_fd(buf, fd);
	free(buf);
	ft_putstr_fd("\n\n", fd);
}

void	write_materials(int fd, t_lst *lst, t_mat *mat)
{
	char *buf;

	mat = lst->scn->mats->next;
	while (mat)
	{
		ft_putstr_fd("[material]:\nname: ", fd);
		ft_putstr_fd(mat->name, fd);
		ft_putstr_fd("\n1	color: ", fd);
		buf = get_thre_int(mat->col.r, mat->col.g, mat->col.b);
		ft_putstr_fd(buf, fd);
		free(buf);
		ft_putstr_fd("\n2	diffuse: ", fd);
		ft_putstr_fd(mat->diff_map.name_map, fd);
		ft_putstr_fd("\n3	normal: ", fd);
		ft_putstr_fd(mat->norm_map.name_map, fd);
		ft_putstr_fd("\n4	mask: ", fd);
		ft_putstr_fd(mat->mask_map.name_map, fd);
		ft_putstr_fd("\n5	specular: ", fd);
		buf = get_inbr_to_string(mat->spec, "");
		ft_putstr_fd(buf, fd);
		free(buf);
		ft_putstr_fd("\n6	reflection: ", fd);
		write_materials0(fd, mat, buf);
		mat = mat->next;
	}
}
