#include "views/testWindow.h"
#include "containers/vbox.h"

void view_test_container(){
    init();
    SDL_Rect r;
	SDL_GetDisplayBounds(0, &r);
    Window *window = newWindow("Test Container", r, WINDOW_DEFAULT_FLAGS, 1);

    VBox vbox = newVBox(window_getBounds(window));
    //window_add_container(window, vbox, 0);

    Container fixed = newContainer(CNT_FIXED, window_getBounds(window));
    window_add_container(window, fixed, 0);

    Text txt1 = newText("Texto 1", region_position(0,0));
    //vbox->add_widget(vbox, txt1);
    fixed->add_widget(fixed, txt1);

    while(!window->quit_requested){

		if(SDL_PollEvent(&window->event)){
            window_processEvents(window);
            if(window->event.type == SDL_KEYDOWN){
				switch(window->event.key.keysym.sym){
					case SDLK_x:
						window->quit_requested = 1;
						break;
				}
            }

            window_draw(window);
		}
    }
}