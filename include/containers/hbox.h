#ifndef HBOX_H
#define HBOX_H

#include "container.h"

typedef Container HBox;

HBox newHBox();

void hbox_add_widget(HBox hbox, Widget widget);

void hbox_add_container(HBox hbox, Container widget);

#endif // HBOX_H