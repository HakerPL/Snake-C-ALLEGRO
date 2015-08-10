#include "Top10_Screen.h"


void Top10_Screen::Handling_Mouse( ALLEGRO_EVENT &events ) 
{
	if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		x = events.mouse.x ;
		y = events.mouse.y ;
	}

	if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		//POBIERAMY STAN MYSZKI
		al_get_mouse_state(&state);

		//KLIKNIECIE LEWY PRZYCISK MYSZKI
		if( state.buttons & 1 )
			End_Top10_ = true ;
	}
}

void Top10_Screen::Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER *MapFPS )
{
	if(events.type == ALLEGRO_EVENT_KEY_DOWN)
		End_Top10_ = true ;
}

void Top10_Screen::Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS )
{
	//OBSLUGA EVENTU CZASU
	if(events.type == ALLEGRO_EVENT_TIMER)
	{
		if( events.timer.source == FPS )
			draw = true ;
	}

	if(draw)
	{
		al_draw_bitmap( Screen_Bitmap["Top10_Background"] , 0 , 0 , NULL ) ;

		//NAZWA PLANSZY I "TOP10"
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 200 , 40 , ALLEGRO_ALIGN_LEFT , "TOP10" ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 40 , ALLEGRO_ALIGN_LEFT , Name_File_.c_str() ) ;

		//ZMIENNE DLA PETLI FOR
		//char Nr = '1' ;
		int TextY ;
		int ForI ;

		//WYPIS TOP10
		for( TextY = 100 , ForI = 0 ; ForI < 10 ; ForI++ , TextY += 50 )
		{
			//std::cout << "Maps->Top10_Points[" << ForI << "] " << Maps->Top10_Points[ForI] << std::endl ;
			//std::cout << "Maps->Top10_Nick[" << ForI << "] " << Maps->Top10_Nick[ForI] << std::endl ;

			Top10_Points << Maps->Top10_Points[ForI] ;
			Top10_Nr << ForI + 1 ;

			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 80 , TextY , ALLEGRO_ALIGN_LEFT , Top10_Nr.str().c_str() ) ;
			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 150 , TextY , ALLEGRO_ALIGN_LEFT , Maps->Top10_Nick[ForI].c_str() ) ;
			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 550 , TextY , ALLEGRO_ALIGN_LEFT , Top10_Points.str().c_str() ) ;


			//CZYSZCZENIE STRINGSTREAM
			Top10_Points.str( std::string() ) ;
			Top10_Points.clear() ;

			Top10_Nr.str( std::string() ) ;
			Top10_Nr.clear() ;
		}
		//al_rest(20.0) ;
	}
}

void Top10_Screen::Screen_Lighten()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Top10_Background"] , 0 , 0 , NULL ) ;

	//NAZWA PLANSZY I "TOP10"
	al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 200 , 40 , ALLEGRO_ALIGN_LEFT , "TOP10" ) ;
	al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 40 , ALLEGRO_ALIGN_LEFT , Name_File_.c_str() ) ;

	//ZMIENNE DLA PETLI FOR
	//char Nr = '1' ;
	int TextY ;
	int ForI ;

	//WYPIS TOP10
	for( TextY = 100 , ForI = 0 ; ForI < 10 ; ForI++ , TextY += 50 )
	{
		//std::cout << "Maps->Top10_Points[" << ForI << "] " << Maps->Top10_Points[ForI] << std::endl ;
		//std::cout << "Maps->Top10_Nick[" << ForI << "] " << Maps->Top10_Nick[ForI] << std::endl ;

		Top10_Points << Maps->Top10_Points[ForI] ;
		Top10_Nr << ForI + 1 ;

		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 80 , TextY , ALLEGRO_ALIGN_LEFT , Top10_Nr.str().c_str() ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 150 , TextY , ALLEGRO_ALIGN_LEFT , Maps->Top10_Nick[ForI].c_str() ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 550 , TextY , ALLEGRO_ALIGN_LEFT , Top10_Points.str().c_str() ) ;


		//CZYSZCZENIE STRINGSTREAM
		Top10_Points.str( std::string() ) ;
		Top10_Points.clear() ;

		Top10_Nr.str( std::string() ) ;
		Top10_Nr.clear() ;
	}
	//al_rest(20.0) ;
	
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

void Top10_Screen::Screen_Fading()
{
	ALLEGRO_BITMAP * Prev_Target = al_get_target_bitmap() ;
	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Top10_Background"] , 0 , 0 , NULL ) ;

	//NAZWA PLANSZY I "TOP10"
	al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 200 , 40 , ALLEGRO_ALIGN_LEFT , "TOP10" ) ;
	al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 400 , 40 , ALLEGRO_ALIGN_LEFT , Name_File_.c_str() ) ;

	//ZMIENNE DLA PETLI FOR
	//char Nr = '1' ;
	int TextY ;
	int ForI ;

	//WYPIS TOP10
	for( TextY = 100 , ForI = 0 ; ForI < 10 ; ForI++ , TextY += 50 )
	{
		//std::cout << "Maps->Top10_Points[" << ForI << "] " << Maps->Top10_Points[ForI] << std::endl ;
		//std::cout << "Maps->Top10_Nick[" << ForI << "] " << Maps->Top10_Nick[ForI] << std::endl ;

		Top10_Points << Maps->Top10_Points[ForI] ;
		Top10_Nr << ForI + 1 ;

		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 80 , TextY , ALLEGRO_ALIGN_LEFT , Top10_Nr.str().c_str() ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 150 , TextY , ALLEGRO_ALIGN_LEFT , Maps->Top10_Nick[ForI].c_str() ) ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 550 , TextY , ALLEGRO_ALIGN_LEFT , Top10_Points.str().c_str() ) ;


		//CZYSZCZENIE STRINGSTREAM
		Top10_Points.str( std::string() ) ;
		Top10_Points.clear() ;

		Top10_Nr.str( std::string() ) ;
		Top10_Nr.clear() ;
	}
	//al_rest(20.0) ;
	

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
