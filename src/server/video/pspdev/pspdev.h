/***************************************************************************
    begin                : Thu Sep 22 2005
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


#include "config.h"

#include <psptypes.h>
#include <pspdebug.h>
#include <pspge.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <psputils.h>
#include <pspdisplay.h>
#include <pspgu.h>

typedef struct s_video_pspdev_data_s {
	int mouse_fd[2];
	int keybd_fd[2];
	s_thread_t *event_tid;
	void *vram_base;
} s_video_pspdev_data_t;

void s_video_pspdev_mouse_cursor_init (void);
void s_video_pspdev_mouse_setcursor (s_cursor_type_t c);
void s_video_pspdev_mouse_draw (void);

void * s_video_pspdev_event_parse (void *);

int s_video_pspdev_kbd_init (s_server_conf_t *cfg);
int s_video_pspdev_kbd_update (s_video_input_data_t *keybd);
void s_video_pspdev_kbd_uninit (void);

int s_video_pspdev_mouse_init (s_server_conf_t *cfg);
void s_video_pspdev_mouse_setcursor (s_cursor_type_t c);
void s_video_pspdev_mouse_draw (void);
int s_video_pspdev_mouse_update (s_video_input_data_t *mouse);
void s_video_pspdev_mouse_uninit (void);

void s_video_pspdev_server_uninit (void);
int s_video_pspdev_server_init (s_server_conf_t *cfg);
void s_video_pspdev_server_surface_update (s_rect_t *coor);
