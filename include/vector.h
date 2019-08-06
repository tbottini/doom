#ifndef VECTOR_H
# define VECTOR_H

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
t_vct2					*vct2_value(t_vct2 *vct2, int x, int y);
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

#endif
