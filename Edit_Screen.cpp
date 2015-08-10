#include "Edit_Screen.h"
//#include <iostream>


void Edit_Screen::Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER *MapFPS ) 
{
	if(events.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if(Enter_the_String)
		{
			//ZAPISUJEMY ZNAKI POBRANE Z KLAWIATURY
			Enter_Nick_MapName( keyState , Name_File_To_Save , Maps->Max ) ;
			//std::cout << " 1111111 " << Name_File_To_Save << " "<< Name_File_To_Save.size() << Maps->Max << std::endl ;
		}
	}
}

void Edit_Screen::Handling_Mouse( ALLEGRO_EVENT &events )
{
	//EVENT MYSZKI
	if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		x = events.mouse.x ;
		y = events.mouse.y ;

		if(Enter_the_String)
		{
			//SAVE PLIK
			if( x < 350 && x > 150 && y < 430 && y > 380 )
				Mouse_Select = 1 ;
			//ANULUJ PLIK
			else if( x < 650 && x > 450 && y < 430 && y > 380 )
				Mouse_Select = 2 ;
			else
				Mouse_Select = 0 ;
		}

		else
		{
			//WSKAZANIE NAJECHANEJ POZYCJI
			if( x < 760 && x > 640 && y < 80 && y > 20 )
				Mouse_Select = 1 ;

			else if( x < 760 && x > 640 && y < 160 && y > 100 )
				Mouse_Select = 2 ;

			else if( x < 685 && x > 625 && y < 300 && y > 180 )
				Mouse_Select = 3 ;

			else if( x < 775 && x > 715 && y < 300 && y > 180 )
				Mouse_Select = 4 ;
		
			else if( x < 730 && x > 670 && y < 380 && y > 320 )
				Mouse_Select = 5 ;
		
			else if( x < 730 && x > 670 && y < 460 && y > 400 )
				Mouse_Select = 6 ;

			else if( x < 800 && x > 600 && y < 550 && y > 500 )
				Mouse_Select = 7 ;

			else if( x < 800 && x > 600 && y < 600 && y > 550 )
				Mouse_Select = 8 ;
			else
				Mouse_Select = 0 ;
		}
	}

	//OBSLUGA KLIKNIECIA MYSZKI
	if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		//POBIERAMY STAN MYSZKI
		al_get_mouse_state(&state);

		//KLIKNIECIE LEWY PRZYCISK MYSZKI
		if( state.buttons & 1 )
		{
			if(Enter_the_String)
			{
				//SAVE PLIK
				if( x < 350 && x > 150 && y < 430 && y > 380 )
				{
					int Choice = al_show_native_message_box(display , "SAVE MAP" , "SAVE MAP" , "ARE YOU SURE, YOU WANT CREATE MAP ?" , NULL , ALLEGRO_MESSAGEBOX_YES_NO ) ;

					if(Choice == 1)
					{	

						Maps->File_Name = "Maps\\" + Name_File_To_Save + ".adi" ;
						//std::cout << "Maps->File_Name " << Maps->File_Name << std::endl ;

						if( Maps->Save_Map(display) )
						{
							//USTAWIAMY NA POCZATKOWE ZMIENNE
							Enter_the_String = false ;
							Maps->File_Name.clear()  ;
							Select           = false ;
							What_Draw		 = 10	 ;
							Mouse_Select     = 0     ;

							al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
							al_flip_display() ;
		
							al_show_native_message_box(display , "SUCCESS" , "MAP BUILD" , "MAP WAS SUCCESS CREATE" , NULL , ALLEGRO_MESSAGEBOX_OK_CANCEL ) ;
						}
						else 
							al_show_native_message_box(display , "ERROR" , "MAP BUILD" , "MAP CANNOT BE CREATED" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
					}
				}
				//ANULUJ PLIK
				else if( x < 650 && x > 450 && y < 430 && y > 380 )
				{
					Enter_the_String = false ;
					Mouse_Select     = 0     ;
					Maps->File_Name.clear()  ;
					Select           = false ;
					What_Draw		 = 10	 ;
				}
			}//if(Enter_the_String)

			else
			{
				//JESLI JESTESMY NA MAPIE
				if( x < 600 )
				{
					//PRZYGOTOWANIE DO POZYCJI NA VEKTORZE MAPY (30 WIELKOSC BITMAPY)
					y /= 30 ;
					x /= 30 ;

					//WPISUJEMY DO MAPY
					Maps->Update_Map_Edit( y , x , What_Draw ) ;

					//PRZYPISANIE ZMIENNEJ X Y MIEJSCA MYSZKI (PRZY 2KROTNYM WCISNIECIU MYSZKI BEZ JEJ RUSZENIA RYZUJE ELEMENT NA POZYCJI 0 0)
					x = events.mouse.x ;
					y = events.mouse.y ; 
				}

				//ZAZNACZENIE ELEMENTU Z EDYCJI
				else if( x < 760 && x > 640 && y < 80 && y > 20 )	// -[]
				{													//
					Select     = true ;
					selectedX1 = 640  ;
					selectedY1 = 20   ;
					selectedX2 = 760  ;
					selectedY2 = 80   ;
					What_Draw  = 0    ;
				}
				else if( x < 760 && x > 640 && y < 160 && y > 100 ) // []-
				{													// 
					Select     = true ;
					selectedX1 = 640  ;
					selectedY1 = 100  ;
					selectedX2 = 760  ;
					selectedY2 = 160  ;
					What_Draw  = 2    ;
				}
				else if( x < 685 && x > 625 && y < 300 && y > 180 ) //  |
				{													// [ ]
					Select     = true ;
					selectedX1 = 625  ;
					selectedY1 = 180  ;
					selectedX2 = 685  ;
					selectedY2 = 300  ;
					What_Draw  = 1    ;
				}
				else if( x < 775 && x > 715 && y < 300 && y > 180 ) // [ ]
				{													//  |
					Select     = true ;
					selectedX1 = 715  ;
					selectedY1 = 180  ;
					selectedX2 = 775  ;
					selectedY2 = 300  ;
					What_Draw  = 3    ;
				}
				else if( x < 730 && x > 670 && y < 380 && y > 320 ) // SCIANA
				{													// 
					Select     = true ;
					selectedX1 = 670  ;
					selectedY1 = 320  ;
					selectedX2 = 730  ;
					selectedY2 = 380  ;
					What_Draw  = 16   ;
				}
				else if( x < 730 && x > 670 && y < 460 && y > 400 ) // PUSTE MIEJSCE
				{													// 
					Select     = true ;
					selectedX1 = 670  ;
					selectedY1 = 400  ;
					selectedX2 = 730  ;
					selectedY2 = 460  ;
					What_Draw  = 15   ;
				}
				else if( x < 800 && x > 600 && y < 550 && y > 500 ) // ZAPISZ
				{													// 
					if( Maps->Check_Map(display) )
					{
						Select           = false ;
						Enter_the_String = true  ;
					}
				}
				else if( x < 800 && x > 600 && y < 600 && y > 550 ) // ANULUJ
				{													// 
					//KASUJEMY OBIEKT Screen
					End_Edit_ = true ; 
				}
			}//else
		}//if( state.buttons & 1 )
	}
}

void Edit_Screen::Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS)
{
	//OBSLUGA EVENTU CZASU
	if(events.type == ALLEGRO_EVENT_TIMER)
	{
		if( events.timer.source == FPS )
			draw = true ;
	}

	if(draw)
	{
		//draw = false ;

		al_draw_bitmap( Screen_Bitmap["Background_Stat"] , 600 , 0 , NULL ) ;

		Maps->Draw_Map() ;

		// BITMAPA , POZYCJA NA BITMAPIE 0 , 0 , WYMIARY BITMAPY 30 , 30 , POZYCJA 
		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head1"] , 0 , 0 , 30 , 30 , 640 , 20 , 60 , 60 , NULL ) ;
		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail1"] , 0 , 0 , 30 , 30 , 700 , 20 , 60 , 60 , NULL ) ;

		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail3"] , 0 , 0 , 30 , 30 , 640 , 100 , 60 , 60 , NULL ) ;
		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head3"] , 0 , 0 , 30 , 30 , 700 , 100 , 60 , 60 , NULL ) ;

		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head2"] , 0 , 0 , 30 , 30 , 625 , 180 , 60 , 60 , NULL ) ;
		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail2"] , 0 , 0 , 30 , 30 , 625 , 240 , 60 , 60 , NULL ) ;

		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail4"] , 0 , 0 , 30 , 30 , 715 , 180 , 60 , 60 , NULL ) ;
		al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head4"] , 0 , 0 , 30 , 30 , 715 , 240 , 60 , 60 , NULL ) ;

		al_draw_scaled_bitmap( Screen_Bitmap["Wall"] , 0 , 0 , 30 , 30 , 670 , 320 , 60 , 60 , NULL ) ;
		al_draw_scaled_bitmap( Screen_Bitmap["Empty"] , 0 , 0 , 30 , 30 , 670 , 400 , 60 , 60 , NULL ) ;

		al_draw_bitmap( Screen_Bitmap["Save"] , 600 , 500 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Cancel"] , 600 , 550 , NULL ) ;

		if(Enter_the_String)
		{
			al_draw_bitmap( Screen_Bitmap["Write_String"] , 150 , 150 , NULL ) ;
			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 155 , ALLEGRO_ALIGN_CENTER , "NAME MAP" ) ;
			al_draw_filled_rectangle( 190 , 240 , 460 , 275 , al_map_rgb( 255 , 255 , 255 ) ) ;
			al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 200, 250 , ALLEGRO_ALIGN_LEFT , Name_File_To_Save.c_str() ) ;

			al_draw_bitmap( Screen_Bitmap["Save"] , 150 , 380 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Cancel"] , 450 , 380 , NULL ) ;
		}

		switch(Mouse_Select)
		{
			case 1:

				if(Enter_the_String)
					al_draw_bitmap( Screen_Bitmap["Save2"] , 150 , 380 , NULL ) ;
				else
					al_draw_rectangle( 640 ,  20 , 760 ,  80 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;

				break ;

			case 2:

				if(Enter_the_String)
					al_draw_bitmap( Screen_Bitmap["Cancel2"] , 450 , 380 , NULL ) ;
				else
					al_draw_rectangle( 640 , 100 , 760 , 160 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;

				break ;

			case 3:

				al_draw_rectangle( 625 , 180 , 685 , 300 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;

				break ;

			case 4:

				al_draw_rectangle( 715 , 180 , 775 , 300 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;

				break ;

			case 5:

				al_draw_rectangle( 670 , 320 , 730 , 380 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;

				break ;

			case 6:

				al_draw_rectangle( 670 , 400 , 730 , 460 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;

				break ;

			case 7:

				al_draw_bitmap( Screen_Bitmap["Save2"] , 600 , 500 , NULL ) ;
		
				break ;

			case 8:

				al_draw_bitmap( Screen_Bitmap["Cancel2"] , 600 , 550 , NULL ) ;

				break ;

			default :

				break ;
		}


		if(Select)
			al_draw_rounded_rectangle( selectedX1 , selectedY1 , selectedX2 , selectedY2 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;

		//al_flip_display() ;
		//al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
	}
}

void Edit_Screen::Screen_Lighten()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Background_Stat"] , 600 , 0 , NULL ) ;

	Maps->Draw_Map() ;

	// BITMAPA , POZYCJA NA BITMAPIE 0 , 0 , WYMIARY BITMAPY 30 , 30 , POZYCJA 
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head1"] , 0 , 0 , 30 , 30 , 640 , 20 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail1"] , 0 , 0 , 30 , 30 , 700 , 20 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail3"] , 0 , 0 , 30 , 30 , 640 , 100 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head3"] , 0 , 0 , 30 , 30 , 700 , 100 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head2"] , 0 , 0 , 30 , 30 , 625 , 180 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail2"] , 0 , 0 , 30 , 30 , 625 , 240 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail4"] , 0 , 0 , 30 , 30 , 715 , 180 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head4"] , 0 , 0 , 30 , 30 , 715 , 240 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Wall"] , 0 , 0 , 30 , 30 , 670 , 320 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Empty"] , 0 , 0 , 30 , 30 , 670 , 400 , 60 , 60 , NULL ) ;

	al_draw_bitmap( Screen_Bitmap["Save"] , 600 , 500 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Cancel"] , 600 , 550 , NULL ) ;

	//USTAWIAMY STARY display (CHODZI O RYSOWANIE JAKBY WYBOR OKNA)
	al_set_target_bitmap( Prev_Target ) ;

	//PETLA RYSUJACA OBRAZ Z CORAZ MNIEJSZA PRZEZROCZYSTOSCIA
	for( float i = 0 ; i <= 1 ; i += 0.002 )
	{
		//ZMIANA KOLORU (JESLI DOBRZE ROZUMIEM) [BEZ TEGO NIE DZIALA TAK JAK TRZEBA]
		al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA ) ;

		//RYSUJEMY BITMAPE Z ODPOWIEDNIM KANALEM ALPHA (PRZEZROCZYSTOSC)
		al_draw_tinted_bitmap( Screen_Photo , al_map_rgba_f( 1 , 1 , 1 , i ) , 0 , 0 , 0 ) ;

		al_flip_display() ;
		al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
		//al_rest(5.0) ;
	}
}

void Edit_Screen::Screen_Fading()
{
	ALLEGRO_BITMAP * Prev_Target = al_get_target_bitmap() ;
	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Background_Stat"] , 600 , 0 , NULL ) ;

	Maps->Draw_Map() ;

	// BITMAPA , POZYCJA NA BITMAPIE 0 , 0 , WYMIARY BITMAPY 30 , 30 , POZYCJA 
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head1"] , 0 , 0 , 30 , 30 , 640 , 20 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail1"] , 0 , 0 , 30 , 30 , 700 , 20 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail3"] , 0 , 0 , 30 , 30 , 640 , 100 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head3"] , 0 , 0 , 30 , 30 , 700 , 100 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head2"] , 0 , 0 , 30 , 30 , 625 , 180 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail2"] , 0 , 0 , 30 , 30 , 625 , 240 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Tail4"] , 0 , 0 , 30 , 30 , 715 , 180 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Snake_Head4"] , 0 , 0 , 30 , 30 , 715 , 240 , 60 , 60 , NULL ) ;

	al_draw_scaled_bitmap( Screen_Bitmap["Wall"] , 0 , 0 , 30 , 30 , 670 , 320 , 60 , 60 , NULL ) ;
	al_draw_scaled_bitmap( Screen_Bitmap["Empty"] , 0 , 0 , 30 , 30 , 670 , 400 , 60 , 60 , NULL ) ;

	al_draw_bitmap( Screen_Bitmap["Save"] , 600 , 500 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Cancel"] , 600 , 550 , NULL ) ;

	//USTAWIAMY STARY display (CHODZI O RYSOWANIE JAKBY WYBOR OKNA)
	al_set_target_bitmap( Prev_Target ) ;

	for( float i = 1 ; i >= 0 ; i -= 0.002 )
	{
		//ZMIANA KOLORU (JESLI DOBRZE ROZUMIEM) [BEZ TEGO NIE DZIALA TAK JAK TRZEBA]
		al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA ) ;

		//RYSUJEMY BITMAPE Z ODPOWIEDNIM KANALEM ALPHA (PRZEZROCZYSTOSC)
		al_draw_tinted_bitmap( Screen_Photo , al_map_rgba_f( 1 , 1 , 1 , i ) , 0 , 0 , 0 ) ;

		al_flip_display() ;
		al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
		//al_rest(5.0) ;
	}
}
