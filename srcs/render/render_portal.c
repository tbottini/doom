#include "doom_nukem.h"


/*
**	-on determine avec px.x et px.y les nouvelles bornes de l'ecran
**	-sur le zline on mets sur 0 les pixels ou le portail est plus proche
**	-on ajuste les bornes up et down au debut du portail
**
**	-on lance une recursion sur le render sector avec une definition du portail
**
**	modif render
**	-si un portail de reference est definit dans l'arch
**		on rentre dans le bunch que les pillier qui sont plus loin que le portail de ref
** 		on n'ajoute pas le portail (qui fait partie du secteur) au bunch
**		sinon il y a une recursive
*/


/*
**	recupere le pixel actuel fait une verif si le wall
*/