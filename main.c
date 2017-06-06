#include "window.h"

int main(){
    init();

    //Janela
    Window *window = newWindow("Janela Teste", region_size(800, 600), WINDOW_DEFAULT_FLAGS, 1);

    int i, n = 5;
    
    //Container
    Container hbox = newHBox(window_getBounds(window));
    window_add_container(window, hbox, 0);
    
    Container vbox[n];
    for(i=0; i<n; i++){
        //vbox[i] = newVBox()
    }

    //Widgets
    Image img = newImage("Resources/Images/test/img.png", region_size(0,0));
    Button btn = newButton("Me clique", NULL, region_size(100, 50));
    //Image imgs[n];
    //Button btns[n];

    //for(i=0)

    //Adicionando os widgets no container
    container_add_image(hbox, img);
    container_add_button(hbox, btn);

    //Loop principal
    while(!window->quit_requested){
        if(SDL_PollEvent(&window->event)){
            window_processEvents(window);
            window_draw(window);
        }
    }

    return 0;
}