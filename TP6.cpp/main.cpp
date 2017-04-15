#include <cstdlib>
#include <iostream>
#include "point.h"
#include "gif.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

typedef char BYTE;

int main(int argc, char** argv) {
	
	if(!al_init()) return -1;
	if(!al_init_primitives_addon()) return -1;	//ya se que esta muy cabeza	if(!al_init_image_addon()) return -1;

	
	ALLEGRO_DISPLAY* display = al_create_display(1000, 900);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));	
	
/********************************************************
 * 
 * 
 * 
 * LO UTIL ARRANCA ACA, MAS ARRIBA ESTA TODO RE CABEZA
 * 
 * 
 ********************************************************/	
	
	BYTE animationCode; 
//	animationCode = getchar();	//getchar es para debuggear, en el posta lo leemos del paquete
	animationCode = 'B';
	
	std::string gifName;	//nombre del gif
	unsigned int gifLength;	//frames que conforman el gif
	point position;			//posicion inicial
	point mov;				//valores por los cuales se debe modificar la posicion ("vector de movimiento")
	unsigned int framesPerMovement = 1;	//cada cuantos frames se debe cambiar la posicion
	float timePerFrame;		//tiempo que dura cada frame en pantalla en segundos

	
	switch(animationCode)
	{
		case 'A':{
			gifName = "Cat Running";
			gifLength = 12;
			position.setX(0);
			position.setY(0);
			mov.setX(2);
			mov.setY(0);
			framesPerMovement = 1;
			timePerFrame = 0.1;
			break;}
		case 'B':{
			gifName = "Explosion 1";
			gifLength = 8;
			position.setX(0);
			position.setY(0);
			mov.setX(0);
			mov.setY(0);
			framesPerMovement = 1;
			timePerFrame = 0.12;
			break;}
		case 'C':{
			gifName = "Explosion 2";
			gifLength = 48;
			position.setX(0);
			position.setY(0);
			mov.setX(0);
			mov.setY(0);
			framesPerMovement = 1;
			timePerFrame = 0.1;
			break;}		
		case 'D':{
			gifName = "Homer Dance";
			gifLength = 10;
			position.setX(0);
			position.setY(0);
			mov.setX(100);
			mov.setY(0);
			framesPerMovement = 1;
			timePerFrame = 0.1;
			break;}
		case 'E':{
			gifName = "Super Mario Running";
			gifLength = 12;
			position.setX(0);
			position.setY(0);
			mov.setX(2);
			mov.setY(0);
			framesPerMovement = 1;
			timePerFrame = 0.04;
			break;}
		case 'F':{
			gifName = "Sonic Running";
			gifLength = 10;
			position.setX(0);
			position.setY(0);
			mov.setX(70);
			mov.setY(0);
			framesPerMovement = 4;
			timePerFrame = 0.06;
			break;}
		default:
#warning sacar este return horripilante
			cout << "Error: codigo de gif incorrecto" << endl;
			return -1;	
	}

	ALLEGRO_TIMER* timer = al_create_timer(timePerFrame);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	{
		gif animation(gifName, gifLength, mov, framesPerMovement);
		if(!animation.isValid())
			return -1;

		al_start_timer(timer);

		ALLEGRO_EVENT ev;
		do
		{
			al_wait_for_event(event_queue, &ev);
			if(ev.type == ALLEGRO_EVENT_TIMER) 
			{	
				al_clear_to_color(al_map_rgb(0,0,0));	//poner cualquier color de fondo o incluso una imagen
				animation.drawNextImage();				//dibujar la proxima imagen de la animacion
				al_flip_display();						//mostrar los cambios en pantalla
			}
		}
		while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE && animation.getPosition().getX() <= al_get_display_width(display));		
	}
	//al salir de este bloque, se destruye animation y todos los bitmaps que cargo.
	//Importante que se destruya antes de desintalar el addon de allegro de imagen, ya que sino no se podria invocar a al_destroy_bitmap().
	
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_shutdown_image_addon();
	
	return 0;
}

