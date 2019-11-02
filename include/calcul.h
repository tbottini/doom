/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:39:33 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 20:43:37 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
**	autres
*/

int				opacity(int s, int c, double f);
double			double_modulo(double num);
int				trunc_int(int value, int min, int max);

#endif
