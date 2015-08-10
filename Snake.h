#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include <array>

//#include <iostream>
//#include <conio.h>
#include "zmienne.h"

//#include "Map.h"
#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>

class Snakes
{
	public:

		Snakes()
		{
			//REZERWUJEMY MIEJSCE NA GLOWE I OGON
			std::array<int, 2> a = { 0 , 0 } ;
			Snake.push_back( a ) ;
			Snake.push_back( a ) ;
			//POCZATKOWA ILOSC PUNKTOW
			Points = 0 ;

			//ZMIENNE ZALEZNE OD POZIOMU TRUDNOSCI
			switch(Difficulty)
			{
				case 1: //EASY

					//CO 4 ZJEDZONE OWOCE PRZYSPIESZA
					When = 4 ;
					//PUNKTY ZA POZIOM TRUDNOSCI
					Bonus = 0 ;
					//PRZYSPIESZENIE
					Speed = 0.5 ;

					break ;

				case 2: //MEDIUM

					//CO 4 ZJEDZONE OWOCE PRZYSPIESZA
					When = 3 ;
					//PUNKTY ZA POZIOM TRUDNOSCI
					Bonus = 4 ;
					//PRZYSPIESZENIE
					Speed = 0.6 ; 

					break ;

				case 3: //HARD

					//CO 4 ZJEDZONE OWOCE PRZYSPIESZA
					When = 2 ;
					//PUNKTY ZA POZIOM TRUDNOSCI
					Bonus = 15 ;
					//PRZYSPIESZENIE
					Speed = 0.8 ;

					break ;
			}
		}

		//KIERUNEK WEZA PODANY PRZEZ GRACZA
		void Move_Snake( ALLEGRO_KEYBOARD_STATE keyState , ALLEGRO_TIMER * MapFPS ) ;
		
		//RUCH WEZA
		void Update_Snake() ;

		//KOLIZJA ZE SCIANA , Z SAMYM SOBA I WYJSCIE PO ZA PLANSZE
		bool Colision_Snake(const std::vector<ALLEGRO_BITMAP *> & Map , const ALLEGRO_BITMAP * EMPTY, const ALLEGRO_BITMAP * SPAWN) ;
		//KOLIZJA Z OWOCEM (EAT_ME)
		bool Colision_Snake_Fruit(const std::vector<ALLEGRO_BITMAP *> & Map , const ALLEGRO_BITMAP * SPAWN , ALLEGRO_TIMER * MapFPS ) ;
		
		//ZWRACAMY PUNKTY GRACZA
		unsigned Return_Points() { return Points ; }

		friend class Map ;

	private:

		//ILOSC PUNKTOW
		unsigned Points ;
		//ZMIENNA PRZECHOWUJACA POZYCJE WEZA [0 = X / 1 = Y]
		std::vector< std::array<int, 2> > Snake ;
		//CZESTOSC ODSWIEZANIA MAPY (RUCH WEZA CO ILE ZJEDZONYCH OWOCOW)
		int When ;
		//PREMIA OD POZIOMU TRUDNOSCI
		int Bonus ;
		//SZYBKOSC PRZYSPIESZENIA
		float Speed ;
		
};

#endif