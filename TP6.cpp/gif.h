#ifndef GIF_H
#define GIF_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>
#include <iostream>
#include "point.h"

class gif {
public:
	gif(std::string _gifName, unsigned int _gifLength, point _movement, point _position,  unsigned int _framesPerMovement, bool _looping);
	gif(const gif& orig);
	virtual ~gif();
	bool isValid();
	point getPosition();
	/* drawNextImg
	 * Dibuja en 
	 */
	bool updateImg();
private:
	bool valid;
	ALLEGRO_BITMAP** loadedImgs;	//Puntero a arreglo de punteros a bitmap
	unsigned int gifLength;			//Cantidad de imagenes que forman al gif
	point movement;					//Vector que describe el movimiento
	point position;					//Posicion del objeto
	unsigned int framesPerMovement;	//Cantidad de frames que deben pasar entre cada desplazamiento
	unsigned int frameCounter;		//Contador de frames
	void draw();
	void move();
	bool looping;
};

#endif /* GIF_H */

