#include "Map.h"
#include <ctime>
#include <algorithm>
//#include <iostream>

void Map::Draw_Map () 
{
	//POZYCJA GDZIE ZACZAC RYSOWAC MAPE ORAZ WIELKOSC BITMAPY
	int y = 0 , x = 0 , wielkosc = 30 ;
	//PRZEBIEGAMY PO KOLUMNACH
	for(int my = 0 ; my < 20 ; my++)
	{
		//PRZEBIEGAMY PO WIERSZACH
		for(int mx = 20 * my ; mx < 20 * (my + 1) ; mx++)
		{
			//RYSUJEM ODPOWIEDNIA BITMAPE NA ODPOWIEDNIEJ POZYCJI
			al_draw_bitmap( Screen_Map[mx] , x , y , NULL) ;
			//PRZESUWAMY SIE W PRAWO
			x += wielkosc ;
		}

		//PRZESUWAMY SIE W DOL ORAZ USTAWIAMY X NA 0
		x = 0 ;
		y += wielkosc ;
	}
}

void Map::Update_Map()
{
	//CZYSCIMY PLANSZE Z WEZA
	for(int y = 0 ; y < 400 ; y++)
			for(int vec = 0 ; vec < 14 ; vec++)
				if(Screen_Map[y] == Elements[vec])
					Screen_Map[y] = Elements[15] ;

	//WSTAWIAMY WEZA DO MAPY
	int SnakeX , SnakeY , SnakeXnext , SnakeYnext , SnakeXprev , SnakeYprev ;

	for(int i = 0 ; i < Snakess->Snake.size() ; i++)
	{
		//SRODEK WEZA
		if( i > 0 && i < (Snakess->Snake.size() - 1) )
		{
			//POZYCJA WCZESNIEJSZEGO OBIEKTU WEZA [0 = X / 1 = Y]
			SnakeXprev = Snakess->Snake[i - 1][0] ;
			SnakeYprev = Snakess->Snake[i - 1][1] ;
			//SPRAWDZANA POZYCJA
			SnakeX	   = Snakess->Snake[i][0]	 ;
			SnakeY	   = Snakess->Snake[i][1]	 ;
			//NASTEPNA POZYCJA
			SnakeXnext = Snakess->Snake[i + 1][0] ;
			SnakeYnext = Snakess->Snake[i + 1][1] ;

			// [][]
			if(SnakeX == SnakeXnext && SnakeX == SnakeXprev)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[12];

			// []
			// []
			else if(SnakeY == SnakeYnext && SnakeY == SnakeYprev)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[13];

			// [][]
			//   []
			else if((SnakeX > SnakeXprev && SnakeY < SnakeYnext) ||
				    (SnakeY < SnakeYprev && SnakeX > SnakeXnext) )
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[7];

			// [][]
			// []
			else if((SnakeX < SnakeXnext && SnakeY < SnakeYprev) ||
				    (SnakeX < SnakeXprev && SnakeY < SnakeYnext))
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[6];

			// []
			// [][]
			else if((SnakeX < SnakeXnext && SnakeY > SnakeYprev) ||
				    (SnakeX < SnakeXprev && SnakeY > SnakeYnext))
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[5];

			//   []
			// [][]
			else //if((SnakeX > SnakeXnext && SnakeY > SnakeYprev) ||
				 //   (SnakeX > SnakeXprev && SnakeY > SnakeYnext))
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[4];
		}//if( i > 0 && i < (Snake.size() - 1) )

		else if(i == (Snakess->Snake.size() - 1))   //OSTATNI ELEMENT (OGON)
		{
			//POZYCJA WCZESNIEJSZEGO OBIEKTU WEZA [0 = X / 1 = Y]
			SnakeXprev = Snakess->Snake[i - 1][0] ;
			SnakeYprev = Snakess->Snake[i - 1][1] ;
			//SPRAWDZANA POZYCJA
			SnakeX	   = Snakess->Snake[i][0]	 ;
			SnakeY	   = Snakess->Snake[i][1]	 ;

			// []-
			if(SnakeX > SnakeXprev)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[8];
			
			//  |
			// [ ]
			else if(SnakeY < SnakeYprev)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[11];

			// -[]
			else if(SnakeX < SnakeXprev)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[10];

			// [ ]
			//  |
			else if(SnakeY > SnakeYprev)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[9];
		}//if(i == (Snake.size() - 1))

		else if(i == 0)               // GLOWA
		{ 
			//SPRAWDZANA POZYCJA OBIEKTU WEZA [0 = X / 1 = Y]
			SnakeX	   = Snakess->Snake[i][0]	 ;
			SnakeY	   = Snakess->Snake[i][1]	 ;
			//NASTEPNA POZYCJA
			SnakeXnext = Snakess->Snake[i + 1][0] ;
			SnakeYnext = Snakess->Snake[i + 1][1] ;

			//  @
			// [ ]
			if(SnakeY < SnakeYnext)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[1];

			// @[]
			else if(SnakeX < SnakeXnext)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[0];

			// []@
			else if(SnakeX > SnakeXnext)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[2];

			// [ ]
			//  @
			else if(SnakeY > SnakeYnext)
				Screen_Map[SnakeY * 20 + SnakeX] = Elements[3];
		}//if(i == 0)  

	}//for(int i = 0 ; i < Snake.size() ; i++)

	//SPRAWDZAMY CZY TRZEBA POKAZAC OBIEKT DO ZJEDZENIA
	if(Spawn)
	{
		//POZYCJA GDZIE BEDZIEMY RYSOWAC OWOC
		int x1 , y1 ;
		do
		{
			//LOSUJEMY MIEJSCE DLA OWOCA
			x1 = rand() % 20 ;
			y1 = rand() % 20 ;
			//SPRAWDZAMY CZY MIEJSCE JESY PUSTE
		}while(!(Screen_Map[ y1 * 20 + x1 ] == Elements[15])) ;
		//RYSUJEMY NA TEJ POSYCJI OWOC I USTAWIAMY SPAWN NA FALSE
		Screen_Map[ y1 * 20 + x1 ] = Elements[14] ;
		Spawn = false ;
	}
}

void Map::Update_Map_Edit( int PositionY , int PositionX , int Bitmap )
{
	//SPRAWDZAMY CZY JEST JUZ POSTAWIONY WAZ JESLI TAK TO GO KAZUJEMY
	if( Bitmap >= 0 && Bitmap <= 3 )
	{
		for(int i = 0 ; i < 400 ; i++)
			if(Screen_Map[i] == Elements[0] || Screen_Map[i] == Elements[1] || Screen_Map[i] == Elements[2] || Screen_Map[i] == Elements[3] || 
			   Screen_Map[i] == Elements[8] || Screen_Map[i] == Elements[9] || Screen_Map[i] == Elements[10] || Screen_Map[i] == Elements[11] )
			   Screen_Map[i] = Elements[15] ;
	}

	//GLOWA -[] ORAZ USTAWIAMY OGON
	if(Bitmap == 0)
	{
		if( PositionX == 19 )
		{
			Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[8] ;
		}
		else
		{
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
			Screen_Map[ PositionY * 20 + PositionX + 1 ] = Elements[8] ;
		}
	}
	//GLOWA |
	//     [ ]
	else if(Bitmap == 1)
	{
		if( PositionY == 19 )
		{
			Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[9] ;
		}
		else
		{
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
			Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[9] ;
		}
	}
	//Glowa []-
	else if(Bitmap == 2)
	{
		if( PositionX == 0 )
		{
			Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[10] ;
		}
		else
		{
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
			Screen_Map[ PositionY * 20 + PositionX - 1 ] = Elements[10] ;
		}
	}
	//GLOWA [ ]
	//       |
	else if(Bitmap == 3)
	{
		if( PositionY == 0 )
		{
			Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[11] ;
		}
		else
		{
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
			Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[11] ;
		}
	}

	//SCIANA
	else if(Bitmap == 16)
	{
		//SPRAWDZAMY CZY CZASEM NIE POSTAWILISMY NA WEZU
		if(Screen_Map[ PositionY * 20 + PositionX ] == Elements[0]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[1] || 
		   Screen_Map[ PositionY * 20 + PositionX ] == Elements[2]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[3] || 
		   Screen_Map[ PositionY * 20 + PositionX ] == Elements[8]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[9] || 
		   Screen_Map[ PositionY * 20 + PositionX ] == Elements[10] || Screen_Map[ PositionY * 20 + PositionX ] == Elements[11] )
		{
			//LEWY GORNY ROG MAPY
			if( PositionY == 0 && PositionX == 0 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//PRAWY GORNY ROG MAPY
			else if( PositionY == 0 && PositionX == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//LEWY DOLNY ROG MAPY
			else if( PositionY == 19 && PositionX == 0 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//PRAWY DOLNY ROG MAPY
			else if( PositionY == 19 && PositionX == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//GORNA KRAWEDZ MAPY
			else if( PositionY == 0 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//DOLNA KRAWEDZ MAPY
			else if( PositionY == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//LEWA KRAWEDZ MAPY
			else if( PositionX == 0 )
			{
				if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
				   Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
				   Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
				   Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[15] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//PRAWA KRAWEDZ MAPY
			else if( PositionX == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[15] ;
				}
			}
			//SRODEK MAPY
			else
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[15] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[15] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[15] ;
				}
			}

		}
		else
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
	}

	//PUSTE MIEJSCE
	else if(Bitmap == 15)
	{
		//SPRAWDZAMY CZY CZASEM NIE POSTAWILISMY NA WEZU
		if(Screen_Map[ PositionY * 20 + PositionX ] == Elements[0]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[1] || 
		   Screen_Map[ PositionY * 20 + PositionX ] == Elements[2]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[3] || 
		   Screen_Map[ PositionY * 20 + PositionX ] == Elements[8]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[9] || 
		   Screen_Map[ PositionY * 20 + PositionX ] == Elements[10] || Screen_Map[ PositionY * 20 + PositionX ] == Elements[11] )
		{
			if( PositionY == 0 && PositionX == 0 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionY == 0 && PositionX == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionY == 19 && PositionX == 0 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionY == 19 && PositionX == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionY == 0 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionY == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionX == 0 )
			{
				if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
				   Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
				   Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
				   Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else if( PositionX == 19 )
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
			}
			else
			{
				if(Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[1] || 
				   Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[3] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[9] || 
		           Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX - 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX - 1) ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY - 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY - 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[0]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[1] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[2]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[3] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[8]  || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[9] || 
						Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[10] || Screen_Map[ (PositionY + 1) * 20 + PositionX ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ (PositionY + 1) * 20 + PositionX ] = Elements[Bitmap] ;
				}
				else if(Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[0]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[1] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[2]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[3] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[8]  || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[9] || 
					    Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[10] || Screen_Map[ PositionY * 20 + (PositionX + 1) ] == Elements[11] )
				{
					Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
					Screen_Map[ PositionY * 20 + (PositionX + 1) ] = Elements[Bitmap] ;
				}
			}

		}//if(Screen_Map[ PositionY * 20 + PositionX ] == Elements[0]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[1] || 
		 //Screen_Map[ PositionY * 20 + PositionX ] == Elements[2]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[3] || 
		 //Screen_Map[ PositionY * 20 + PositionX ] == Elements[8]  || Screen_Map[ PositionY * 20 + PositionX ] == Elements[9] || 
		 //Screen_Map[ PositionY * 20 + PositionX ] == Elements[10] || Screen_Map[ PositionY * 20 + PositionX ] == Elements[11] )
		else 
			Screen_Map[ PositionY * 20 + PositionX ] = Elements[Bitmap] ;
	}
}

bool Map::Check_Map(ALLEGRO_DISPLAY * display) 
{
	//SPRAWDZAMY CZY NA MAPIE JEST WAZ I PUSTE MIEJSCE
	bool BSnake = false , BEmpty = false ;
	for(int i = 0 ; i < 400 ; i++)
	{
		if(Screen_Map[i] == Elements[0] || Screen_Map[i] == Elements[1] || Screen_Map[i] == Elements[2] || Screen_Map[i] == Elements[3])
			BSnake = true ;
		if(Screen_Map[i] == Elements[15])
			BEmpty = true ;
	}

	if(BSnake && BEmpty)
		return true ;
	else 
	{
		al_show_native_message_box(display , "ERROR MAP" , "WRONG MAP" , "YOU FORGET ABOUT SNAKE OR EMPTY SPACE" , NULL , ALLEGRO_MESSAGEBOX_ERROR) ;
		return false ;
	}
}

bool Map::Load_Map(ALLEGRO_DISPLAY *display , std::string Name )
{
	File_Name = "Maps\\" + Name ;
	//OTWIERAMY PLIK DO ODCZYTU BINARNEGO
	std::fstream File ; 
	File.open( File_Name.c_str() , std::ios::in | std::ios::binary ) ;

	if(!File)
	{
		al_show_native_message_box( display , "MAP ERROR" , "ERROR" , "You can not open the map, possible that the map does not exist" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//CO MAMY WGRAC DO MAPY
	int What[400] ;

	File.read( reinterpret_cast<char*>(&What) , sizeof( What ) ) ;

	for(int y = 0 ; y < 400 ; y++)
	{
		//PUSTE MIEJSCE
		if(What[y] == 1)
			Screen_Map[ y ] = Elements[15] ;
		//SCIANA
		else if(What[y] == 2)
			Screen_Map[ y ] = Elements[16] ;
		//GLOWA WEZA  -[]
		else if(What[y] == 3)
		{
			//std::cout << "Y W ODCZYCIE MAPY = " << y << std::endl ;
				
			//POBIERAMY POZYCJE WEZA
			Snakess->Snake[0][0] = y % 20 ;
			Snakess->Snake[0][1] = y / 20 ;

			Screen_Map[ y ] = Elements[0] ;
		}
		//OGON WEZA []-
		else if(What[y] == 4)
		{

			//POBIERAMY POZYCJE WEZA
			Snakess->Snake[1][0] = y % 20 ;
			Snakess->Snake[1][1] = y / 20 ;

			Screen_Map[ y ] = Elements[8] ;
		}
	}

	
	///POBIERAMY MIEJSCE NICKOW W PLIKU
	int place = Return_Place_of_String( File , Code_Nick ) ;

	if( place == -1 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR FILE" , "FILE DONT HAVE TOP10 NICK" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//std::cout << "place = " << place << std::endl ;
	//al_rest(2) ;
	///USTAWIAMY WSKAZNIK DO CZYTANIA (seekp WSKAZNIK PISANIA)
	File.seekg( place ) ; 
	for(int i = 0 ; i < 10 ; i++)
	{
		//ODCZYTUJ DO ZNAKU NULL ('\0')
		//Top10_Nick[i].resize( Max ) ;
		std::getline( File , Top10_Nick[i] , '\0' ) ;
		//File.read( reinterpret_cast<char*>(&Top10_Nick[i]) , Top10_Nick[i].size() ) ;
		//std::cout << "Top10_Nick[" << i << "].capacity() " << Top10_Nick[i].capacity() << std::endl ;

		//= a ;
	}
	//al_rest(5) ;
	
	///POBIERAMY MIEJSCE PUNKTY W PLIKU
	place = Return_Place_of_String( File , Code_Point ) ;

	if( place == -1 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR FILE" , "FILE DONT HAVE TOP10 POINTS" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//std::cout << "place = " << place << std::endl ;
	//al_rest(2) ;
	//USTAWIAMY WSKAZNIK ODCZYTU
	File.seekg( place ) ; 
	for(int i = 0 ; i < 10 ; i++)
		File.read( reinterpret_cast<char*>(&Top10_Points[i]) , sizeof(unsigned) ) ;

	File.close() ;

	///POPRAWIAMY ZDJECIA WEZA (ZEBY PASOWALY DO SWOICH POZYCJI) ORAZ USTAWIAMY KIERUNEK
	for(int y = 0 ; y < 20 ; y++)
	{
		for(int x = 0 ; x < 20 ; x++)
		{
			if(Screen_Map[ (y * 20) + x ] == Elements[0])
			{
				if( x == 0 && y == 0 )
				{
					//std::cout << " x == 0 && y == 0 " << std::endl ;
					if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
					{	
						//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[1] ;
						Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;

						//USTALAMY KIERUNEK WEZA
						dir = UP ;
					}
					else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[0] ;
						Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;

						//USTALAMY KIERUNEK WEZA
						dir = LEFT ;
					}
				}//if( x == 0 && y == 0 )
				else if( x == 19 && y == 19 )
				{
					//std::cout << " x == 19 && y == 19 " << std::endl ;
					if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[3] ;
						Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;

						//USTALAMY KIERUNEK WEZA
						dir = DOWN ;
					}
					else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[2] ;
						Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;

						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
				}//else if( x == 19 && y == 19 )
				else if( x == 19 && y == 0 )
				{
					//std::cout << " x == 19 && y == 0 " << std::endl ;
					if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
					{	
						//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[1] ;
						Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;

						//USTALAMY KIERUNEK WEZA
						dir = UP ;
					}
					else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[2] ;
						Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;

						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
				}//else if( x == 19 && y == 0 )
				else if( x == 0 && y == 19 )
				{
					//std::cout << " x == 0 && y == 19 " << std::endl ;
					if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[3] ;
						Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;

						//USTALAMY KIERUNEK WEZA
						dir = DOWN ;
					}
					else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[0] ;
						Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;

						//USTALAMY KIERUNEK WEZA
						dir = LEFT ;
					}
				}//else if( x == 0 && y == 19 )
				else if( y == 0 )
				{
					//std::cout << " y == 0 " << std::endl ;
					if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
					{	
						//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[1] ;
						Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;

						//USTALAMY KIERUNEK WEZA
						dir = UP ;
					}
					else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[2] ;
						Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;

						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
					else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[0] ;
						Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = LEFT ;
					}
				}//else if( y == 0 )
				else if( y == 19 )
				{
					//std::cout << " y == 19 " << std::endl ;
					if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[3] ;
						Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;

						//USTALAMY KIERUNEK WEZA
						dir = DOWN ;
					}
					else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[2] ;
						Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
					else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[0] ;
						Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = LEFT ;
					}
				}//else if( y == 19 )
				else if( x == 0 )
				{
					//std::cout << " X == 0 " << std::endl ;
					if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
					{	
						//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[1] ;
						Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = UP ;
					}
					else if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[3] ;
						Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
					else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[0] ;
						Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = LEFT ;
					}
				}//else if( x == 0 )
				else if( x == 19 )
				{
					//std::cout << " X == 19 " << std::endl ;
					if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
					{	
						//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[1] ;
						Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = UP ;
					}
					else if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[3] ;
						Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = DOWN ;
					}
					else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[2] ;
						Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
				}//else if( x == 19 )
				else
				{
					//std::cout << "ELSE" << std::endl ;
					if(Screen_Map[ (y + 1) * 20 + x ] == Elements[8])
					{	
						//std::cout << "                    W Screen_Map[ (y + 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[1] ;
						Screen_Map[ (y + 1) * 20 + x ] = Elements[9] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = UP ;
					}
					else if(Screen_Map[ (y - 1) * 20 + x ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ (y - 1) * 20 + x ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[3] ;
						Screen_Map[ (y - 1) * 20 + x ] = Elements[11] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = DOWN ;
					}
					else if(Screen_Map[ y * 20 + x - 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x - 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[2] ;
						Screen_Map[ y * 20 + x - 1 ] = Elements[10] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = RIGHT ;
					}
					else if(Screen_Map[ y * 20 + x + 1 ] == Elements[8])
					{
						//std::cout << "                    W Screen_Map[ y * 20 + x + 1 ] == Elements[8]" << std::endl ;
						Screen_Map[ y * 20 + x ] = Elements[0] ;
						Screen_Map[ y * 20 + x + 1 ] = Elements[8] ;
						
						//USTALAMY KIERUNEK WEZA
						dir = LEFT ;
					}
				}//else
			}//if(Screen_Map[ (y * 20) + x ] == Elements[0])
		}//for(int x = 0 ; x < 20 ; x++)
	}//for(int y = 0 ; y < 20 ; y++)

	//std::cout << " ZZZZZZZZZZZZZZZZAAAAAAAAAAAAAAAAA " << std::endl ;

	return true ;
}

bool Map::Load_Top10(ALLEGRO_DISPLAY *display , std::string Name )
{
	File_Name = "Maps\\" + Name ;
	//OTWIERAMY PLIK DO ODCZYTU BINARNEGO
	std::fstream File( File_Name.c_str() , std::ios::in | std::ios::binary ) ;

	if(!File)
	{
		al_show_native_message_box( display , "MAP ERROR" , "ERROR" , "You can not open the map, possible that the map does not exist" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	///POBIERAMY MIEJSCE NICKOW W PLIKU
	int place = Return_Place_of_String( File , Code_Nick ) ;

	if( place == -1 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR FILE" , "FILE DONT HAVE TOP10 NICK" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//std::cout << "place = " << place << std::endl ;
	//al_rest(2) ;
	///USTAWIAMY WSKAZNIK DO CZYTANIA (seekp WSKAZNIK PISANIA)
	File.seekg( place ) ; 
	for(int i = 0 ; i < 10 ; i++)
	{
		//ODCZYTUJ DO ZNAKU NULL ('\0')
		//Top10_Nick[i].resize( Max ) ;
		std::getline( File , Top10_Nick[i] , '\0' ) ;
		//File.read( reinterpret_cast<char*>(&Top10_Nick[i]) , Top10_Nick[i].size() ) ;
		//std::cout << "Top10_Nick[" << i << "].capacity() " << Top10_Nick[i].capacity() << std::endl ;

		//= a ;
	}
	//al_rest(5) ;
	
	///POBIERAMY MIEJSCE PUNKTY W PLIKU
	place = Return_Place_of_String( File , Code_Point ) ;

	if( place == -1 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR FILE" , "FILE DONT HAVE TOP10 POINTS" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//std::cout << "place = " << place << std::endl ;
	//al_rest(2) ;
	//USTAWIAMY WSKAZNIK ODCZYTU
	File.seekg( place ) ; 
	for(int i = 0 ; i < 10 ; i++)
		File.read( reinterpret_cast<char*>(&Top10_Points[i]) , sizeof(unsigned) ) ;

	File.close() ;

	return true ;
}

bool Map::Save_Map(ALLEGRO_DISPLAY *display )
{
	///OTWIERAMY PLIK DO ZAPISU BINARNEGO
	std::ofstream File( File_Name.c_str() , std::ios::out | std::ios::binary ) ;
	//std::cout << "11111" << std::endl ;
	if(!File)
	{
		//std::cout << "22222" << std::endl ;
		al_show_native_message_box( display , "MAP ERROR" , "ERROR" , "You can not save the map" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//std::cout << "33333" << std::endl ;
	int What[400] ;

	for(int y = 0 ; y < 400 ; y++)
	{
		//PUSTE MIEJSCE 1
		if(Screen_Map[ y ] == Elements[15])
		{
			//std::cout << "44411" << std::endl ;
			What[y] = 1 ;
			//File.write( reinterpret_cast<const char*>(&What) , sizeof(char) ) ;
		}
		//SCIANA 2
		else if(Screen_Map[ y ] == Elements[16])
		{
			//std::cout << "44422" << std::endl ;
			What[y] = 2 ;
			//File.write( (char*) &What , sizeof(int) ) ;
		}
		//GLOWA WEZA  -[] 3
		else if( (Screen_Map[ y ] == Elements[0]) || (Screen_Map[ y ] == Elements[1]) || 
				    (Screen_Map[ y ] == Elements[2]) || (Screen_Map[ y ] == Elements[3]) )
		{
			//std::cout << "44433" << std::endl ;
			What[y] = 3 ;
			//File.write( (char*) &What , sizeof(int) ) ;
		}
		//OGON WEZA []-  4
		else if( (Screen_Map[ y ] == Elements[8])  || (Screen_Map[ y ] == Elements[9]) || 
				    (Screen_Map[ y ] == Elements[10]) || (Screen_Map[ y ] == Elements[11]) )
		{
			//std::cout << "44441" << std::endl ;
			What[y] = 4 ;
			//File.write( (char*) &What , sizeof(int) ) ;
		}
	}

	/////////////////////////////////////////////////////
	File.write( reinterpret_cast<const char*>(&What) , sizeof( What ) ) ;
	//std::cout << "55555" << std::endl ;
	///WSTAWIAMY KOD
	File.write( Code_Nick.c_str() , Code_Nick.size() + 1 ) ;

	//std::cout << "66666" << std::endl ;
	for(int i = 0 ; i < 10  ; i++)
	{
		//Top10_Nick[i].resize( Max ) ;
		File.write( Top10_Nick[i].c_str()  , Top10_Nick[i].size() + 1 ) ;
		//std::cout << "Top10_Nick[" << i << "].capacity() " << Top10_Nick[i].capacity() << std::endl ;
	}
	//al_rest(5) ;
	//(const char*)

	//std::cout << "77777" << std::endl ;
	///KOLEJNY KOD
	File.write( Code_Point.c_str() , Code_Point.size() + 1 ) ;

	for(int i = 0 ; i < 10 ; i++)
		File.write( reinterpret_cast < const char *>(&Top10_Points[i]) , sizeof(unsigned) ) ;
	//std::cout << "88888" << std::endl ;

	File.write( Check_File.c_str() , Check_File.size() + 1 ) ;

	//std::cout << "99999" << std::endl ;
	File.close() ;

	return true ;
}

bool Map::Save_Top10(ALLEGRO_DISPLAY *display )
{
	//OTWIERAMY PLIK DO ODCZYTU I ZAPISU BINARNEGO
	std::fstream File( File_Name.c_str() , std::ios::in | std::ios::out | std::ios::binary ) ;
	//std::cout << "11111" << std::endl ;
	if(!File)
	{
		//std::cout << "22222" << std::endl ;
		al_show_native_message_box( display , "MAP ERROR" , "ERROR" , "You can not save the map" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	///POBIERAMY MIEJSCE NICKOW W PLIKU
	int place = Return_Place_of_String( File , Code_Nick ) ;

	if( place == -1 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR FILE" , "FILE DONT HAVE TOP10 NICK" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//USTAWIAMY WSKAZNIK PISANIA
	File.seekp( place ) ;
	//std::cout << "66666" << std::endl ;
	for(int i = 0 ; i < 10  ; i++)
	{
		//Top10_Nick[i].resize( Max ) ;
		File.write( Top10_Nick[i].c_str()  , Top10_Nick[i].size() + 1 ) ;
		//std::cout << "Top10_Nick[" << i << "].capacity() " << Top10_Nick[i].capacity() << std::endl ;
	}
	//al_rest(5) ;
	//(const char*)

	//std::cout << "77777" << std::endl ;
	///POBIERAMY MIEJSCE PUNKTOW W PLIKU
	place = Return_Place_of_String( File , Code_Point ) ;

	if( place == -1 )
	{
		al_show_native_message_box(display , "ERROR" , "ERROR FILE" , "FILE DONT HAVE TOP10 NICK" , NULL , ALLEGRO_MESSAGEBOX_ERROR ) ;
		return false ;
	}

	//USTAWIAMY WSKAZNIK PISANIA
	File.seekp( place ) ;

	for(int i = 0 ; i < 10 ; i++)
		File.write( reinterpret_cast < const char *>(&Top10_Points[i]) , sizeof(unsigned) ) ;
	//std::cout << "88888" << std::endl ;

	//std::cout << "99999" << std::endl ;
	File.close() ;

	return true ;
}
