/***************************************************************************
    begin                : Mon Aug 9 2004
    copyright            : (C) 2004 - 2008 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as               *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/


#include "../lib/xfast_.h"
#include "server.h"

void s_server_window_btn_resize_o (s_cursor_type_t cursor)
{
	int id;
	id = s_server_pri_id(0);
	if (id < 0) {
		return;
	}
	if (id == server->cursor.xyid) {
		s_server_mouse_setcursor(cursor);
	} else {
		s_server_mouse_setcursor(server->client[id].cursor);
	}
}

void s_server_window_btn_resize_oh (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	int id = s_server_pri_id(0);
	if (id < 0) {
		s_server_mouse_setcursor(CURSOR_TYPE_ARROW);
	} else {
		s_server_mouse_setcursor(server->client[id].cursor);
	}
}
void s_server_window_btn_resize_u_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZEV);
}
void s_server_window_btn_resize_ur_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZES);
}
void s_server_window_btn_resize_r_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZEH);
}
void s_server_window_btn_resize_dr_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZEB);
}
void s_server_window_btn_resize_d_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZEV);
}
void s_server_window_btn_resize_dl_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZES);
}
void s_server_window_btn_resize_l_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZEH);
}
void s_server_window_btn_resize_ul_o (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_resize_o(CURSOR_TYPE_SIZEB);
}

#define s_server_window_btn_x(a, b)\
	int id;\
	s_rect_t coor;\
	id = s_server_pri_id(0);\
	if (id < 0) {\
		return;\
	}\
	coor.x = server->client[id].button[b].x;\
	coor.y = server->client[id].button[b].y;\
	coor.w = server->client[id].button[b].w;\
	coor.h = server->client[id].button[b].h;\
	s_server_putbox(window, id, &coor, coor.x, coor.y, &server->theme.button[a][b]);\
	s_server_surface_update(&coor);

#define s_server_window_btn_x_(a, b)\
	if ((event->mouse->px >= handler->mouse.x) &&\
	    (event->mouse->px <= (handler->mouse.x + handler->mouse.w)) &&\
	    (event->mouse->py >= handler->mouse.y) &&\
	    (event->mouse->py <= (handler->mouse.y + handler->mouse.h))) {\
		s_server_window_btn_x(a, b);\
	}

void s_server_window_btn_menu_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(2, THEME_BUTTON_MENU);
}
void s_server_window_btn_menu_ho (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x_(2, THEME_BUTTON_MENU);
}
void s_server_window_btn_menu_oh (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(1, THEME_BUTTON_MENU);
}
void s_server_window_btn_menu_r (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_menu_oh(window, event, handler);
}

void s_server_window_btn_hide_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(2, THEME_BUTTON_HIDE);
}
void s_server_window_btn_hide_ho (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x_(2, THEME_BUTTON_HIDE);
}
void s_server_window_btn_hide_oh (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(1, THEME_BUTTON_HIDE);
}
void s_server_window_btn_hide_r (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_hide_oh(window, event, handler);
}

void s_server_window_btn_maximize_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(2, THEME_BUTTON_MAXIMIZE);
}
void s_server_window_btn_maximize_ho (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x_(2, THEME_BUTTON_MAXIMIZE);
}
void s_server_window_btn_maximize_oh (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(1, THEME_BUTTON_MAXIMIZE);
}
void s_server_window_btn_maximize_r (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_maximize_oh(window, event, handler);
	s_server_window_maximize(window);
}

void s_server_window_btn_close_p (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(2, THEME_BUTTON_CLOSE);
}
void s_server_window_btn_close_ho (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x_(2, THEME_BUTTON_CLOSE);
}
void s_server_window_btn_close_oh (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_btn_x(1, THEME_BUTTON_CLOSE);
}
void s_server_window_btn_close_r (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_close(window);
}
void s_server_window_btn_move (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_move(window);
}
void s_server_window_btn_resize_up (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_up(window);
}
void s_server_window_btn_resize_up_left (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_up_left(window);
}
void s_server_window_btn_resize_up_right (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_up_right(window);
}
void s_server_window_btn_resize_left (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_left(window);
}
void s_server_window_btn_resize_right (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_right(window);
}
void s_server_window_btn_resize_down (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_down(window);
}
void s_server_window_btn_resize_down_left (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_down_left(window);
}
void s_server_window_btn_resize_down_right (s_window_t *window, s_event_t *event, s_handler_t *handler)
{
	s_server_window_resize_down_right(window);
}

void s_server_window_handlers_del_mouse (void)
{
	int i;
	for (i = 0; i < 20; i++) {
		s_handler_del(server->window, server->whndl[i]);
	}
}

void s_server_window_handlers_add_mouse (int id)
{
        int v = 1;
	s_handler_t *hndl;

	/* menu */
	hndl = server->whndl[0];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].button[THEME_BUTTON_MENU].x + server->theme.button[v][THEME_BUTTON_MENU].handler->x;
	hndl->mouse.y = server->client[id].button[THEME_BUTTON_MENU].y + server->theme.button[v][THEME_BUTTON_MENU].handler->y;
	hndl->mouse.w = server->theme.button[v][THEME_BUTTON_MENU].handler->w;
	hndl->mouse.h = server->theme.button[v][THEME_BUTTON_MENU].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_menu_p;
	hndl->mouse.r = s_server_window_btn_menu_r;
	hndl->mouse.oh = s_server_window_btn_menu_oh;
	hndl->mouse.ho = s_server_window_btn_menu_ho;
	hndl->mouse.hoh = s_server_window_btn_menu_oh;
	s_handler_add(server->window, hndl);

	/* hide */
	hndl = server->whndl[1];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].button[THEME_BUTTON_HIDE].x + server->theme.button[v][THEME_BUTTON_HIDE].handler->x;
	hndl->mouse.y = server->client[id].button[THEME_BUTTON_HIDE].y + server->theme.button[v][THEME_BUTTON_HIDE].handler->y;
	hndl->mouse.w = server->theme.button[v][THEME_BUTTON_HIDE].handler->w;
	hndl->mouse.h = server->theme.button[v][THEME_BUTTON_HIDE].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_hide_p;
	hndl->mouse.r = s_server_window_btn_hide_r;
	hndl->mouse.oh = s_server_window_btn_hide_oh;
	hndl->mouse.ho = s_server_window_btn_hide_ho;
	hndl->mouse.hoh = s_server_window_btn_hide_oh;
	s_handler_add(server->window, hndl);

	/* close */
	hndl = server->whndl[2];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].button[THEME_BUTTON_CLOSE].x + server->theme.button[v][THEME_BUTTON_CLOSE].handler->x;
	hndl->mouse.y = server->client[id].button[THEME_BUTTON_CLOSE].y + server->theme.button[v][THEME_BUTTON_CLOSE].handler->y;
	hndl->mouse.w = server->theme.button[v][THEME_BUTTON_CLOSE].handler->w;
	hndl->mouse.h = server->theme.button[v][THEME_BUTTON_CLOSE].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_close_p;
	hndl->mouse.r = s_server_window_btn_close_r;
	hndl->mouse.oh = s_server_window_btn_close_oh;
	hndl->mouse.ho = s_server_window_btn_close_ho;
	hndl->mouse.hoh = s_server_window_btn_close_oh;
	s_handler_add(server->window, hndl);

	if (server->client[id].resizeable == 1) {
		/* maximize */
	        hndl = server->whndl[3];
	        hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].button[THEME_BUTTON_MAXIMIZE].x + server->theme.button[v][THEME_BUTTON_MAXIMIZE].handler->x;
		hndl->mouse.y = server->client[id].button[THEME_BUTTON_MAXIMIZE].y + server->theme.button[v][THEME_BUTTON_MAXIMIZE].handler->y;
		hndl->mouse.w = server->theme.button[v][THEME_BUTTON_MAXIMIZE].handler->w;
		hndl->mouse.h = server->theme.button[v][THEME_BUTTON_MAXIMIZE].handler->h;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_maximize_p;
		hndl->mouse.r = s_server_window_btn_maximize_r;
		hndl->mouse.oh = s_server_window_btn_maximize_oh;
		hndl->mouse.ho = s_server_window_btn_maximize_ho;
		hndl->mouse.hoh = s_server_window_btn_maximize_oh;
		s_handler_add(server->window, hndl);
	}

        if (server->client[id].win.w > server->theme.form_min.w) {
		/* move 2 */
	        hndl = server->whndl[4];
	        hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_2].x;
		hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_2].y + server->theme.form[v][THEME_FORM_TOP_2].handler->y + 4;
		hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_2].w;
		hndl->mouse.h = server->theme.form[v][THEME_FORM_TOP_2].handler->h - 4;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_move;
		s_handler_add(server->window, hndl);

                /* move 3 */
	        hndl = server->whndl[5];
	        hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_3].x;
		hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_3].y + server->theme.form[v][THEME_FORM_TOP_3].handler->y + 4;
		hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_3].w;
		hndl->mouse.h = server->theme.form[v][THEME_FORM_TOP_3].handler->h - 4;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_move;
		s_handler_add(server->window, hndl);


                /* move 4 */
	        hndl = server->whndl[6];
	        hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_4].x;
		hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_4].y + server->theme.form[v][THEME_FORM_TOP_4].handler->y + 4;
		hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_4].w;
		hndl->mouse.h = server->theme.form[v][THEME_FORM_TOP_4].handler->h - 4;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_move;
		s_handler_add(server->window, hndl);
	}

	/* move 5*/
	hndl = server->whndl[7];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_5].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_5].y + server->theme.form[v][THEME_FORM_TOP_5].handler->y + 4;
	hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_5].w;
	hndl->mouse.h = server->theme.form[v][THEME_FORM_TOP_5].handler->h - 4;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_move;
	s_handler_add(server->window, hndl);

	if (server->client[id].resizeable == 0) {
		return;
	}

	/* resize u1 */
	hndl = server->whndl[8];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_1].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_1].y + server->theme.form[v][THEME_FORM_TOP_1].handler->y;
	hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_1].w;
	hndl->mouse.h = 4;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_up;
	hndl->mouse.o = s_server_window_btn_resize_u_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

        if (server->client[id].win.w > server->theme.form_min.w) {
		/* resize u2 */
	        hndl = server->whndl[9];
        	hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_2].x;
		hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_2].y + server->theme.form[v][THEME_FORM_TOP_2].handler->y;
		hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_2].w;
		hndl->mouse.h = 4;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_resize_up;
		hndl->mouse.o = s_server_window_btn_resize_u_o;
		hndl->mouse.oh = s_server_window_btn_resize_oh;
		s_handler_add(server->window, hndl);

		/* resize u3 */
	        hndl = server->whndl[10];
        	hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_3].x;
		hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_3].y + server->theme.form[v][THEME_FORM_TOP_3].handler->y;
		hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_3].w;
		hndl->mouse.h = 4;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_resize_up;
		hndl->mouse.o = s_server_window_btn_resize_u_o;
		hndl->mouse.oh = s_server_window_btn_resize_oh;
		s_handler_add(server->window, hndl);

                /* resize u4 */
	        hndl = server->whndl[11];
        	hndl->type = MOUSE_HANDLER;
		hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_4].x;
		hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_4].y + server->theme.form[v][THEME_FORM_TOP_4].handler->y;
		hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_4].w;
		hndl->mouse.h = 4;
		hndl->mouse.button = MOUSE_BUTTON_LEFT;
		hndl->mouse.p = s_server_window_btn_resize_up;
		hndl->mouse.o = s_server_window_btn_resize_u_o;
		hndl->mouse.oh = s_server_window_btn_resize_oh;
		s_handler_add(server->window, hndl);
	}

	/* resize u5 */
        hndl = server->whndl[12];
       	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_5].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_5].y + server->theme.form[v][THEME_FORM_TOP_5].handler->y;
	hndl->mouse.w = server->client[id].form[THEME_FORM_TOP_5].w;
	hndl->mouse.h = 4;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_up;
	hndl->mouse.o = s_server_window_btn_resize_u_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

        /* resize ul */
        hndl = server->whndl[13];
       	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_LEFT].x + server->theme.form[v][THEME_FORM_TOP_LEFT].handler->x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_LEFT].y + server->theme.form[v][THEME_FORM_TOP_LEFT].handler->y;
	hndl->mouse.w = server->theme.form[v][THEME_FORM_TOP_LEFT].handler->w;
	hndl->mouse.h = server->theme.form[v][THEME_FORM_TOP_LEFT].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_up_left;
	hndl->mouse.o = s_server_window_btn_resize_ul_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

	/* resize ur */
	hndl = server->whndl[14];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_TOP_RIGHT].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_TOP_RIGHT].y + server->theme.form[v][THEME_FORM_TOP_RIGHT].handler->y;
	hndl->mouse.w = server->theme.form[v][THEME_FORM_TOP_RIGHT].handler->w;
	hndl->mouse.h = server->theme.form[v][THEME_FORM_TOP_RIGHT].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_up_right;
	hndl->mouse.o = s_server_window_btn_resize_ur_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

	/* resize l */
	hndl = server->whndl[15];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_LEFT].x + server->theme.form[v][THEME_FORM_LEFT].handler->x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_LEFT].y;
	hndl->mouse.w = server->theme.form[v][THEME_FORM_LEFT].handler->w;
	hndl->mouse.h = server->client[id].form[THEME_FORM_LEFT].h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_left;
	hndl->mouse.o = s_server_window_btn_resize_l_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

	/* resize r */
	hndl = server->whndl[16];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_RIGHT].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_RIGHT].y;
	hndl->mouse.w = server->theme.form[v][THEME_FORM_RIGHT].handler->w;
	hndl->mouse.h = server->client[id].form[THEME_FORM_RIGHT].h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_right;
	hndl->mouse.o = s_server_window_btn_resize_r_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

	/* resize d */
	hndl = server->whndl[17];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_BOTTOM].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_BOTTOM].y;
	hndl->mouse.w = server->client[id].form[THEME_FORM_BOTTOM].w;
	hndl->mouse.h = server->theme.form[v][THEME_FORM_BOTTOM].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_down;
	hndl->mouse.o = s_server_window_btn_resize_d_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

	/* resize dl */
	hndl = server->whndl[18];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_BOTTOM_LEFT].x + server->theme.form[v][THEME_FORM_BOTTOM_LEFT].handler->x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_BOTTOM_LEFT].y;
	hndl->mouse.w = server->theme.form[v][THEME_FORM_BOTTOM_LEFT].handler->w;
	hndl->mouse.h = server->theme.form[v][THEME_FORM_BOTTOM_LEFT].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_down_left;
	hndl->mouse.o = s_server_window_btn_resize_dl_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);

	/* resize dr */
	hndl = server->whndl[19];
	hndl->type = MOUSE_HANDLER;
	hndl->mouse.x = server->client[id].form[THEME_FORM_BOTTOM_RIGHT].x;
	hndl->mouse.y = server->client[id].form[THEME_FORM_BOTTOM_RIGHT].y;
	hndl->mouse.w = server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].handler->w;
	hndl->mouse.h = server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].handler->h;
	hndl->mouse.button = MOUSE_BUTTON_LEFT;
	hndl->mouse.p = s_server_window_btn_resize_down_right;
	hndl->mouse.o = s_server_window_btn_resize_dr_o;
	hndl->mouse.oh = s_server_window_btn_resize_oh;
	s_handler_add(server->window, hndl);
}
