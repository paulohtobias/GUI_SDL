#ifndef HBOX_H
#define HBOX_H

#include "container.h"

typedef Container HBox;

HBox newHBox(SDL_Rect region);

void hbox_add_widget(HBox hbox, Widget widget);

#endif // HBOX_H