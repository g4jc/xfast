/***************************************************************************
    begin                : Mon Feb 21 2005
    copyright            : (C) 2005 - 2008 by Alper Akcan
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
#include "sdl.h"
#include "../helper/helper.h"

#include <unistd.h>

int s_video_sdl_mouse_init (s_server_conf_t *cfg)
{
	s_video_sdl_data_t *priv = server->driver->driver_data;
	if (s_pipe_api_pipe(priv->mouse_fd)) {
		debugf(DSER | DSYS, "pipe failed");
		goto err0;
	}
	
	SDL_ShowCursor(0);
	return priv->mouse_fd[0];
err0:	priv->mouse_fd[0] = -1;
	priv->mouse_fd[1] = -1;
	return -1;
}

int s_video_sdl_mouse_update (s_video_input_data_t *mouse)
{
        int x;
        int y;
	SDL_Event event;
        unsigned int state;
	s_video_sdl_data_t *priv = server->driver->driver_data;
	
        s_pipe_api_read(priv->mouse_fd[0], &event.type, sizeof(event.type));

        state = SDL_GetMouseState(&x, &y);

        mouse->mouse.x = x;
        mouse->mouse.y = y;
        mouse->mouse.buttons = 0;
	
        if (state & (1 << (SDL_BUTTON_LEFT - 1))) {
		mouse->mouse.buttons |= MOUSE_BUTTON_LEFT;
	}
        if (state & (1 << (SDL_BUTTON_MIDDLE - 1))) {
		mouse->mouse.buttons |= MOUSE_BUTTON_MIDDLE;
	}
        if (state & (1 << (SDL_BUTTON_RIGHT - 1))) {
		mouse->mouse.buttons |= MOUSE_BUTTON_RIGHT;
	}

	return 0;
}

void s_video_sdl_mouse_uninit (void)
{
	s_video_sdl_data_t *priv = server->driver->driver_data;
	s_pipe_api_close(priv->mouse_fd[0]);
	s_pipe_api_close(priv->mouse_fd[1]);
	priv->mouse_fd[0] = -1;
	priv->mouse_fd[1] = -1;
	s_server_cursor_uninit();
}
