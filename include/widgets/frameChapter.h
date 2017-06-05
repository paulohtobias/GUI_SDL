/*
 * Paulo Henrique Tobias
 * Manga Library
 *
 * Frame Chapter
 * Frame Chapter library using SDL2
 */

#ifndef FRAMECHAPTER_H
#define FRAMECHAPTER_H

#include "manga.h"
#include "widgets/frame.h"
#include "widgets/text.h"
#include "widgets/image.h"

#define default_frameChapter_frame_color COLOR_GREY(66)
#define default_frameChapter_border_color COLOR_BLACK
#define default_frameChapter_border_size 5
#define default_frameChapter_contentFrame_height 90
#define default_frameChapter_contentFrame_color COLOR_WHITE
#define default_frameChapter_padding 10
#define default_frameChapter_title_size (default_frameChapter_contentFrame_height/3)
#define default_frameChapter_title_color COLOR_WHITE
#define default_frameChapter_coverBorder_color COLOR_GREY(31)
#define default_frameChapter_text_size 18
#define default_frameChapter_text_color COLOR_GREY(51)

struct FrameChapter_{
	Frame frame;
	Square contentArea;

	//Text info
	int titleSize;
	int textSize;
	char *textFont;
	SDL_Color textColor;

	Text title;
	Square coverBorder;
	Image cover;
	Text staticAuthor;
	Text author;
	Text staticPages;
	Text pages;
	Text staticScore;
	Text score;
	Text staticDate;
	Text date;
	Text staticTags;
	int tagCount;
	Text *tags;

	char *mangaPath;

	Bounds region;
	WidgetState state;
};
typedef struct FrameChapter_* FrameChapter;

FrameChapter newFrameChapter(Manga manga, SDL_Rect bounds);
void init_frameChapter(FrameChapter frameC, SDL_Renderer *renderer);
void freeFrameChapter(FrameChapter frameC);

//Get
Manga frameChapter_getManga(FrameChapter frameC);
SDL_Rect frameChapter_getBounds(FrameChapter frameC);

//Set and Update
void frameChapter_setTitleSize(FrameChapter frameC, int size);
void frameChapter_setTextSize(FrameChapter frameC, int size);
void frameChapter_setTextFont(FrameChapter frameC, char *font);
void frameChapter_setTextColor(FrameChapter frameC, SDL_Color textColor);
void frameChapter_setBounds(FrameChapter frameC, SDL_Rect region);
void frameChapter_updateBounds(FrameChapter frameC, SDL_Rect region);
void frameChapter_setManga(FrameChapter frameC, Manga manga);

//Events
void frameChapter_processEvents(SDL_Event event, Mouse mouseState, FrameChapter frameC);
bool frameChapter_isFocused(FrameChapter frameC);
bool frameChapter_isPressed(FrameChapter frameC);
bool frameChapter_isReleased(FrameChapter frameC);
bool frameChapter_isDragged(FrameChapter frameC);
int open_manga(void *data);

//Render
void renderFrameChapter(FrameChapter frameC, SDL_Renderer *renderer, Camera camera);

#endif //FRAMECHAPTER_H
