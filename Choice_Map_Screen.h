#pragma once
#include "screen_abstract.h"
#include <dirent.h>
#include <stdio.h>

class Choice_Map_Screen :
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

		//ODCZYT MAP W PLIKU
		void Load_File_Map() ;

		//KASUJEMY MAPE
		bool Delete_Map() ;

		Choice_Map_Screen()
		{
			//WCZYTUJEMY MAPY
			Load_File_Map() ;

			//WCZYTUJEMY BITMAPY
			Screen_Bitmap["Map_Background"]   = load_bitmap_at_size( "Graphics\\Select_Map\\Center.png" , 600 , 600 )	   ;
			Screen_Bitmap["Left_Background"]  = load_bitmap_at_size( "Graphics\\Select_Map\\Left.png" , 100 , 600 )		   ;
			Screen_Bitmap["Right_Background"] = load_bitmap_at_size( "Graphics\\Select_Map\\Right.png" , 100 , 600 )       ;
			Screen_Bitmap["Left_Arrow"]		  = load_bitmap_at_size( "Graphics\\Select_Map\\Arow_Left.png" , 100 , 100 )   ;
			Screen_Bitmap["Left_Arrow2"]	  = load_bitmap_at_size( "Graphics\\Select_Map\\Arow_Left2.png" , 100 , 100 )  ;
			Screen_Bitmap["Right_Arrow"]	  = load_bitmap_at_size( "Graphics\\Select_Map\\Arow_Right.png" , 100 , 100 )  ;
			Screen_Bitmap["Right_Arrow2"]	  = load_bitmap_at_size( "Graphics\\Select_Map\\Arow_Right2.png" , 100 , 100 ) ;
			Screen_Bitmap["Edit"]			  = load_bitmap_at_size( "Graphics\\Select_Map\\Edit.png" , 100 , 50 )		   ;
			Screen_Bitmap["Edit2"]			  = load_bitmap_at_size( "Graphics\\Select_Map\\Edit2.png" , 100 , 50 )		   ;
			Screen_Bitmap["Back"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Back.png" , 100 , 50 )	       ;
			Screen_Bitmap["Back2"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Back2.png" , 100 , 50 )	       ;
			Screen_Bitmap["Delete"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Delete.png" , 100 , 50 )	   ;
			Screen_Bitmap["Delete2"]		  = load_bitmap_at_size( "Graphics\\Select_Map\\Delete2.png" , 100 , 50 )	   ;
			Screen_Bitmap["Play"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Play.png" , 100 , 50 )	       ;
			Screen_Bitmap["Play2"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Play2.png" , 100 , 50 )	       ;
			Screen_Bitmap["Top10"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Top10.png" , 100 , 50 )		   ;
			Screen_Bitmap["Top102"]		      = load_bitmap_at_size( "Graphics\\Select_Map\\Top102.png" , 100 , 50 )	   ;

			//SPRAWDZAMY CZY BITMAPY ISTNIEJA
			if( !Screen_Bitmap["Map_Background"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Center.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Left_Background"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Left.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Right_Background"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Right.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Left_Arrow"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Arow_Left.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Right_Arrow"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Arow_Right.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Edit"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Edit.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Back"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Back.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Delete"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Delete.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Play"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Play.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Top10"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Top10.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Left_Arrow2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Arow_Left2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Right_Arrow2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Arow_Right2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Edit2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Edit2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Back2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Back2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Delete2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Delete2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Play2"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Play2.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}
			else if( !Screen_Bitmap["Top102"] )
			{
				al_show_native_message_box( display , "ERROR BITMAP" , "ERROR" , "You don't have bitmap \"Graphics\\Select_Map\\Top102.png\" " , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
				exit(1) ;
			}

			//USTAWIAMY MASKE DLA PRZYCISKOW
			al_convert_mask_to_alpha( Screen_Bitmap["Left_Arrow"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Left_Arrow2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Right_Arrow"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Right_Arrow2"] , al_map_rgb(255 , 255 , 255) )	;
			al_convert_mask_to_alpha( Screen_Bitmap["Edit"] , al_map_rgb(255 , 255 , 255) )			;
			al_convert_mask_to_alpha( Screen_Bitmap["Edit2"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Back"] , al_map_rgb(255 , 255 , 255) )			;
			al_convert_mask_to_alpha( Screen_Bitmap["Back2"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Delete"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Delete2"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Play"] , al_map_rgb(255 , 255 , 255) )			;
			al_convert_mask_to_alpha( Screen_Bitmap["Play2"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Top10"] , al_map_rgb(255 , 255 , 255) )		;
			al_convert_mask_to_alpha( Screen_Bitmap["Top102"]	 , al_map_rgb(255 , 255 , 255) )	;
		}

		~Choice_Map_Screen()
		{
			//KASUJEMY MINIATURY ORAZ BITMAPY EKRANU
			for(int i = 0 ; i < Miniature_Map.size() ; i++)
				al_destroy_bitmap( Miniature_Map[i] ) ;

			al_destroy_bitmap( Screen_Bitmap["Map_Background"] )   ;
			al_destroy_bitmap( Screen_Bitmap["Left_Background"] )  ; 
			al_destroy_bitmap( Screen_Bitmap["Right_Background"] ) ; 
			al_destroy_bitmap( Screen_Bitmap["Left_Arrow"] )	   ;		 
			al_destroy_bitmap( Screen_Bitmap["Right_Arrow"] )      ;	 
			al_destroy_bitmap( Screen_Bitmap["Edit"] )			   ;			 
			al_destroy_bitmap( Screen_Bitmap["Back"] )			   ;		     
			al_destroy_bitmap( Screen_Bitmap["Delete"] )		   ;
			al_destroy_bitmap( Screen_Bitmap["Left_Arrow2"] )	   ;		 
			al_destroy_bitmap( Screen_Bitmap["Right_Arrow2"] )     ;	 
			al_destroy_bitmap( Screen_Bitmap["Edit2"] )			   ;			 
			al_destroy_bitmap( Screen_Bitmap["Back2"] )			   ;		     
			al_destroy_bitmap( Screen_Bitmap["Delete2"] )		   ;
		}

	private:	

		//ZAPAMIETA KTORA MAPE WYBRALISMY
		int Select_Map ;
		//CZY RYSOWAC ZAZNACZENIE
		bool Select ;
		
		//MINIATURY MAP
		std::vector< ALLEGRO_BITMAP *> Miniature_Map ;
		//NAZWY PLIKOW
		std::vector< std::string > Files_Name ;

		//ZAZNACZONA POZYCJA PRZEZ MYSZKE
		int Mouse_Select ;

		//POKAZAC PRZYCISKI
		bool Show_Button ;

		//ILE "EKRANOW" BEDZIE SIE WYSWIETLAC
		int Which_Screen ;

		//ZMIENNE DO WYPISANIA MAP
		int Map1 , Map2 ;

		//TYLKO 1 MAPA
		bool One_Map ;

		//ANI JEDNEJ MAPY
		bool Zero_Map ;
};