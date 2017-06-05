#include "views/views.h"

#include "library.h"

void view_library_select(Window *window){

    window_emptyList(window);

    //Container fixed = newContainer(CNT_FIXED, window_getBounds(window));
    Container fixed = newHBox(window_getBounds(window));
    //setBounds(&fixed->region, region_area(0, 0, 250, 705));
    window_add_container(window, fixed, 0);

    Text txt_title = newText("Manga Library", region_position(0, 0));
    text_setFont(txt_title, default_text_font, 30);
    container_add_text(fixed, txt_title);
    //text_center(txt_title, region_area(0,0,window_getBounds(window).w, text_getBounds(txt_title).h));

    int libCount = 0;
    File **libraries = dir_getFileList("./Data", ".*\\.txt", &libCount);
    if(libraries == NULL){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "There are no libraries to load", NULL);
        exit(1);
    }

    int i=0, width = manga_cover_width, height =  manga_cover_height;
    Library lib[libCount];
    Image img_lib[libCount];
    Text txt_lib[libCount];

    srand((unsigned) time(NULL));
    lib[i] = library_load(libraries[i]->name);
    img_lib[i] = newImage(lib[i]->manga[rand()%lib[i]->mangas]->cover, region_area(0,0,width,height));
    container_add_image(fixed, img_lib[i]);
    /*image_setBounds(
        img_lib[i],
        get_widgetFit_position(
            text_getBounds(txt_title),
            image_getBounds(img_lib[i]),
            WIDGET_FIT_DOWN,
            0,
            50,
            50
        )
    );*/
    txt_lib[i] = newText(lib[i]->name, region_position(0,0));
    container_add_text(fixed, txt_lib[i]);
    /*text_center(
        txt_lib[i],
        region_area(
            image_getBounds(img_lib[i]).x,
            region_reachY(image_getBounds(img_lib[i])),
            image_getBounds(img_lib[i]).w,
            text_getBounds(txt_lib[i]).h
        )
    );*/

    for(i=1; i<libCount; i++){
        lib[i] = library_load(libraries[i]->name);
        img_lib[i] = newImage(lib[i]->manga[rand()%lib[i]->mangas]->cover, region_area(0,0,width,height));
        container_add_image(fixed, img_lib[i]);
        /*image_setBounds(
            img_lib[i],
            get_widgetFit_position(
                image_getBounds(img_lib[i-1]),
                image_getBounds(img_lib[i]),
                container_getBounds(fixed).w,
                50,
                50,
                50
            )
        );*/
        txt_lib[i] = newText(lib[i]->name, region_position(0,0));
        container_add_text(fixed, txt_lib[i]);
        /*text_center(
            txt_lib[i],
            region_area(
                image_getBounds(img_lib[i]).x,
                region_reachY(image_getBounds(img_lib[i])),
                image_getBounds(img_lib[i]).w,
                text_getBounds(txt_lib[i]).h
            )
        );*/
        freeLibrary(lib[i]);
        lib[i] = NULL;
    }

    printf("(%d, %d, %d, %d)\n", window_getBounds(window).x, window_getBounds(window).y, window_getBounds(window).w, window_getBounds(window).h);

    int l=0, k=0;

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
                    case SDLK_l:
                        container_setBounds(fixed, region_position(l++, k));
                        break;
                    case SDLK_k:
                        container_setBounds(fixed, region_position(l, k++));
                        break;
				}
            }

            for(i=0; i<libCount; i++){
                if( image_isReleased(img_lib[i]) ){
                    view_library(window, NULL, libraries[i]);
                }
            }

            window_draw(window);
		}
	}
	exit(0);
}
