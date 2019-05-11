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
	float				x;
	float				y;
}						t_fvct2;

typedef struct			s_fvct3
{
	float				x;
	float				y;
	float				z;
}						t_fvct3;


t_vct2					*vct2_value(t_vct2 *vct2, int x, int y);

#endif