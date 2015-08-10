#include "Choice_Map_Screen.h"
//#include <iostream>


void Choice_Map_Screen::Handling_Mouse( ALLEGRO_EVENT &events )
{
	//EVENT MYSZKI
	if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		x = events.mouse.x ;
		y = events.mouse.y ;

		if( Show_Button ) 
		{
			//EDYCJA LUB START (STATE = EDIT LUB STATE = GAME)
			if( x > 110 && x < 210 && y > 500 && y < 550 )
				Mouse_Select = 1 ;
			//KASUJ LUB TOP10 (STATE = EDIT LUB STATE = GAME)
			else if( x > 240 && x < 340 && y > 500 && y < 550 )
				Mouse_Select = 2 ;
			//POWROT DO MENU
			else if( x > 590 && x < 690 && y > 500 && y < 550 )
				Mouse_Select = 3 ;
			//MAPA LEWA
			else if( x > 125 && x < 375 && y > 200 && y < 450 )
			{
				if(!Zero_Map)
					Mouse_Select = 4 ;
			}
			//MAPA PRAWA
			else if( x > 425 && x < 675 && y > 200 && y < 450 )
			{	
				if(!Zero_Map)
					if(!One_Map)
						Mouse_Select = 5 ;
			}
			//STRZALKA LEWA
			else if ( ( x < 97 && x > 49 && y < 322 && y > 276 ) || Mouse_In_Triangle( 4 , 298 , 49 , 256 , 49 , 343 , x , y ) )
			{
				Mouse_Select = 6 ;
			}
			//PRAWA STRZALAK
			else if ( ( x < 750 && x > 702 && y < 322 && y > 276 ) || Mouse_In_Triangle( 797 , 298 , 750 , 256 , 750 , 343 , x , y ) )
			{
				Mouse_Select = 7 ;
			}
			else
				Mouse_Select = 0 ;
		}
		else
		{
			//POWROT DO MENU
			if( x > 590 && x < 690 && y > 500 && y < 550 )
				Mouse_Select = 3 ;
			//MAPA LEWA
			else if( x > 125 && x < 375 && y > 200 && y < 450 )
			{
				if(!Zero_Map)
					Mouse_Select = 4 ;
			}
			//MAPA PRAWA
			else if( x > 425 && x < 675 && y > 200 && y < 450 )
			{	
				if(!Zero_Map)
					if(!One_Map)
						Mouse_Select = 5 ;
			}
			//STRZALKA LEWA
			else if ( ( x < 97 && x > 49 && y < 322 && y > 276 ) || Mouse_In_Triangle( 4 , 298 , 49 , 256 , 49 , 343 , x , y ) )
			{
				Mouse_Select = 6 ;
			}
			//PRAWA STRZALAK
			else if ( ( x < 750 && x > 702 && y < 322 && y > 276 ) || Mouse_In_Triangle( 797 , 298 , 750 , 256 , 750 , 343 , x , y ) )
			{
				Mouse_Select = 7 ;
			}
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
			if( Show_Button ) 
			{
				//EDYCJA LUB START (STATE = EDIT LUB STATE = GAME)
				if( x > 110 && x < 210 && y > 500 && y < 550 )
				{
					//KASUJEMY OBIEKT
					End_Choice_Map_ = true ;

					//URUCHAMIAMY GRE LUB EDYCJE
					if(STATE == EDIT)
						Edit_ = true ;
					else if(STATE == GAME)
						Start_Game_ = true ;

					//KASUJEMY ZAZNACZENIE
					Mouse_Select = 0 ;
					Select = false ;
				}

				//KASUJ LUB TOP10 (STATE = EDIT LUB STATE = GAME)
				if( x > 240 && x < 340 && y > 500 && y < 550 ) 
				{
					//std::cout << "                KASUJ /// TOP10" << std::endl ;
					if(STATE == EDIT)
					{
						//std::cout << "                  KASUJ" << std::endl ;
						int Choice = al_show_native_message_box(display , "DETELE MAP" , "DETELE MAP" , "ARE YOU SURE, YOU WANT DETELE MAP ?" , NULL , ALLEGRO_MESSAGEBOX_YES_NO ) ;
				
						if(Choice == 1 )
							if(Delete_Map())
							{
								Load_File_Map() ;

								al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
								al_flip_display() ;
		
								al_show_native_message_box(display , "SUCCESS" , "MAP DELETE" , "MAP WAS SUCCESS DELETE" , NULL , ALLEGRO_MESSAGEBOX_OK_CANCEL ) ;
							}
					}
					else if(STATE == GAME)
					{
						//std::cout << "                   TOP10" << std::endl ;
						STATE = TOP10 ;
					}
				}
			}

			if(!Zero_Map)
			{
				//MAPA LEWA
				if( x > 125 && x < 375 && y > 200 && y < 450 )
				{
					Show_Button = true ;
					Select = true ;
					Name_Selected_Map = Files_Name[Map1] ;
					Select_Map = Map1 ;
					//std::cout << "Map1 = " << Map1 << "  Select_Map = " << Select_Map << "  Name_Selected_Map = " << Name_Selected_Map << "  Files_Name[Map1] = " << Files_Name[Map1] << std::endl ;
				}
				//MAPA PRAWA
				if(!One_Map)
				{	
					if( x > 425 && x < 675 && y > 200 && y < 450 )
					{
						Show_Button = true ;
						Select = true ;
						Name_Selected_Map = Files_Name[Map2] ;
						Select_Map = Map2 ;
						//std::cout << "Map2 = " << Map2 << "  Select_Map = " << Select_Map << "  Name_Selected_Map = " << Name_Selected_Map << "  Files_Name[Map2] = " << Files_Name[Map2] << std::endl ;
					}
				} 
			}

			if( x > 590 && x < 690 && y > 500 && y < 550 ) // ANULUJ
			{													// 
				//KASUJEMY OBIEKT Screen
				End_Choice_Map_ = true ;

				//KASUJEMY ZAZNACZENIE MYSZKA
				//Mouse_Select = 0 ; 
				//Show_Button = false ;
				Back_To_Menu = true ;
				//Select = false ;

				//USTAWIAMT ZMIENNE TAK ABY PRZY NASTEPNYM WEJSCIU W EDYCJE WSZYSTKO DZIALALO
				Edit_ = true ;
				Choice_Map_ = true ;
			}
			//LEWA STRZALKA
			else if ( ( x < 97 && x > 49 && y < 322 && y > 276 ) || Mouse_In_Triangle( 4 , 298 , 49 , 256 , 49 , 343 , x , y ) )
			{
				//JESLI SA JAKIES MAPY TO JE WYPISUJEMY
				if( !Zero_Map )
					if( Which_Screen > 0 )
					{
						//ZMNIEJSZAMY WARTOSCI
						Which_Screen-- ;
						Map1--		   ;
						Map2--		   ;
					}
			}
			//PRAWA STRZALAK
			else if ( ( x < 750 && x > 702 && y < 322 && y > 276 ) || Mouse_In_Triangle( 797 , 298 , 750 , 256 , 750 , 343 , x , y ) )
			{
				//JESLI SA JAKIES MAPY TO JE WYPISUJEMY
				if( !Zero_Map )
					if( !One_Map )
						if( Which_Screen < Miniature_Map.size() - 2 )
						{
							//ZMNIEJSZAMY WARTOSCI
							Which_Screen++ ;
							Map1++		   ;
							Map2++		   ;
						}
			}
		}
	}
}

void Choice_Map_Screen::Handling_Keyboard( ALLEGRO_EVENT &events , ALLEGRO_KEYBOARD_STATE &keyState , ALLEGRO_TIMER *MapFPS )
{
	if(events.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		if( al_key_down( &keyState , ALLEGRO_KEY_LEFT ) )
		{
			//JESLI SA JAKIES MAPY TO JE WYPISUJEMY
			if( !Zero_Map )
				if( Which_Screen > 0 )
				{
					//ZMNIEJSZAMY WARTOSCI
					Which_Screen-- ;
					Map1--		   ;
					Map2--		   ;
				}
		}
		else if( al_key_down( &keyState , ALLEGRO_KEY_RIGHT ) )
		{
			//JESLI SA JAKIES MAPY TO JE WYPISUJEMY
			if( !Zero_Map )
				if(!One_Map)
					if( Which_Screen < Miniature_Map.size() - 2 )
					{
						//ZMNIEJSZAMY WARTOSCI
						Which_Screen++ ;
						Map1++		   ;
						Map2++		   ;
					}
		}
	}
}

void Choice_Map_Screen::Load_File_Map()
{
	//CZYSCIMY MINIATURY I NAZWY
	for(int i = 0 ; i < Miniature_Map.size() ; i++)
		al_destroy_bitmap( Miniature_Map[i] ) ;
	//std::cout << "Load_File 111111111" << std::endl ;
	Miniature_Map.clear() ;
	Files_Name.clear()	  ;

	//USTAWIAMY ZMIENNE NA FALSE
	Zero_Map	= false ;
	One_Map		= false ;
	Show_Button = false ;
	Select		= false ;

	//KTORY EKRAN WYSWIETLIC
	Which_Screen = 0 ;

	//ZAZNACZONA POZYCJA PRZEZ MYSZKE
	Mouse_Select = 0 ;

	//ZMIENNE DO WYSWIETLANIA MAP
	Map1 = 0 ;
	Map2 = 1 ;

	//std::cout << "Load_File 22222222" << std::endl ;
	//LADUJEMY BITMAPE ZEBY STWORZYC MINIATURE
	std::vector< ALLEGRO_BITMAP *> Elements ;
	std::vector< ALLEGRO_BITMAP *> Screen_Map ;
	//WCZYTUJEMY WEZA
	for(int i = 0 ; i < 14 ; i++)
	{
		std::stringstream snake ;
		snake << "Graphics\\Snake\\" << i + 1 << ".png" ;
		Elements.push_back( load_bitmap_at_size( snake.str().c_str() , 12.5 , 12.5 ) ) ;
	}
	//WCZYTUJEMY SPAWN
	Elements.push_back( load_bitmap_at_size( "Graphics\\Eat_Me\\1.png" , 12.5 , 12.5 ) ) ;
	//WCZYTUJEMY EMPTY
	Elements.push_back( load_bitmap_at_size( "Graphics\\Empty.png" , 12.5 , 12.5 ) ) ;
	//WCZYTUJEMY SCIANE
	Elements.push_back( load_bitmap_at_size( "Graphics\\Wall\\1.png" , 12.5 , 12.5 ) ) ;

	for(int i = 0 ; i < 400 ; i++)
		Screen_Map.push_back( Elements[15] ) ;

	DIR* pdir = NULL ;	//WSKAZNIK SCIEZKI

	dirent* ps_dirent = NULL ;		//PRZECHOWUJE DANE O PLIKU. readdir ZWRACA STRUKTURE dirent struct

	pdir = opendir (".\\Maps") ;			//OTWIERANIE SCIEZKI ////////O ILE ZADZIALA TAKA
	
	//JESLI SCIEZKA JEST OTWARTA
	if(pdir)
	{
		//CZYTAMY POKOLEI PLIKI
		while(ps_dirent = readdir(pdir))
		{
			//POBIERAMY NAZWE PLIKU
			std::string a = ps_dirent->d_name ;
			//SZUKAMY OSTATNIEJ KROPKI
			unsigned ilosc = a.find_last_of(".") + 1;
			//POBIERAMY NAPISZ PO KROPCE
			a = a.substr(ilosc) ;

			//SPRAWDZAMY CZY TO MOJE ROZSZEZENIE
			if( a == "adi")    //WLASNE ROZSZEZENIE
			{
				//std::cout << "111111111111" << std::endl ;

				std::string bb = ps_dirent->d_name ;
				std::string aa = "Maps\\" + bb ;
				//OTWIERAMY PLIK
				std::fstream File ( aa.c_str() , std::ios::in | std::ios::binary ) ;
				//ZMIENNA DO SPRAWDZENIA KODU
				std::string Code_From_File ;
				//USTAWIAMY CZYTANIE NA KONIEC - DLUGOSC KODU PLIKU 
				//File.seekg( Check_File.size() , std::ios::end ) ;
				//CZYTAMY KOD Z PLIKU
				//File.read( (char*) &Code_From_File , Check_File.size() ) ;

				//JESLI JEST TAKI ZAM JAK W PROGRAMIE
				if( Return_Place_of_String( File , Check_File ) != -1 )  
				{
					//std::cout << "2222222222222" << std::endl ;
					//WSKAZNIK CZYTANIA USTAWIAMY NA POCZATEK
					File.seekg( 0 ) ;

					//CO MAMY WGRAC DO MAPY
					int What[400] ;

					File.read( (char*) &What , sizeof(What) ) ;
					for(int y = 0 ; y < 400 ; y++)
					{
						//std::cout << "              " << " Y = " << y << std::endl ;
						//PUSTE MIEJSCE
						if(What[y] == 1)
						{
							//std::cout << "What[" << y << "] " << What[y] << std::endl ;
							Screen_Map[ y ] = Elements[15] ;
						}
						//SCIANA
						if(What[y] == 2)
						{
							//std::cout << "What[" << y << "] " << What[y] << std::endl ;
							Screen_Map[ y ] = Elements[16] ;
						}
						//GLOWA WEZA  -[]
						else if(What[y] == 3)
						{
							//std::cout << "What[" << y << "] " << What[y] << std::endl ;
							Screen_Map[ y ] = Elements[0] ;
						}
						//OGON WEZA []-
						else if(What[y] == 4)
						{
							//std::cout << "What[" << y << "] " << What[y] << std::endl ;
							Screen_Map[ y ] = Elements[8] ;
						}
						
					}

					//POPRAWIAMY ZDJECIA WEZA (ZEBY PASOWALY DO SWOICH POZYCJI)
					for(int y = 0 ; y < 20 ; y++)
					{
						for(int x = 0 ; x < 20 ; x++)
						{
							if(Screen_Map[ (y * 20) + x ] == Elements[0])
							{
								if( x == 0 && y == 0 )
								{
									if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
									{	
										//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[1] ;
										Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
									}
									else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[0] ;
										Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
									}
								}//if( x == 0 && y == 0 )
								else if( x == 19 && y == 19 )
								{
									if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[3] ;
										Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
									}
									else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[2] ;
										Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
									}
								}//else if( x == 19 && y == 19 )
								else if( x == 19 && y == 0 )
								{
									if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
									{	
										//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[1] ;
										Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
									}
									else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[2] ;
										Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
									}
								}//else if( x == 19 && y == 0 )
								else if( x == 0 && y == 19 )
								{
									if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[3] ;
										Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
									}
									else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[0] ;
										Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
									}
								}//else if( x == 0 && y == 19 )
								else if( y == 0 )
								{
									if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
									{	
										//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[1] ;
										Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
									}
									else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[2] ;
										Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
									}
									else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[0] ;
										Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
									}
								}//else if( y == 0 )
								else if( y == 19 )
								{
									if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[3] ;
										Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
									}
									else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[2] ;
										Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
									}
									else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[0] ;
										Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
									}
								}//else if( y == 19 )
								else if( x == 0 )
								{
									if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
									{	
										//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[1] ;
										Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
									}
									else if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[3] ;
										Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
									}
									else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[0] ;
										Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
									}
								}//else if( x == 0 )
								else if( x == 19 )
								{
									if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
									{	
										//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[1] ;
										Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
									}
									else if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[3] ;
										Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
									}
									else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[2] ;
										Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
									}
								}//else if( x == 19 )
								else
								{
									if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
									{	
										//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[1] ;
										Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
									}
									else if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[3] ;
										Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
									}
									else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[2] ;
										Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
									}
									else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
									{
										//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
										Screen_Map[ y * 20 + x ] = Elements[0] ;
										Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
									}
								}//else
							}//if(Screen_Map[ (y * 20) + x ] == Elements[0])
						}//for(int x = 0 ; x < 20 ; x++)
					}//for(int y = 0 ; y < 20 ; y++)

					//ZAPAMIETUJE POPRZEDNI WSKAZNIK NA OBRAZ
					ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();
					//TWORZYMY BITMAPE
					Miniature_Map.push_back( al_create_bitmap( 250 , 250 ) ) ;
					//USTAWIAMY RYSOWANIE NA NOWA BITMAPE
					al_set_target_bitmap( Miniature_Map[ (Miniature_Map.size() - 1) ] ) ;
					//RYSUJEMY 
					float y = 0 , x = 0 , wielkosc = 12.5 ;
					for(int my = 0 ; my < 20 ; my++)
					{
						for(int mx = 20 * my ; mx < 20 * (my + 1) ; mx++)
						{
							al_draw_bitmap( Screen_Map[mx] , x , y , NULL) ;
							x += wielkosc ;
						}

						x = 0 ;
						y += wielkosc ;
					}
					//ZMIENIAMY RYSOWANIE NA POPRZEDNI EKRAN
					al_set_target_bitmap( prev_target ) ;
					//ZAPISUJEMY NAZWE PLIKU
					Files_Name.push_back( ps_dirent->d_name ) ;
				}//if( Return_Place_of_String( File , Check_File ) != 0 )  
			}//if( a == "adi")    //WLASNE ROZSZEZENIE
		}//while(ps_dirent = readdir(pdir))
		

		//KASUJEMY CHWILOWE BITMAPY
		for(int i = 0 ; i < Elements.size() ; i++)
			al_destroy_bitmap(Elements[i]) ;

		//std::cout << "ILOSC MINIATOR " << Miniature_Map.size() << std::endl ;
		//std::cout << "ILOSC NAZW " << Files_Name.size() << std::endl ;

		//EMPTY ZWRACA TRUE JAK VEKTOR JEST PUSTY
		if( !Miniature_Map.empty() )
		{
			//JESLI JEST TYLKO JEDNA MAPA
			if( Miniature_Map.size() == 1 )
				One_Map = true ;
		}
		else //JESLI NIE MA MAP
			Zero_Map = true ;

		//std::cout << "Load_File 3333333" << std::endl ;
	}//if(pdir)
	else 
	{
		al_show_native_message_box(display , "ERROR PATH" , "ERROR PATH" , "CAN'T OPEN PATH (\\Maps\\...)" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		End_Choice_Map_ = true ;
		Start_Game_     = true ;
		Back_To_Menu    = true ;
	}
}	

void Choice_Map_Screen::Draw_Screen( ALLEGRO_EVENT &events , ALLEGRO_TIMER *FPS , ALLEGRO_TIMER *MapFPS)
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

		al_draw_bitmap( Screen_Bitmap["Map_Background"] , 100 , 0 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Left_Background"] , 0 , 0 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Right_Background"] , 700 , 0 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Left_Arrow"] , 0 , 250 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Right_Arrow"] , 700 , 250 , NULL ) ;
		al_draw_bitmap( Screen_Bitmap["Back"] , 590 , 500 , NULL ) ;
		
		if(Zero_Map)
		{
			al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 120 , 150 , ALLEGRO_ALIGN_LEFT , "IN FOLDER \"MAPS\"" )  ;
		    al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 120 , 250 , ALLEGRO_ALIGN_LEFT , "THERE IS NO MAPS" )  ;
		}
		else
		{
			//WYPISUJEMY PIERWSZA MAPE
			al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 125 , 150 , ALLEGRO_ALIGN_LEFT , Files_Name[Map1].c_str() ) ;
			al_draw_bitmap( Miniature_Map[Map1] , 125 , 200 , NULL ) ;

			if( !One_Map )
			{
				//WYPISUJEMY DRUGA MAPE (O ILE JEST)
				al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 425 , 150 , ALLEGRO_ALIGN_LEFT , Files_Name[Map2].c_str() ) ;
				al_draw_bitmap( Miniature_Map[Map2] , 425 , 200 , NULL ) ;
			}
		}

		if(Show_Button)
		{
			if( STATE == EDIT )
			{
				al_draw_bitmap( Screen_Bitmap["Delete"] , 240 , 500 , NULL ) ;
				al_draw_bitmap( Screen_Bitmap["Edit"] , 110 , 500 , NULL )	 ;
			}
			else
			{
				al_draw_bitmap( Screen_Bitmap["Top10"] , 240 , 500 , NULL )  ;
				al_draw_bitmap( Screen_Bitmap["Play"] , 110 , 500 , NULL )	 ;
			}
		}

		switch( Mouse_Select )
		{

			case 1:

				if( STATE == EDIT )
					al_draw_bitmap( Screen_Bitmap["Edit2"] , 110 , 500 , NULL )	 ;
				else
					al_draw_bitmap( Screen_Bitmap["Play2"] , 110 , 500 , NULL )	 ;
				
				break ;

			case 2:
				
				if( STATE == EDIT )
					al_draw_bitmap( Screen_Bitmap["Delete2"] , 240 , 500 , NULL ) ;
				else
					al_draw_bitmap( Screen_Bitmap["Top102"] , 240 , 500 , NULL ) ;
				
				break ;

			case 3:

				al_draw_bitmap( Screen_Bitmap["Back2"] , 590 , 500 , NULL ) ;

				break ;

			case 4:

				if(!Zero_Map)
					al_draw_rectangle( 125 , 200 , 375 , 450 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;
				break ;

			case 5:

				if(!Zero_Map)
					al_draw_rectangle( 425 , 200 , 675 , 450 , al_map_rgb( 0 , 255 , 0 ) , 10 ) ;
				break ;

			case 6:		//LEWA STRZALKA

				al_draw_bitmap( Screen_Bitmap["Left_Arrow2"] , 0 , 250 , NULL ) ;

				break ;

			case 7:		//PRAWA STRZALKA

				al_draw_bitmap( Screen_Bitmap["Right_Arrow2"] , 700 , 250 , NULL ) ;

				break ;

			default :

				break ;
		}


		if(Select)
		{
			if(Map1 == Select_Map)
				al_draw_rounded_rectangle( 125 , 200 , 375 , 450 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;
			else if(Map2 == Select_Map)
				al_draw_rounded_rectangle( 425 , 200 , 675 , 450 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;
		}

		//al_flip_display() ;
		//al_clear_to_color(al_map_rgb(0 , 0 , 0)) ;
	}
}

bool Choice_Map_Screen::Delete_Map()
{
	std::string Name_Delete = "Maps\\" + Name_Selected_Map ;

	if( remove( Name_Delete.c_str() ) != 0 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR DELETE" , "I CAN'T DELETE THAT MAP" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}
	else
		return true ;
}

void Choice_Map_Screen::Screen_Lighten()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Map_Background"] , 100 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Left_Background"] , 0 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Right_Background"] , 700 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Left_Arrow"] , 0 , 250 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Right_Arrow"] , 700 , 250 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Back"] , 590 , 500 , NULL ) ;
		
	if(Zero_Map)
	{
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 120 , 150 , ALLEGRO_ALIGN_LEFT , "IN FOLDER \"MAPS\"" )  ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 120 , 250 , ALLEGRO_ALIGN_LEFT , "THERE IS NO MAPS" )  ;
	}
	else
	{
		//WYPISUJEMY PIERWSZA MAPE
		al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 125 , 150 , ALLEGRO_ALIGN_LEFT , Files_Name[Map1].c_str() ) ;
		al_draw_bitmap( Miniature_Map[Map1] , 125 , 200 , NULL ) ;

		if( !One_Map )
		{
			//WYPISUJEMY DRUGA MAPE (O ILE JEST)
			al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 425 , 150 , ALLEGRO_ALIGN_LEFT , Files_Name[Map2].c_str() ) ;
			al_draw_bitmap( Miniature_Map[Map2] , 425 , 200 , NULL ) ;
		}
	}

	if(Show_Button)
	{
		if( STATE == EDIT )
		{
			al_draw_bitmap( Screen_Bitmap["Delete"] , 240 , 500 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Edit"] , 110 , 500 , NULL )	 ;
		}
		else
		{
			al_draw_bitmap( Screen_Bitmap["Top10"] , 240 , 500 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Play"] , 110 , 500 , NULL )	 ;
		}
	}

	if(Select)
	{
		if(Map1 == Select_Map)
			al_draw_rounded_rectangle( 125 , 200 , 375 , 450 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;
		else if(Map2 == Select_Map)
			al_draw_rounded_rectangle( 425 , 200 , 675 , 450 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;
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

void Choice_Map_Screen::Screen_Fading()
{
	//TWORZYMY BITMAPE ORAZ KOPIUJEMY OBECNY display
	Screen_Photo = al_create_bitmap( 800 , 600 ) ;
	ALLEGRO_BITMAP *Prev_Target = al_get_target_bitmap() ;

	//USTAWIAMY RYSOWANIE NA NOWEJ BITMAPIE
	al_set_target_bitmap( Screen_Photo ) ;

	al_draw_bitmap( Screen_Bitmap["Map_Background"] , 100 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Left_Background"] , 0 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Right_Background"] , 700 , 0 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Left_Arrow"] , 0 , 250 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Right_Arrow"] , 700 , 250 , NULL ) ;
	al_draw_bitmap( Screen_Bitmap["Back"] , 590 , 500 , NULL ) ;
		
	if(Zero_Map)
	{
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 120 , 150 , ALLEGRO_ALIGN_LEFT , "IN FOLDER \"MAPS\"" )  ;
		al_draw_text( Font_Big , al_map_rgb(44 , 100 , 255) , 120 , 250 , ALLEGRO_ALIGN_LEFT , "THERE IS NO MAPS" )  ;
	}
	else
	{
		//WYPISUJEMY PIERWSZA MAPE
		al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 125 , 150 , ALLEGRO_ALIGN_LEFT , Files_Name[Map1].c_str() ) ;
		al_draw_bitmap( Miniature_Map[Map1] , 125 , 200 , NULL ) ;

		if( !One_Map )
		{
			//WYPISUJEMY DRUGA MAPE (O ILE JEST)
			al_draw_text( Font_Smal , al_map_rgb(44 , 100 , 255) , 425 , 150 , ALLEGRO_ALIGN_LEFT , Files_Name[Map2].c_str() ) ;
			al_draw_bitmap( Miniature_Map[Map2] , 425 , 200 , NULL ) ;
		}
	}

	if(Show_Button)
	{
		if( STATE == EDIT )
		{
			al_draw_bitmap( Screen_Bitmap["Delete"] , 240 , 500 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Edit"] , 110 , 500 , NULL )	 ;
		}
		else
		{
			al_draw_bitmap( Screen_Bitmap["Top10"] , 240 , 500 , NULL ) ;
			al_draw_bitmap( Screen_Bitmap["Play"] , 110 , 500 , NULL )	 ;
		}
	}

	if(Select)
	{
		if(Map1 == Select_Map)
			al_draw_rounded_rectangle( 125 , 200 , 375 , 450 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;
		else if(Map2 == Select_Map)
			al_draw_rounded_rectangle( 425 , 200 , 675 , 450 , 10 , 10 , al_map_rgb( 0 , 0 , 255 ) , 10 ) ;
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
