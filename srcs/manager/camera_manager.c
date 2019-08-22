/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrache <akrache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 08:01:40 by akrache           #+#    #+#             */
/*   Updated: 2019/08/13 08:02:20 by akrache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** camera->fov_ver = atan2(camera->d_screen, sdl->size.y / 2);
*/

t_camera		*camera_init(t_camera *camera, t_sdl *sdl, int fov)
{
	camera->fov = fov;
	camera->d_screen = (sdl->size.x / 2) / tan(camera->fov / 2.0 * PI180);
	camera->fov_ver = atan2(sdl->size.y / 2, camera->d_screen) * 2;
	return (camera);
}
