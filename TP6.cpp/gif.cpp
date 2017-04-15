#include "gif.h"

gif::gif(std::string _gifName, unsigned int _gifLength, point _movement, point _position, unsigned int _framesPerMovement)
{
	valid = true;		//es true hasta que se encuentre un error
	gifName = _gifName;
	gifLength = _gifLength;
	movement = _movement;
	position = _position;
	framesPerMovement = _framesPerMovement;
	frameCounter = 0;
	position.setX(0);
	position.setY(0);
	
	loadedImgs = new ALLEGRO_BITMAP*[gifLength];
	
	ALLEGRO_BITMAP* imgPointer = nullptr;	//contiene el puntero a la ultima imagen cargado. Si hubo error, vale nullptr
	for(int i = 0; i < gifLength; ++i)		//inicializar todos los punteros en nullptr para asegurarse de no levantar basura
		loadedImgs[i] = nullptr;
		
	int i = 0;	//contador
	do
	{
		imgPointer = nullptr;
		std::string path = ( gifName + "/" + gifName + "-F"  + std::to_string(i+1) + ".png");	//path de las imagenes
		std::cout << path << std::endl;		//para debug
		imgPointer = al_load_bitmap(path.c_str());
		if(imgPointer != nullptr)	//si el bitmap de cargo exitosamente, poner el puntero en el arreglo
			loadedImgs[i] = imgPointer;
		else	//si el bitmap no se cargo exitosamente, indicarlo en la variable valid
		{
			valid = false;
			std::cout << "error cargando la imagen " << path << std::endl;	//para debug
		}
		++i;
	}
	while(i < gifLength && imgPointer != nullptr);
}

gif::gif(const gif& orig) {
}

gif::~gif() 
{
	if (loadedImgs != nullptr)	//si es nullptr, no hay que hacer delete porque no se hizo new
	{
		for(int i = 0; i < gifLength && loadedImgs[i] != nullptr; ++i)
			al_destroy_bitmap(loadedImgs[i]);
		delete[] loadedImgs;
	}
}

void gif::drawNextImage()
{
	if(frameCounter % framesPerMovement == 0)	//si corresponde moverse, calcular las nuevas coordenadas y guardarlas en position
	{
		position.setX(position.getX() + movement.getX());
		position.setY(position.getY() + movement.getY());
	}
	al_draw_bitmap(loadedImgs[frameCounter], position.getX(), position.getY(), 0);
	frameCounter + 1 == gifLength ? frameCounter = 0 : frameCounter++ ;	//si se llego al max frameCounter, resetear. Sino, incrementar
}

point gif::getPosition()
{
	return position;
}

bool gif::isValid()
{
	return valid;
}

bool gif::finishedLooping()

