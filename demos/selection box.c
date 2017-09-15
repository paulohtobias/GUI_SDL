#include "gui.h"

#define printR(c) SDL_Rect r = c; printf("(%d, %d, %d, %d)\n", r.x, r.y, r.w, r.h);

int main(int argc, char *argv[]){
	Window *window = new_Window("selection", new_rect(0, 0, 800, 600), WINDOW_DEFAULT_FLAGS);
	
	Container c = new_Container_max_widgets(2);
    window_add_container(window, &c);
    
    Image bg = new_Image_with_bounds("Resources/Images/bg.jpg", container_get_bounds_origin(&c));
    container_add_widget(&c, &bg);

    Color rec_color = COLOR_RGBA(51, 173, 255, 64);
    Position grpos = new_Position(0, 0);
    Rectangle rec = new_Rectangle(window->background_color);
    container_add_widget(&c, &rec);

	while(!window->quit_requested){
		if(SDL_WaitEvent(&window->event)){
			window_process_events(window);
            
            if(window->event.type == SDL_MOUSEBUTTONDOWN){
                set_position_origin(&rec.widget.bounds, mouse_get_position());
                grpos = get_position_origin(rec.widget.bounds);
                
                set_size(&rec.widget.bounds, new_Size(1, 1));
                rec.widget.style->background_color = rec_color;
                rec.functions->set_changed(&rec, true);
            }else if(mouse_is_pressed(window->mouse)){
                Position mpos = mouse_get_position();
                Position rpos = grpos;
                Size offset = new_Size(mpos.x - rpos.x, mpos.y - rpos.y);
                if(offset.w < 0){
                    rpos.x = mpos.x;
                    offset.w = grpos.x - rpos.x;
                }
                if(offset.h < 0){
                    rpos.y = mpos.y;
                    offset.h = grpos.y - rpos.y;
                }

                set_position_origin(&rec.widget.bounds, rpos);
                set_size(&rec.widget.bounds, offset);
                rec.functions->set_changed(&rec, true);
            }
            if(window->event.type == SDL_MOUSEBUTTONUP){
                //window->background_color = COLOR_GREY(240);
                rec.widget.style->background_color = COLOR_RGBA(0, 0, 0, 0);
                rec.functions->set_changed(&rec, true);
            }
			
			window_draw(window);
		}else{
			printf("%s\n", SDL_GetError());
			return 1;
		}
	}
	return 0;
}

