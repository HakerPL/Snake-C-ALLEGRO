#pragma once

#include "screen_abstract.h"
#include "zmienne.h"

#include <sstream>


class Top10_Screen :
	public Screen_Abstract
{
	public:

		//OBSLUGA MYSZKI
		void Handling_Mouse( ALLEGRO_EVENT &events ) ;
		//OBSLUGA KLAWIATURY
		void Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER *MapFPS = 0 ) ;
		//RYSOWANIE EKRANU
		void Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS = 0 ) ;
		//PRZYCIEMNIANIE EKRANU PRZY PRZEJSCIU NA INNY
		void Screen_Fading() ; 
		//ROZJASNIANIE EKRANU PRZY WCZYTANIU
		void Screen_Lighten() ;

		Top10_Screen( std::string Name )
		{
			Screen_Bitmap["Top10_Background"] = load_bitmap_at_size( "Graphics\\Top10\\Background_Top10.png" , 800 , 600 ) ;
			
			Maps = new Map() ;

			//SPRAWDZAMY CZY BITMAPY ISTNIEJA
			if( !Screen_Bitmap["Top10_Background"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Top10\\Background_Top10.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}

			if( !Maps->Load_Top10(display , Name ) )
				End_Top10_ = true ;

			//PO ODCZYCIE MAPY KASUJE 4 OSTATNIE LITERY (.adi) I PRZYPISUJE DO NOWEJ 
			Name.erase( Name.end() - 4 , Name.end() ) ;
			Name_File_ = Name ;
		
		}

		~Top10_Screen(void)
		{
			al_destroy_bitmap( Screen_Bitmap["Top10_Background"] ) ;
		}

	private:

		//NAZWA PLIKU + SCIEZKA
		std::string Name_File_ ; 

		//ZMIANA Z INT NA STRING
		std::stringstream Top10_Points ;
		std::stringstream Top10_Nr ;

		//WSKAZNIK DO MAPY
		Map * Maps ;
};


