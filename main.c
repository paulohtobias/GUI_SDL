#include "window.h"

void printb(char *str, Bounds r){
    SDL_Rect r1 = r.real;
    SDL_Rect r2 = r.relative;

    printf(str);
    printf("%d, %d, %d, %d\n", r1.x, r1.y, r1.w, r1.h);
    printf("%d, %d, %d, %d\n\n", r2.x, r2.y, r2.w, r2.h);
}

int main(){
    init();

    //Janela
    Window *window = newWindow("Janela Teste", region_size(800, 600), WINDOW_DEFAULT_FLAGS, 1);

    int i, n = 1;
    
    //Container
    Container hbox = newHBox(window_getBounds(window));
    window_add_container(window, hbox, 0);
    
    Container vbox[n];
    Image imgs[n];
    Button btns[n];
    for(i=0; i<n; i++){
        vbox[i] = newVBox();

        imgs[i] = newImage("Resources/Images/test/img.png", region_size(0,0));
        btns[i] = newButton("Me clique", NULL, region_size(100, 50));

        hbox_add_container(hbox, vbox[i]);
        printb("vbox antes\n", vbox[i]->region);

        container_add_image(vbox[i], imgs[i]);
        printb("vbox add image\n", vbox[i]->region);
        
        container_add_button(vbox[i], btns[i]);
        printb("vbox add button\n", vbox[i]->region);

        //window_add_container(window, vbox[i], 0);
    }

    //Loop principal
    while(!window->quit_requested){
        window->backgroundColor = COLOR_GREY(240);
        if(SDL_PollEvent(&window->event)){
            window_processEvents(window);

            for(i=0; i<n; i++){
                if(button_isFocused(btns[i])){
                    window->backgroundColor = COLOR_RED;
                }
            }

            window_draw(window);
        }
    }

    return 0;
}
