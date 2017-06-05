#ifndef VIEWS_H
#define VIEWS_H

#include "window.h"
#include "manager/library_manager.h"

//void window_main();
void view_library_select(Window *window);
void view_library(Window *window, char *libName, File *libFile);

#endif // VIEWS_H
