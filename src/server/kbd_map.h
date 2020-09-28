/***************************************************************************
    begin                : Sun Feb 16 2003
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


#ifndef S_KBD_MAP_H_
#define S_KBD_MAP_H_

typedef struct s_keycode_map_s {
	char *name;
	s_keyboard_button_t code;
} s_keycode_map_t;

static s_keycode_map_t s_keycodes_map[] = {
	{"KEYBOARD_BUTTON_ESCAPE", KEYBOARD_BUTTON_ESCAPE},
	{"KEYBOARD_BUTTON_ONE", KEYBOARD_BUTTON_ONE},
	{"KEYBOARD_BUTTON_TWO", KEYBOARD_BUTTON_TWO},
	{"KEYBOARD_BUTTON_THREE", KEYBOARD_BUTTON_THREE},
	{"KEYBOARD_BUTTON_FOUR", KEYBOARD_BUTTON_FOUR},
	{"KEYBOARD_BUTTON_FIVE", KEYBOARD_BUTTON_FIVE},
	{"KEYBOARD_BUTTON_SIX", KEYBOARD_BUTTON_SIX},
	{"KEYBOARD_BUTTON_SEVEN", KEYBOARD_BUTTON_SEVEN},
	{"KEYBOARD_BUTTON_EIGHT", KEYBOARD_BUTTON_EIGHT},
	{"KEYBOARD_BUTTON_NINE", KEYBOARD_BUTTON_NINE},
	{"KEYBOARD_BUTTON_ZERO", KEYBOARD_BUTTON_ZERO},
	{"KEYBOARD_BUTTON_MINUS", KEYBOARD_BUTTON_MINUS},
	{"KEYBOARD_BUTTON_EQUAL", KEYBOARD_BUTTON_EQUAL},
	{"KEYBOARD_BUTTON_DELETE", KEYBOARD_BUTTON_DELETE},
	{"KEYBOARD_BUTTON_TAB", KEYBOARD_BUTTON_TAB},
	{"KEYBOARD_BUTTON_q", KEYBOARD_BUTTON_q},
	{"KEYBOARD_BUTTON_w", KEYBOARD_BUTTON_w},
	{"KEYBOARD_BUTTON_e", KEYBOARD_BUTTON_e},
	{"KEYBOARD_BUTTON_r", KEYBOARD_BUTTON_r},
	{"KEYBOARD_BUTTON_t", KEYBOARD_BUTTON_t},
	{"KEYBOARD_BUTTON_y", KEYBOARD_BUTTON_y},
	{"KEYBOARD_BUTTON_u", KEYBOARD_BUTTON_u},
	{"KEYBOARD_BUTTON_i", KEYBOARD_BUTTON_i},
	{"KEYBOARD_BUTTON_o", KEYBOARD_BUTTON_o},
	{"KEYBOARD_BUTTON_p", KEYBOARD_BUTTON_p},
	{"KEYBOARD_BUTTON_BRACKETLEFT", KEYBOARD_BUTTON_BRACKETLEFT},
	{"KEYBOARD_BUTTON_BRACKETRIGHT", KEYBOARD_BUTTON_BRACKETRIGHT},
	{"KEYBOARD_BUTTON_RETURN", KEYBOARD_BUTTON_RETURN},
	{"KEYBOARD_BUTTON_LEFTCONTROL", KEYBOARD_BUTTON_LEFTCONTROL},
	{"KEYBOARD_BUTTON_a", KEYBOARD_BUTTON_a},
	{"KEYBOARD_BUTTON_s", KEYBOARD_BUTTON_s},
	{"KEYBOARD_BUTTON_d", KEYBOARD_BUTTON_d},
	{"KEYBOARD_BUTTON_f", KEYBOARD_BUTTON_f},
	{"KEYBOARD_BUTTON_g", KEYBOARD_BUTTON_g},
	{"KEYBOARD_BUTTON_h", KEYBOARD_BUTTON_h},
	{"KEYBOARD_BUTTON_j", KEYBOARD_BUTTON_j},
	{"KEYBOARD_BUTTON_k", KEYBOARD_BUTTON_k},
	{"KEYBOARD_BUTTON_l", KEYBOARD_BUTTON_l},
	{"KEYBOARD_BUTTON_SEMICOLON", KEYBOARD_BUTTON_SEMICOLON},
	{"KEYBOARD_BUTTON_APOSTROPHE", KEYBOARD_BUTTON_APOSTROPHE},
	{"KEYBOARD_BUTTON_GRAVE", KEYBOARD_BUTTON_GRAVE},
	{"KEYBOARD_BUTTON_LEFTSHIFT", KEYBOARD_BUTTON_LEFTSHIFT},
	{"KEYBOARD_BUTTON_BACKSLASH", KEYBOARD_BUTTON_BACKSLASH},
	{"KEYBOARD_BUTTON_z", KEYBOARD_BUTTON_z},
	{"KEYBOARD_BUTTON_x", KEYBOARD_BUTTON_x},
	{"KEYBOARD_BUTTON_c", KEYBOARD_BUTTON_c},
	{"KEYBOARD_BUTTON_v", KEYBOARD_BUTTON_v},
	{"KEYBOARD_BUTTON_b", KEYBOARD_BUTTON_b},
	{"KEYBOARD_BUTTON_n", KEYBOARD_BUTTON_n},
	{"KEYBOARD_BUTTON_m", KEYBOARD_BUTTON_m},
	{"KEYBOARD_BUTTON_COMMA", KEYBOARD_BUTTON_COMMA},
	{"KEYBOARD_BUTTON_PERIOD", KEYBOARD_BUTTON_PERIOD},
	{"KEYBOARD_BUTTON_SLASH", KEYBOARD_BUTTON_SLASH},
	{"KEYBOARD_BUTTON_RIGHTSHIFT", KEYBOARD_BUTTON_RIGHTSHIFT},
	{"KEYBOARD_BUTTON_KP_MULTIPLY", KEYBOARD_BUTTON_KP_MULTIPLY},
	{"KEYBOARD_BUTTON_ALT", KEYBOARD_BUTTON_ALT},
	{"KEYBOARD_BUTTON_SPACE", KEYBOARD_BUTTON_SPACE},
	{"KEYBOARD_BUTTON_CAPS_LOCK", KEYBOARD_BUTTON_CAPS_LOCK},
	{"KEYBOARD_BUTTON_F1", KEYBOARD_BUTTON_F1},
	{"KEYBOARD_BUTTON_F2", KEYBOARD_BUTTON_F2},
	{"KEYBOARD_BUTTON_F3", KEYBOARD_BUTTON_F3},
	{"KEYBOARD_BUTTON_F4", KEYBOARD_BUTTON_F4},
	{"KEYBOARD_BUTTON_F5", KEYBOARD_BUTTON_F5},
	{"KEYBOARD_BUTTON_F6", KEYBOARD_BUTTON_F6},
	{"KEYBOARD_BUTTON_F7", KEYBOARD_BUTTON_F7},
	{"KEYBOARD_BUTTON_F8", KEYBOARD_BUTTON_F8},
	{"KEYBOARD_BUTTON_F9", KEYBOARD_BUTTON_F9},
	{"KEYBOARD_BUTTON_F10", KEYBOARD_BUTTON_F10},
	{"KEYBOARD_BUTTON_NUM_LOCK", KEYBOARD_BUTTON_NUM_LOCK},
	{"KEYBOARD_BUTTON_SCROLL_LOCK", KEYBOARD_BUTTON_SCROLL_LOCK},
	{"KEYBOARD_BUTTON_KP_7", KEYBOARD_BUTTON_KP_7},
	{"KEYBOARD_BUTTON_KP_8", KEYBOARD_BUTTON_KP_8},
	{"KEYBOARD_BUTTON_KP_9", KEYBOARD_BUTTON_KP_9},
	{"KEYBOARD_BUTTON_KP_SUBTRACT", KEYBOARD_BUTTON_KP_SUBTRACT},
	{"KEYBOARD_BUTTON_KP_4", KEYBOARD_BUTTON_KP_4},
	{"KEYBOARD_BUTTON_KP_5", KEYBOARD_BUTTON_KP_5},
	{"KEYBOARD_BUTTON_KP_6", KEYBOARD_BUTTON_KP_6},
	{"KEYBOARD_BUTTON_KP_ADD", KEYBOARD_BUTTON_KP_ADD},
	{"KEYBOARD_BUTTON_KP_1", KEYBOARD_BUTTON_KP_1},
	{"KEYBOARD_BUTTON_KP_2", KEYBOARD_BUTTON_KP_2},
	{"KEYBOARD_BUTTON_KP_3", KEYBOARD_BUTTON_KP_3},
	{"KEYBOARD_BUTTON_KP_0", KEYBOARD_BUTTON_KP_0},
	{"KEYBOARD_BUTTON_KP_PERIOD", KEYBOARD_BUTTON_KP_PERIOD},
	{"KEYBOARD_BUTTON_LAST_CONSOLE", KEYBOARD_BUTTON_LAST_CONSOLE},
	{"KEYBOARD_BUTTON_LESS", KEYBOARD_BUTTON_LESS},
	{"KEYBOARD_BUTTON_F11", KEYBOARD_BUTTON_F11},
	{"KEYBOARD_BUTTON_F12", KEYBOARD_BUTTON_F12},
	{"KEYBOARD_BUTTON_KP_ENTER", KEYBOARD_BUTTON_KP_ENTER},
	{"KEYBOARD_BUTTON_RIGHTCONTROL", KEYBOARD_BUTTON_RIGHTCONTROL},
	{"KEYBOARD_BUTTON_KP_DIVIDE", KEYBOARD_BUTTON_KP_DIVIDE},
	{"KEYBOARD_BUTTON_VOIDSYMBOL", KEYBOARD_BUTTON_VOIDSYMBOL},
	{"KEYBOARD_BUTTON_ALTGR", KEYBOARD_BUTTON_ALTGR},
	{"KEYBOARD_BUTTON_BREAK", KEYBOARD_BUTTON_BREAK},
	{"KEYBOARD_BUTTON_HOME", KEYBOARD_BUTTON_HOME},
	{"KEYBOARD_BUTTON_UP", KEYBOARD_BUTTON_UP},
	{"KEYBOARD_BUTTON_PAGEUP", KEYBOARD_BUTTON_PAGEUP},
	{"KEYBOARD_BUTTON_LEFT", KEYBOARD_BUTTON_LEFT},
	{"KEYBOARD_BUTTON_RIGHT", KEYBOARD_BUTTON_RIGHT},
	{"KEYBOARD_BUTTON_END", KEYBOARD_BUTTON_END},
	{"KEYBOARD_BUTTON_DOWN", KEYBOARD_BUTTON_DOWN},
	{"KEYBOARD_BUTTON_PAGEDOWN", KEYBOARD_BUTTON_PAGEDOWN},
	{"KEYBOARD_BUTTON_INSERT", KEYBOARD_BUTTON_INSERT},
	{"KEYBOARD_BUTTON_REMOVE", KEYBOARD_BUTTON_REMOVE},
	{"KEYBOARD_BUTTON_PAUSE", KEYBOARD_BUTTON_PAUSE},
	{"KEYBOARD_BUTTON_EXCLAM", KEYBOARD_BUTTON_EXCLAM},
	{"KEYBOARD_BUTTON_AT", KEYBOARD_BUTTON_AT},
	{"KEYBOARD_BUTTON_NUMBERSIGN", KEYBOARD_BUTTON_NUMBERSIGN},
	{"KEYBOARD_BUTTON_DOLLAR", KEYBOARD_BUTTON_DOLLAR},
	{"KEYBOARD_BUTTON_PERCENT", KEYBOARD_BUTTON_PERCENT},
	{"KEYBOARD_BUTTON_ASCIICIRCUM", KEYBOARD_BUTTON_ASCIICIRCUM},
	{"KEYBOARD_BUTTON_AMPERSAND", KEYBOARD_BUTTON_AMPERSAND},
	{"KEYBOARD_BUTTON_ASTERISK", KEYBOARD_BUTTON_ASTERISK},
	{"KEYBOARD_BUTTON_PARENLEFT", KEYBOARD_BUTTON_PARENLEFT},
	{"KEYBOARD_BUTTON_PARENRIGHT", KEYBOARD_BUTTON_PARENRIGHT},
	{"KEYBOARD_BUTTON_UNDERSCORE", KEYBOARD_BUTTON_UNDERSCORE},
	{"KEYBOARD_BUTTON_PLUS", KEYBOARD_BUTTON_PLUS},
	{"KEYBOARD_BUTTON_Q", KEYBOARD_BUTTON_Q},
	{"KEYBOARD_BUTTON_W", KEYBOARD_BUTTON_W},
	{"KEYBOARD_BUTTON_E", KEYBOARD_BUTTON_E},
	{"KEYBOARD_BUTTON_R", KEYBOARD_BUTTON_R},
	{"KEYBOARD_BUTTON_T", KEYBOARD_BUTTON_T},
	{"KEYBOARD_BUTTON_Y", KEYBOARD_BUTTON_Y},
	{"KEYBOARD_BUTTON_U", KEYBOARD_BUTTON_U},
	{"KEYBOARD_BUTTON_I", KEYBOARD_BUTTON_I},
	{"KEYBOARD_BUTTON_O", KEYBOARD_BUTTON_O},
	{"KEYBOARD_BUTTON_P", KEYBOARD_BUTTON_P},
	{"KEYBOARD_BUTTON_BRACELEFT", KEYBOARD_BUTTON_BRACELEFT},
	{"KEYBOARD_BUTTON_BRACERIGHT", KEYBOARD_BUTTON_BRACERIGHT},
	{"KEYBOARD_BUTTON_A", KEYBOARD_BUTTON_A},
	{"KEYBOARD_BUTTON_S", KEYBOARD_BUTTON_S},
	{"KEYBOARD_BUTTON_D", KEYBOARD_BUTTON_D},
	{"KEYBOARD_BUTTON_F", KEYBOARD_BUTTON_F},
	{"KEYBOARD_BUTTON_G", KEYBOARD_BUTTON_G},
	{"KEYBOARD_BUTTON_H", KEYBOARD_BUTTON_H},
	{"KEYBOARD_BUTTON_J", KEYBOARD_BUTTON_J},
	{"KEYBOARD_BUTTON_K", KEYBOARD_BUTTON_K},
	{"KEYBOARD_BUTTON_L", KEYBOARD_BUTTON_L},
	{"KEYBOARD_BUTTON_COLON", KEYBOARD_BUTTON_COLON},
	{"KEYBOARD_BUTTON_QUOTEDBL", KEYBOARD_BUTTON_QUOTEDBL},
	{"KEYBOARD_BUTTON_ASCIITILDE", KEYBOARD_BUTTON_ASCIITILDE},
	{"KEYBOARD_BUTTON_BAR", KEYBOARD_BUTTON_BAR},
	{"KEYBOARD_BUTTON_Z", KEYBOARD_BUTTON_Z},
	{"KEYBOARD_BUTTON_X", KEYBOARD_BUTTON_X},
	{"KEYBOARD_BUTTON_C", KEYBOARD_BUTTON_C},
	{"KEYBOARD_BUTTON_V", KEYBOARD_BUTTON_V},
	{"KEYBOARD_BUTTON_B", KEYBOARD_BUTTON_B},
	{"KEYBOARD_BUTTON_N", KEYBOARD_BUTTON_N},
	{"KEYBOARD_BUTTON_M", KEYBOARD_BUTTON_M},
	{"KEYBOARD_BUTTON_GREATER", KEYBOARD_BUTTON_GREATER},
	{"KEYBOARD_BUTTON_QUESTION", KEYBOARD_BUTTON_QUESTION},
	{"KEYBOARD_BUTTON_F13", KEYBOARD_BUTTON_F13},
	{"KEYBOARD_BUTTON_F14", KEYBOARD_BUTTON_F14},
	{"KEYBOARD_BUTTON_F15", KEYBOARD_BUTTON_F15},
	{"KEYBOARD_BUTTON_F16", KEYBOARD_BUTTON_F16},
	{"KEYBOARD_BUTTON_F17", KEYBOARD_BUTTON_F17},
	{"KEYBOARD_BUTTON_F18", KEYBOARD_BUTTON_F18},
	{"KEYBOARD_BUTTON_F19", KEYBOARD_BUTTON_F19},
	{"KEYBOARD_BUTTON_F20", KEYBOARD_BUTTON_F20},
	{"KEYBOARD_BUTTON_F21", KEYBOARD_BUTTON_F21},
	{"KEYBOARD_BUTTON_F22", KEYBOARD_BUTTON_F22},
	{"KEYBOARD_BUTTON_SHOW_MEMORY", KEYBOARD_BUTTON_SHOW_MEMORY},
	{"KEYBOARD_BUTTON_F23", KEYBOARD_BUTTON_F23},
	{"KEYBOARD_BUTTON_F24", KEYBOARD_BUTTON_F24},
	{"KEYBOARD_BUTTON_SCROLL_BACKWARD", KEYBOARD_BUTTON_SCROLL_BACKWARD},
	{"KEYBOARD_BUTTON_SCROLL_FORWARD", KEYBOARD_BUTTON_SCROLL_FORWARD},
	{"KEYBOARD_BUTTON_CURRENCY", KEYBOARD_BUTTON_CURRENCY},
	{"KEYBOARD_BUTTON_CENT", KEYBOARD_BUTTON_CENT},
	{"KEYBOARD_BUTTON_HEX_C", KEYBOARD_BUTTON_HEX_C},
	{"KEYBOARD_BUTTON_HEX_A", KEYBOARD_BUTTON_HEX_A},
	{"KEYBOARD_BUTTON_SHOW_REGISTERS", KEYBOARD_BUTTON_SHOW_REGISTERS},
	{"KEYBOARD_BUTTON_HEX_7", KEYBOARD_BUTTON_HEX_7},
	{"KEYBOARD_BUTTON_HEX_8", KEYBOARD_BUTTON_HEX_8},
	{"KEYBOARD_BUTTON_HEX_9", KEYBOARD_BUTTON_HEX_9},
	{"KEYBOARD_BUTTON_HEX_D", KEYBOARD_BUTTON_HEX_D},
	{"KEYBOARD_BUTTON_HEX_4", KEYBOARD_BUTTON_HEX_4},
	{"KEYBOARD_BUTTON_HEX_5", KEYBOARD_BUTTON_HEX_5},
	{"KEYBOARD_BUTTON_HEX_6", KEYBOARD_BUTTON_HEX_6},
	{"KEYBOARD_BUTTON_HEX_E", KEYBOARD_BUTTON_HEX_E},
	{"KEYBOARD_BUTTON_HEX_1", KEYBOARD_BUTTON_HEX_1},
	{"KEYBOARD_BUTTON_HEX_2", KEYBOARD_BUTTON_HEX_2},
	{"KEYBOARD_BUTTON_HEX_3", KEYBOARD_BUTTON_HEX_3},
	{"KEYBOARD_BUTTON_HEX_0", KEYBOARD_BUTTON_HEX_0},
	{"KEYBOARD_BUTTON_HEX_F", KEYBOARD_BUTTON_HEX_F},
	{"KEYBOARD_BUTTON_HEX_B", KEYBOARD_BUTTON_HEX_B},
	{"KEYBOARD_BUTTON_USER0", KEYBOARD_BUTTON_USER0},
	{"KEYBOARD_BUTTON_USER1", KEYBOARD_BUTTON_USER1},
	{"KEYBOARD_BUTTON_USER2", KEYBOARD_BUTTON_USER2},
	{"KEYBOARD_BUTTON_USER3", KEYBOARD_BUTTON_USER3},
	{"KEYBOARD_BUTTON_USER4", KEYBOARD_BUTTON_USER4},
	{"KEYBOARD_BUTTON_USER5", KEYBOARD_BUTTON_USER5},
	{"KEYBOARD_BUTTON_USER6", KEYBOARD_BUTTON_USER6},
	{"KEYBOARD_BUTTON_USER7", KEYBOARD_BUTTON_USER7},
	{"KEYBOARD_BUTTON_USER8", KEYBOARD_BUTTON_USER8},
	{"KEYBOARD_BUTTON_USER9", KEYBOARD_BUTTON_USER9},
	{"KEYBOARD_BUTTON_USER10", KEYBOARD_BUTTON_USER10},
	{"KEYBOARD_BUTTON_USER11", KEYBOARD_BUTTON_USER11},
	{"KEYBOARD_BUTTON_USER12", KEYBOARD_BUTTON_USER12},
	{"KEYBOARD_BUTTON_USER13", KEYBOARD_BUTTON_USER13},
	{"KEYBOARD_BUTTON_USER14", KEYBOARD_BUTTON_USER14},
	{"KEYBOARD_BUTTON_USER15", KEYBOARD_BUTTON_USER15},
	{"KEYBOARD_BUTTON_USER16", KEYBOARD_BUTTON_USER16},
	{"KEYBOARD_BUTTON_USER17", KEYBOARD_BUTTON_USER17},
	{"KEYBOARD_BUTTON_USER18", KEYBOARD_BUTTON_USER18},
	{"KEYBOARD_BUTTON_USER19", KEYBOARD_BUTTON_USER19},
	{"KEYBOARD_BUTTON_USER20", KEYBOARD_BUTTON_USER20},
	{"KEYBOARD_BUTTON_USER21", KEYBOARD_BUTTON_USER21},
	{"KEYBOARD_BUTTON_USER22", KEYBOARD_BUTTON_USER22},
	{"KEYBOARD_BUTTON_USER23", KEYBOARD_BUTTON_USER23},
	{"KEYBOARD_BUTTON_USER24", KEYBOARD_BUTTON_USER24},
	{"KEYBOARD_BUTTON_USER25", KEYBOARD_BUTTON_USER25},
	{"KEYBOARD_BUTTON_USER26", KEYBOARD_BUTTON_USER26},
	{"KEYBOARD_BUTTON_USER27", KEYBOARD_BUTTON_USER27},
	{"KEYBOARD_BUTTON_USER28", KEYBOARD_BUTTON_USER28},
	{"KEYBOARD_BUTTON_USER29", KEYBOARD_BUTTON_USER29},
	{"KEYBOARD_BUTTON_USER30", KEYBOARD_BUTTON_USER30},
	{"KEYBOARD_BUTTON_USER31", KEYBOARD_BUTTON_USER31},
	{"KEYBOARD_BUTTON_USER32", KEYBOARD_BUTTON_USER32},
	{"KEYBOARD_BUTTON_USER33", KEYBOARD_BUTTON_USER33},
	{"KEYBOARD_BUTTON_USER34", KEYBOARD_BUTTON_USER34},
	{"KEYBOARD_BUTTON_USER35", KEYBOARD_BUTTON_USER35},
	{"KEYBOARD_BUTTON_USER36", KEYBOARD_BUTTON_USER36},
	{"KEYBOARD_BUTTON_USER37", KEYBOARD_BUTTON_USER37},
	{"KEYBOARD_BUTTON_USER38", KEYBOARD_BUTTON_USER38},
	{"KEYBOARD_BUTTON_USER39", KEYBOARD_BUTTON_USER39},
	{"KEYBOARD_BUTTON_USER40", KEYBOARD_BUTTON_USER40},
	{"KEYBOARD_BUTTON_NOCODE", KEYBOARD_BUTTON_NOCODE},
	{"KEYBOARD_BUTTON_MAX", KEYBOARD_BUTTON_MAX},
};

#endif /* S_KBD_MAP_H_ */
