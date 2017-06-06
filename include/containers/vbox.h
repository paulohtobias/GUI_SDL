#ifndef VBOX_H
#define VBOX_H

#include "container.h"

typedef Container VBox;

VBox newVBox();

void vbox_add_widget(VBox vbox, Widget widget);

void vbox_add_container(VBox vbox, Container widget);

#endif // VBOX_H