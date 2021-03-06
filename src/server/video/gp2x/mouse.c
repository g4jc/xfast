/***************************************************************************
    begin                : Thu Feb 2 2006
    copyright            : (C) 2006 - 2008 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as               *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/


#include "../../../lib/xfast_.h"
#include "server.h"
#include "../helper/helper.h"
#include "gp2x.h"

int s_video_gp2x_mouse_init (s_server_conf_t *cfg)
{
	s_video_gp2x_data_t *priv = server->driver->driver_data;
	if (s_pipe_api_pipe(priv->mouse_fd)) {
		debugf(DSER | DSYS, "pipe failed");
		goto err0;
	}
	return priv->mouse_fd[0];
err0:	priv->mouse_fd[0] = -1;
	priv->mouse_fd[1] = -1;
	return -1;
}

int s_video_gp2x_mouse_update (s_video_input_data_t *mouse)
{
	s_video_input_data_mouse_t pad_recv;
	s_video_gp2x_data_t *priv = server->driver->driver_data;
	s_pipe_api_read(priv->mouse_fd[0], &pad_recv, sizeof(s_video_input_data_mouse_t));
	mouse->mouse.x = pad_recv.x;
	mouse->mouse.y = pad_recv.y;
	mouse->mouse.buttons = 0;
	mouse->mouse.buttons |= (pad_recv.buttons & GP2X_L) ? MOUSE_BUTTON_LEFT : 0;
	mouse->mouse.buttons |= (pad_recv.buttons & GP2X_R) ? MOUSE_BUTTON_RIGHT : 0;
	return 0;
}

void s_video_gp2x_mouse_uninit (void)
{
	s_video_gp2x_data_t *priv = server->driver->driver_data;
	s_pipe_api_close(priv->mouse_fd[0]);
	s_pipe_api_close(priv->mouse_fd[1]);
	priv->mouse_fd[0] = -1;
	priv->mouse_fd[1] = -1;
	s_server_cursor_uninit();
}
