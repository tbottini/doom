
#ifndef DEBUG_H
# define DEBUG_H

# include "doom_struct.h"

# define WEND		"\e[0m"

# define WRED		"\e[31m\e[1m"
# define WGREEN		"\e[32m\e[1m"
# define WYELLOW 	"\e[33m\e[1m"
# define WBLUE 		"\e[34m\e[1m"
# define WMAGENTA 	"\e[35m\e[1m"
# define WCYAN 		"\e[36m\e[1m"
# define WGREY		"\e[38;5;250;250;250m"

# define WBRED		"\e[41m"
# define WBGREEN	"\e[42m"
# define WBYELLOW 	"\e[43m"
# define WBBLUE 	"\e[44m"
# define WBMAGENTA 	"\e[45m"
# define WBCYAN 	"\e[46m"
void					sector_recursif(t_sector sector, int sub);
#endif
