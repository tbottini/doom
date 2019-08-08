
#ifndef CALCUL_H
# define CALCUL_H

# define PI 3.1415926535897932
# define PI180 0.01745329251
# define TOANGLE 57.2957795131
# define TO_RADIAN PI180

/*
**	lock == 1 si la droite affine est constante sur l'absice (x)
*/
typedef struct	s_affine
{
	double		a;
	double		b;
	char		lock;
}				t_affine;

/*
**	affine fonctions
*/
double			affine_val(t_affine affine, double x);
t_affine		affine_def(double a, double b);
double			affine_val_index(t_affine affine, double y);

/*
**	autres
*/
int				opacity(int s, int c, double f);
double					double_modulo(double num);

#endif