/***************************************************************************
    begin                : Tue Oct 14 2003
    copyright            : (C) 2003 - 2008 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "../lib/xfast_.h"
#include "server.h"

#if defined(CONFIG_THEME_PLUGIN)
	#include <dlfcn.h>
#else
	#include "theme_static.h"
#endif

int s_server_theme_set (char *name)
{
	s_theme_form_t f;
	s_theme_state_t v;
	s_theme_button_t b;

#if defined(CONFIG_THEME_PLUGIN)
	char *tfile;
	char *error;
	void *handle;
	void (*theme_init) (s_theme_t *theme);
	
	tfile = (char *) s_malloc(strlen(CONFIG_PATH_INSTALL) + strlen(CONFIG_PATH_THEMES) + strlen(name) + 10);
	sprintf(tfile, "%s/%s/%s.so", CONFIG_PATH_INSTALL, CONFIG_PATH_THEMES, name);
	handle = dlopen(tfile, RTLD_LAZY);
	if (!handle) {
		debugf(DSER /*| DFAT*/, "%s: %s",tfile,dlerror());
		return 1;
	}

	theme_init = dlsym(handle, "theme_init");
	if ((error = dlerror()) != NULL)  {
		debugf(DSER | DFAT, "%s", error);
		return 0;
	}
	free(tfile);
#else
#endif
	s_server_theme_uninit();

	memset(&(server->theme), 0, sizeof(s_theme_t));
	theme_init(&server->theme);

        for (b = 0; b < THEME_BUTTON_MAX; b++) {
		for (v = 0; v < 3; v++) {
			s_image_get_buf(server->window->surface, &server->theme.button[v][b]);
			s_image_get_mat(&server->theme.button[v][b]);
			s_image_get_handler(&server->theme.button[v][b]);
			s_image_free_rgba(&server->theme.button[v][b]);
		}
	}

	for (f = 0; f < THEME_FORM_MAX; f++) {
		for (v = 0; v < 2; v++) {
			s_image_get_buf(server->window->surface, &server->theme.form[v][f]);
			s_image_get_mat(&server->theme.form[v][f]);
			s_image_get_handler(&server->theme.form[v][f]);
			s_image_free_rgba(&server->theme.form[v][f]);
		}
	}

	s_font_init(&(server->theme.font[0]), "arial.ttf");
	s_font_set_size(server->theme.font[0], server->theme.form[0][THEME_FORM_TOP_3].h - 8+server->theme.text_vsize_off[0]);
	server->theme.font[0]->rgb=server->theme.text_color[0];
	s_font_init(&(server->theme.font[1]), "arial.ttf");
	s_font_set_size(server->theme.font[1], server->theme.form[1][THEME_FORM_TOP_3].h - 8+server->theme.text_vsize_off[1]);
	server->theme.font[1]->rgb=server->theme.text_color[1];
	
#if defined(CONFIG_THEME_PLUGIN)
	dlclose(handle);
#endif

	s_server_surface_refresh();
	return 0;
}

void s_server_theme_init (char *name)
{
	s_server_theme_set((name == NULL) ? "keramik" : name);
}

void s_server_theme_uninit (void)
{
	int f;
	int b;
	int v;
	
	s_font_uninit(server->theme.font[0]);
	s_font_uninit(server->theme.font[1]);
	
	for (f = 0; f < THEME_FORM_MAX; f++) {
		for (v = 0; v < 2; v++) {
			s_image_free_buf(&server->theme.form[v][f]);
			s_image_free_mat(&server->theme.form[v][f]);
			s_image_free_rgba(&server->theme.form[v][f]);
			s_image_free_handler(&server->theme.form[v][f]);
			s_image_layers_uninit(&server->theme.form[v][f]);
		}
	}
        for (b = 0; b < THEME_BUTTON_MAX; b++) {
		for (v = 0; v < 3; v++) {
			s_image_free_buf(&server->theme.button[v][b]);
			s_image_free_mat(&server->theme.button[v][b]);
			s_image_free_rgba(&server->theme.button[v][b]);
			s_image_free_handler(&server->theme.button[v][b]);
			s_image_layers_uninit(&server->theme.button[v][b]);
		}
	}
}

