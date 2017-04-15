#ifndef GIF_H
#define GIF_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>
#include "point.h"

class gif {
public:
	gif(std::string _gifName, unsigned int _gifLength, point _movement, point _position,  unsigned int _framesPerMovement = 1);
	gif(const gif& orig);
	virtual ~gif();
	bool isValid();
	point getPosition();
	void drawNextImage();
	bool finishedLooping();
private:
	point position;
	bool valid;
	ALLEGRO_BITMAP** loadedImgs;	//Puntero a arreglo de punteros a bitmap
	std::string gifName;			//nombre de la carpeta que contiene al gif
	unsigned int gifLength;			//Cantidad de imagenes que forman al gif
	point movement;					//Vector que describe el movimiento
	unsigned int framesPerMovement;	//Cantidad de frames que deben pasar entre cada desplazamiento
	unsigned int frameCounter;		//Contador de frames
	bool looping;					//indica si debe loopear el gif o no.
};

#endif /* GIF_H */

