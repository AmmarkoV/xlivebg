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
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <dlfcn.h>
#include "app.h"
#include "plugin.h"


int app_init(int argc, char **argv)
{
	int i, num_plugins;

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	init_plugins();

	num_plugins = get_plugin_count();
	for(i=0; i<num_plugins; i++) {
		struct xlivebg_plugin *plugin = get_plugin(i);

		if(plugin->init && plugin->init(plugin->data) == -1) {
			fprintf(stderr, "xlivebg: plugin %s failed to initialize\n", plugin->name);
			remove_plugin(i--);
			continue;
		}

		if(!get_active_plugin()) {
			activate_plugin(plugin);
		}
	}


	return 0;
}

void app_cleanup(void)
{
	int i, num_plugins;

	num_plugins = get_plugin_count();
	for(i=0; i<num_plugins; i++) {
		struct xlivebg_plugin *plugin = get_plugin(i);
		void *so = plugin->so;

		if(plugin->cleanup) {
			plugin->cleanup(plugin->data);
		}

		dlclose(so);
	}
}

void app_draw(void)
{
	struct xlivebg_plugin *plugin = get_active_plugin();

	if(plugin) {
		plugin->draw(msec, plugin->data);
	} else {
		glClearColor(0.2, 0.1, 0.1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void app_reshape(int x, int y)
{
	scr_width = x;
	scr_height = y;
}

void app_keyboard(int key, int pressed)
{
	switch(key) {
	case 27:
		app_quit();
		break;
	}
}
