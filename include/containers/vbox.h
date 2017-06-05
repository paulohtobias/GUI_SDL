#ifndef VBOX_H
#define VBOX_H

#include "container.h"

typedef Container VBox;

VBox newVBox(SDL_Rect region);

void vbox_add_widget(VBox vbox, Widget widget);

#endif // VBOX_H