#pragma once
#include "screen_abstract.h"
class Game_Screen :
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

		//SPRAWDZA CZY NASZ WYNIK ZNAJDUJE SIE NA TOP10
		bool Check_Score() ;


		Game_Screen( std::string Name )
		{
			//WPROWADZ NAZWE MAPY LUB IMIE GRACZA
			Enter_the_String = false ;
			//ZAZNACZONA POZYCJA PRZEZ MYSZKE
			Mouse_Select = 0 ;

			Maps = new Map() ;

			if( !Maps->Load_Map(display , Name ) )
				End_Choice_Map_ = true ;

			Game_Over  = false ;
			Start_Game = false ;
			Draw_Over  = false ;
			

			Screen_Bitmap["Background_Stat"] = load_bitmap_at_size( "Graphics\\Game\\Background_Stat.png" , 200 , 600 ) ;
			Screen_Bitmap["Write_String"]    = load_bitmap_at_size( "Graphics\\Game\\Write_String.png" , 500 , 300 ) ;
			Screen_Bitmap["Save_Nick"]       = load_bitmap_at_size( "Graphics\\Game\\Nick.png" , 200 , 50 ) ;
			Screen_Bitmap["Arrow"]           = load_bitmap_at_size( "Graphics\\Game\\Keyboard_Arrow.png" , 200 , 100 ) ;
			Screen_Bitmap["Back"]            = load_bitmap_at_size( "Graphics\\Game\\Back_to_Choice.png" , 200 , 50 ) ;
			Screen_Bitmap["Start"]           = load_bitmap_at_size( "Graphics\\Game\\Start.png" , 200 , 50 ) ;
			Screen_Bitmap["Pause"]           = load_bitmap_at_size( "Graphics\\Game\\Pause.png" , 200 , 50 ) ;
			Screen_Bitmap["Pause_Screen"]    = load_bitmap_at_size( "Graphics\\Game\\Pause_Screen.png" , 600 , 600 ) ;
			Screen_Bitmap["Game_Over"]       = load_bitmap_at_size( "Graphics\\Game\\Game_Over.png" , 600 , 400 ) ;
			Screen_Bitmap["Back2"]           = load_bitmap_at_size( "Graphics\\Game\\Back_to_Choice2.png" , 200 , 50 ) ;
			Screen_Bitmap["Start2"]          = load_bitmap_at_size( "Graphics\\Game\\Start2.png" , 200 , 50 ) ;
			Screen_Bitmap["Pause2"]          = load_bitmap_at_size( "Graphics\\Game\\Pause2.png" , 200 , 50 ) ;
			Screen_Bitmap["Save_Nick2"]      = load_bitmap_at_size( "Graphics\\Game\\Nick2.png" , 200 , 50 ) ;

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
			else if( !Screen_Bitmap["Save_Nick"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Nick.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Save_Nick2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Nick2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Arrow"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Keyboard_Arrow.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Back"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Back_to_Choice.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Start"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Start.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Pause"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Pause.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Back2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Back_to_Choice2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Start2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Start2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Pause2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Pause2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Pause_Screen"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Pause_Screen.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Game_Over"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Game\\Game_Over.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}

			//USTAWIAMY MASKE DLA PRZYCISKOW
			al_convert_mask_to_alpha( Screen_Bitmap["Arrow"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Save_Nick"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Save_Nick2"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Back"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Back2"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Start"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Start2"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Pause"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Pause2"] , al_map_rgb(255 , 255 , 255) ) ;
		}

		~Game_Screen()
		{
			delete Maps ;
			al_destroy_bitmap( Screen_Bitmap["Background_Stat"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Write_String"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Save_Nick"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Save_Nick2"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Arrow"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Back"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Start"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Pause"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Back2"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Start2"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Pause2"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Pause_Screen"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Game_Over"] ) ;
		}

	private:

		//ZAZNACZONA POZYCJA PRZEZ MYSZKE
		int Mouse_Select ;

		//WPROWADZ NAZWE MAPY LUB IMIE GRACZA
		bool Enter_the_String ;

		//WYPISUJEMY PUNKTY GRACZY
		std::stringstream Player_Points ;
		//NAZWA GRACZA
		std::string Nick ;
		//WSKAZNIK MAPY
		Map * Maps ;
		//KONIEC GRY
		bool Game_Over ; 
		//START PAUZA
		bool Start_Game ; 
		//ZMIENNA DO RYSOWANIA GAMEOVER
		bool Draw_Over ;
		//MIEJSCE NA TOP10
		int Place_on_Top10 ;
};

