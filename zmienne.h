#ifndef ZMIENNE_H
#define ZMIENNE_H
//#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <string>
#include <fstream>
//#include <time.h>

//CHECK FILE
extern std::string Check_File ;

//NAZWA WYBRANEJ MAPY (GRA / EDYCJA)
extern std::string Name_Selected_Map ;

//KODY DO DANYCH
extern std::string Code_Nick  ;
extern std::string Code_Point ;

//KIERUNEK PORUSZANIA SIE
enum DIRECTION { DOWN , UP , LEFT , RIGHT } ;
extern DIRECTION dir ;
//STAN GRY
enum GAME_STATE { MENU , GAME , NEW_MAP , EDIT , TOP10 } ;
extern GAME_STATE STATE ;

//STWORZYC MENU
extern bool Menu_ ;
//WYJSCIE Z MENU
extern bool End_Menu_ ;
//STWORZYC Game
extern bool Start_Game_ ;
//WYJSCIE Z Game
extern bool End_Start_Game_ ;
//STWORZYC Choice_Map
extern bool Choice_Map_ ;
//WYJSCIE Z Choice_Map
extern bool End_Choice_Map_ ;
//STWORZYC Top10
extern bool Top10_ ;
//WYJSCIE Z Top10
extern bool End_Top10_ ;
//STWORZYC Edit
extern bool Edit_ ;
//WYJSCIE Z New_Map
extern bool End_Edit_ ;

//WRACAMY DO MENU Z WYBORU MAPY
extern bool Back_To_Menu ;

//ZMIENNA DO WLACZENIA GRY
extern bool Game_ ;

//ODSWIEZAMY EKRAN
extern bool draw ;

//WYMIARY OKNA
extern int ScreenHight ;
extern int ScreenWidth ;

//ZMIENNE DLA MYSZKI
extern float x , y ;

//CZY JEST KOLKA DO "ZJEDZENIA" NA MAPIE
extern bool Spawn ;

//POZIOM TRUDNOSCI
extern int Difficulty ;

//SZYBKOSC ODSWIEZANIA MAPY
extern float Frame ;
//SZYBKOSC ODSWIEZANIA EKRANU
extern float FrameFPS ;

//ZMIENNA EKRAN
extern ALLEGRO_DISPLAY * display ;

//CZCIONKA DLA NAPISOW
extern ALLEGRO_FONT *Font_Big  ;
extern ALLEGRO_FONT *Font_Smal ;

/////////////////////////////////////
///            FUNKCJE            ///
/////////////////////////////////////

///SZUKANIE W PLIKU BINARNYM ODPOWIEDNIEGO SLOWA
extern int Return_Place_of_String( std::fstream &File , std::string Searches ) ;
///USTAWIANIE WIELKOSCI BITMAPY
extern ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, float w, float h) ;
///WPROWADZAMY IMIE LUB NAZWE MAPY (NEW MAP)
extern void Enter_Nick_MapName(ALLEGRO_KEYBOARD_STATE &keyState , std::string &Inscription , int Max_Char) ;
///FUNKCJA SPRAWDZA CZY MYSZKA ZNAJDUJE SIE NA TRUJKACIE
extern bool Mouse_In_Triangle( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , float x , float y ) ;

#endif