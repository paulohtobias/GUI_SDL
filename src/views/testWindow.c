#include "views/testWindow.h"

char *ss(char *str, int f){
	int i, t = strlen(str);
	char *s = malloc(f+1);
	for(i=0; i<t && i<f; i++){s[i] = str[i];}
	s[i] = '\0';
	return s;
}

void mainGUITest4(Window *window, int argc, char *argv[]){

	Text txt = newText("texto", region_position(0,0));
	window_add_text(window, txt, 0);

	char *text = malloc(500);
	char *composition;
	Sint32 cursor;
	Sint32 selection_len;

	window->quit_requested = 0;
	while(!window->quit_requested){
		window->backgroundColor = COLOR_WHITE;

		SDL_PollEvent(&window->event);
		window_processEvents(window);
        if(window->event.type == SDL_QUIT){
            window->quit_requested = 1;
        }
        if(window->event.type == SDL_KEYDOWN){
			printf("NAO\n");
            if(window->event.key.keysym.sym == SDLK_x){
                window->quit_requested = 1;
            }
			if(window->event.key.keysym.sym == SDLK_l){
				//SDL_StartTextInput();printf("Sim\n");
            }
			if(window->event.key.keysym.sym == SDLK_BACKSPACE){
				int t = strlen(txt->content);
				if(t>1){
					text_setText( txt, ss(txt->content, t-1) );
				}
            }
        }
        if(window->event.type == SDL_TEXTINPUT){
			strcat(txt->content, window->event.text.text);
			text_setText(txt, txt->content);
			//printf("TEXT: %s\n", window->event.text.text);
		}
		if(window->event.type == SDL_TEXTEDITING){
			composition = window->event.edit.text;
            cursor = window->event.edit.start;
            selection_len = window->event.edit.length;
			printf("com: <%s>\n", composition);
			printf("cursor: %d\n", cursor);
			printf("sel_len: %d\n\n", selection_len);
		}
        camera_move(window->camera);

        window_draw(window);
	}
	window_emptyList(window);
}

void mainGUITest3(Window *window, int argc, char *argv[]){
	SDL_Color c1 = COLOR_BLUE;
	SDL_Color c2 = COLOR_GREEN;

	Square sqr2 = newSquare(c2, region_position(0,0));
	window_add_square(window, sqr2, 0);

	Text txt;
	txt = newText("Um Texto gránde.", region_position(0, 0));
	window_add_text(window, txt, 0);
	text_setFont(txt, NULL, 36);

	TTF_Font *font = TTF_OpenFont(txt->font, txt->txt_size);
	if(TTF_FontFaceIsFixedWidth(font))
		printf("The font is fixed width.\n");
	else
		printf("The font is not fixed width.\n");
	int i,tam = strlen(txt->content);

	Square sqr[tam];
	for(i=0; i<tam; i++){
		sqr[i] = newSquare((i%2)?c1:c2, region_area(0,0,0,0));
		window_add_square(window, sqr[i], 0);
	}

	int minx,maxx,miny,maxy,advance, x0 = text_getBounds(txt).x, y0 = bounds_reachY(txt->region);

	int xi=0, xf;
	int is=0;

	printf("TAM: %d\n", tam);

	for(i=0; i<tam; i++){
		/*TTF_GlyphMetrics(font,txt->content[i],&minx,&maxx,&miny,&maxy,&advance);
		if(i==0){
			square_setBounds(sqr2, region_area(0, miny, advance, maxy));
		}
		printf("%c\n", txt->content[i]);
		printf("  minx    : %3d | %d\n",minx, minx + is);
		printf("  maxx    : %3d | %d\n",maxx, maxx + is);
		printf("  advance : %3d | %d\n",advance, advance + is);
		xi = is;*/
		//TTF_SizeUTF8(font, ss(txt->content, i), &advance, NULL);
		//square_setBounds(sqr[i], region_area(0, 40 + 10*i, advance, 10));
		xi+=advance;
	}
	int dsa = TTF_SizeUTF8(font, "t", &xf, NULL);
	printf("SIZE: %d\n\n", xf);
	square_setBounds(sqr2, region_area(121,0, xf, 50));
	MousePos mpos;

	int paulo = 0;
    window->quit_requested = 0;
	while(!window->quit_requested){
		window->backgroundColor = COLOR_WHITE;

		SDL_PollEvent(&window->event);
		window_processEvents(window);
        if(window->event.type == SDL_QUIT){
            window->quit_requested = 1;
        }
        if(window->event.type == SDL_KEYDOWN){
            if(window->event.key.keysym.sym == SDLK_x){
                window->quit_requested = 1;
            }
			if(window->event.key.keysym.sym == SDLK_n){
				if(paulo<tam){
					TTF_SizeUTF8(font, ss(txt->content, paulo+1), &advance, NULL);
					square_setBounds(sqr[paulo], region_area(0, 40, advance, 10));
					paulo++;
				}
            }
        }
		if(window->event.type == SDL_MOUSEMOTION){
			mpos = getMousePosition();
			system("clear");printf("(%d, %d)\n", mpos.x, mpos.y);
		}
        camera_move(window->camera);

		if(text_isFocused(txt)){
			for(i=0; i<tam; i++){
				TTF_GlyphMetrics(font, txt->content[i], &minx, &maxx, &miny, &maxy, &advance);
			}
		}

        window_draw(window);
	}
	window_emptyList(window);
}

void mainGUITest2(Window *window, int argc, char *argv[]){
	//init();
	//Window *window = newWindow("Titulo da Janela", region_size(800, 600), SDL_WINDOW_MINIMIZED, 3);
	SDL_Delay(5000);

	int i, op = atoi(argv[1]);
	printf("OP: %d\n", op);

	if(op == 1){
        printf("img\n");
        int n_img=300;
        Image img[n_img];
        for(i=0; i<n_img; i++){
            img[i] = newImage("Resources/Images/test/img.png", region_position(300*i+10, 20));
            window_add_image(window, img[i], 0);
        }
	}else if(op == 2){
	    printf("sqr\n");
        int n_sqr = 100000;
        Square sqr[n_sqr];
        for(i=0; i<n_sqr; i++){
            sqr[i] = newSquare(COLOR_RED, region_area(300*i+10, 20, 300, 300));
            window_add_square(window, sqr[i], 0);
        }
	}else if(op == 3){
	    printf("frame\n");
        int n_frame = 10000;
        Frame frame[n_frame];
        for(i=0; i<n_frame; i++){
            frame[i] = newFrame(COLOR_GREEN,
								COLOR_LIGHT_BLUE, 5,
								region_area(300*i+10, 20, 300, 100));
            window_add_frame(window, frame[i], 0);
        }
    }else if(op == 4){
        printf("txt\n");
        int n_txt = 1000;
        Text txt[n_txt];
        for(i=0; i<n_txt; i++){
			char asd[20];
			sprintf(asd, "Hello %4d", i);
            txt[i] = newText(asd, region_position(100*i + 10, 20));
            window_add_text(window, txt[i], 0);
        }
    }else if(op == 5){
        printf("btn\n");
        int n_btn = 100;
        Button btn[n_btn];
        for(i=0; i<n_btn; i++){
            btn[i] = newButton("Botão", NULL, region_area(100*i+10, 500, 100, 50));
            window_add_button(window, btn[i], 0);
        }
    }

    window->quit_requested = 0;
	while(!window->quit_requested){
		window->backgroundColor = COLOR_WHITE;

		SDL_PollEvent(&window->event);
		window_processEvents(window);
        if(window->event.type == SDL_QUIT){
            window->quit_requested = 1;
        }
        if(window->event.type == SDL_KEYDOWN){
            if(window->event.key.keysym.sym == SDLK_x){
                window->quit_requested = 1;
            }
        }
        camera_move(window->camera);

        window_draw(window);
	}
	window_emptyList(window);
}

void mainGUITest(int argc, char *argv[]){
	init();
	Window *window = newWindow("Titulo da Janela", region_size(800, 600), WINDOW_DEFAULT_FLAGS, 3);

	int i, n=2;
	Image img[n];

	for(i=0; i<n; i++){
		img[i] = newImage("Resources/Images/test/img.png",
						  region_position(300*i+10, 20));
		window_add_image(window, img[i], 0);
	}
	img[0]->state.isFixed = false;
	SDL_Rect a = image_getBounds(img[0]);
	printf("(%d, %d, %d, %d)\n", a.x, a.y, a.w, a.h);

	Square sqr = newSquare(COLOR_RED, region_area(20, 20, 300, 300));
	window_add_square(window, sqr, 0);
	sqr->state.isFixed = false;

	Frame frame = newFrame(COLOR_GREEN,
							COLOR_LIGHT_BLUE, 5,
							region_area(10, 10, 310, 100));
	window_add_frame(window, frame, 0);
	frame->state.isFixed = false;

	Text txt = newText("Text teste mas é bem grande asjdhasd", region_position(20, 1000));
	text_center(txt, region_area(20, 1000, 1366, 100));
	window_add_text(window, txt, 0);

	Text txt2 = newText("Hello world!!!", region_position(300, 1100));
	text_center(txt, region_area(300, 1100, 1366, 100));
	window_add_text(window, txt2, 0);

	Button btn = newButton("Botão", NULL, region_area(700, 500, 50, 50));
	window_add_button(window, btn, 0);

	while(!window->quit_requested){
		window->backgroundColor = COLOR_WHITE;

		SDL_PollEvent(&window->event);
		window_processEvents(window);
        if(window->event.type == SDL_QUIT){
            window->quit_requested = 1;
        }
        if(window->event.type == SDL_KEYDOWN){
            if(window->event.key.keysym.sym == SDLK_x){
                window->quit_requested = 1;
            }else if(window->event.key.keysym.sym == SDLK_q){
				//image_updateBounds(window->widgets[0]->last->obj->obj_data->img, region_position(0, 40));
				//text_setWrap(txt, true);
				text_setText(txt, "Qualquer merda, muito obrigado moreira");
				text_setFont(txt, "calibri", 28);
			}else if(window->event.key.keysym.sym == SDLK_w){
				image_updateBounds(img[0], region_position(0, 40));
			}else if(window->event.key.keysym.sym == SDLK_r){
				list_remove_last(window->widgets[2]);
			}else if(window->event.key.keysym.sym == SDLK_c){
				window->backgroundColor = COLOR_YELLOW;
			}else if(window->event.key.keysym.sym == SDLK_DOWN){
				window->camera->region.y+=window->camera->movSpeed;
			}else if(window->event.key.keysym.sym == SDLK_UP){
				window->camera->region.y-=window->camera->movSpeed;
			}else if(window->event.key.keysym.sym == SDLK_RIGHT){
				window->camera->region.x+=window->camera->movSpeed;
			}else if(window->event.key.keysym.sym == SDLK_LEFT){
				window->camera->region.x-=window->camera->movSpeed;
			}else if(window->event.key.keysym.sym == SDLK_v){
				frame_updateBounds(frame, region_size(1,1));
			}
        }
		camera_move(window->camera);

		if(window->widgets[0]){
			for(i=0; i<n; i++){
				if(image_isFocused(img[i])){
					//image_updateBounds(img[i], region_position(0, -1));
					//window->backgroundColor = COLOR_PINK);
				}else if(image_isPressed(img[i])){
					//image_updateBounds(img[i], region_position(0, 1));
					window->backgroundColor = COLOR_BROWN;
				}else if(image_isReleased(img[i])){
					window->backgroundColor = COLOR_BLUE;
					//image_updateBounds(img[n-1], region_position(0, 10));
				}
				if(image_isDragged(img[i])){
					window->backgroundColor = COLOR_PURPLE;
				}
			}
			if(square_isFocused(sqr)){
				window->backgroundColor = COLOR_PINK;
			}
		}
		if(mouseOver(txt->region)){
			window->backgroundColor = COLOR_YELLOW;
		}

		window_draw(window);
	}
	/*printf("Window->layers: %d\n", window->layers);
	freeWindow(window);
	printf("Apaguei\n");*/
}
