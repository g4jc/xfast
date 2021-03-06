/***************************************************************************
    begin                : Tue Oct 5 2004
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

#include "desktop.h"

int desktop_self_system (char *command)
{
	int i = 0;
	char *tmp;
	char *ptr;
	char *str;
        char *arg[10];
	
	memset(arg, 0, sizeof(char *) * 10);
	
	tmp = strdup(command);
	ptr = tmp;
	str = tmp;
	while (*ptr) {
		arg[i++] = ptr;
		if ((str = strchr(ptr, ' ')) != NULL) {
			*str = '\0';
			ptr = str + 1;
		} else {
			break;
		}
	}
#if defined(CONFIG_SINGLE_APPLICATION)
	{
		void * s_server_single_app_start (void *arg);
		extern s_single_app_t *s_server_single_apps[];
		s_single_app_t **sa;
		for (sa = s_server_single_apps; *sa; sa++) {
			if (strcmp(arg[0], (*sa)->argv[0]) == 0) {
				s_thread_create(s_server_single_app_start, *sa);
				goto end;
			}
		}
		debugf(DCLI, "Error executing %s. Could not find %s in single application list.", arg[0], arg[0]);
	}
end:
#else
	{
		pid_t pid;
		if ((pid = fork()) < 0) {
			s_free(tmp);
			return -1;
		}
		if (pid == 0) {
#if defined(PLATFORM_GP2X)
			system(arg[0]);
			exit(0);
#else
			execvp(arg[0], arg);
			debugf(DCLI, "Error executing %s", arg[0]);
			exit(2);
#endif
		}
	}
#endif
	s_free(tmp);
	return 0;
}

int main (int argc, char *argv[])
{
	s_config_t *cfg;
	s_window_t *desktop;
	s_window_t *taskbar;

#if defined(PLATFORM_MINGW)
#else
	setenv("SDL_VIDEODRIVER", "xfast", 1);
#endif

	s_config_init(&cfg);
	s_config_parse(cfg, DESKTOPDIR "/cfg/desktop.cfg");

	s_window_init(&desktop);
	s_window_init(&taskbar);

	s_window_new(desktop, WINDOW_TYPE_MAIN | WINDOW_TYPE_NOFORM, NULL);
	s_window_new(taskbar, WINDOW_TYPE_CHILD | WINDOW_TYPE_NOFORM | WINDOW_TYPE_DESKTOP, desktop);

	taskbar_start(taskbar, cfg);
	desktop_start(desktop, cfg);

	s_config_uninit(cfg);

	return 0;
}

#if defined(CONFIG_SINGLE_APPLICATION)
s_single_app_t single_desktop = {
	desktop_main,
	1,
	{"desktop"}
};
#endif
