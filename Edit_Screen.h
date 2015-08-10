#pragma once
#include "screen_abstract.h"
#include "Map.h"
//#include <allegro5\allegro_primitives.h>


class Edit_Screen :
	public Screen_Abstract
{

	public:
		
		//ZWYKLY KONSTRUKTOR
		Edit_Screen()
		{
			//WPROWADZ NAZWE MAPY LUB IMIE GRACZA
			Enter_the_String = false ;
			//ZAZNACZONA POZYCJA PRZEZ MYSZKE
			Mouse_Select = 0 ;
			//USTAWIAMY NA TAKA WARTOSC KTOREJ NIE OBSLUGUJEMY
			What_Draw = 10 ;
			Select = false ;
			Maps = new Map() ;

			///PRZYPISUJEMY BITMAPY OD MAPY
			Screen_Bitmap["Background_Stat"] = load_bitmap_at_size( "Graphics\\Game\\Background_Stat.png" , 200 , 600 ) ;

			Screen_Bitmap["Write_String"]    = load_bitmap_at_size( "Graphics\\Game\\Write_String.png" , 500 , 300 ) ;

			Screen_Bitmap["Snake_Head1"]	 = Maps->Elements[0]  ;  ///  -[]
			Screen_Bitmap["Snake_Tail1"]	 = Maps->Elements[8]  ;

			Screen_Bitmap["Snake_Head2"]	 = Maps->Elements[1]  ;  ///  |
			Screen_Bitmap["Snake_Tail2"]	 = Maps->Elements[9]  ;  /// [ ]

			Screen_Bitmap["Snake_Head3"]	 = Maps->Elements[2]  ;  /// []-
			Screen_Bitmap["Snake_Tail3"]	 = Maps->Elements[10] ;

			Screen_Bitmap["Snake_Head4"]	 = Maps->Elements[3]  ;	 /// [ ]
			Screen_Bitmap["Snake_Tail4"]	 = Maps->Elements[11] ;	 ///  |

			Screen_Bitmap["Empty"]		     = Maps->Elements[15] ;
			Screen_Bitmap["Wall"]			 = Maps->Elements[16] ;

			Screen_Bitmap["Save"]			 = load_bitmap_at_size( "Graphics\\Game\\Save.png" , 200 , 50 ) ;
			Screen_Bitmap["Cancel"]		     = load_bitmap_at_size( "Graphics\\Game\\Cancel.png" , 200 , 50 ) ;
			Screen_Bitmap["Save2"]			 = load_bitmap_at_size( "Graphics\\Game\\Save2.png" , 200 , 50 ) ;
			Screen_Bitmap["Cancel2"]		 = load_bitmap_at_size( "Graphics\\Game\\Cancel2.png" , 200 , 50 ) ;

			//SPRAWDZAMY CZY BITMAPY ISTNIEJA
			if( !Screen_Bitmap["Background_Stat"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Background_Stat.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Write_String"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Write_String.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Save"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Save.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Cancel"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Cancel.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Save2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Save2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Cancel2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Cancel2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}

			//USTAWIAMY MASKE DLA PRZYCISKOW
			al_convert_mask_to_alpha( Screen_Bitmap["Cancel"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Cancel2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Save"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Save2"] , al_map_rgb(255 , 255 , 255) )	;
		}

		//KONSTRUKTOR KTORY ODRAZU LADUJE MAPE
		Edit_Screen( std::string Name )
		{
			//WPROWADZ NAZWE MAPY LUB IMIE GRACZA
			Enter_the_String = false ;
			//ZAZNACZONA POZYCJA PRZEZ MYSZKE
			Mouse_Select = 0 ;
			//USTAWIAMY NA TAKA WARTOSC KTOREJ NIE OBSLUGUJEMY
			What_Draw = 10 ;
			Select = false ;
			Maps = new Map() ;

			if( !Maps->Load_Map(display , Name ) )
				End_Edit_ = true ;
			//PO ODCZYCIE MAPY KASUJE 4 OSTATNIE LITERY (.adi) I PRZYPISUJE DO NOWEJ 
			Name.erase( Name.end() - 4 , Name.end() ) ;
			Name_File_To_Save = Name ;


			///PRZYPISUJEMY BITMAPY OD MAPY
			Screen_Bitmap["Background_Stat"] = load_bitmap_at_size( "Graphics\\Game\\Background_Stat.png" , 200 , 600 ) ;

			Screen_Bitmap["Write_String"]    = load_bitmap_at_size( "Graphics\\Game\\Write_String.png" , 500 , 300 ) ;

			Screen_Bitmap["Snake_Head1"]	 = Maps->Elements[0]  ;  ///  -[]
			Screen_Bitmap["Snake_Tail1"]	 = Maps->Elements[8]  ;

			Screen_Bitmap["Snake_Head2"]	 = Maps->Elements[1]  ;  ///  |
			Screen_Bitmap["Snake_Tail2"]	 = Maps->Elements[9]  ;  /// [ ]

			Screen_Bitmap["Snake_Head3"]	 = Maps->Elements[2]  ;  /// []-
			Screen_Bitmap["Snake_Tail3"]	 = Maps->Elements[10] ;

			Screen_Bitmap["Snake_Head4"]	 = Maps->Elements[3]  ;	 /// [ ]
			Screen_Bitmap["Snake_Tail4"]	 = Maps->Elements[11] ;	 ///  |

			Screen_Bitmap["Empty"]		     = Maps->Elements[15] ;
			Screen_Bitmap["Wall"]			 = Maps->Elements[16] ;

			Screen_Bitmap["Save"]			 = load_bitmap_at_size( "Graphics\\Game\\Save.png" , 200 , 50 ) ;
			Screen_Bitmap["Cancel"]		     = load_bitmap_at_size( "Graphics\\Game\\Cancel.png" , 200 , 50 ) ;
			Screen_Bitmap["Save2"]			 = load_bitmap_at_size( "Graphics\\Game\\Save2.png" , 200 , 50 ) ;
			Screen_Bitmap["Cancel2"]		 = load_bitmap_at_size( "Graphics\\Game\\Cancel2.png" , 200 , 50 ) ;

			//SPRAWDZAMY CZY BITMAPY ISTNIEJA
			if( !Screen_Bitmap["Background_Stat"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Background_Stat.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Write_String"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Write_String.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Save"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Save.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Cancel"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Cancel.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Save2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Save2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Cancel2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Cancel2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}

			//USTAWIAMY MASKE DLA PRZYCISKOW
			al_convert_mask_to_alpha( Screen_Bitmap["Cancel"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Cancel2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Save"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Save2"] , al_map_rgb(255 , 255 , 255) )	;
		}

		~Edit_Screen()
		{
			delete Maps ;
			al_destroy_bitmap( Screen_Bitmap["Save"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Cancel"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Save2"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Cancel2"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Background_Stat"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Write_String"] ) ;
		}
		

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

	private:

		//CZY RYSOWAC ZAZNACZENIE
		bool Select ;

		//WPROWADZ NAZWE MAPY LUB IMIE GRACZA
		bool Enter_the_String ;

		//ZAZNACZONA POZYCJA PRZEZ MYSZKE
		int Mouse_Select ;

		//NAZWA PLIKU + SCIEZKA
		std::string Name_File_To_Save ;

		//ZMIENNE DO WYRYSOWANIA ZAZNACZENIA POZYCJI
		int selectedX1 ;
		int selectedY1 ;
		int selectedX2 ;
		int selectedY2 ;

		//CO WPISAC DO MAPY
		int What_Draw ;

		//PLANSZA
		Map *Maps ;
};

