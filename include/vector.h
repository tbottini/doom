#ifndef VECTOR_H
# define VECTOR_H

#include "calcul.h"

typedef struct			s_vct2
{
	int					x;
	int					y;
}						t_vct2;

typedef struct			s_vct3
{
	int					x;
	int					y;
	int					z;
}						t_vct3;

typedef struct			s_fvct2
{
	double				x;
	double				y;
}						t_fvct2;

typedef struct			s_fvct3
{
	double				x;
	double				y;
	double				z;
}						t_fvct3;

/*
**	operation
*/
//t_vct2					*vct2_value(t_vct2 *vct2, int x, int y);
double					ft_atof(char *str);
double					ft_catof(char *str, char c);
unsigned int			ft_catoi_u(char *str, char c);
char					*double_atof(char *line, t_fvct2 *fvct);
char					*triple_atof(char *line, t_fvct3 *fvct);

/*
**	debug
*/
void					double_msg(char *msg, double num);
void					ft_putdouble(double num);
void					fvct2_msg(char *msg, t_fvct2 vct);
void					fvct2_print(t_fvct2 vct);
void					fvct3_print(t_fvct3 vector);
void					fvct3_msg(char *msg, t_fvct3 vector);

/*
**	calcul
*/
double					dist(t_fvct2 vct1, t_fvct2 vct2);

int				double_sup(double a, double b);
int				double_inf(double a, double b);
void			dbl_cmp_affect2(double *affect, double b, double c, int (*cmp)(double, double));
void			dbl_cmp_affect(double *affect, double b, double c, int (*cmp)(double, double));
void			fvct2_cmp_affect(t_fvct2 *affect, t_fvct2 *b, t_fvct2 *c, int (*cmp)(double, double));
void			fvct2_cmp_affect2(t_fvct2 *affect, t_fvct2 *b, t_fvct2 *c, int (*cmp)(double, double));

t_fvct2			fvct2_rotation(t_fvct2 vector, double rotation);
t_fvct2			fvct2_addition(t_fvct2 vector, t_fvct2 add);
t_fvct2			fvct2_from_angle(double angle);
double			fvct2_angle(t_fvct2 origin, t_fvct2 pos, double rot_origin);

double			coef_vct(t_fvct2 quantity, t_vct2 step);
double			coef_diff(double diff, t_vct2 step);
double			coef_vct2(t_fvct2 value, t_fvct2 value2);
t_fvct2			interpolation_linear(t_affine d1, t_affine d2);
int				interpolation_linear_secur(t_affine affine1, t_affine affine2, t_fvct2 *inter);
t_affine		affine_points(t_fvct2 point1, t_fvct2 point2);
t_fvct2			inter(t_fvct2 p1, t_fvct2 p2, t_fvct2 p3, t_fvct2 p4);
double			hypothenuse(t_fvct2 vct);
double			distance(t_fvct2 vct1, t_fvct2 vct2);
void			fvct3_sub(t_fvct3 *vector_sub, t_fvct3 *vector_sub2);
void			fvct3_rotation(t_fvct3 *point, t_fvct2 rot);

t_affine		affine_points_secur(t_fvct2 point1, t_fvct2 point2);
double			affine_val_index(t_affine affine, double y);
#endif
