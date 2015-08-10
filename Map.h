#ifndef MAP_H
#define MAP_H

//PLIK ZE ZMIENNYMI
#include "zmienne.h"
#include "Snake.h"
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <sstream>
#include <vector>
#include <string>

class Map
{
	public:

		//WYPISUJE MAPE
		void Draw_Map () ;  
		//UAKTUALNIA POZYCJE WEZA NA MAPIE
		//const std::vector<int[2]> & Snake = REFERENCJA NA STALY OBIEKT (NIE ZMIENIMY)
		void Update_Map() ;
		//UMIESZCZENIE ODPOWIEDNICH ELEMENTOW NA MAPIE PRZY EDYCJI I NOWEJ MAPIE
		void Update_Map_Edit(  int PositionY , int PositionX , int Bitmap ) ;
		//SPRAWDZANIE MAPY PRZY EDYCJI I NOWEJ MAPIE (MUSI POSIADAC PRZYNAJMNIEJ JEDNO PUSTE MIEJSCE ORAZ WEZA)
		bool Check_Map(ALLEGRO_DISPLAY * display) ;
		//WCZYTUJE DANE Z PLIKU DO MAPY I TOP10
		bool Load_Map(ALLEGRO_DISPLAY *display , std::string Name ) ;
		//ODCZYT TYLKO TOP10
		bool Load_Top10(ALLEGRO_DISPLAY *display , std::string Name ) ;
		//ZAPISUJEMY MAPE I TOP10
		bool Save_Map(ALLEGRO_DISPLAY *display ) ;
		//ZAPISUJEMY TYLKO TOP10
		bool Save_Top10(ALLEGRO_DISPLAY *display ) ;

		//ZWRACAMY POTRZEBNE ZDJECIA
		const ALLEGRO_BITMAP * Return_Spawn()			     { return Elements[14] ; } ;
		const ALLEGRO_BITMAP * Return_Empty()			     { return Elements[15] ; } ;
		const std::vector<ALLEGRO_BITMAP *> & Return_Map()   { return Screen_Map   ; } ;

		//PRZYJAZN Z KLASAMI EKRANU
		friend class Edit_Screen  ;
		friend class Top10_Screen ;
		friend class Game_Screen  ;

		Map(void)
		{
			//MAKSYMALNA ILOSC ZNAKOW PRZY NICKU I NAZWIE PLIKU
			Max = 15 ;	

			//URUCHAMIAMY LOSOWANIE LICZB
			srand( static_cast<unsigned int>(time(NULL)) ) ;

			Snakess = new Snakes() ;

			//WCZYTUJEMY WEZA
			for(int i = 0 ; i < 14 ; i++)
			{
				std::stringstream snake ;
				snake << "Graphics\\Snake\\" << i + 1 << ".png" ;
				Elements.push_back( load_bitmap_at_size( snake.str().c_str() , 30 , 30 ) ) ;
			}
			//WCZYTUJEMY SPAWN
			Elements.push_back( load_bitmap_at_size( "Graphics\\Eat_Me\\1.png" , 30 , 30 ) ) ;
			//WCZYTUJEMY EMPTY
			Elements.push_back( load_bitmap_at_size( "Graphics\\Empty.png" , 30 , 30 ) ) ;
			//WCZYTUJEMY SCIANE
			Elements.push_back( load_bitmap_at_size( "Graphics\\Wall\\1.png" , 30 , 30 ) ) ;

			//SPRAWDZAMY CZY BITMAPY ISTNIEJA
			for(int i = 0 ; i < Elements.size() ; i++)
			{
				if( !Elements[i] )
				{
					switch(i)
					{
						case 0:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\1.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 1:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 2:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\3.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 3:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\4.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 4:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\5.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 5:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\6.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 6:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\7.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 7:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\8.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 8:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\9.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 9:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\10.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 10:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\11.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 11:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\12.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 12:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\13.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 13:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Snake\\14.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 14:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Eat_Me\\1.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 15:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Empty.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
						case 16:
							al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Wall\\1.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
							break ;
					}
					exit(1) ;
				}
			}
			
			//WYPELNIAMY KONTENERY POCZATKOWYMI DANYMI
			for(int i = 0 ; i < 400 ; i++)
				Screen_Map.push_back(Elements[15]) ;

			std::string Nick = "***************"  ;
			
			for(int i = 0 ; i < 10 ; i++)
			{
				Top10_Nick.push_back( Nick ) ;
				Top10_Points.push_back( 0 ) ;
			}

			//USTAWIAMY MASKE DLA WEZA
			for( int i = 0 ; i < 14 ; i++)
				al_convert_mask_to_alpha( Elements[i] , al_map_rgb(0 , 0 , 0) )	;
		};
				
		~Map(void)
		{
			//KASUJEMY BITMAPE
			for(int i = 0 ; i < Elements.size() ; i++)
				al_destroy_bitmap(Elements[i]) ;

			//KASUJEMY WEZA
			delete Snakess ;
			//USTAWIAMY Spawn NA TRUE 
			Spawn = true ;
		};

		
	private:

		//OBIEKT WEZA
		Snakes * Snakess ;

		//MAPA
		std::vector <ALLEGRO_BITMAP *> Screen_Map ;
		//ELEMENTY MAPY
		std::vector <ALLEGRO_BITMAP *> Elements ;
		//TOPKA NICK GLACZA
		std::vector <std::string> Top10_Nick ;
		//TOPKA PUNKTY GRACZA
		std::vector <unsigned> Top10_Points ;

		//NAZWA PLIKU DO WCZYTANIA / ZAPISANIA
		std::string File_Name ;

		//MAKSYMALNA ILOSC ZNAKOW W NAZWIE I NICKU
		int Max ;
};

#endif

