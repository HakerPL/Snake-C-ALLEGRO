#pragma once
#include "zmienne.h"
#include "screen_abstract.h"
//#include <allegro5\allegro_primitives.h>

class Menu_Screen :
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
		void Screen_Fading()  ; 
		//ROZJASNIANIE EKRANU PRZY WCZYTANIU
		void Screen_Lighten() ;


		Menu_Screen()
		{
			//USTAWIAMY POCZATKOWE WARTOSCI
			Options = false ;
			Select_Options = 0 ;
			//ZAZNACZENIE POZIOMU TRUDNOSCI EASY
			switch(Difficulty)
			{
				case 1:

					difficultyX1 = 500 ;
					difficultyY1 = 225 ;
					difficultyX2 = 600 ;
					difficultyY2 = 275 ;
					break ;
	
				case 2:

					difficultyX1 = 500 ;
					difficultyY1 = 300 ;
					difficultyX2 = 600 ;
					difficultyY2 = 350 ;
					break ;

				case 3:

					difficultyX1 = 500 ;
					difficultyY1 = 375 ;
					difficultyX2 = 600 ;
					difficultyY2 = 425 ;
					break ;
			}//switch(Difficulty)

			//MENU
			Screen_Bitmap["Menu_Background"] = load_bitmap_at_size( "Graphics\\Menu\\Menu_Background.png" , 800 , 600 )  ;
			Screen_Bitmap["Title"]			 = load_bitmap_at_size( "Graphics\\Menu\\Title.png" , 600 , 100 )   ;
			Screen_Bitmap["Start"]			 = load_bitmap_at_size( "Graphics\\Menu\\Start.png" , 199 , 70 )    ;
			Screen_Bitmap["Start2"]			 = load_bitmap_at_size( "Graphics\\Menu\\Start2.png" , 199 , 70 )   ;
			Screen_Bitmap["Edit"]			 = load_bitmap_at_size( "Graphics\\Menu\\Edit.png" , 199 , 70 )     ;
			Screen_Bitmap["Edit2"]			 = load_bitmap_at_size( "Graphics\\Menu\\Edit2.png" , 199 , 70 )    ;
			Screen_Bitmap["New"]			 = load_bitmap_at_size( "Graphics\\Menu\\New.png" , 199 , 70 )      ;
			Screen_Bitmap["New2"]			 = load_bitmap_at_size( "Graphics\\Menu\\New2.png" , 199 , 70 )     ;
			Screen_Bitmap["Options"]		 = load_bitmap_at_size( "Graphics\\Menu\\Options.png" , 199 , 70 )  ;
			Screen_Bitmap["Options2"]		 = load_bitmap_at_size( "Graphics\\Menu\\Options2.png" , 199 , 70 ) ;
			Screen_Bitmap["Exit"]		     = load_bitmap_at_size( "Graphics\\Menu\\Exit.png" , 199 , 70 )     ;
			Screen_Bitmap["Exit2"]		     = load_bitmap_at_size( "Graphics\\Menu\\Exit2.png" , 199 , 70 )    ;

			//OPCJE
			Screen_Bitmap["Options_Background"] = load_bitmap_at_size( "Graphics\\Menu\\Options_Background.png" , 500 , 300 ) ;
			Screen_Bitmap["Options_Easy"]       = load_bitmap_at_size( "Graphics\\Menu\\Easy.png" , 100 , 50 )       ;
			Screen_Bitmap["Options_Easy2"]      = load_bitmap_at_size( "Graphics\\Menu\\Easy2.png" , 100 , 50 )      ;
			Screen_Bitmap["Options_Medium"]     = load_bitmap_at_size( "Graphics\\Menu\\Medium.png" , 100 , 50 )     ;
			Screen_Bitmap["Options_Medium2"]    = load_bitmap_at_size( "Graphics\\Menu\\Medium2.png" , 100 , 50 )    ;
			Screen_Bitmap["Options_Hard"]       = load_bitmap_at_size( "Graphics\\Menu\\Hard.png" , 100 , 50 )       ;
			Screen_Bitmap["Options_Hard2"]      = load_bitmap_at_size( "Graphics\\Menu\\Hard2.png" , 100 , 50 )      ;
			Screen_Bitmap["Options_Back"]       = load_bitmap_at_size( "Graphics\\Menu\\Save_Back.png" , 200 , 50 )  ;
			Screen_Bitmap["Options_Back2"]      = load_bitmap_at_size( "Graphics\\Menu\\Save_Back2.png" , 200 , 50 ) ;

			//SPRAWDZAMY CZY BITMAPY ISTNIEJA
			if( !Screen_Bitmap["Menu_Background"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Menu_Background.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Title"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Title.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Start"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Start.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Start2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Start2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Edit"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Edit.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Edit2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Edit2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["New"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\New.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["New2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\New2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Options.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Options2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Exit"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Exit.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Exit2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Exit2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Background"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Options_Background.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Easy"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Easy.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Easy2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Easy2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Medium"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Medium.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Medium2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Medium2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Hard"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Hard.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Hard2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Hard2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Back"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Save_Back.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Options_Back2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Menu\\Save_Back2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}

			//USTAWIAMY MASKE DLA PRZYCISKOW
			al_convert_mask_to_alpha( Screen_Bitmap["Start"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Start2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Edit"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Edit2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["New"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["New2"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Options"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Options2"] , al_map_rgb(255 , 255 , 255) ) ;
			al_convert_mask_to_alpha( Screen_Bitmap["Exit"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Exit2"] , al_map_rgb(255 , 255 , 255) )	;

			al_convert_mask_to_alpha( Screen_Bitmap["Options_Easy"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Easy2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Medium"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Medium2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Hard"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Hard2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Back"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Options_Back2"] , al_map_rgb(255 , 255 , 255) )	;
		}

		~Menu_Screen()
		{
			al_destroy_bitmap( Screen_Bitmap["Menu_Background"] )	 ;
			al_destroy_bitmap( Screen_Bitmap["Title"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["Title2"] )			 ;
			al_destroy_bitmap( Screen_Bitmap["Start"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["Start2"] )			 ;
			al_destroy_bitmap( Screen_Bitmap["Edit"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["Edit2"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["New"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["New2"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["Options"] )			 ;
			al_destroy_bitmap( Screen_Bitmap["Options2"] )			 ;
			al_destroy_bitmap( Screen_Bitmap["Exit"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["Exit2"] )				 ;
			al_destroy_bitmap( Screen_Bitmap["Options_Background"] ) ;
			al_destroy_bitmap( Screen_Bitmap["Options_Easy"] )		 ;  
			al_destroy_bitmap( Screen_Bitmap["Options_Easy2"] )		 ;
			al_destroy_bitmap( Screen_Bitmap["Options_Medium"] )	 ;  
			al_destroy_bitmap( Screen_Bitmap["Options_Medium2"] )	 ;
			al_destroy_bitmap( Screen_Bitmap["Options_Hard"] )		 ;
			al_destroy_bitmap( Screen_Bitmap["Options_Hard2"] )		 ;
			al_destroy_bitmap( Screen_Bitmap["Options_Back"] )		 ;
			al_destroy_bitmap( Screen_Bitmap["Options_Back2"] )		 ;
			al_destroy_bitmap( Screen_Photo )						 ;
		}

	private:

		//CZY WYSWIETLIC OPCJE
		bool Options ;
		//POZYCJA NA MENU (STRZALKI / MYSZKA)
		int Select_Options ;

		//ZMIENNE DO RYSOWANIA OBRAMOWANIA PRZY WYBRANYM POZIOMIE TRUDNOSCI
		int difficultyX1   ;
		int difficultyY1   ;
		int difficultyX2   ;
		int difficultyY2   ;

};
