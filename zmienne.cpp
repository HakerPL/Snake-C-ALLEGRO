#include <allegro5\allegro5.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <istream>
//#include <time.h>

//CHECK FILE
std::string Check_File = "!!!HakerPL!!!" ;

//NAZWA WYBRANEJ MAPY (GRA / EDYCJA)
std::string Name_Selected_Map ;

//KODY DO DANYCH
std::string Code_Nick  = "#@$Nick$@#"  ;
std::string Code_Point = "#@$Point$@#" ;

//STWORZYC MENU
bool Menu_ = true ;
//WYJSCIE Z MENU
bool End_Menu_ = false ;
//STWORZYC Game
bool Start_Game_ = true ;
//WYJSCIE Z Game
bool End_Start_Game_ = false ;
//STWORZYC Choice_Map
bool Choice_Map_ = true  ;
//WYJSCIE Z Choice_Map
bool End_Choice_Map_ = false  ;
//STWORZYC Top10
bool Top10_ = true  ;
//WYJSCIE Z Top10
bool End_Top10_ = false ;
//STWORZYC Edit
bool Edit_ = true ;
//WYJSCIE Z New_Map
bool End_Edit_ = false ;

//WRACAMY DO MENU Z WYBORU MAPY
bool Back_To_Menu = false ;

//ZMIENNA DO WLACZENIA GRY
bool Game_ = true ;

//ODSWIEZAMY EKRAN
bool draw = false ;

//WYMIARY OKNA
int ScreenHight = 600 ;
int ScreenWidth = 800 ;

//ZMIENNE DLA MYSZKI
float x , y ;

//CZY JEST KOLKA DO "ZJEDZENIA" NA MAPIE
bool Spawn = true ;

//POZIOM TRUDNOSCI
int Difficulty = 1 ;

//SZYBKOSC ODSWIEZANIA MAPY
float Frame = 1.5  ;
//SZYBKOSC ODSWIEZANIA EKRANU
float FrameFPS = 60 ;  

enum GAME_STATE { MENU , GAME , NEW_MAP , EDIT , TOP10 } STATE ;
enum DIRECTION { DOWN , UP , LEFT , RIGHT } dir ;

/////////////////////////////////////
///            FUNKCJE            ///
/////////////////////////////////////

///SZUKANIE W PLIKU BINARNYM ODPOWIEDNIEGO SLOWA
int Return_Place_of_String( std::fstream &File , std::string Searches )
{	
	//USTAWIAMY WSKAZNIK ODCZYTU NA POZYCJE 0 (POCZATEK PLIKU)
	File.seekg( 0 ) ; 
	std::string str(( std::istreambuf_iterator < char >( File ) ), std::istreambuf_iterator < char >() );
	//std::string a ( (std::istreambuf_iterator<char>(File)) , std::istreambuf_iterator<char>() ) ;
	
	//std::istreambuf_iterator<int>()
	//SZUKAMY W PLIKU STRINGA
	size_t pos = str.find( Searches ) ;
		//std::search( File.beg , File.end , Searches.begin() , Searches.end() ) ;

	if( pos == std::string::npos )
		return -1 ;
	else
		return pos + Searches.length() + 1 ;
}

///USTAWIANIE WIELKOSCI BITMAPY
ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, float w, float h)
{
  ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

  // 1. create a temporary bitmap of size we want
  resized_bmp = al_create_bitmap(w, h);
  if (!resized_bmp) return NULL;

  // 2. load the bitmap at the original size
  loaded_bmp = al_load_bitmap(filename);
  if (!loaded_bmp)
  {
     al_destroy_bitmap(resized_bmp);
     return NULL;
  }

  // 3. set the target bitmap to the resized bmp
  prev_target = al_get_target_bitmap();
  al_set_target_bitmap(resized_bmp);

  // 4. copy the loaded bitmap to the resized bmp
  al_draw_scaled_bitmap(loaded_bmp,
     0, 0,                                // source origin
     al_get_bitmap_width(loaded_bmp),     // source width
     al_get_bitmap_height(loaded_bmp),    // source height
     0, 0,                                // target origin
     w, h,                                // target dimensions
     0                                    // flags
  );

  // 5. restore the previous target and clean up
  al_set_target_bitmap(prev_target);
  al_destroy_bitmap(loaded_bmp);

  return resized_bmp;      
}

///WPROWADZAMY IMIE LUB NAZWE MAPY (NEW MAP)
void Enter_Nick_MapName(ALLEGRO_KEYBOARD_STATE &keyState , std::string &Inscription , int Max_Char)
{
	if( Inscription.size() < Max_Char )
	{
		if( al_key_down(&keyState , ALLEGRO_KEY_A) )
			Inscription += "A" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_B) )
			Inscription += "B" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_C) )
			Inscription += "C" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_D) )
			Inscription += "D" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_E) )
			Inscription += "E" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_F) )
			Inscription += "F" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_G) )
			Inscription += "G" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_H) )
			Inscription += "H" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_I) )
			Inscription += "I" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_J) )
			Inscription += "J" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_K) )
			Inscription += "K" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_L) )
			Inscription += "L" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_M) )
			Inscription += "M" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_N) )
			Inscription += "N" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_O) )
			Inscription += "O" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_P) )
			Inscription += "P" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_Q) )
			Inscription += "Q" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_R) )
			Inscription += "R" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_S) )
			Inscription += "S" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_T) )
			Inscription += "T" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_U) )
			Inscription += "U" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_V) )
			Inscription += "V" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_W) )
			Inscription += "W" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_X) )
			Inscription += "X" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_Y) )
			Inscription += "Y" ;
		else if( al_key_down(&keyState , ALLEGRO_KEY_Z) )
			Inscription += "Z" ;
		else //JESLI DLUGOSC STRINGA JEST WIEKSZA OD ZERA TO DOPUSZCZAMY KASOWANIE OSTATNIEGO ZNAKU
			if( Inscription.length() > 0 )
				if( al_key_down(&keyState , ALLEGRO_KEY_BACKSPACE) )
					Inscription.erase(Inscription.end() - 1) ;
	}
	else if( al_key_down(&keyState , ALLEGRO_KEY_BACKSPACE) )
		Inscription.erase(Inscription.end() - 1) ;
}

///FUNKCJA SPRAWDZA CZY MYSZKA ZNAJDUJE SIE NA TRUJKACIE
bool Mouse_In_Triangle( int x1 , int y1 , int x2 , int y2 , int x3 , int y3 , float x , float y )
{
	float denominator = ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
	float a = ((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3)) / denominator;
	float b = ((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3)) / denominator;
	float c = 1 - a - b;

	return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}
