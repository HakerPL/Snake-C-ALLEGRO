#include "Snake.h"

void Snakes::Move_Snake( ALLEGRO_KEYBOARD_STATE keyState , ALLEGRO_TIMER * MapFPS )
{
	//JESLI KLIKNELISMY STRZALKI TO ZMIENIAMY KIERUNEK dir
	if( al_key_down(&keyState , ALLEGRO_KEY_UP) )
	{
		if(Snake[1][1] != (Snake[0][1] - 1 ) )
			dir = UP ;
	}
	else if( al_key_down(&keyState , ALLEGRO_KEY_DOWN) )
	{
		if(Snake[1][1] != (Snake[0][1] + 1 ) )
			dir = DOWN ;
	}
	else if( al_key_down(&keyState , ALLEGRO_KEY_LEFT) )
	{
		if(Snake[1][0] != (Snake[0][0] - 1 ) )
			dir = LEFT ;
	}
	else if( al_key_down(&keyState , ALLEGRO_KEY_RIGHT) )
	{
		if(Snake[1][0] != (Snake[0][0] + 1 ) )
			dir = RIGHT ;
	}

	//OSZUSTWO TYLDA ~
	if( al_key_down(&keyState , ALLEGRO_KEY_TILDE) )
		if( Frame > 2.5 )
		{
			Frame -= 0.5 ;
			//ZMIENIAMY SZYBKOSC ODSWIEZANIA MAPY
			al_set_timer_speed( MapFPS , 1 / Frame ) ;
		}
	
}

void Snakes::Update_Snake()
{
	switch(dir)
	{
		case UP:
			
			//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
			for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
			{
				if( i == 0 )
					Snake[0][1]-- ;
				else
				{
					Snake[i][1] = Snake[i - 1][1] ;
					Snake[i][0] = Snake[i - 1][0] ;
				}
			}

			break ;
			
		case DOWN:
			
			//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
			for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
			{
				if( i == 0 )
					Snake[0][1]++ ;
				else
				{
					Snake[i][1] = Snake[i - 1][1] ;
					Snake[i][0] = Snake[i - 1][0] ;
				}
			}

			break ;

		case LEFT:
			
			//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
			for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
			{
				if( i == 0 )
					Snake[0][0]-- ;
				else
				{
					Snake[i][1] = Snake[i - 1][1] ;
					Snake[i][0] = Snake[i - 1][0] ;
				}
			}

			break ;
			
		case RIGHT:
			
			//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
			for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
			{
				if( i == 0 )
					Snake[0][0]++ ;
				else
				{
					Snake[i][1] = Snake[i - 1][1] ;
					Snake[i][0] = Snake[i - 1][0] ;
				}
			}

			break ;
	}//switch(dir)
}

bool Snakes::Colision_Snake(const std::vector<ALLEGRO_BITMAP *> & Map , const ALLEGRO_BITMAP * EMPTY , const ALLEGRO_BITMAP * SPAWN)
{
	//std::cout << " POCZATEK " << std::endl ;
	//POZYCJA GLOWY WEZA
	int x = Snake[0][0] ; 
	int y = Snake[0][1] ;

	//std::cout << " x = " << x << " y = " << y << std::endl ;

	switch(dir)
	{
		case DOWN:
			
			//std::cout << " DOWN " << std::endl ;
			//JESLI WYSZEDL LUB POLE JEST INNE OD EMPTY (CZYLI JEST TAM WAZ LUB SCIANA)
			if( y == 19 || ( Map[20 * (y + 1) + x] != EMPTY && Map[20 * (y + 1) + x] != SPAWN) )
			{
				//std::cout << " W DOWN " << std::endl ;
				return true ;
			}

			break ;
			
		case UP:

			//std::cout << " UP " << std::endl ;
			//JESLI WYSZEDL LUB POLE JEST INNE OD EMPTY (CZYLI JEST TAM WAZ LUB SCIANA)
			if( y == 0 || ( Map[20 * (y - 1) + x] != EMPTY && Map[20 * (y - 1) + x] != SPAWN) )
			{
				//std::cout << " W UP " << std::endl ;
				return true ;
			}

			break ;

		case LEFT:

			//std::cout << " LEFT " << std::endl ;
			//JESLI WYSZEDL LUB POLE JEST INNE OD EMPTY (CZYLI JEST TAM WAZ LUB SCIANA)
			if( x == 0 || ( Map[20 * y + x - 1] != EMPTY && Map[20 * y + x - 1] != SPAWN) )
			{
				//std::cout << " W LEFT " << std::endl ;
				return true ;
			}

			break ;

		case RIGHT:

			//std::cout << " RIGHT " << std::endl ;
			//JESLI WYSZEDL LUB POLE JEST INNE OD EMPTY (CZYLI JEST TAM WAZ LUB SCIANA)
			if( x == 19 || ( Map[20 * y + x + 1] != EMPTY && Map[20 * y + x + 1] != SPAWN) )
			{
				//std::cout << " W RIGHT " << std::endl ;
				return true ;
			}

			break ;
	}//switch(dir)

	//std::cout << " KONIEC " << std::endl ;

	return false ;
}

bool Snakes::Colision_Snake_Fruit(const std::vector<ALLEGRO_BITMAP *> & Map , const ALLEGRO_BITMAP * SPAWN , ALLEGRO_TIMER * MapFPS )
{
	//POZYCJA WEZA
	int x = Snake[0][0] ; 
	int y = Snake[0][1] ;

	switch(dir)
	{
		case DOWN:

			if( Map[20 * (y + 1) + x] == SPAWN )
			{
				//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
				for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
				{
					if( i == 0 )
						Snake[0][1]++ ;
					else
					{
						//OSTATNI ELEMENT
						if( i == (Snake.size() - 1) )
							Snake.push_back( Snake[i] ) ;
						//PRZESUWAMY POZYCJE WEZA (KOPIUJEMY NP 3 ELEMENT DO 4)
						Snake[i][1] = Snake[i - 1][1] ;
						Snake[i][0] = Snake[i - 1][0] ;
					}
				}

				//JESLI WAZ - 2 ELEMENTY (GLOWA I OGON) PO PODZIELENIU PRZEZ 4 
				//DAJE RESZTE 0 TO ZWIEKSZAMY SZYBKOSC RUCHU WEZA
				if( (Snake.size() - 2) != 0 )
				{
					if( !((Snake.size() - 2) % When) )
					{
						Frame += Speed ;
						//ZMIENIAMY PREDKOSC ODSWIEZANIA MAPY
						al_set_timer_speed( MapFPS , 1 / Frame ) ;
					}
				}

				//DODAJEMY PUNKTY
				Points += 10 + Bonus ;
				//UMIESCIC NOWY OWOC DO ZJEDZENIA
				Spawn = true ;
				return true ;
			}
			
			break ;
			
		case UP:

			if( Map[20 * (y - 1) + x] == SPAWN )
			{
				//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
				for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
				{
					if( i == 0 )
						Snake[0][1]-- ;
					else
					{
						//OSTATNI ELEMENT
						if( i == (Snake.size() - 1) )
							Snake.push_back( Snake[i] ) ;
						//PRZESUWAMY POZYCJE WEZA (KOPIUJEMY NP 3 ELEMENT DO 4)
						Snake[i][1] = Snake[i - 1][1] ;
						Snake[i][0] = Snake[i - 1][0] ;
					}
				}

				//JESLI WAZ - 2 ELEMENTY (GLOWA I OGON) PO PODZIELENIU PRZEZ 4 
				//DAJE RESZTE 0 TO ZWIEKSZAMY SZYBKOSC RUCHU WEZA
				if( (Snake.size() - 2) != 0 )
				{
					if( !((Snake.size() - 2) % When) )
					{
						Frame += Speed ;
						//ZMIENIAMY PREDKOSC ODSWIEZANIA MAPY
						al_set_timer_speed( MapFPS , 1 / Frame ) ;
					}
				}

				//DODAJEMY PUNKTY
				Points += 10 + Bonus ;
				//UMIESCIC NOWY OWOC DO ZJEDZENIA
				Spawn = true ;
				return true ;
			}

			break ;

		case LEFT:

			if( Map[20 * y + x - 1] == SPAWN )
			{
				//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
				for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
				{
					if( i == 0 )
						Snake[0][0]-- ;
					else
					{
						//OSTATNI ELEMENT
						if( i == (Snake.size() - 1) )
							Snake.push_back( Snake[i] ) ;
						//PRZESUWAMY POZYCJE WEZA (KOPIUJEMY NP 3 ELEMENT DO 4)
						Snake[i][1] = Snake[i - 1][1] ;
						Snake[i][0] = Snake[i - 1][0] ;
					}
				}

				//JESLI WAZ - 2 ELEMENTY (GLOWA I OGON) PO PODZIELENIU PRZEZ 4 
				//DAJE RESZTE 0 TO ZWIEKSZAMY SZYBKOSC RUCHU WEZA
				if( (Snake.size() - 2) != 0 )
				{
					if( !((Snake.size() - 2) % When) )
					{
						Frame += Speed ;
						//ZMIENIAMY PREDKOSC ODSWIEZANIA MAPY
						al_set_timer_speed( MapFPS , 1 / Frame ) ;
					}
				}

				//DODAJEMY PUNKTY
				Points += 10 + Bonus ;
				//UMIESCIC NOWY OWOC DO ZJEDZENIA
				Spawn = true ;
				return true ;
			}

			break ;

		case RIGHT:

			if( Map[20 * y + x + 1] == SPAWN )
			{
				//OSTATNI ELEMENT JEST ROWNY PRZED OSTATNIEMU I TAK DALEJ AZ DO PIERWSZEGO
				for(int i = (Snake.size() - 1) ; i >= 0 ; i--)
				{
					if( i == 0 )
						Snake[0][0]++ ;
					else
					{
						//OSTATNI ELEMENT
						if( i == (Snake.size() - 1) )
							Snake.push_back( Snake[i] ) ;
						//PRZESUWAMY POZYCJE WEZA (KOPIUJEMY NP 3 ELEMENT DO 4)
						Snake[i][1] = Snake[i - 1][1] ;
						Snake[i][0] = Snake[i - 1][0] ;
					}
				}

				//JESLI WAZ - 2 ELEMENTY (GLOWA I OGON) PO PODZIELENIU PRZEZ 4 
				//DAJE RESZTE 0 TO ZWIEKSZAMY SZYBKOSC RUCHU WEZA
				if( (Snake.size() - 2) != 0 )
				{
					if( !((Snake.size() - 2) % When) )
					{
						Frame += Speed ;
						//ZMIENIAMY PREDKOSC ODSWIEZANIA MAPY
						al_set_timer_speed( MapFPS , 1 / Frame ) ;
					}
				}

				//DODAJEMY PUNKTY
				Points += 10 + Bonus ;
				//UMIESCIC NOWY OWOC DO ZJEDZENIA
				Spawn = true ;
				return true ;
			}

			break ;
	}//switch(dir)

	return false ;
}
