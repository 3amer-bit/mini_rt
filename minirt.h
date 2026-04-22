#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 1e-6

typedef struct s_framebuffer
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_framebuf;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	double	t;
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_vec3	t_point3;

typedef struct s_pixel
{
	int		x;
	int		y;
	t_color	color;
}	t_pixel;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_sphere
{
	t_point3	origin;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_framebuf	*framebuf;
	int			width;
	int			height;
}	t_window;

int		handle_keypress(int keysym, t_window *data);
int		handle_destroy_structure_notify(t_window *data);
void	mlx_destroy(t_window *win_ctx);
void	ft_mlx_put_pixel(t_framebuf *framebuf, t_pixel *pixel);
void	render(t_framebuf *framebuf);

#endif