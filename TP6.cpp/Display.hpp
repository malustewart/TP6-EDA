#ifndef Display_hpp
#define Display_hpp

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define BGWIDTH 1300	//ancho imagen de fondo	PARA HACER: ,conseguir los valores correctos que estos los invente
#define BGHEIGHT 800	//altura imagen de fondo

class Display
{
public:
    Display(float displayWidth = BGWIDTH, float displayHeight = BGHEIGHT);
    ~Display();
	bool isValid();
	ALLEGRO_DISPLAY* getDisplay();
	float getDisplayWidth();
	float getDisplayHeight();
	void drawBackground();
	void showChanges();
private:
	bool valid;
	ALLEGRO_DISPLAY* display;
};

#endif /* Background_hpp */
