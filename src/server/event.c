/***************************************************************************
    begin                : Wed Feb 19 2003
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

void s_server_event_parse_keyboard (s_video_input_data_keybd_t *keybd)
{
	long long time;
	s_keyboard_flag_t keycode_flag;
	
	time = s_gettimeofday();
	keycode_flag = server->window->event->keybd->flag;
        
	if (keybd->state == EVENT_TYPE_KEYBOARD_PRESSED) {
		switch (keybd->keycode) {
			case KEYBOARD_BUTTON_NUM_LOCK:
				keycode_flag ^= KEYBOARD_FLAG_NUMLOCK;
				break;
			case KEYBOARD_BUTTON_CAPS_LOCK:
				keycode_flag ^= KEYBOARD_FLAG_CAPSLOCK;
				break;
			case KEYBOARD_BUTTON_LEFTCONTROL:
				keycode_flag |= KEYBOARD_FLAG_LEFTCTRL;
				break;
			case KEYBOARD_BUTTON_RIGHTCONTROL:
				keycode_flag |= KEYBOARD_FLAG_RIGHTCTRL;
				break;
			case KEYBOARD_BUTTON_LEFTSHIFT:
				keycode_flag |= KEYBOARD_FLAG_LEFTSHIFT;
				break;
			case KEYBOARD_BUTTON_RIGHTSHIFT:
				keycode_flag |= KEYBOARD_FLAG_RIGHTSHIFT;
				break;
			case KEYBOARD_BUTTON_ALT:
				keycode_flag |= KEYBOARD_FLAG_LEFTALT;
				break;
			case KEYBOARD_BUTTON_ALTGR:
				keycode_flag |= KEYBOARD_FLAG_RIGHTALT;
				break;
		}
	} else {
		switch (keybd->keycode) {
			case KEYBOARD_BUTTON_NUM_LOCK:
			case KEYBOARD_BUTTON_CAPS_LOCK:
				break;
			case KEYBOARD_BUTTON_LEFTCONTROL:
				keycode_flag &= ~KEYBOARD_FLAG_LEFTCTRL;
				break;
			case KEYBOARD_BUTTON_RIGHTCONTROL:
				keycode_flag &= ~KEYBOARD_FLAG_RIGHTCTRL;
				break;
			case KEYBOARD_BUTTON_LEFTSHIFT:
				keycode_flag &= ~KEYBOARD_FLAG_LEFTSHIFT;
				break;
			case KEYBOARD_BUTTON_RIGHTSHIFT:
				keycode_flag &= ~KEYBOARD_FLAG_RIGHTSHIFT;
				break;
			case KEYBOARD_BUTTON_ALT:
				keycode_flag &= ~KEYBOARD_FLAG_LEFTALT;
				break;
			case KEYBOARD_BUTTON_ALTGR:
				keycode_flag &= ~KEYBOARD_FLAG_RIGHTALT;
				break;
		}
	}

	server->window->event->type |= (EVENT_TYPE_KEYBOARD | keybd->state);
	server->window->event->keybd->flag = keycode_flag;
	server->window->event->keybd->scancode = keybd->scancode;
	server->window->event->keybd->button = keybd->button;
	server->window->event->keybd->keycode = keybd->keycode;
	server->window->event->keybd->ascii = keybd->ascii;
	server->window->event->keybd->state[keybd->keycode] = keybd->state;
	server->window->event->keybd->time = time;
}

int s_server_event_parse_mouse (s_video_input_data_mouse_t *mouse)
{
	long long time;

	time = s_gettimeofday();
	server->window->event->type |= EVENT_TYPE_MOUSE;

	if ((server->window->event->mouse->x != mouse->x) ||
	    (server->window->event->mouse->y != mouse->y)) {
	    	server->window->event->mouse->x_old = server->window->event->mouse->x;
	    	server->window->event->mouse->y_old = server->window->event->mouse->y;
		server->window->event->mouse->x = mouse->x;
		server->window->event->mouse->y = mouse->y;
		s_server_mouse_draw();
	}

	server->window->event->mouse->pbuttons = server->window->event->mouse->buttons;
	server->window->event->mouse->buttons = mouse->buttons;

        if (server->window->event->mouse->buttons > server->window->event->mouse->pbuttons) {
		server->window->event->type |= EVENT_TYPE_MOUSE_PRESSED;
		server->window->event->mouse->b = (server->window->event->mouse->buttons & ~(server->window->event->mouse->pbuttons));
		server->window->event->mouse->pb = server->window->event->mouse->b;
		server->window->event->mouse->px = server->window->event->mouse->x;
		server->window->event->mouse->py = server->window->event->mouse->y;
	} else if (server->window->event->mouse->buttons < server->window->event->mouse->pbuttons) {
		server->window->event->mouse->b = (~(server->window->event->mouse->buttons) & server->window->event->mouse->pbuttons);
		if ((server->window->event->mouse->buttons == 0) &&
		    (server->window->event->mouse->b == server->window->event->mouse->pb) &&
		    (server->window->event->mouse->x == server->window->event->mouse->px) &&
		    (server->window->event->mouse->y == server->window->event->mouse->py) &&
		    (time - server->window->event->mouse->time <= (unsigned int) 250)) {
			server->window->event->type |= (EVENT_TYPE_MOUSE_CLICKED | EVENT_TYPE_MOUSE_RELEASED);
			if (time - server->window->event->mouse->ctime <= (unsigned int) 500) {
				server->window->event->mouse->clicks++;
			} else {
				server->window->event->mouse->clicks = 1;
			}
			server->window->event->mouse->ctime = time;
		} else {
			server->window->event->type |= EVENT_TYPE_MOUSE_RELEASED;
			server->window->event->mouse->clicks = 0;
		}
	} else {
		if (server->window->event->mouse->buttons == 0) {
			server->window->event->type |= EVENT_TYPE_MOUSE_OVER;
			server->window->event->mouse->b = 0;
		} else {
			server->window->event->type |= (EVENT_TYPE_MOUSE_OVER | EVENT_TYPE_MOUSE_HINT1);
			server->window->event->mouse->b = 0;
		}
	}

	/* this is a pre-patch for wheel buttons */
	server->window->event->mouse->buttons &= ~MOUSE_MASL;

	server->window->event->mouse->time = time;

	return 0;
}

int s_event_changed_ (s_window_t *window)
{
	int r = 1;
	s_event_t *event;
	
	if (server->ph > 0) {
		/* do not parse || send any mouse or keybd event until buttons released
		 */
		if (window->event->mouse->buttons == 0) {
			server->ph = 0;
		}
//		return 0;
	}
	
	if (window->event->type & EVENT_TYPE_MOUSE) {
		if (!s_event_init(&event)) {
			event->type = window->event->type;
			memcpy(event->mouse, window->event->mouse, sizeof(s_mouse_t));
			s_event_parse_mouse(window, event);
			s_event_uninit(event);
		}
	}
	if (window->event->type & EVENT_TYPE_KEYBOARD) {
		if (!s_event_init(&event)) {
			event->type = window->event->type;
			memcpy(event->keybd, window->event->keybd, sizeof(s_keybd_t));
			r = s_event_parse_keybd(window, event);
			s_event_uninit(event);
		}
	}
	return r;
}

void s_server_event_changed (void)
{
	int id;
	int eid;
	int oid;
	int remote;

	id = server->cursor.xyid;
	oid = server->cursor.xyid_old;
	remote = server->window->event->type & EVENT_TYPE_REMOTE;
	server->window->event->type &= ~EVENT_TYPE_REMOTE;
	
	if (server->window->event->type & EVENT_TYPE_MOUSE) {
		server->window->event->type &= EVENT_TYPE_MOUSE_MASK;
		if (server->window->event->type & EVENT_TYPE_MOUSE_PRESSED) {
			if ((id != s_server_pri_id(0)) && (id >= 0) && (id < S_CLIENTS_MAX) && (!server->mh)) {
				if (server->window->event->mouse->b == server->window->event->mouse->buttons) {
					server->ph = 1;
					s_server_pri_set(SURFACE_FOCUS, id);
//					return;
				}
			}
		}
	} else if (server->window->event->type & EVENT_TYPE_KEYBOARD) {
		server->window->event->type &= EVENT_TYPE_KEYBOARD_MASK;
		if (server->window->event->mouse->buttons > 0) {
			return;
		}
	} else {
		return;
	}

	if (s_event_changed_(server->window)) {
		if (server->window->event->type & EVENT_TYPE_MOUSE) {
			if (server->window->event->type & EVENT_TYPE_MOUSE_PRESSED) {
				if ((server->window->event->mouse->b == 4) &&
				    (server->window->event->keybd->flag == KEYBOARD_FLAG_LEFTALT)) {
					s_server_window_move(server->window);
					return;
				}
			}
		}
		if (server->window->event->type & EVENT_TYPE_MOUSE) {
			if (id != oid) {
				server->window->event->type |= EVENT_TYPE_MOUSE_ENTER;
				server->window->event->type &= ~EVENT_TYPE_MOUSE_EXIT;
			}
			s_server_socket_request(SOC_DATA_EVENT, id);
			server->window->event->type &= ~EVENT_TYPE_MOUSE_ENTER;
			server->window->event->type &= ~EVENT_TYPE_MOUSE_EXIT;
			for (eid = 0; eid < S_CLIENTS_MAX; eid++) {
				if (eid != id &&
				    server->client[eid].type & WINDOW_TYPE_INPUT) {
					s_server_socket_request(SOC_DATA_EVENT, eid);
				}
			}
			if (id != oid) {
				server->window->event->type &= ~EVENT_TYPE_MOUSE_ENTER;
				server->window->event->type |= EVENT_TYPE_MOUSE_EXIT;
				s_server_socket_request(SOC_DATA_EVENT, oid);
			}
		} else if (server->window->event->type & EVENT_TYPE_KEYBOARD) {
			if (remote) {
				id = s_server_pri_id(1);
			} else {
				id = s_server_pri_id(0);
			}
			if (id >= 0) {
				s_server_socket_request(SOC_DATA_EVENT, id);
			}
			for (eid = 0; eid < S_CLIENTS_MAX; eid++) {
				if (eid != id &&
				    server->client[eid].type & WINDOW_TYPE_INPUT) {
					s_server_socket_request(SOC_DATA_EVENT, eid);
				}
			}
		}
	}
}
