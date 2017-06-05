/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Frame Chapter
 * Frame Chapter library using SDL2
 */

#include "widgets/frameChapter.h"

FrameChapter newFrameChapter(Manga manga, SDL_Rect bounds){
	FrameChapter frameC = malloc(sizeof(struct FrameChapter_));

	frameC->frame = newFrame(
        default_frameChapter_frame_color,
        default_frameChapter_border_color,
        default_frameChapter_border_size,
        bounds
    );

    frameC->contentArea = newSquare(
        default_frameChapter_contentFrame_color,
        region_area(
            bounds.x,
            bounds.y + default_frameChapter_contentFrame_height,
            bounds.w,
            bounds.h - default_frameChapter_contentFrame_height - 25
        )
    );

    frameC->titleSize = default_frameChapter_title_size;
    frameC->textSize = default_frameChapter_text_size;
    frameC->textColor = default_frameChapter_text_color;
    frameC->textFont = default_text_font;

    //Seting the Manga data
    //Title
    frameC->title = newText(
        manga->title,
        region_position(bounds.x + default_frameChapter_padding,
                        bounds.y + default_frameChapter_padding)
    );

    //Cover
    frameC->cover = newImage(
        manga->cover,
        region_position(
            bounds.x + default_frameChapter_padding,
            region_reachY(text_getBounds(frameC->title)) + 3
        )
    );
    frameC->coverBorder = newSquare(
        default_frameChapter_coverBorder_color,
        region_position(
            image_getBounds(frameC->cover).x - 3,
            image_getBounds(frameC->cover).y - 3
        )
    );

    //Author
    frameC->staticAuthor = newText("Author: ", region_position(0,0));
    frameC->author = newText(manga->author, region_position(0,0));

    //Pages
    frameC->staticPages = newText("Pages: ", region_position(0,0));
    frameC->pages = newText("0", region_position(0,0));

    //Socre
    frameC->staticScore = newText("Score: ", region_position(0,0));
    frameC->score = newText("0", region_position(0,0));

    //Date
    frameC->staticDate = newText("Date: ", region_position(0,0));
    frameC->date = newText(time_show(manga->date), region_position(0,0));

    //Tags
    frameC->staticTags = newText("Tags: ", region_position(0,0));
    frameC->tags = NULL;
    frameC->tagCount = manga->tags;
    if(frameC->tagCount > 0){
        int i;
        frameC->tags = malloc( frameC->tagCount * sizeof(Text ) );
        for(i=0; i<frameC->tagCount; i++){
            frameC->tags[i] = newText(manga->tagList[i], region_position(0,0));
        }
    }

    frameC->mangaPath = calloc(manga_titleSize, sizeof(char));
    frameChapter_setManga(frameC, manga);

    frameChapter_setTitleSize(frameC, frameC->titleSize);
    frameChapter_setTextSize(frameC, frameC->textSize);
    text_setColor(frameC->title, default_frameChapter_title_color);
    frameChapter_setTextColor(frameC, frameC->textColor);

	resetBounds(&frameC->region, bounds);
	//frameChapter_setBounds(frameC, bounds);
	frameC->state = newWidgetState();
	return frameC;
}
void init_frameChapter(FrameChapter frameC, SDL_Renderer *renderer){
	init_text(frameC->title, renderer);
	init_image(frameC->cover, renderer);
	init_text(frameC->staticAuthor, renderer);
	init_text(frameC->author, renderer);
	init_text(frameC->staticPages, renderer);
	init_text(frameC->pages, renderer);
	init_text(frameC->staticScore, renderer);
	init_text(frameC->score, renderer);
	init_text(frameC->staticDate, renderer);
	init_text(frameC->date, renderer);
	init_text(frameC->staticTags, renderer);
	int i;
	for(i=0; i < frameC->tagCount; i++)
        init_text(frameC->tags[i], renderer);
    frameChapter_setBounds(frameC, frameChapter_getBounds(frameC));
}
void freeFrameChapter(FrameChapter frameC){
	freeFrame(frameC->frame);
	freeSquare(frameC->contentArea);
	freeText(frameC->title);
	freeSquare(frameC->coverBorder);
	freeImage(frameC->cover);
	freeText(frameC->staticAuthor);
	freeText(frameC->author);
	freeText(frameC->staticPages);
	freeText(frameC->pages);
	freeText(frameC->staticScore);
	freeText(frameC->score);
	freeText(frameC->staticDate);
	freeText(frameC->date);
	freeText(frameC->staticTags);
	int i;
	for(i=0; i < frameC->tagCount; i++)
        freeText(frameC->tags[i]);
    free(frameC->tags);

	free(frameC);
}

//Get
SDL_Color frameChapter_gettextColor(FrameChapter frameC){
	return frameC->textColor;
}
SDL_Rect frameChapter_getBounds(FrameChapter frameC){
	return getBounds(frameC->region);
}

//Set and Update
void frameChapter_setTitleSize(FrameChapter frameC, int size){
    text_setFont(frameC->title, frameC->textFont, size);
}
void frameChapter_setTextSize(FrameChapter frameC, int size){
    text_setFont(frameC->staticAuthor, frameC->textFont, size);
    text_setFont(frameC->author, frameC->textFont, size);
    text_setFont(frameC->staticPages, frameC->textFont, size);
    text_setFont(frameC->pages, frameC->textFont, size);
    text_setFont(frameC->staticScore, frameC->textFont, size);
    text_setFont(frameC->score, frameC->textFont, size);
    text_setFont(frameC->staticDate, frameC->textFont, size);
    text_setFont(frameC->date, frameC->textFont, size);
    text_setFont(frameC->staticTags, frameC->textFont, size);
    int i;
    for(i=0; i<frameC->tagCount; i++){
        text_setFont(frameC->tags[i], frameC->textFont, size);
    }
}
void frameChapter_setTextFont(FrameChapter frameC, char *font){
    frameC->textFont = font;

    //Tile
    text_setFont(frameC->title, font, frameC->textSize);
    //text_bold(frameC->title);

    //Author
    text_setFont(frameC->staticAuthor, font, frameC->textSize);
    //text_bold(frameC->staticAuthor);
    text_setFont(frameC->author, font, frameC->textSize);

    //Pages
    text_setFont(frameC->staticPages, font, frameC->textSize);
    //text_bold(frameC->staticPages);
    text_setFont(frameC->pages, font, frameC->textSize);

    //Score
    text_setFont(frameC->staticScore, font, frameC->textSize);
    //text_bold(frameC->staticScore);
    text_setFont(frameC->score, font, frameC->textSize);

    //Date
    text_setFont(frameC->staticDate, font, frameC->textSize);
    //text_bold(frameC->staticDate);
    text_setFont(frameC->date, font, frameC->textSize);

    //Tags
    text_setFont(frameC->staticTags, font, frameC->textSize);
    //text_bold(frameC->staticTags);

    int i;
    for(i=0; i<frameC->tagCount; i++){
        text_setFont(frameC->tags[i], font, frameC->textSize);
    }
}
void frameChapter_setTextColor(FrameChapter frameC, SDL_Color textColor){
	frameC->textColor = textColor;
    text_setColor(frameC->staticAuthor, textColor);
    text_setColor(frameC->author, textColor);
    text_setColor(frameC->staticPages, textColor);
    text_setColor(frameC->pages, textColor);
    text_setColor(frameC->staticScore, textColor);
    text_setColor(frameC->score, textColor);
    text_setColor(frameC->staticDate, textColor);
    text_setColor(frameC->date, textColor);
    text_setColor(frameC->staticTags, textColor);
    int i;
    for(i=0; i<frameC->tagCount; i++){
        text_setColor(frameC->tags[i], textColor);
    }
}
void frameChapter_setBounds(FrameChapter frameC, SDL_Rect region){
	setBounds(&frameC->region, region);

	frame_setBounds(frameC->frame, region);
	square_setBounds(
        frameC->contentArea,
        region_area(
            region.x,
            region.y + default_frameChapter_contentFrame_height,
            region.w,
            region.h - default_frameChapter_contentFrame_height - 25
        )
    );

    //Title
	text_setBounds(
        frameC->title,
        region_position(region.x + default_frameChapter_padding,
                        region.y + default_frameChapter_padding)
    );
    text_setWrap(frameC->title, true);
    text_center(
        frameC->title,
        region_area(
            region.x,
            region.y,
            region.w,
            square_getBounds(frameC->contentArea).y - region.y
        )
    );

    //Cover
    image_setBounds(
        frameC->cover,
        region_area(
            square_getBounds(frameC->contentArea).x + default_frameChapter_padding,
            square_getBounds(frameC->contentArea).y + default_frameChapter_padding,
			200,
			300
        )
    );
    square_setBounds(
        frameC->coverBorder,
        region_area(
            image_getBounds(frameC->cover).x - 3,
            image_getBounds(frameC->cover).y - 3,
            image_getBounds(frameC->cover).w + 6,
            image_getBounds(frameC->cover).h + 6
        )
    );
    int cover_margin_left = 5;
    int cover_margin_bottom = 3;

    //Author
    text_setBounds(
        frameC->staticAuthor,
        get_widgetFit_position(
            image_getBounds(frameC->cover),
            text_getBounds(frameC->staticAuthor),
            region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
            cover_margin_left,
            cover_margin_bottom,
            image_getBounds(frameC->cover).x
        )
    );
    //printf("\ncover (%d, %d, %d, %d)\n", image_getBounds(frameC->cover).x, image_getBounds(frameC->cover).y, image_getBounds(frameC->cover).w, image_getBounds(frameC->cover).h);
    //printf("static Author: (%d, %d. %d, %d)\n", text_getBounds(frameC->staticAuthor).x, text_getBounds(frameC->staticAuthor).y, text_getBounds(frameC->staticAuthor).w, text_getBounds(frameC->staticAuthor).h);
    text_setBounds(
        frameC->author,
        get_widgetFit_position(
            text_getBounds(frameC->staticAuthor),
            text_getBounds(frameC->author),
            region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
            0,
            0,
            text_getBounds(frameC->staticAuthor).x
        )
    );
    //printf("author: (%d, %d. %d, %d)\n", text_getBounds(frameC->author).x, text_getBounds(frameC->author).y, text_getBounds(frameC->author).w, text_getBounds(frameC->author).h);

    //Pages
    text_setBounds(
        frameC->staticPages,
        get_widgetFit_position(
            text_getBounds(frameC->author),
            text_getBounds(frameC->staticPages),
            WIDGET_FIT_DOWN,
            0,
            3,
            text_getBounds(frameC->staticAuthor).x
        )
    );
    text_setBounds(
        frameC->pages,
        get_widgetFit_position(
            text_getBounds(frameC->staticPages),
            text_getBounds(frameC->pages),
            region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
            0,
            0,
            text_getBounds(frameC->staticPages).x
        )
    );

    //Score
    text_setBounds(
        frameC->staticScore,
        get_widgetFit_position(
            text_getBounds(frameC->pages),
            text_getBounds(frameC->staticScore),
            WIDGET_FIT_DOWN,
            0,
            3,
            text_getBounds(frameC->staticPages).x
        )
    );
    text_setBounds(
        frameC->score,
        get_widgetFit_position(
            text_getBounds(frameC->staticScore),
            text_getBounds(frameC->score),
            region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
            0,
            0,
            text_getBounds(frameC->staticScore).x
        )
    );

    //Date
    text_setBounds(
        frameC->staticDate,
        get_widgetFit_position(
            text_getBounds(frameC->score),
            text_getBounds(frameC->staticDate),
            WIDGET_FIT_DOWN,
            0,
            3,
            text_getBounds(frameC->staticScore).x
        )
    );
    text_setBounds(
        frameC->date,
        get_widgetFit_position(
            text_getBounds(frameC->staticDate),
            text_getBounds(frameC->date),
            region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
            0,
            0,
            text_getBounds(frameC->staticDate).x
        )
    );

    //Tags
    text_setBounds(
        frameC->staticTags,
        get_widgetFit_position(
            text_getBounds(frameC->date),
            text_getBounds(frameC->staticTags),
            WIDGET_FIT_DOWN,
            0,
            3,
            text_getBounds(frameC->staticDate).x
        )
    );
    if(frameC->tags != NULL){
        text_setBounds(
            frameC->tags[0],
            get_widgetFit_position(
                text_getBounds(frameC->staticTags),
                text_getBounds(frameC->tags[0]),
                region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
                0,
                0,
                text_getBounds(frameC->staticTags).x
            )
        );
        int i;
        for(i=1; frameC->tags[i] != NULL; i++){
            text_setBounds(
                frameC->tags[i],
                get_widgetFit_position(
                    text_getBounds(frameC->tags[i-1]),
                    text_getBounds(frameC->tags[i]),
                    region_reachX(region) - (frameC->frame->borderSize + default_frameChapter_padding),
                    0,
                    0,
                    text_getBounds(frameC->staticTags).x
                )
            );
        }
    }
}
void frameChapter_updateBounds(FrameChapter frameC, SDL_Rect region){
	updateBounds(&frameC->region, region);
	frameChapter_setBounds(frameC, frameChapter_getBounds(frameC));
}
void frameChapter_setManga(FrameChapter frameC, Manga manga){
    strcpy(frameC->mangaPath, manga->path);
    int i;
    char inttostr[11];
    text_setText(frameC->title, manga->title);
    image_setSrc(frameC->cover, manga->cover);
    text_setText(frameC->author, manga->author);
    sprintf(inttostr, "%d", manga->pages);
    text_setText(frameC->pages, inttostr);
    sprintf(inttostr, "%d", manga->score);
    text_setText(frameC->score, inttostr);

    frameC->tagCount = manga->tags;
    if(frameC->tagCount > 0){
        /*realloc(frameC->tags, manga->tags * sizeof(Text ));
        printf("m.2 ");
        for(i=0; i<manga_max_tags; i++){
            if(i < frameC->tagCount){
                text_setText(frameC->tags[i], manga->tagList[i]);
            }else{
                frameC->tags[i] = newText(manga->tagList[i], )
            }
        }*/
    }
}

//Events
void frameChapter_processEvents(SDL_Event event, Mouse mouseState, FrameChapter frameC){
	basic_widget_processEvents(event, mouseState, &frameC->state, frameC->region);
	if(frameChapter_isDragged(frameC)){
		frameChapter_updateBounds(frameC, widget_dragPosition(mouseState));
	}
	//Processing Title and Cover events
	basic_widget_processEvents(event, mouseState, &frameC->title->state, frameC->title->region);
	basic_widget_processEvents(event, mouseState, &frameC->cover->state, frameC->cover->region);
	if(text_isReleased(frameC->title) || image_isReleased(frameC->cover)){
        //printf("abre\n");
        //SDL_CreateThread(open_manga, "Open_Manga", (void*)frameC->mangaPath);
	}
}
bool frameChapter_isFocused(FrameChapter frameC){
	return widget_isFocused(frameC->state);
}
bool frameChapter_isPressed(FrameChapter frameC){
	return widget_isPressed(frameC->state);
}
bool frameChapter_isReleased(FrameChapter frameC){
	return widget_isReleased(frameC->state);
}
bool frameChapter_isDragged(FrameChapter frameC){
	return widget_isDragged(frameC->state);
}
int open_manga(void *mangaPath){
	#ifndef _WIN32
		char linuxOpen[strlen((char*)mangaPath) + 10];
		sprintf(linuxOpen, "xdg-open %s", (char*)mangaPath);
		system(linuxOpen);
	#else
    	system((char*)mangaPath);
	#endif //_WIN32
    return 1;
}

//Render
void renderFrameChapter(FrameChapter frameC, SDL_Renderer *renderer, Camera camera){
	camera_updateWidgetPosition(camera, &frameC->region);

    //Frame
    renderFrame(frameC->frame, renderer, camera);
    renderSquare(frameC->contentArea, renderer, camera);

    //Title and Cover
    renderText(frameC->title, renderer, camera);
    renderSquare(frameC->coverBorder, renderer, camera);
    renderImage(frameC->cover, renderer, camera);

    //Author
    renderText(frameC->staticAuthor, renderer, camera);
    renderText(frameC->author, renderer, camera);

    //Pages
    renderText(frameC->staticPages, renderer, camera);
    renderText(frameC->pages, renderer, camera);

    //Score
    renderText(frameC->staticScore, renderer, camera);
    renderText(frameC->score, renderer, camera);

    //Date
    renderText(frameC->staticDate, renderer, camera);
    renderText(frameC->date, renderer, camera);

    //Tags
    renderText(frameC->staticTags, renderer, camera);
    int i;
    for(i=0; i<frameC->tagCount; i++){
        renderText(frameC->tags[i], renderer, camera);
    }
}
