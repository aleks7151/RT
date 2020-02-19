/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabraham <vabraham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:24:16 by vabraham          #+#    #+#             */
/*   Updated: 2020/02/19 16:04:37 by vabraham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define S_W 400
# define S_H 200
# define H_W 200
# define H_H 100
# define RATIO 2
# define POT 16

# define INFINITY 1e99
# define INFY 1e99
# define MIN_OFFSET 0.01f
# define RECURCE_DEPTH 3
# define REFR_DEPTH 10

# define TAGS 4
# define SCENE 0
# define FIGURE 2
# define LIGHT 3
# define MATERIAL 1

# define SCENE_LINES 10
# define FIGURE_LINES 11
# define LIGHT_LINES 6
# define MATERIAL_LINES 9

# define SCENE_FUNCTIONS 11
# define FIGURE_FUNCTIONS 11
# define LIGHT_FUNCTIONS 6
# define MATERIAL_FUNCTIONS 9

# define END_FOR_POST_EFFECTS 12
# define RAD_BLUR_X 5
# define RAD_BLUR_Y 5

# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>

# include <sys/types.h>
# include <sys/stat.h>

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

typedef struct		s_tag
{
	int				read_tag;
	int				cur_tag;
	int				count;
}					t_tag;

typedef	struct		s_vec3
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec3;

typedef struct		s_mat3
{
	t_vec3			f1;
	t_vec3			f2;
	t_vec3			f3;
}					t_mat3;

typedef struct		s_map
{
	SDL_Surface		*map;
	int				*data;
	char			*name_map;
}					t_map;

typedef struct		s_mat
{
	char			name[18];
	SDL_Color		col;
	t_map			diff_map;
	t_map			norm_map;
	t_map			mask_map;
	int				spec;
	float			refl;
	float			refr;
	float			transpare;
	struct s_mat	*next;
}					t_mat;

typedef struct		s_uv
{
	t_vec3			scale;
	float			rot;
	t_vec3			move;
	t_vec3			rot_tr;
}					t_uv;

typedef enum		e_tfig
{
	sphere,
	cylinder,
	plane,
	conus,
	inv_sph,
	MAX_FIGS
}					t_tfig;

typedef struct		s_fig
{
	t_tfig			type;
	t_vec3			pos;
	t_vec3			begin_pos;
	t_vec3			dir;
	t_vec3			begin;
	t_vec3			look;
	t_vec3			right;
	float			rad;
	float			ang;
	t_vec3			limit;
	t_vec3			alpha;
	t_mat3			mat_x;
	t_mat3			mat_y;
	t_mat3			mat_z;
	t_mat			*mat;
	t_uv			uvt;
	struct s_fig	*next;
}					t_fig;

typedef enum		e_tlght
{
	ambient,
	point,
	direct,
	lconus,
	MAX_LGHT
}					t_tlght;

typedef struct		s_lght
{
	t_tlght			type;
	t_vec3			pos;
	t_vec3			begin_pos;
	t_vec3			dir;
	float			angle;
	float			ints;
	SDL_Color		col;
	struct s_lght	*next;
}					t_lght;

typedef struct		s_isec
{
	float			t;
	t_fig			*fig;
	float			check;
	t_vec3			n;
	t_vec3			n2;
	t_vec3			uv;
	struct s_isec	*next;
	struct s_isec	*prev;
}					t_isec;

typedef struct		s_hit
{
	t_isec			*isec1;
	t_isec			*isec2;
	int				count;
}					t_hit;

typedef struct		s_fog
{
	int				enable;
	float			max_tr;
	float			near;
	SDL_Color		col;
}					t_fog;

typedef enum		e_shader
{
	SIMPLE,
	TEXTURE,
	TRASPARENT,
	REFRLECT,
	REFRACT,
	MAX_SHADER
}					t_shader;

typedef struct		s_scn
{
	t_fig			*figs;
	t_lght			*lghts;
	t_mat			*mats;
	t_fig			*cur_fig;
	t_lght			*cur_lght;
	t_mat			*cur_mat;
	t_vec3			cam_pos;
	t_vec3			cam_pos0;
	float			cam_focus_dist;
	SDL_Color		bgc;
	int				shadow;
	t_map			diff_map;
	t_fog			fog;
	int				inv_surf;
}					t_scn;

typedef struct		s_lst
{
	void			*mlx;
	SDL_Window		*win;
	SDL_Surface		*img;
	SDL_Surface		*mimg;
	SDL_Rect		mrect;
	int				show_menu;
	int				show_help;
	int				*data;
	int				depth;
	SDL_Color		res_help;
	SDL_Point		cursor;
	int				post_effects;
	int				*data_dop;
	int				num_file_for_screen;
	int				change;
	int				pot;
	int				mouse_light;
	t_vec3			alpha_cam;
	t_mat3			camera_x;
	t_mat3			camera_y;
	t_mat3			camera_z;
	t_scn			*scn;
	struct s_read	*set;
	int				depth_refr;
	t_shader		shd;
}					t_lst;

typedef int			(*t_r_fig)(t_lst*, char*);
typedef int			(*t_r_mat)(t_lst*, char*);
typedef int			(*t_r_lght)(t_lst*, char*);
typedef int			(*t_r_scn)(t_lst*, char*);

typedef struct		s_read
{
	t_r_scn			f_scn[SCENE_FUNCTIONS];
	int				(*cre_mat)(t_lst*);
	t_r_mat			f_mat[MATERIAL_FUNCTIONS];
	int				(*cre_fig)(t_lst*);
	t_r_fig			f_fig[FIGURE_FUNCTIONS];
	int				(*cre_lght)(t_lst*);
	t_r_lght		f_lght[LIGHT_FUNCTIONS];
}					t_read;

typedef struct		s_trc
{
	t_vec3			o;
	t_vec3			d;
	t_vec3			p;
	float			min;
	float			max;
}					t_trc;

typedef struct		s_l_prm
{
	t_vec3			p;
	t_vec3			n;
	t_vec3			v;
}					t_l_prm;

SDL_Surface			*scrin0(t_lst *lst, int i, int j, Uint8 red);
int					read_scene0(char **line, char **word);
void				free_get(char **buf, char **s);
t_vec3				get_shadow(t_lst *lst,
						t_trc *trc, t_l_prm b, t_lght *c_lght);
int					show_help(t_lst *lst, SDL_Rect *r);
SDL_Surface			*hide_menu_for_screen(t_lst *lst);
void				show_menu(t_lst *lst);
SDL_Color			return_background(t_lst *lst, t_trc trc);
SDL_Color			mix_color(SDL_Color c1, SDL_Color c2, float koef);
SDL_Color			return_trace(t_lst *lst, t_vec3 fkt,
						SDL_Color col, t_isec **cisec);
void				init_trace0(t_lst *lst, int depth,
						t_vec3 *fkt, SDL_Color *res);
int					idono(t_vec3 *fkt, SDL_Color *res,
						SDL_Color tres, t_isec **cur_isec);
int					init_trace(t_lst *lst, t_isec **cisec,
						t_trc trc, SDL_Color *col);
void				check_refr(t_lst *lst, t_trc *trc,
						t_isec *ci, SDL_Color *tres);
void				get_normal_from_file(t_isec *cisec);

void				draw_cre_button(t_lst *l, int fig, SDL_Rect *d);
void				draw_cam_pos(t_lst *l, int fsize, int x, int y);
void				draw_type_lght(t_lst *l, int fsize, int x, int y);
char				*c_lim(char *a);
void				print_ttf(SDL_Surface *sdest,
						char *msg, int size, SDL_Rect *dest);
t_isec				*check_inv_figs(t_lst *lst, t_trc trc, float t);
void				set_inv_surf1(t_lst *lst, t_hit *h, t_fig *fig);
t_isec				*set_isec_inv_sph(t_trc trc, t_fig *isph, float p);
t_isec				*check_inv_sph(t_trc trc, float t, t_fig *isph);
t_isec				*check_inv_figs(t_lst *lst, t_trc trc, float t);
t_isec				*ret_inv_isec(t_lst *lst, t_isec *isec, t_fig *fig);
t_isec				*ret_cyl_con_isec(t_trc trc, t_fig *cyl, float t, float m);
t_isec				*get_isec_cyl(t_lst *lst, t_trc trc, float t, t_fig *cyl);

t_l_prm				set_l_prm(t_trc trc, t_vec3 n);
SDL_Color			plus_sdl_color(SDL_Color col1, SDL_Color col2);
SDL_Color			mult_int_color(int c, float koef);
SDL_Color			mult_sdl_color(SDL_Color col, float koef);
SDL_Color			get_refl_col(t_lst *lst, t_trc trc, t_vec3 n, int depth);
SDL_Color			get_refr_col(t_lst *lst, t_trc trc, t_vec3 n, float ito);
int					set_refr_mat(t_lst *lst, char *word);
int					set_inv_surf(t_lst *lst, char *word);
t_trc				get_all_really(t_vec3 *ints, t_l_prm b,
						t_lght **c_lght, int check);
void				trc_init(t_trc *trc, t_lght *c_lght, t_l_prm b);
t_vec3				transpare_shadow(t_isec *shdw, t_vec3 kof);
void				cls_isec3(t_isec **cisec, t_lst *lst, t_trc trc);
void				free_isec_list(t_isec *cisec);
int					check_valid_iter(t_tag *ctag);
int					cre_cur_obj(t_lst *l, t_tag *ctag);
int					key_press0(SDL_Keycode key, t_lst *lst);
int					key_press_dop(SDL_Keycode key, t_lst *lst);
int					scrin(t_lst *lst);
void				sdl_cycle(t_lst *lst);
void				sld_events(t_lst *lst, SDL_Event e, int *qt, int *repaint);
void				sld_events0(t_lst *lst, SDL_Event e, int *repaint);
void				close_sdl(t_lst *lst);
void				write_figure(int fd, t_lst *lst);
char				*get_thre_float(float x, float y, float z);
char				*get_thre_int(int x, int y, int z);
int					get_file_scene(char *str_scene);
char				*get_fnbr_to_string(float num);
char				*get_inbr_to_string(int num, char *s);

SDL_Color			pixel_picture(int *data, int i, int pix_x, int pix_y);
SDL_Color			blur(int *data, int i, float blur_x, float blur_y);
void				draw(t_lst *lst);
int					save_scene(t_lst *lst);

void				cls_isec2(t_isec **cisec, t_lst *lst, t_trc trc);
void				post_effects(t_lst *lst);

int					scene_init(t_lst *lst, char *file);
void				init_f_read(t_lst *lst);
int					check_tag(t_lst *l, char **word, t_tag *ctag);
int					read_scene(t_lst *l, char *file);

int					init_sdl(t_lst *lst);

void				free_figs(t_fig *figs);
void				free_lghts(t_lght *lghts);
void				free_mats(t_mat *mats);
void				free_l(t_lst *lst);
int					free_word_line(char **line, char **word);
int					close_free(int fd, char **line, char **word, int ret);
int					free_words(char **words, int res);
int					close_dir(int fd, char **line, int ret);

int					key_press(SDL_Keycode key, t_lst *lst);
int					close_window(void *lst);
void				mouse_move(SDL_MouseMotionEvent *e, t_lst *lst);
void				mouse_press(SDL_MouseButtonEvent *e, t_lst *lst);
void				mouse_weel(Sint32 y, t_lst *lst);

int					clamp(int n, int min, int max);
float				clampf(float n, float min, float max);
float				dot(t_vec3 v1, t_vec3 v2);
t_vec3				cross(t_vec3 v1, t_vec3 v2);
float				len_vec3(t_vec3 v);
float				modul(t_vec3 v);
t_vec3				set_vec3(t_vec3 src);
t_vec3				cre_vec3(float x, float y, float z);
t_vec3				minus_vec3(t_vec3 src1, t_vec3 src2);
t_vec3				plus_vec3(t_vec3 src1, t_vec3 src2);
t_vec3				mult_vec3f(t_vec3 src, float n);
t_vec3				div_vec3f(t_vec3 src, float n);
t_vec3				invert_vec3(t_vec3 src);
SDL_Color			set_col(int r, int g, int b, int a);
t_vec3				refl_r(t_vec3 l, t_vec3 n);

void				sel_fig_check(t_lst *lst, t_hit *hit, t_trc trc,
									t_fig *cur_fig);
void				intersec_sph(t_lst *lst, t_hit *hit, t_trc trc, t_fig *sph);
void				intersec_cyl(t_lst *lst, t_hit *hit, t_trc trc, t_fig *cyl);
void				intersec_pln(t_lst *lst, t_hit *hit, t_trc trc, t_fig *pln);
void				intersec_con(t_lst *lst, t_hit *hit, t_trc trc, t_fig *con);

float				get_transp_from_file(t_map map, t_vec3 uv);
void				cls_isec(t_isec **cisec, t_lst *lst, t_trc trc);
SDL_Color			trace(t_lst *lst, t_trc trc, int depth, t_isec *cisec);
t_vec3				light(t_lst *lst, t_l_prm b, t_fig *fig, t_lght *c_lght);

void				rain(t_lst *lst);
void				set_m4_rz(t_mat3 *m, float fi);
void				set_m4_rx(t_mat3 *m, float fi);
void				set_m4_ry(t_mat3 *m, float fi);
void				rotation_fig(t_fig *fig);
void				mult_m3(t_vec3 *d, t_vec3 s, t_mat3 m);
void				rot_v3z(t_vec3 *dst, t_vec3 *src, float fi);
void				rot_v3x(t_vec3 *dst, t_vec3 *src, float fi);
void				rot_v3y(t_vec3 *dst, t_vec3 *src, float fi);

float				ft_atof(char *f);
int					set_pos_cam(t_lst *lst, char *word);
int					set_rot_cam(t_lst *lst, char *word);
int					set_cam_focus_dist(t_lst *lst, char *word);
int					set_col_bgc(t_lst *lst, char *word);
int					set_diff_map_scn(t_lst *lst, char *word);
int					set_fog_enable(t_lst *lst, char *word);
int					set_fog_near(t_lst *lst, char *word);
int					set_fog_max_tr(t_lst *lst, char *word);
int					set_fog_color(t_lst *lst, char *word);

int					cre_mat(t_lst *lst);
void				load_map(t_map *map, char *filename);
int					set_name_mat(t_lst *lst, char *word);
int					set_col_mat(t_lst *lst, char *word);
int					set_diff_map_mat(t_lst *lst, char *word);
int					set_norm_map_mat(t_lst *lst, char *word);
int					set_mask_map_mat(t_lst *lst, char *word);
int					set_spec_mat(t_lst *lst, char *word);
int					set_refl_mat(t_lst *lst, char *word);
int					set_transpare_mat(t_lst *lst, char *word);

int					cre_fig(t_lst *lst);
int					set_type_fig(t_lst *lst, char *word);
int					set_pos_fig(t_lst *lst, char *word);
int					set_dir_fig(t_lst *lst, char *word);
int					set_rot_fig(t_lst *lst, char *word);
int					set_rad_fig(t_lst *lst, char *word);
int					set_ang_fig(t_lst *lst, char *word);
int					set_lim_fig(t_lst *lst, char *word);
int					set_mat_fig(t_lst *lst, char *word);
int					set_uv_rot(t_lst *lst, char *word);
int					set_uv_move(t_lst *lst, char *word);
int					set_uv_scale(t_lst *lst, char *word);

int					cre_lght(t_lst *lst);
int					set_type_lght(t_lst *lst, char *word);
int					set_pos_lght(t_lst *lst, char *word);
int					set_dir_lght(t_lst *lst, char *word);
int					set_ints_lght(t_lst *lst, char *word);
int					set_col_lght(t_lst *lst, char *word);
int					set_angle_lght(t_lst *lst, char *word);

void				move_light(t_lst *lst, SDL_Point p);
void				move_fig(t_lst *lst, SDL_Point p);
void				multy_x(t_lst *lst, int tmp);
void				multy_y(t_lst *lst, int tmp);
void				multy_z(t_lst *lst, int tmp);
void				ret(t_lst *lst);

void				button_bg(int *data, SDL_Rect *d, int fig);
void				draw_vec(t_lst *l, int fsize, SDL_Rect *d, t_vec3 *v);
void				draw_col(t_lst *l, int fsize, SDL_Rect *d, SDL_Color *c);
void				draw_type_fig(t_lst *l, int fsize, int x, int y);
void				draw_text_menu1(t_lst *lst);
void				draw_text_menu2(t_lst *lst);
void				draw_text_menu3(t_lst *lst);
void				draw_text_menu4(t_lst *l);
SDL_Rect			*set_rect(SDL_Rect *rect, int x, int y);
void				ft_exit(char *line);
int					free_scene_init(t_lst *lst);
int					free_init_sdl(t_lst *lst);
int					check_split_len(char **split);
int					find_me_clrs(t_isec **csc, t_lst *l,
t_trc trc, SDL_Color *col);
void				draw_shader(t_lst *l, int fsize, int x, int y);

void				add_figure(t_lst *lst, int num_fig);
void				next_mat(t_lst *lst);
void				search_fig(t_lst *lst, int x, int y);
void				write_materials(int fd, t_lst *lst, t_mat *mat);

#endif
