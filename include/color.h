/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbottini <tbottini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 16:39:33 by tbottini          #+#    #+#             */
/*   Updated: 2019/08/26 17:05:48 by tbottini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

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

# define RED		0xff0000ff
# define BLUE		0x0000ffff
# define GREEN		0x00ff00ff
# define BROWN		0xff00ffff
# define YELLOW		0xffff00ff
# define PURPLE		0xff00ffff
# define WHITE		0xffffffff

# define CWALL 		0xDADADAFF
# define CPORT 		0xE6E678FF
# define DEEPBLUE 	0x0000FFFF
# define CENEMY 	0x8E24AAFF

# define BLUE_SOFT	0x138fa2ff
# define RED_SOFT	0x831a1aff
# define GREEN_SOFT	0x548528ff

#endif
