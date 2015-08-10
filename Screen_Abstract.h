#pragma once
#include <allegro5\allegro_primitives.h>
#include <allegro5/allegro_image.h>
//#include <allegro5\allegro_font.h>
//#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro5.h>
#include <vector>
#include <string>
#include <map>
#include "Map.h"

class Screen_Abstract
{
	public:

		//OBSLUGA MYSZKI
		virtual void Handling_Mouse( ALLEGRO_EVENT &events ) = 0 ;
		//OBSLUGA KLAWIATURY
		virtual void Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER *MapFPS = 0 ) = 0 ;
		//RYSOWANIE EKRANU
		virtual void Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS = 0 ) = 0 ;
		//PRZYCIEMNIANIE EKRANU PRZY PRZEJSCIU NA INNY
		virtual void Screen_Fading() = 0 ; 
		//ROZJASNIANIE EKRANU PRZY WCZYTANIU
		virtual void Screen_Lighten() = 0 ;
		//VIRTUALNY DESTRUKTOR
		virtual ~Screen_Abstract() {}  ; 

	protected:

		//ZDJECIE EKRANU
		ALLEGRO_BITMAP * Screen_Photo ;
		//PRZECHOWUJE BITMAPE OBRAZU
		std::map< std::string , ALLEGRO_BITMAP * > Screen_Bitmap ;
		//KTORY PRZYCISK MYSZKI ZOSTAL WCISNIETY
		ALLEGRO_MOUSE_STATE state;
};