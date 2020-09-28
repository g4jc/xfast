/***************************************************************************
    begin                : Sun Feb 23 2003
    copyright            : (C) 2003 - 2008 by Alper Akcan
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

void s_server_window_new (int id)
{
	int v = (s_server_id_pri(id) <= 0) ? 1 : 0;

	server->client[id].win.x = server->client[id].buf.x;
	server->client[id].win.y = server->client[id].buf.y;

	if (server->client[id].type & WINDOW_TYPE_NOFORM) {
		server->client[id].win.w = server->client[id].buf.w;
		server->client[id].win.h = server->client[id].buf.h;
	} else {
		server->client[id].win.w = server->client[id].buf.w + (server->theme.form[v][THEME_FORM_LEFT].w + server->theme.form[v][THEME_FORM_RIGHT].w);
		server->client[id].win.h = server->client[id].buf.h + (server->theme.form[v][THEME_FORM_TOP_1].h + server->theme.form[v][THEME_FORM_BOTTOM].h);
	}

        /* if the caller does not know what he/she is doing we will correct his/her shit */
	server->client[id].win.x = (server->client[id].win.x < 0) ? 0 : server->client[id].win.x;
	server->client[id].win.y = (server->client[id].win.y < 0) ? 0 : server->client[id].win.y;

        if (server->client[id].type & WINDOW_TYPE_NOFORM) {
		if (server->client[id].win.w < 0) {
			server->client[id].win.w = 0;
		}
		if (server->client[id].win.h < 0) {
			server->client[id].win.h = 0;
		}
	} else {
		if (server->client[id].win.w < server->theme.form_min.w_) {
			server->client[id].win.w = server->theme.form_min.w_;
		}
		if (server->client[id].win.h < server->theme.form_min.h) {
			server->client[id].win.h = server->theme.form_min.h;
		}
	}

        if (server->client[id].type & WINDOW_TYPE_NOFORM) {
		server->client[id].win.x = (server->client[id].win.x > server->window->surface->width) ? 0 : server->client[id].win.x;
		server->client[id].win.y = (server->client[id].win.y > server->window->surface->height) ? 0 : server->client[id].win.y;
	} else {
		server->client[id].win.x = (server->client[id].win.x > server->window->surface->width - server->theme.form_min.w) ? 0 : server->client[id].win.x;
		server->client[id].win.y = (server->client[id].win.y > server->window->surface->height - server->theme.form_min.h) ? 0 : server->client[id].win.y;
	}

	/* coor&dim correcting, done. */

        if (server->client[id].type & WINDOW_TYPE_NOFORM) {
		server->client[id].buf.x = server->client[id].win.x;
		server->client[id].buf.y = server->client[id].win.y;
		server->client[id].buf.w = server->client[id].win.w;
		server->client[id].buf.h = server->client[id].win.h;
	} else {
		server->client[id].buf.x = server->client[id].win.x + server->theme.form[v][THEME_FORM_LEFT].w;
		server->client[id].buf.y = server->client[id].win.y + server->theme.form[v][THEME_FORM_TOP_1].h;
		server->client[id].buf.w = server->client[id].win.w - server->theme.form[v][THEME_FORM_LEFT].w - server->theme.form[v][THEME_FORM_RIGHT].w;
		server->client[id].buf.h = server->client[id].win.h - server->theme.form[v][THEME_FORM_TOP_1].h - server->theme.form[v][THEME_FORM_BOTTOM].h;
	}

	server->client[id].title.str = (char *) s_malloc(sizeof(char) * 23);
	sprintf(server->client[id].title.str, "XFast Windowing System");
	s_server_window_title(id, server->client[id].title.str);
}

void s_server_window_title (int id, char *title)
{
	int i;
        int v;
        int h;
        int yo;
	s_font_t *font;
	s_surface_t *srf;

        if ((id < 0) ||
	    (title == NULL) ||
	    (server->client[id].type & WINDOW_TYPE_NOFORM)) {
		return;
	}
	
        for (v = 0; v < 2; v++) {
		font = server->theme.font[v];
		s_font_set_str(font, title);
		s_font_get_glyph(font);
		s_image_get_mat(font->glyph.img);
		s_image_get_handler(font->glyph.img);

		font->glyph.img->buf = (char *) s_calloc(1, font->glyph.img->w * font->glyph.img->h * server->window->surface->bytesperpixel);
		if (s_surface_create_from_data(&srf, font->glyph.img->w, font->glyph.img->h, server->window->surface->bitsperpixel, font->glyph.img->buf)) {
			goto out;
		}

		if ((i = font->glyph.img->w / server->theme.form[v][THEME_FORM_TOP_3].w) > 0) {
			while (i--) {
				yo = server->theme.text_v_off[v] - font->glyph.img->handler->y + (server->theme.form[v][THEME_FORM_TOP_3].handler->h - font->glyph.img->handler->h) / 2;
				if ((font->glyph.img->h + yo) > server->theme.form[v][THEME_FORM_TOP_3].h) {
					h = server->theme.form[v][THEME_FORM_TOP_3].h - yo;
				} else {
					h = font->glyph.img->h;
				}
				s_putboxpart(srf, i * server->theme.form[v][THEME_FORM_TOP_3].w, 0, server->theme.form[v][THEME_FORM_TOP_3].w, h, server->theme.form[v][THEME_FORM_TOP_3].w, server->theme.form[v][THEME_FORM_TOP_3].h, server->theme.form[v][THEME_FORM_TOP_3].buf, 0, yo);
			}
		}
		if ((i = font->glyph.img->w % server->theme.form[v][THEME_FORM_TOP_3].w) > 0) {
				s_putboxpart(srf, font->glyph.img->w - server->theme.form[v][THEME_FORM_TOP_3].w, 0, server->theme.form[v][THEME_FORM_TOP_3].w, font->glyph.img->h, server->theme.form[v][THEME_FORM_TOP_3].w, server->theme.form[v][THEME_FORM_TOP_3].h, server->theme.form[v][THEME_FORM_TOP_3].buf, 0, server->theme.text_v_off[v] - font->glyph.img->handler->y + (server->theme.form[v][THEME_FORM_TOP_3].handler->h - font->glyph.img->handler->h) / 2);
		}
		s_putboxrgba(srf, 0, 0, font->glyph.img->w, font->glyph.img->h, font->glyph.img->rgba);

		s_free(server->client[id].title.img[v].mat);
		s_free(server->client[id].title.img[v].buf);
		server->client[id].title.img[v].mat = (unsigned char *) s_malloc(font->glyph.img->w * font->glyph.img->h);
		server->client[id].title.img[v].buf = (char *) s_malloc(font->glyph.img->w * font->glyph.img->h * server->window->surface->bytesperpixel);
		server->client[id].title.img[v].w = font->glyph.img->w;
		server->client[id].title.img[v].h = font->glyph.img->h;
		server->client[id].title.hy[v] = font->glyph.img->handler->y;
		server->client[id].title.hh[v] = font->glyph.img->handler->h;
		memcpy(server->client[id].title.img[v].mat, font->glyph.img->mat, font->glyph.img->w * font->glyph.img->h);
		memcpy(server->client[id].title.img[v].buf, font->glyph.img->buf, font->glyph.img->w * font->glyph.img->h * server->window->surface->bytesperpixel);
		s_surface_destroy(srf);
out:		s_image_uninit(font->glyph.img);
		s_image_init(&(font->glyph.img));
	}
}

void s_server_putbox (s_window_t *window, int id, s_rect_t *coor, int x, int y, s_image_t *img)
{
        int add;
	s_rect_t to;
	s_rect_t intr;
	s_rect_t icoor;

	icoor.x = x;
	icoor.y = y;
	icoor.w = img->w;
	icoor.h = img->h;

	if (s_region_rect_intersect(coor, &icoor, &intr)) {
		return;
	}
	if (s_region_rect_intersect(window->surface->buf, &intr, &to)) {
		return;
	}
	add = (to.y - icoor.y) * img->w + (to.x - icoor.x);
	bpp_putbox_mask_o(window->surface, id, to.x, to.y, to.w, to.h, img->buf + add * window->surface->bytesperpixel, img->mat + add, img->w);
}

void s_server_putmat (s_window_t *window, int id, s_rect_t *coor, int x, int y, s_image_t *img)
{
        s_rect_t mcoor;
	mcoor.x = x;
	mcoor.y = y;
	mcoor.w = img->w;
	mcoor.h = img->h;
	s_server_surface_matrix_add_this(id, coor, &mcoor, img->mat);
}

int s_server_window_form_mat_verbose (int id)
{
	int i = s_server_pri_id(0);
	if ((id < 0) ||
	    (server->client[id].type & WINDOW_TYPE_NOFORM) ||
	    (s_server_id_pri(id) < 0)) {
		return -1;
	}
	if ((s_server_id_pri(id) == 0) ||
	    ((i >= 0) &&
	     (server->client[i].type & WINDOW_TYPE_TEMP) &&
	     (s_server_window_is_parent_temp(id, i)))) {
		return 1;
        }
        return 0;
}

void s_server_window_form_mat (int v, int id, s_rect_t *coor, void (*func) (s_window_t *, int, s_rect_t *, int, int, s_image_t *))
{
	int i;
	/* top */
	func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_LEFT].x, server->client[id].form[THEME_FORM_TOP_LEFT].y, &server->theme.form[v][THEME_FORM_TOP_LEFT]);
	for (i = 0; i < server->client[id].form[THEME_FORM_TOP_1].w; i += server->theme.form[v][THEME_FORM_TOP_1].w) {
		func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_1].x + i, server->client[id].form[THEME_FORM_TOP_1].y, &server->theme.form[v][THEME_FORM_TOP_1]);
	}
	if (server->client[id].win.w >= server->theme.form_min.w) {
		func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_2].x, server->client[id].form[THEME_FORM_TOP_2].y, &server->theme.form[v][THEME_FORM_TOP_2]);
		if ((i = server->client[id].form[THEME_FORM_TOP_3].w / server->theme.form[v][THEME_FORM_TOP_3].w) > 0) {
			while (i--) {
				func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_3].x + i * server->theme.form[v][THEME_FORM_TOP_3].w, server->client[id].form[THEME_FORM_TOP_3].y, &server->theme.form[v][THEME_FORM_TOP_3]);
			}
		}
		if (server->client[id].form[THEME_FORM_TOP_3].w % server->theme.form[v][THEME_FORM_TOP_3].w) {
			func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_4].x - server->theme.form[v][THEME_FORM_TOP_3].w, server->client[id].form[THEME_FORM_TOP_3].y, &server->theme.form[v][THEME_FORM_TOP_3]);
		}
		func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_4].x, server->client[id].form[THEME_FORM_TOP_4].y, &server->theme.form[v][THEME_FORM_TOP_4]);
	}
	if ((i = server->client[id].form[THEME_FORM_TOP_5].w / server->theme.form[v][THEME_FORM_TOP_5].w) > 0) {
		while (i--) {
			func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_5].x + i * server->theme.form[v][THEME_FORM_TOP_5].w, server->client[id].form[THEME_FORM_TOP_5].y, &server->theme.form[v][THEME_FORM_TOP_5]);
		}
	}
	if (server->client[id].form[THEME_FORM_TOP_5].w % server->theme.form[v][THEME_FORM_TOP_5].w) {
		func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_RIGHT].x - server->theme.form[v][THEME_FORM_TOP_5].w, server->client[id].form[THEME_FORM_TOP_5].y, &server->theme.form[v][THEME_FORM_TOP_5]);
	}
	func(server->window, id, coor, server->client[id].form[THEME_FORM_TOP_RIGHT].x, server->client[id].form[THEME_FORM_TOP_RIGHT].y, &server->theme.form[v][THEME_FORM_TOP_RIGHT]);
	/* left */
	if ((i = server->client[id].form[THEME_FORM_LEFT].h / server->theme.form[v][THEME_FORM_LEFT].h) > 0) {
		while (i--) {
			func(server->window, id, coor, server->client[id].form[THEME_FORM_LEFT].x, server->client[id].form[THEME_FORM_LEFT].y + i * server->theme.form[v][THEME_FORM_LEFT].h, &server->theme.form[v][THEME_FORM_LEFT]);
		}
	}
	if (server->client[id].form[THEME_FORM_LEFT].h % server->theme.form[v][THEME_FORM_LEFT].h) {
		func(server->window, id, coor, server->client[id].form[THEME_FORM_LEFT].x, server->client[id].form[THEME_FORM_BOTTOM_LEFT].y - server->theme.form[v][THEME_FORM_LEFT].h, &server->theme.form[v][THEME_FORM_LEFT]);
	}
        /* right */
	if ((i = server->client[id].form[THEME_FORM_RIGHT].h / server->theme.form[v][THEME_FORM_RIGHT].h) > 0) {
		while (i--) {
			func(server->window, id, coor, server->client[id].form[THEME_FORM_RIGHT].x, server->client[id].form[THEME_FORM_RIGHT].y + i * server->theme.form[v][THEME_FORM_RIGHT].h, &server->theme.form[v][THEME_FORM_RIGHT]);
		}
	}
	if (server->client[id].form[THEME_FORM_RIGHT].h % server->theme.form[v][THEME_FORM_RIGHT].h) {
		func(server->window, id, coor, server->client[id].form[THEME_FORM_RIGHT].x, server->client[id].form[THEME_FORM_BOTTOM_RIGHT].y - server->theme.form[v][THEME_FORM_RIGHT].h, &server->theme.form[v][THEME_FORM_RIGHT]);
	}
        /* bottom */
        func(server->window, id, coor, server->client[id].form[THEME_FORM_BOTTOM_LEFT].x, server->client[id].form[THEME_FORM_BOTTOM_LEFT].y, &server->theme.form[v][THEME_FORM_BOTTOM_LEFT]);
        if ((i = server->client[id].form[THEME_FORM_BOTTOM].w / server->theme.form[v][THEME_FORM_BOTTOM].w) > 0) {
		while (i--) {
			func(server->window, id, coor, server->client[id].form[THEME_FORM_BOTTOM].x + i * server->theme.form[v][THEME_FORM_BOTTOM].w, server->client[id].form[THEME_FORM_BOTTOM].y, &server->theme.form[v][THEME_FORM_BOTTOM]);
		}
	}
	if (server->client[id].form[THEME_FORM_BOTTOM].w % server->theme.form[v][THEME_FORM_BOTTOM].w) {
		func(server->window, id, coor, server->client[id].form[THEME_FORM_BOTTOM_RIGHT].x - server->theme.form[v][THEME_FORM_BOTTOM].w, server->client[id].form[THEME_FORM_BOTTOM].y, &server->theme.form[v][THEME_FORM_BOTTOM]);
	}
        func(server->window, id, coor, server->client[id].form[THEME_FORM_BOTTOM_RIGHT].x, server->client[id].form[THEME_FORM_BOTTOM_RIGHT].y, &server->theme.form[v][THEME_FORM_BOTTOM_RIGHT]);
}

void s_server_window_form (int id, s_rect_t *_coor_)
{
	int v = 0;
	s_rect_t coort;
	s_rect_t intersect;

	s_rect_t coor;
	s_rect_t coor_ = server->client[id].win;

	v = s_server_window_form_mat_verbose(id);
	if (v < 0) {
		return;
	}

	if (s_region_rect_intersect(_coor_, &coor_, &coor)) {
		return;
	}

        coort.x = server->client[id].form[THEME_FORM_TOP_3].x;
        coort.y = server->client[id].form[THEME_FORM_TOP_3].y;
        coort.w = server->client[id].form[THEME_FORM_TOP_3].w;
        coort.h = server->theme.form[v][THEME_FORM_TOP_3].handler->h;

	s_server_window_form_mat(v, id, &coor, s_server_putbox);

	/* buttons */
	s_server_putbox(server->window, id, &coor, server->client[id].button[THEME_BUTTON_MENU].x, server->client[id].button[THEME_BUTTON_MENU].y, &server->theme.button[v][THEME_BUTTON_MENU]);
	s_server_putbox(server->window, id, &coor, server->client[id].button[THEME_BUTTON_HIDE].x, server->client[id].button[THEME_BUTTON_HIDE].y, &server->theme.button[v][THEME_BUTTON_HIDE]);
	s_server_putbox(server->window, id, &coor, server->client[id].button[THEME_BUTTON_CLOSE].x, server->client[id].button[THEME_BUTTON_CLOSE].y, &server->theme.button[v][THEME_BUTTON_CLOSE]);
	if (server->client[id].resizeable == 1) {
		s_server_putbox(server->window, id, &coor, server->client[id].button[THEME_BUTTON_MAXIMIZE].x, server->client[id].button[THEME_BUTTON_MAXIMIZE].y, &server->theme.button[v][THEME_BUTTON_MAXIMIZE]);
	}

	/* title */
	if ((!s_region_rect_intersect(&coor, &coort, &intersect)) && (server->client[id].win.w > server->theme.form_min.w)) {
		s_server_putbox(server->window, id, &intersect, coort.x, coort.y + server->theme.text_v_off[v] - server->client[id].title.hy[v] + (server->theme.form[v][THEME_FORM_TOP_3].handler->h - server->client[id].title.hh[v]) / 2, &server->client[id].title.img[v]);
	}
}

void s_server_window_matrix_add (int id, s_rect_t *_coor_)
{
	int v = 0;
	s_rect_t coor;
	s_rect_t coor_ = server->client[id].win;

	v = s_server_window_form_mat_verbose(id);
	if (v < 0) {
		return;
	}

	if (s_region_rect_intersect(_coor_, &coor_, &coor)) {
		return;
	}

	s_server_window_form_mat(v, id, &coor, s_server_putmat);
}

void s_server_window_calculate (int id)
{
        int i;
	int v = 0;
	int title_len;
	int btns_w;

	v = s_server_window_form_mat_verbose(id);
	if (v < 0) {
		return;
	}

        title_len = server->client[id].title.img[v].w;
        btns_w = server->theme.button[v][THEME_BUTTON_HIDE].w + server->theme.button[v][THEME_BUTTON_CLOSE].w;
        if (server->client[id].resizeable == 1) {
		btns_w += server->theme.button[v][THEME_BUTTON_MAXIMIZE].w;
	}

	server->client[id].win.x = server->client[id].buf.x - server->theme.form[v][THEME_FORM_LEFT].w;
	server->client[id].win.y = server->client[id].buf.y - server->theme.form[v][THEME_FORM_TOP_1].h;
	if ((server->client[id].win.w = server->client[id].buf.w + server->theme.form[v][THEME_FORM_LEFT].w + server->theme.form[v][THEME_FORM_RIGHT].w) < server->theme.form_min.w_) {
		server->client[id].buf.w += server->theme.form_min.w_ - server->client[id].win.w;
		server->client[id].win.w += server->theme.form_min.w_ - server->client[id].win.w;
	}
	if ((server->client[id].win.h = server->client[id].buf.h + server->theme.form[v][THEME_FORM_TOP_1].h + server->theme.form[v][THEME_FORM_BOTTOM].h) < server->theme.form_min.h) {
		server->client[id].buf.h += server->theme.form_min.h - server->client[id].win.h;
		server->client[id].win.h += server->theme.form_min.h - server->client[id].win.h;
	}

        /* window form */
        /* top */
	server->client[id].form[THEME_FORM_TOP_LEFT].x = server->client[id].win.x;
	server->client[id].form[THEME_FORM_TOP_LEFT].y = server->client[id].win.y;
	server->client[id].form[THEME_FORM_TOP_LEFT].w = server->theme.form[v][THEME_FORM_TOP_LEFT].w;
	server->client[id].form[THEME_FORM_TOP_LEFT].h = server->theme.form[v][THEME_FORM_TOP_LEFT].h;

	server->client[id].form[THEME_FORM_TOP_RIGHT].x = server->client[id].win.x + server->client[id].win.w - server->theme.form[v][THEME_FORM_TOP_RIGHT].w;
	server->client[id].form[THEME_FORM_TOP_RIGHT].y = server->client[id].win.y;
	server->client[id].form[THEME_FORM_TOP_RIGHT].w = server->theme.form[v][THEME_FORM_TOP_RIGHT].w;
	server->client[id].form[THEME_FORM_TOP_RIGHT].h = server->theme.form[v][THEME_FORM_TOP_RIGHT].h;

        server->client[id].form[THEME_FORM_TOP_1].x = server->client[id].win.x + server->theme.form[v][THEME_FORM_TOP_LEFT].w;
        server->client[id].form[THEME_FORM_TOP_1].y = server->client[id].win.y;
        server->client[id].form[THEME_FORM_TOP_1].w = server->theme.button[v][THEME_BUTTON_MENU].w;
        server->client[id].form[THEME_FORM_TOP_1].h = server->theme.form[v][THEME_FORM_TOP_1].h;

        server->client[id].form[THEME_FORM_TOP_2].x = server->client[id].form[THEME_FORM_TOP_1].x + server->client[id].form[THEME_FORM_TOP_1].w;
        server->client[id].form[THEME_FORM_TOP_2].y = server->client[id].win.y;
        server->client[id].form[THEME_FORM_TOP_2].w = server->theme.form[v][THEME_FORM_TOP_2].w;
        server->client[id].form[THEME_FORM_TOP_2].h = server->theme.form[v][THEME_FORM_TOP_2].h;

        server->client[id].form[THEME_FORM_TOP_3].x = server->client[id].form[THEME_FORM_TOP_2].x + server->client[id].form[THEME_FORM_TOP_2].w;
        server->client[id].form[THEME_FORM_TOP_3].y = server->client[id].win.y;

        i = server->client[id].win.w - server->client[id].form[THEME_FORM_TOP_LEFT].w - server->client[id].form[THEME_FORM_TOP_RIGHT].w -
            server->client[id].form[THEME_FORM_TOP_1].w - server->client[id].form[THEME_FORM_TOP_2].w - server->theme.form[v][THEME_FORM_TOP_4].w - btns_w;

        if (server->theme.title_full) {
                server->client[id].form[THEME_FORM_TOP_3].w = i;
                if (server->theme.title_alignment == THEME_ALIGNMENT_LEFT) {
                        server->client[id].title.hx[v] = 0;
                } else if (server->theme.title_alignment == THEME_ALIGNMENT_RIGHT) {
                        server->client[id].title.hx[v] = MAX(i - title_len, 0);
                } else {
                        server->client[id].title.hx[v] = MAX((i - title_len) / 2, 0);
                }
        } else {
                server->client[id].form[THEME_FORM_TOP_3].w = (i < title_len) ? i : title_len;
        }
        server->client[id].form[THEME_FORM_TOP_3].h = server->theme.form[v][THEME_FORM_TOP_3].h;

        if (server->theme.title_full) {
                server->client[id].form[THEME_FORM_TOP_4].x = server->client[id].win.x + server->client[id].win.w - server->theme.form[v][THEME_FORM_TOP_4].w -
                                                   btns_w - server->client[id].form[THEME_FORM_TOP_RIGHT].w;
        } else {
                server->client[id].form[THEME_FORM_TOP_4].x = server->client[id].form[THEME_FORM_TOP_3].x + server->client[id].form[THEME_FORM_TOP_3].w;
        }
        server->client[id].form[THEME_FORM_TOP_4].y = server->client[id].win.y;
        server->client[id].form[THEME_FORM_TOP_4].w = server->theme.form[v][THEME_FORM_TOP_4].w;
        server->client[id].form[THEME_FORM_TOP_4].h = server->theme.form[v][THEME_FORM_TOP_4].h;

	if (server->client[id].win.w < server->theme.form_min.w) {
		server->client[id].form[THEME_FORM_TOP_5].x = server->client[id].form[THEME_FORM_TOP_2].x;
	} else {
		server->client[id].form[THEME_FORM_TOP_5].x = server->client[id].form[THEME_FORM_TOP_4].x + server->client[id].form[THEME_FORM_TOP_4].w;
	}
        server->client[id].form[THEME_FORM_TOP_5].y = server->client[id].win.y;
        server->client[id].form[THEME_FORM_TOP_5].w = server->client[id].form[THEME_FORM_TOP_RIGHT].x - server->client[id].form[THEME_FORM_TOP_5].x;
        server->client[id].form[THEME_FORM_TOP_5].h = server->theme.form[v][THEME_FORM_TOP_5].h;

	/* left */
	server->client[id].form[THEME_FORM_LEFT].x = server->client[id].win.x;
	server->client[id].form[THEME_FORM_LEFT].y = server->client[id].win.y + server->theme.form[v][THEME_FORM_TOP_LEFT].h;
	server->client[id].form[THEME_FORM_LEFT].w = server->theme.form[v][THEME_FORM_LEFT].w;
	server->client[id].form[THEME_FORM_LEFT].h = server->client[id].win.h - server->theme.form[v][THEME_FORM_TOP_LEFT].h - server->theme.form[v][THEME_FORM_BOTTOM_LEFT].h;

	/* right */
	server->client[id].form[THEME_FORM_RIGHT].x = server->client[id].win.x + server->client[id].win.w - server->theme.form[v][THEME_FORM_RIGHT].w;
	server->client[id].form[THEME_FORM_RIGHT].y = server->client[id].win.y + server->theme.form[v][THEME_FORM_TOP_RIGHT].h;
	server->client[id].form[THEME_FORM_RIGHT].w = server->theme.form[v][THEME_FORM_RIGHT].w;
	server->client[id].form[THEME_FORM_RIGHT].h = server->client[id].win.h - server->theme.form[v][THEME_FORM_TOP_RIGHT].h - server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].h;

	/* bottom */
	server->client[id].form[THEME_FORM_BOTTOM_LEFT].x = server->client[id].win.x;
	server->client[id].form[THEME_FORM_BOTTOM_LEFT].y = server->client[id].win.y + server->client[id].win.h - server->theme.form[v][THEME_FORM_BOTTOM_LEFT].h;
	server->client[id].form[THEME_FORM_BOTTOM_LEFT].w = server->theme.form[v][THEME_FORM_BOTTOM_LEFT].w;
	server->client[id].form[THEME_FORM_BOTTOM_LEFT].h = server->theme.form[v][THEME_FORM_BOTTOM_LEFT].h;

        server->client[id].form[THEME_FORM_BOTTOM].x = server->client[id].win.x + server->client[id].form[THEME_FORM_BOTTOM_LEFT].w;
        server->client[id].form[THEME_FORM_BOTTOM].y = server->client[id].win.y + server->client[id].win.h - server->theme.form[v][THEME_FORM_BOTTOM].h;
        server->client[id].form[THEME_FORM_BOTTOM].w = server->client[id].win.w - server->client[id].form[THEME_FORM_BOTTOM_LEFT].w - server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].w;
        server->client[id].form[THEME_FORM_BOTTOM].h = server->theme.form[v][THEME_FORM_BOTTOM].h;

	server->client[id].form[THEME_FORM_BOTTOM_RIGHT].x = server->client[id].win.x + server->client[id].win.w - server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].w;
	server->client[id].form[THEME_FORM_BOTTOM_RIGHT].y = server->client[id].win.y + server->client[id].win.h - server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].h;
	server->client[id].form[THEME_FORM_BOTTOM_RIGHT].w = server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].w;
	server->client[id].form[THEME_FORM_BOTTOM_RIGHT].h = server->theme.form[v][THEME_FORM_BOTTOM_RIGHT].h;

	/* buttons */
	/* menu */
	server->client[id].button[THEME_BUTTON_MENU].x = server->client[id].form[THEME_FORM_TOP_1].x;
	server->client[id].button[THEME_BUTTON_MENU].y = server->client[id].form[THEME_FORM_TOP_1].y;
	server->client[id].button[THEME_BUTTON_MENU].w = server->theme.button[v][THEME_BUTTON_MENU].w;
	server->client[id].button[THEME_BUTTON_MENU].h = server->theme.button[v][THEME_BUTTON_MENU].h;

	/* close */
	server->client[id].button[THEME_BUTTON_CLOSE].x = server->client[id].form[THEME_FORM_TOP_RIGHT].x - server->theme.button[v][THEME_BUTTON_CLOSE].w;
	server->client[id].button[THEME_BUTTON_CLOSE].y = server->client[id].form[THEME_FORM_TOP_5].y;
	server->client[id].button[THEME_BUTTON_CLOSE].w = server->theme.button[v][THEME_BUTTON_CLOSE].w;
	server->client[id].button[THEME_BUTTON_CLOSE].h = server->theme.button[v][THEME_BUTTON_CLOSE].h;

	/* maximize */
	server->client[id].button[THEME_BUTTON_MAXIMIZE].x = server->client[id].button[THEME_BUTTON_CLOSE].x - server->theme.button[v][THEME_BUTTON_MAXIMIZE].w;
	server->client[id].button[THEME_BUTTON_MAXIMIZE].y = server->client[id].form[THEME_FORM_TOP_5].y;
	server->client[id].button[THEME_BUTTON_MAXIMIZE].w = server->theme.button[v][THEME_BUTTON_MAXIMIZE].w;
	server->client[id].button[THEME_BUTTON_MAXIMIZE].h = server->theme.button[v][THEME_BUTTON_MAXIMIZE].h;

	/* hide */
	if (server->client[id].resizeable == 1) {
		server->client[id].button[THEME_BUTTON_HIDE].x = server->client[id].button[THEME_BUTTON_MAXIMIZE].x - server->theme.button[v][THEME_BUTTON_HIDE].w;
	} else {
		server->client[id].button[THEME_BUTTON_HIDE].x = server->client[id].button[THEME_BUTTON_CLOSE].x - server->theme.button[v][THEME_BUTTON_HIDE].w;
	}
	server->client[id].button[THEME_BUTTON_HIDE].y = server->client[id].form[THEME_FORM_TOP_5].y;
	server->client[id].button[THEME_BUTTON_HIDE].w = server->theme.button[v][THEME_BUTTON_HIDE].w;
	server->client[id].button[THEME_BUTTON_HIDE].h = server->theme.button[v][THEME_BUTTON_HIDE].h;
}

int s_server_window_is_parent_temp (int pid, int cid)
{
	int i = cid;

	while (i >= 0) {
		if (server->client[i].type & (WINDOW_TYPE_MAIN | WINDOW_TYPE_CHILD)) {
			return 0;
		}
		i = server->client[i].pid;
		if (i < 0) {
			return 0;
		}
		if (i == pid) {
			return 1;
		}
	}

	return 0;
}

int s_server_window_temp_parent (int cid)
{
	int i = cid;

	while (i >= 0) {
		if (server->client[i].type & (WINDOW_TYPE_MAIN | WINDOW_TYPE_CHILD)) {
			return i;
		}
		i = server->client[i].pid;
		if (i < 0) {
			return -1;
		}
	}

	return -1;
}

void s_server_window_close_temps (int id)
{
	int i;

	if (id < 0) {
		return;
	}
	for (i = 0; i < S_CLIENTS_MAX; i++) {
		if ((server->client[i].pid == id) && (server->client[i].type & WINDOW_TYPE_TEMP)) {
			s_server_window_close_id(i);
		}
	}
}

void s_server_window_close_id (int id)
{
	if (id < 0) {
		return;
	}
	s_server_socket_request(SOC_DATA_CLOSE, id);
}

void s_server_window_hide_id (int id)
{
        int i;
	int p;
        s_rect_t c;

        if (id < 0) {
		return;
	}
	p = s_server_id_pri(id);
	if (p < 0) {
		return;
	}

	if (server->client[id].win.w < 0) {
		server->client[id].win.w = 0;
	}
        if (server->client[id].win.h < 0) {
		server->client[id].win.h = 0;
	}
	c = server->client[id].win;

	if (p >= 0) {
		for (i = p; i < (S_CLIENTS_MAX - 1); i++) {
			server->pri[i] = server->pri[i + 1];
		}
		server->pri[S_CLIENTS_MAX - 1] = -1;
	}

	s_server_pri_set(SURFACE_CLOSE, &c);

	{
		s_rect_t coor = {0, 0, 0, 0};
		s_server_socket_request(SOC_DATA_EXPOSE, id, &coor);
	}
}

void s_server_window_close (s_window_t *window)
{
	int id = s_server_pri_id(0);
	if (id < 0) {
		return;
	}
	s_server_window_close_id(id);
}

void s_server_window_move_resize (int id, s_rect_t *new)
{
        int mw;
	int mh;
	s_rect_t old = server->client[id].win;
        int w = server->client[id].win.w - server->client[id].buf.w;
        int h = server->client[id].win.h - server->client[id].buf.h;

        if (server->client[id].type & WINDOW_TYPE_NOFORM) {
		mw = 0;
		mh = 0;
	} else {
		mw = server->theme.form_min.w_ - w;
		mh = server->theme.form_min.h - h;
	}

	if ((new->x < 0) && (new->y < 0) && (s_server_id_pri(id) < 0)) {
		new->x += w;
		new->y += h;
	}

	if (new->w < (mw + w)) {
		new->w = mw + w;
	}
	if (new->h < (mh + h)) {
		new->h = mh + h;
	}
	if ((new->x + new->w) <= 5) {
		new->x = 5 - new->w;
	}
	if ((new->y + new->h) <= 5) {
		new->y = 5 - new->h;
	}
	if (new->x >= (server->window->surface->width - 5)) {
		new->x = server->window->surface->width - 5;
	}
	if (new->y >= (server->window->surface->height - 5)) {
		new->y = server->window->surface->height - 5;
	}

	server->client[id].buf.x += new->x - old.x;
	server->client[id].buf.y += new->y - old.y;
	server->client[id].buf.w += new->w - old.w;
	server->client[id].buf.h += new->h - old.h;
	server->client[id].win = *new;

	s_server_pri_set(SURFACE_CHANGED, id, &old, new);
}

void s_server_window_maximize (s_window_t *window)
{
	int id;
        s_rect_t new;
	new.x = 0;
	new.y = 0;
	new.w = window->surface->width;
	new.h = window->surface->height;
	id = s_server_pri_id(0);
	if (id < 0) {
		return;
	}
	s_server_window_move_resize(id, &new);
}
