#include "views/views.h"

void view_library(Window *window, char *libName, File *libFile){
    if(libName == NULL){
        if(libFile != NULL){
            libName = libFile->name;
        }else{
            printf("There's no library to load\n");
            return;
        }
    }
    Library lib = library_load(libName);
    if(lib == NULL){
        return;
    }
    int i=0, n=lib->mangas;
	//n = 10;

    window_emptyList(window);

    Container fixed = newContainer(CNT_FIXED, window_getBounds(window));
    //setBounds(&fixed->region, region_area(0, 0, 1100, 705));
    window_add_container(window, fixed, 0);

    //Loading bar
    int lb_w = window_getBounds(window).w / n;
    Square loading_bar = newSquare(COLOR_GREEN, region_area(0,0,lb_w,2));
    container_add_square(fixed, loading_bar);
    window_draw(window);

    //Library Name
    Text txtLib = newText(lib->name, region_position(5,5));
    text_setFont(txtLib, default_text_font, 36);
    container_add_text(fixed, txtLib);
    text_center(
        txtLib,
        region_area(
            0,
            0,
            container_getBounds(fixed).w,
            text_getBounds(txtLib).h + 10
        )
    );
    window_draw(window);

    //Home Button
    Button btnHome = newButton("Home", NULL, region_area(10, 10, 70, text_getBounds(txtLib).h));
    container_add_button(fixed, btnHome);
    window_draw(window);

    //Frame info
    int maxX = container_getBounds(fixed).w;
    int frame_line_count = 3;
    int frameW = (maxX/frame_line_count)-(4*frame_line_count);
    while(frame_line_count > 1 && frameW < manga_cover_width){
        frame_line_count--;
        frameW = maxX/frame_line_count-(4*frame_line_count);
    }
    int frameH = 450;
    if(frameW < manga_cover_width * 1.5){
        frameH = 750;
    }
    SDL_Rect frameSize = region_size(frameW, frameH);

    FrameChapter *frameC = malloc( n * sizeof(FrameChapter ) );
    frameC[0] = newFrameChapter(
        lib->manga[0],
        get_widgetFit_position(
            text_getBounds(txtLib),
            frameSize,
            WIDGET_FIT_DOWN,
            0,
            10,
            5
        )
    );
    container_add_frameChapter(fixed, frameC[0]);
    square_updateBounds(loading_bar, region_size(lb_w, 0));
    window_draw(window);

    for(i=1; i<n; i++){
        frameC[i] = newFrameChapter(
            lib->manga[i],
            get_widgetFit_position(
                frameChapter_getBounds(frameC[i-1]),
                frameSize,
                maxX,
                13,
                13,
                5
            )
        );
        container_add_frameChapter(fixed, frameC[i]);
        square_updateBounds(loading_bar, region_size(lb_w, 0));
        window_draw(window);
    }
    square_updateBounds(loading_bar, region_size(window_getBounds(window).w, 0));
    window_draw(window);

    freeWidget(list_remove_first(fixed->wlist));

	while(!window->quit_requested){

		if(SDL_PollEvent(&window->event)){
            window_processEvents(window);
            if(window->event.type == SDL_QUIT){
                window->quit_requested = 1;
            }
            if(window->event.type == SDL_KEYDOWN){
				switch(window->event.key.keysym.sym){
					case SDLK_x:
						window->quit_requested = 1;
						break;
					case SDLK_p:
						frameChapter_setTextSize(frameC[0], frameC[0]->textSize+1);
						frameChapter_updateBounds(frameC[0], region_area(0,0,0,0));
						break;
					case SDLK_o:
						frameChapter_setTextSize(frameC[0], frameC[0]->textSize-1);
						frameChapter_updateBounds(frameC[0], region_area(0,0,0,0));
						break;
				}
            }
		}
		//camera_move(window->camera);

		if(frameChapter_isFocused(frameC[0])){
            frame_setBorderColor(frameC[0]->frame, COLOR_GREEN);
		}else{
		    frame_setBorderColor(frameC[0]->frame, COLOR_BLACK);
		}
		if(button_isReleased(btnHome)){
            view_library_select(window);
		}

		window_draw(window);
	}
    exit(0);
}
