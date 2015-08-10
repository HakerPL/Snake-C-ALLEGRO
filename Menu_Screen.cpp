#include "Menu_Screen.h"


void Menu_Screen::Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER *MapFPS )
{
	//EVENT KLAWIATURY
	if(events.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		//JESLI NIE JESTESMY W OPCJACH TO OBSLUGUJEMY MENU
		if(!Options)
		{
			//PORUSZANIE SIE PO MENU
			if( al_key_down(&keyState , ALLEGRO_KEY_UP) )
			{
				if(Select_Options <= 0)
					Select_Options = 0 ;
				else
					Select_Options-- ;
			}

			else if( al_key_down(&keyState , ALLEGRO_KEY_DOWN) )
			{
				if(Select_Options >= 4)
					Select_Options = 4 ;
				else
					Select_Options++ ;
			}

			//WYBOR POZYCJI NA MENU
			if(al_key_down(&keyState , ALLEGRO_KEY_ENTER))
				switch(Select_Options)
				{
					case 0:

						End_Menu_ = true ;
						STATE = GAME ;
						break ;

					case 1:
					
						End_Menu_ = true ;
						STATE = EDIT ;
						break ;

					case 2:

						End_Menu_ = true ;
						STATE = NEW_MAP ;
						break ;

					case 3:

						Select_Options = 0 ;
						Options = true ;
						break;

					case 4:

						End_Menu_ = true ;
						Game_ = false ;
						break ;
				}
		}//if(!Options)

		else   //OBSLUGA OPCJE
		{
			//PORUSZANIE SIE PO OPCJACH
			if( al_key_down(&keyState , ALLEGRO_KEY_UP) )
			{
				if(Select_Options <= 0)
					Select_Options = 0 ;
				else
					Select_Options-- ;
			}

			else if( al_key_down(&keyState , ALLEGRO_KEY_DOWN) )
			{
				if(Select_Options >= 3)
					Select_Options = 3 ;
				else
					Select_Options++ ;
			}

			//WYBOR POZYCJI NA MENU
			if(al_key_down(&keyState , ALLEGRO_KEY_ENTER))
				switch(Select_Options)
				{
					case 0:

						Difficulty = 1 ;
						difficultyX1 = 500 ;
						difficultyY1 = 225 ;
						difficultyX2 = 600 ;
						difficultyY2 = 275 ;
						break ;

					case 1:
					
						Difficulty = 2 ;
						difficultyX1 = 500 ;
						difficultyY1 = 300 ;
						difficultyX2 = 600 ;
						difficultyY2 = 350 ;
						break ;

					case 2:

						Difficulty = 3 ;
						difficultyX1 = 500 ;
						difficultyY1 = 375 ;
						difficultyX2 = 600 ;
						difficultyY2 = 425 ;
						break ;

					//WYJSCIE
					case 3:

						Options = false ;
						Select_Options = 0 ;
						break ;
				}//switch(Position)
		}//else   //OBSLUGA OPCJE
	}//if(events.type == ALLEGRO_EVENT_KEY_DOWN)
}

void Menu_Screen::Handling_Mouse( ALLEGRO_EVENT &events )
{
	//EVENT MYSZKI
	if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		x = events.mouse.x ;
		y = events.mouse.y ;

		//JESLI NIE JESTESMY W OPCJACH TO OBSLUGUJEMY MENU
		if(!Options)
		{
			//START
			if( x < (ScreenWidth / 2 - 100 + 199) && x > (ScreenWidth / 2 - 100) && y < 270 && y > 200 )
				Select_Options   = 0 ;

			//EDIT
			else if( x < (ScreenWidth / 2 - 11) && x > (ScreenWidth / 2 - 210) && y < 370 && y > 300 )
				Select_Options   = 1 ;

			//NEW MAP
			else if( x < (ScreenWidth / 2 + 209) && x > (ScreenWidth / 2 + 10) && y < 370 && y > 300 )
				Select_Options   = 2 ;

			//OPTIONS
			else if( x < (ScreenWidth / 2 - 100 + 199) && x > (ScreenWidth / 2 - 100) && y < 470 && y > 400 )
				Select_Options   = 3 ;

			//EXIT
			else if( x < (ScreenWidth / 2 - 100 + 199) && x > (ScreenWidth / 2 - 100) && y < 570 && y > 500 )
				Select_Options   = 4 ;
		}//if(!Options)

		else   //OBSLUGA OPCJI
		{
			//EASY
			if( x < 600 && x > 500 && y < 275 && y > 225 )
				Select_Options = 0 ;

			//MEDIUM
			else if( x < 600 && x > 500 && y < 350 && y > 300 )
				Select_Options = 1 ;

			//HARD
			else if( x < 600 && x > 500 && y < 425 && y > 375 )
				Select_Options = 2 ;

			//BACK
			else if( x < 400 && x > 200 && y < 430 && y > 380 )
				Select_Options = 3 ;
		}//else   //OBSLUGA OPCJI
	}//if(events.type == ALLEGRO_EVENT_MOUSE_AXES)

	//OBSLUGA KLIKNIECIA MYSZKI
	if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		//OBSLUGA MENU
		if(!Options)
		{
			//START
			if( x < (ScreenWidth / 2 - 100 + 199) && x > (ScreenWidth / 2 - 100) && y < 270 && y > 200 )
			{
				End_Menu_ = true ;
				STATE = GAME ;
			}

			//EDIT
			if( x < (ScreenWidth / 2 - 11) && x > (ScreenWidth / 2 - 210) && y < 370 && y > 300 )
			{
				End_Menu_ = true ;
				STATE = EDIT ;
			}

			//NEW MAP
			if( x < (ScreenWidth / 2 + 209) && x > (ScreenWidth / 2 + 10) && y < 370 && y > 300 )
			{
				End_Menu_ = true ;
				STATE = NEW_MAP ;
			}

			//OPTIONS
			if( x < (ScreenWidth / 2 - 100 + 199) && x > (ScreenWidth / 2 - 100) && y < 470 && y > 400 )
			{
				Select_Options = 0 ;
				Options = true ;
			}

			//EXIT
			if( x < (ScreenWidth / 2 - 100 + 199) && x > (ScreenWidth / 2 - 100) && y < 570 && y > 500 )
			{
				End_Menu_ = true ;
				Game_ = false ;
			}
		}//if(!Options)

		else   //OBSLUGA OPCJI
		{
			//EASY
			if( x < 600 && x > 500 && y < 275 && y > 225 )
			{
				Difficulty = 1 ;
				difficultyX1 = 500 ;
				difficultyY1 = 225 ;
				difficultyX2 = 600 ;
				difficultyY2 = 275 ;
			}

			//MEDIUM
			else if( x < 600 && x > 500 && y < 350 && y > 300 )
			{
				Difficulty = 2 ;
				difficultyX1 = 500 ;
				difficultyY1 = 300 ;
				difficultyX2 = 600 ;
				difficultyY2 = 350 ;
			}

			//HARD
			else if( x < 600 && x > 500 && y < 425 && y > 375 )
			{
				Difficulty = 3 ;
				difficultyX1 = 500 ;
				difficultyY1 = 375 ;
				difficultyX2 = 600 ;
				difficultyY2 = 425 ;
			}

			//BACK
			else if( x < 400 && x > 200 && y < 430 && y > 380 )
			{
				Options = false ;
				Select_Options = 0 ;
			}
		}//else   //OBSLUGA OPCJI
	}//if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
}

void Menu_Screen::Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS)
{
	//OBSLUGA EVENTU CZASU
	if(events.type == ALLEGRO_EVENT_TIMER)
	{
		if( events.timer.source == FPS )
			draw = true ;
	}
	//ODSWIEZAMY EKRAN
	if(draw)
	{
		//draw = false ;
		
		al_draw_bitmap( Screen_Bitmap["Menu_Background"] , 0 , 0 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Title"] , 100 , 0 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Start"] , ScreenWidth / 2 - 100 , 200 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Edit"] , ScreenWidth / 2 - 210 , 300 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["New"] , ScreenWidth / 2 + 10 , 300 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Options"] , ScreenWidth / 2 - 100 , 400 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Exit"] , ScreenWidth / 2 - 100 , 500 , NULL ) ;

		//OPCJE
		if(Options)
		{
			al_draw_bitmap( Screen_Bitmap["Options_Background"] , 150 , 150 , NULL ) ;
			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 155 , ALLEGRO_ALIGN_CENTER , "OPTIONS" ) ;
			al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 350 , 300 , ALLEGRO_ALIGN_CENTER , "DIFFICULTY" ) ;
			al_draw_bitmap( Screen_Bitmap["Options_Back"] , 200 , 380 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Options_Easy"] , 500 , 225 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Options_Medium"] , 500 , 300 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Options_Hard"] , 500 , 375 , NULL ) ;
		}

		switch(Select_Options)
		{
			case 0:

				if(Options)
					al_draw_bitmap( Screen_Bitmap["Options_Easy2"] , 500 , 225 , NULL ) ;
				else
					al_draw_bitmap( Screen_Bitmap["Start2"] , ScreenWidth / 2 - 100 , 200 , NULL ) ;
				break ;

			case 1:

				if(Options)
					al_draw_bitmap( Screen_Bitmap["Options_Medium2"] , 500 , 300 , NULL ) ;
				else
					al_draw_bitmap( Screen_Bitmap["Edit2"] , ScreenWidth / 2 - 210 , 300 , NULL ) ;
				break ;

			case 2:

				if(Options)
					al_draw_bitmap( Screen_Bitmap["Options_Hard2"] , 500 , 375 , NULL ) ;
				else 
					al_draw_bitmap( Screen_Bitmap["New2"] , ScreenWidth / 2 + 10 , 300 , NULL ) ;
				break ;

			case 3:

				if(Options) 
					al_draw_bitmap( Screen_Bitmap["Options_Back2"] , 200 , 380 , NULL ) ;
				else
					al_draw_bitmap( Screen_Bitmap["Options2"] , ScreenWidth / 2 - 100 , 400 , NULL ) ;
				break ;

			case 4:

				if(!Options)
					al_draw_bitmap( Screen_Bitmap["Exit2"] , ScreenWidth / 2 - 100 , 500 , NULL ) ;
				break ;
		}//switch(Select_Options)

		//ZAZNACZENIE WYBRANEGO POZIOMU TRUDNOSCI
		if(Options)
			al_draw_rounded_rectangle( difficultyX1 , difficultyY1 , difficultyX2 , difficultyY2 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;

		//al_flip_display() ;
		//al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
	}
}

void Menu_Screen::Screen_Lighten()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Menu_Background"] , 0 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Title"] , 100 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Start"] , ScreenWidth / 2 - 100 , 200 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Edit"] , ScreenWidth / 2 - 210 , 300 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["New"] , ScreenWidth / 2 + 10 , 300 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Options"] , ScreenWidth / 2 - 100 , 400 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Exit"] , ScreenWidth / 2 - 100 , 500 , NULL ) ;

	//USTAWIAMY STARY display (CHODZI O RYSOWANIE JAKBY WYBOR OKNA)
	al_set_target_bitmap( Prev_Target ) ;

	//PETLA RYSUJACA OBRAZ Z CORAZ MNIEJSZA PRZEZROCZYSTOSCIA
	for( float i = 0 ; i <= 1 ; i += 0.001 )
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

void Menu_Screen::Screen_Fading()
{
	for( float i = 1 ; i >= 0 ; i -= 0.001 )
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
