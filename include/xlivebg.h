/*
xlivebg - live wallpapers for the X window system
Copyright (C) 2019  John Tsiombikas <nuclear@member.fsf.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef XLIVEBG_H_
#define XLIVEBG_H_

#include <stdint.h>

/* microsecond intervals for common framerates for upd_interval */
#define XLIVEBG_NOUPD	0
#define XLIVEBG_15FPS	66666
#define XLIVEBG_20FPS	50000
#define XLIVEBG_30FPS	33333


typedef int (*xlivebg_init_func)(void*);
typedef void (*xlivebg_cleanup_func)(void*);
typedef void (*xlivebg_start_func)(long, void*);
typedef void (*xlivebg_stop_func)(void*);
typedef void (*xlivebg_draw_func)(long, void*);

struct xlivebg_image {
	int width, height;
	uint32_t *pixels;
};

struct xlivebg_screen {
	int x, y, width, height;
	int phys_width, phys_height;
	float aspect;

	struct xlivebg_image *bgimg;
	int num_bgimg;
};

struct xlivebg_plugin {
	char *name, *desc;
	long upd_interval;	/* requested update interval in microseconds */
	xlivebg_init_func init;		/* called during init, with a valid OpenGL context */
	xlivebg_cleanup_func cleanup;	/* called during shutdown (optional) */
	xlivebg_start_func start;	/* called when the plugin is activated (optional) */
	xlivebg_stop_func stop;		/* called when the plugin is deactivated (optional) */
	xlivebg_draw_func draw;		/* called to draw every frame */
	void *data, *so;
};

int xlivebg_register_plugin(struct xlivebg_plugin *plugin);

int xlivebg_screen_count(void);
struct xlivebg_screen *xlivebg_screen(int idx);



#endif	/* XLIVEBG_H_ */
