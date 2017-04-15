#include <cstdlib>
#include <iostream>
#include "point.h"
#include "gif.h"
#include "Display.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

bool initAllegro();
void shutdownAllegro();

typedef char BYTE;

int main(int argc, char** argv) {
	
	if(!initAllegro())
	{
		std::cout << "Error inicializando allegro" << std::endl;
		return -1;
	}	
	
/********************************************************
 * 
 * 
 * CONECTAR, RECIBIR PAQUETE Y TODA ESA MAGIA
 * 
 * 
 ********************************************************/	
	
	BYTE animationCode; 
	animationCode = 'C';	//para debuggear
	
	std::string gifName;	//nombre del gif
	unsigned int gifLength;	//frames que conforman el gif
	point position;			//posicion inicial
	point mov;				//valores por los cuales se debe modificar la posicion ("vector de movimiento")
	unsigned int framesPerMovement = 1;	//cada cuantos frames se debe cambiar la posicion
	float timePerFrame;		//tiempo que dura cada frame en pantalla en segundos
	bool looping;

	gif* animation = nullptr;
	
	switch(animationCode)
	{
		case 'A':
			timePerFrame = 0.1;
			animation = new gif("Cat Running", 12, point (2,0), point (0,0), 1, true);
			break;
		case 'B':
			timePerFrame = 0.12;
			animation = new gif("Explosion 1", 8, point (0,0), point (0,0), 1, false);
			break;
		case 'C':
			timePerFrame = 0.1;
			animation = new gif("Explosion 2", 48, point (0,0), point (0,0), 1, false);
			break;		
		case 'D':
			timePerFrame = 0.1;
			animation = new gif("Homer Dance", 12, point (100,0), point (0,0), 1, true);
			break;
		case 'E':
			timePerFrame = 0.04;
			animation = new gif("Super Mario Running", 12, point (2,0), point (0,0), 1, true);
			break;
		case 'F':
			timePerFrame = 0.06;
			animation = new gif("Sonic Running", 10, point (70,0), point (0,0), 4, true);
			break;
		default:
			#warning sacar este return horripilante
			std::cout << "Error: codigo de gif incorrecto" << std::endl;
			return -1;	
	}
	if(!animation->isValid())
		return -1;		//PONER DEFINE GATOS


	Display* dis = new Display(1000, 1000);	//crear display. 
	//Se crea en el heap para tener control de cuando se destruye 
	//(se debe destruir antes de que se desinstale allegro para poder invocar a la funcion al_destroy_display())
	ALLEGRO_TIMER* timer = al_create_timer(timePerFrame);		//crear timer con el tiempo correspondiente a la animacion
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();	//crear cola de eventos

	al_register_event_source(event_queue, al_get_display_event_source(dis->getDisplay()));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	ALLEGRO_EVENT ev;
	bool keepDrawing = true;

	al_start_timer(timer);

	do
	{
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER) 
		{	
			al_clear_to_color(al_map_rgb(0,0,0));	//poner cualquier color de fondo o incluso una imagen
			keepDrawing = animation->updateImg();	//dibujar la proxima imagen de la animacion
			dis->showChanges();						//mostrar los cambios del display
		}
	}
	while (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE 		//salir si se cierra el display
		&& animation->getPosition().getX() <= dis->getDisplayWidth()	//salir si el gif se va de pantalla
		&& animation->getPosition().getX() >= 0			//salir si el gif se va de pantalla
		&& keepDrawing == true);						//salir si se llego al final del gif

	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	delete dis;
	delete animation;

	//al salir de este bloque, se destruye animation y todos los bitmaps que cargo, y el display.
	//Importante que se destruya antes de desintalar el addon de allegro de imagen, ya que sino el destructor 
	//no podria invocar a al_destroy_bitmap() ni al_destroy_display();
	
	
	/**************************************
	 * 
	 * 
	 * CONECTAR Y FOWARDEAR PAQUETE YOU_GO
	 * 
	 **************************************/
	
	shutdownAllegro();
	
	return 0;
}

//Devuelve true si no hubo un error en la inicializacion y false en caso contrario.
bool initAllegro()
{
    if(!al_init())
        return false;
	else  if(!al_init_image_addon())
		return false;
	return true;
}

//
void shutdownAllegro()
{
	al_shutdown_image_addon();
}

