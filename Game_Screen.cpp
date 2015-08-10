#include "Game_Screen.h"


void Game_Screen::Handling_Mouse( ALLEGRO_EVENT &events )
{
	//EVENT MYSZKI
	if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		x = events.mouse.x ;
		y = events.mouse.y ;

		if(Enter_the_String)
		{
			//ZAPISZ NICK GRACZA
			if( x < 650 && x > 450 && y < 430 && y > 380 )
				Mouse_Select = 1 ;
			else
				Mouse_Select = 0 ;
		}
		else 
		{
			if( x < 800 && x > 600 && y < 350 && y > 300 )
				Mouse_Select = 1 ;
			else if( x < 800 && x > 600 && y < 410 && y > 360 )
				Mouse_Select = 2 ;
			else
				Mouse_Select = 0 ;
		}
	}//if(events.type == ALLEGRO_EVENT_MOUSE_AXES)

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
				//ZAPISZ NICK GRACZA
				if( x < 650 && x > 450 && y < 430 && y > 380 )
				{
					//SZUKAMY MIEJSCA W KTORE TRZEBA WPISAC DANE
					//JESLI JESZCZE DO NIEGO NIE DOSZLISMY TO PRZESTAWIAMY
					//DANE TAK ABY ZACHOWAC KOLEJNOSC
					for( int i = 9 ; i >= 0 ; i--)
					{
						if( i == Place_on_Top10 )
						{
							Maps->Top10_Points[i] = Maps->Snakess->Return_Points() ;
							Maps->Top10_Nick[i] = Nick ;
							break ;
						}
						else
						{
							Maps->Top10_Points[i] = Maps->Top10_Points[i - 1] ;
							Maps->Top10_Nick[i]   = Maps->Top10_Nick[i - 1]   ;
						}
					}
					Maps->Save_Top10(display) ;
					End_Start_Game_ = true ; 
					STATE = TOP10 ;
				}//if( x < 650 && x > 450 && y < 430 && y > 380 )
			}//if(Enter_the_String)
			else 
			{
				//START STOP GAME
				if( x < 800 && x > 600 && y < 350 && y > 300 )
					Start_Game = ( Start_Game == true ? false : true ) ;
				//WYJSCIE Z GRY
				else if( x < 800 && x > 600 && y < 410 && y > 360 )
					End_Start_Game_ = true ;
			}
		}//if( state.buttons & 1 )
	}//if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
}

void Game_Screen::Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER * MapFPS )
{
	if(events.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if( Game_Over )
		{
			//WPISUJEMY NAZWE GRACZA O ILE ZNAJDUJE SIE NA TOP10
			if(Enter_the_String)
			{
				//ZAPISUJEMY ZNAKI POBRANE Z KLAWIATURY
				Enter_Nick_MapName( keyState , Nick , Maps->Max ) ;
				//std::cout << " 1111111 " << Nick << " "<< Nick.size() << Maps->Max << std::endl ;
			}
		}
		//JESLI GRA CIAGLE TRWA
		else if( Start_Game )
			Maps->Snakess->Move_Snake( keyState , MapFPS ) ;
	}
}

void Game_Screen::Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS)
{
	//OBSLUGA EVENTU CZASU
	if(events.type == ALLEGRO_EVENT_TIMER)
	{
		//ZWYKLY CZAS DO RYSOWANIA EKRANU
		if( events.timer.source == FPS )
			draw = true ;
		//CZAS UAKTUALNIENIA MAPY (RYCH / KOLIZJE ...)
		else if( events.timer.source == MapFPS )
		{
			//ROZPOCZECIE GRY 
			if( Start_Game )
			{
				//JESLI GRA CIAGLE TRWA
				if( !Game_Over )
				{
					//std::cout << " !Game_Over " << std::endl ;
					//SPRAWDZAMY KOLIZJE DO ZAKONCZENIA GRY
					if( ! Maps->Snakess->Colision_Snake( Maps->Screen_Map , Maps->Elements[15] , Maps->Elements[14] ) )
					{
						//std::cout << " KOLIZJA " << std::endl ;
						//SPRAWDZAMY CZY WPASLISMY NA OWOC
						if( ! Maps->Snakess->Colision_Snake_Fruit( Maps->Screen_Map , Maps->Elements[14] , MapFPS ) )
						{
							//std::cout << " KOLIZJA OWOC " << std::endl ;
							//ZMIENIAMY POZYCJE WEZA ORAZ UAKTUALNIAMY MAPE
							Maps->Snakess->Update_Snake() ;
							//std::cout << " UAKTUALNIENIE WEZA " << std::endl ;
							Maps->Update_Map() ;
							//std::cout << " UAKTUALNIENIE MAPY " << std::endl ;
						}
						else
						{
							//UAKTUALNIENIE MAPY PO ZJEDZENIU OWOCA
							Maps->Update_Map() ;
							//std::cout << " UAKTUALNIENIE MAPY ELSE " << std::endl ;
						}
					}
					else
					{
						//std::cout << " ELSE OD KOLIZJI " << std::endl ;
						Game_Over = true ;
						Draw_Over = true ;
						//SPRAWDZAMY CZY GRACZ DOSTAL SIE DO TOP10
						if( Check_Score() )
							Enter_the_String = true ;
						else
						{
							End_Start_Game_ = true ;
						}
					}
				}//if( !Game_Over )
			}//if( Start_Game )
		}//else if( events.timer.source == MapFPS )
	}//if(events.type == ALLEGRO_EVENT_TIMER)

	if(draw)
	{
		//draw = false ;

		al_draw_bitmap( Screen_Bitmap["Background_Stat"] , 600 , 0 , NULL ) ;

		Maps->Draw_Map() ;

		//POBIERAMY PUNKTY
		Player_Points << Maps->Snakess->Return_Points() ;

		//PUNKTY GRACZA
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 0 , ALLEGRO_ALIGN_LEFT , "PLAYER POINTS" ) ;
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 30 , ALLEGRO_ALIGN_LEFT , Player_Points.str().c_str() ) ;

		//CZYSCIMY STRINGSTREAM
		Player_Points.str( std::string() ) ;
		Player_Points.clear() ;

		//POBIERAMY NAJLEPSZY WYNIK
		Player_Points << Maps->Top10_Points[0] ;

		//NAJLEPSZY WYNIK (TOP1)
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 70 , ALLEGRO_ALIGN_LEFT , "BEST SCORE" ) ;
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 100 , ALLEGRO_ALIGN_LEFT , Player_Points.str().c_str() ) ;
		
		//CZYSCIMY STRINGSTREAM
		Player_Points.str( std::string() ) ;
		Player_Points.clear() ;
		
		if( Start_Game )
			al_draw_bitmap( Screen_Bitmap["Pause"] , 600 , 300 , NULL ) ;
		else
		{
			//ZMIANA KOLORU (JESLI DOBRZE ROZUMIEM) [BEZ TEGO NIE DZIALA TAK JAK TRZEBA]
			al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA ) ;
			//RYSUJEMY BITMAPE Z ODPOWIEDNIM KANALEM ALPHA (PRZEZROCZYSTOSC)
			al_draw_tinted_bitmap( Screen_Bitmap["Pause_Screen"] , al_map_rgba_f( 1 , 1 , 1 , 0.7 ) , 0 , 0 , 0 ) ;
			al_draw_bitmap( Screen_Bitmap["Start"] , 600 , 300 , NULL ) ;
		}

		al_draw_bitmap( Screen_Bitmap["Back"] , 600 , 360 , NULL ) ;

		//INSTRUKCJA
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 450 , ALLEGRO_ALIGN_LEFT , "CONTROL" ) ;
		al_draw_bitmap( Screen_Bitmap["Arrow"], 600 , 500 , NULL ) ;

		if(Draw_Over)
		{
			//RYSUJEMY GAME OVER
			al_draw_bitmap( Screen_Bitmap["Game_Over"] , 100 , 100 , NULL ) ;
			al_flip_display() ;
			al_rest(3.0) ;
			Draw_Over = false ;
		}

		if(Enter_the_String)
		{
			al_draw_bitmap( Screen_Bitmap["Write_String"] , 150 , 150 , NULL ) ;
			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 155 , ALLEGRO_ALIGN_CENTER , "YOUR NAME" ) ;
			al_draw_filled_rectangle( 190 , 240 , 460 , 275 , al_map_rgb( 255 , 255 , 255 ) ) ;
			al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 200, 250 , ALLEGRO_ALIGN_LEFT , Nick.c_str() ) ;
			al_draw_bitmap( Screen_Bitmap["Save_Nick"] , 450 , 380 , NULL ) ;
		}

		switch(Mouse_Select)
		{
			case 1:

				if(Enter_the_String)
					al_draw_bitmap( Screen_Bitmap["Save_Nick2"] , 450 , 380 , NULL ) ;
				else
				{
					if( Start_Game )
						al_draw_bitmap( Screen_Bitmap["Pause2"] , 600 , 300 , NULL ) ;
					else
						al_draw_bitmap( Screen_Bitmap["Start2"] , 600 , 300 , NULL ) ;
				}

				break ;

			case 2:

				if(!Enter_the_String)
					al_draw_bitmap( Screen_Bitmap["Back2"] , 600 , 360 , NULL ) ;

				break ;

			default :

				break ;
		}


		//al_flip_display() ;
		//al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
	}//if(draw)
}

bool Game_Screen::Check_Score()
{
	//SPRAWDZAMY CZY OSTATNI ELEMENT TOP10_POINT JEST WIEKSZY OD PUNKTOW GRACZA
	if( Maps->Snakess->Return_Points() > Maps->Top10_Points[9] )
	{
		//JESLI GRACZ MA WIECEJ PUNKTOW TO SPRAWDZAMY NA KTORYM MIEJSCU GO UMIESCIC
		for( int i = 9 ; i >= 0 ; i--)
			if( Maps->Snakess->Return_Points() > Maps->Top10_Points[i] )
				Place_on_Top10 = i ;
	}
	else 
		return false ;

	return true ;
}

void Game_Screen::Screen_Lighten()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Background_Stat"] , 600 , 0 , NULL ) ;

	Maps->Draw_Map() ;

	//POBIERAMY PUNKTY
	Player_Points << Maps->Snakess->Return_Points() ;

	//PUNKTY GRACZA
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 0 , ALLEGRO_ALIGN_LEFT , "PLAYER POINTS" ) ;
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 30 , ALLEGRO_ALIGN_LEFT , Player_Points.str().c_str() ) ;

	//CZYSCIMY STRINGSTREAM
	Player_Points.str( std::string() ) ;
	Player_Points.clear() ;

	//POBIERAMY NAJLEPSZY WYNIK
	Player_Points << Maps->Top10_Points[0] ;

	//NAJLEPSZY WYNIK (TOP1)
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 70 , ALLEGRO_ALIGN_LEFT , "BEST SCORE" ) ;
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 100 , ALLEGRO_ALIGN_LEFT , Player_Points.str().c_str() ) ;
		
	//CZYSCIMY STRINGSTREAM
	Player_Points.str( std::string() ) ;
	Player_Points.clear() ;
		
	if( Start_Game )
		al_draw_bitmap( Screen_Bitmap["Pause"] , 600 , 300 , NULL ) ;
	else
	{
		//ZMIANA KOLORU (JESLI DOBRZE ROZUMIEM) [BEZ TEGO NIE DZIALA TAK JAK TRZEBA]
		al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA ) ;
		//RYSUJEMY BITMAPE Z ODPOWIEDNIM KANALEM ALPHA (PRZEZROCZYSTOSC)
		al_draw_tinted_bitmap( Screen_Bitmap["Pause_Screen"] , al_map_rgba_f( 1 , 1 , 1 , 0.7 ) , 0 , 0 , 0 ) ;
		al_draw_bitmap( Screen_Bitmap["Start"] , 600 , 300 , NULL ) ;
	}

	al_draw_bitmap( Screen_Bitmap["Back"] , 600 , 360 , NULL ) ;

	//INSTRUKCJA
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 450 , ALLEGRO_ALIGN_LEFT , "CONTROL" ) ;
	al_draw_bitmap( Screen_Bitmap["Arrow"], 600 , 500 , NULL ) ;

	if(Enter_the_String)
	{
		al_draw_bitmap( Screen_Bitmap["Write_String"] , 150 , 150 , NULL ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 155 , ALLEGRO_ALIGN_CENTER , "NAME MAP" ) ;
		al_draw_filled_rectangle( 190 , 240 , 460 , 275 , al_map_rgb( 255 , 255 , 255 ) ) ;
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 200, 250 , ALLEGRO_ALIGN_LEFT , Nick.c_str() ) ;
		al_draw_bitmap( Screen_Bitmap["Save_Nick"] , 450 , 380 , NULL ) ;
	}

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

void Game_Screen::Screen_Fading()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Background_Stat"] , 600 , 0 , NULL ) ;

	Maps->Draw_Map() ;

	//POBIERAMY PUNKTY
	Player_Points << Maps->Snakess->Return_Points() ;

	//PUNKTY GRACZA
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 0 , ALLEGRO_ALIGN_LEFT , "PLAYER POINTS" ) ;
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 30 , ALLEGRO_ALIGN_LEFT , Player_Points.str().c_str() ) ;

	//CZYSCIMY STRINGSTREAM
	Player_Points.str( std::string() ) ;
	Player_Points.clear() ;

	//POBIERAMY NAJLEPSZY WYNIK
	Player_Points << Maps->Top10_Points[0] ;

	//NAJLEPSZY WYNIK (TOP1)
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 70 , ALLEGRO_ALIGN_LEFT , "BEST SCORE" ) ;
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 100 , ALLEGRO_ALIGN_LEFT , Player_Points.str().c_str() ) ;
		
	//CZYSCIMY STRINGSTREAM
	Player_Points.str( std::string() ) ;
	Player_Points.clear() ;
		
	if( Start_Game )
		al_draw_bitmap( Screen_Bitmap["Pause"] , 600 , 300 , NULL ) ;
	else
	{
		//ZMIANA KOLORU (JESLI DOBRZE ROZUMIEM) [BEZ TEGO NIE DZIALA TAK JAK TRZEBA]
		al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA ) ;
		//RYSUJEMY BITMAPE Z ODPOWIEDNIM KANALEM ALPHA (PRZEZROCZYSTOSC)
		al_draw_tinted_bitmap( Screen_Bitmap["Pause_Screen"] , al_map_rgba_f( 1 , 1 , 1 , 0.7 ) , 0 , 0 , 0 ) ;
		al_draw_bitmap( Screen_Bitmap["Start"] , 600 , 300 , NULL ) ;
	}

	al_draw_bitmap( Screen_Bitmap["Back"] , 600 , 360 , NULL ) ;

	//INSTRUKCJA
	al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 600 , 450 , ALLEGRO_ALIGN_LEFT , "CONTROL" ) ;
	al_draw_bitmap( Screen_Bitmap["Arrow"], 600 , 500 , NULL ) ;

	if(Enter_the_String)
	{
		al_draw_bitmap( Screen_Bitmap["Write_String"] , 150 , 150 , NULL ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 155 , ALLEGRO_ALIGN_CENTER , "NAME MAP" ) ;
		al_draw_filled_rectangle( 190 , 240 , 460 , 275 , al_map_rgb( 255 , 255 , 255 ) ) ;
		al_draw_text( Font_Smal , al_map_rgb(255 , 0 , 0) , 200, 250 , ALLEGRO_ALIGN_LEFT , Nick.c_str() ) ;
		al_draw_bitmap( Screen_Bitmap["Save_Nick"] , 450 , 380 , NULL ) ;
	}

	//USTAWIAMY STARY display (CHODZI O RYSOWANIE JAKBY WYBOR OKNA)
	al_set_target_bitmap( Prev_Target ) ;

	//PETLA RYSUJACA OBRAZ Z CORAZ MNIEJSZA PRZEZROCZYSTOSCIA
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
