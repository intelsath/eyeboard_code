/********************************************************************\
 * EyeBoard - Board used to write with the eyes using the EOG system*
 * Copyright (C) 2011 Luis Cruz <lcruz@intelsath.com>               *
 * For further information, support, and contributions please visit:*
 *                    http://www.intelsath.com                      *
 *                                                                  *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation, either version 3 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program. If not, see                             *
 * <http://www.gnu.org/licenses/>.                                  *
\********************************************************************/


//SDL Libraries
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

//C++ Libraries
#include <fstream>
#include <cstring>
#include <iostream>

#include <windows.h> //Windows library


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* WINDOW_TITTLE = "Eyeboard version 3.5 (beta)";

bool FULLSCREEN = {false};
bool continue1 = {false}; //After choosing something

bool gameRunning = {true};

bool keysHeld[323] = {false}; //initialized to falsez

int keyZ = 0; //Avoids delay when user doesn't releases key or doesn't looks at the center
int keyZ1 = 0; //Avoids delay when user doesn't releases key
int keyZ2 = 0; //Avoids delay when user doesn't releases key
int keyZ3 = 0; //Avoids delay when user doesn't releases key
int keyZ4 = 0; //Avoids delay when user doesn't releases key
int keyZ5 = 0; //Avoids delay when user doesn't releases key
int keyZ6 = 0; //Avoids delay when user doesn't releases key
int keyZ7 = 0; //Avoids delay when user doesn't releases key


int arrowPos[7] = {50, 108, 167, 224, 282, 338, 395}; //this is the arrow position in the Y axis

int nPZ = 0; //starts at position 0 on notepad
int y; //y position (box)
int x = 1; //letters (x-axis, inside the box)
//moves letter backwards, so that the written letter aren't deleted when n==6


//keeps track of time
 float deltaTime = 0.0;
 double thisTime = 0.0;
 double lastTime = 0.0;

 const float SPEEDX = 25;
 float speedX = 0.0;

bool WRITE = {false}; //writes to notepad

int notepadPos[6] = {295, 338, 381, 424, 467, 510 };
int nP = 0; //position

int delz = 0;

//what letter should be written?
bool Ba = false;
bool Bb = false;
bool Bc = false;
bool Bd = false;
bool Be = false;
bool Bf = false;
bool Bg = false;
bool Bh = false;
bool Bi = false;
bool Bj = false;
bool Bk = false;
bool Bl = false;
bool Bm = false;
bool Bn = false;
bool Bo = false;
bool Bp = false;
bool Bq = false;
bool Br = false;
bool Bs = false;
bool Bt = false;
bool Bu = false;
bool Bv = false;
bool Bw = false;
bool Bx = false;
bool By = false;
bool Bz = false;
bool Bspace = false;
bool Bbackspace = false;

char letters[] = {""};//avoids sintax error
char *letter = letters;
char *letter1 = letters;
char *letter2 = letters;
char *letter3 = letters;
char *letter4 = letters;
char *letter5 = letters;
char *letter6 = letters;

//character to be written on notepad
char La[] = "A";
char Lb[] = "B";
char Lc[] = "C";
char Ld[] = "D";
char Le[] = "E";
char Lf[] = "F";
char Lg[] = "G";
char Lh[] = "H";
char Li[] = "I";
char Lj[] = "J";
char Lk[] = "K";
char Ll[] = "L";
char Lm[] = "M";
char Ln[] = "N";
char Lo[] = "O";
char Lp[] = "P";
char Lq[] = "Q";
char Lr[] = "R";
char Ls[] = "S";
char Lt[] = "T";
char Lu[] = "U";
char Lv[] = "V";
char Lw[] = "W";
char Lx[] = "X";
char Ly[] = "Y";
char Lz[] = "Z";
char Lspace[] = "_";

char Lasterisk[] = "*";
//WINDOW, ALSO AREA IN MEMORY. HSURFACE = TELLS SDL WE WILL USE THE VIDEO, DOUBLEBUF = CREATES TWO BUFFERS
SDL_Surface* screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);

   //Loads images into a SDL surface
SDL_Surface * eyeboard = IMG_Load("eyeboard3.png");
SDL_Surface * arrow = IMG_Load("arrow2.png");
SDL_Surface * notepad = IMG_Load("notepad.png");

//Letters
SDL_Surface * A = IMG_Load("a.png");
SDL_Surface * B = IMG_Load("b.png");
SDL_Surface * C = IMG_Load("c.png");
SDL_Surface * D = IMG_Load("d.png");

SDL_Surface * E = IMG_Load("e.png");
SDL_Surface * F = IMG_Load("f.png");
SDL_Surface * G = IMG_Load("g.png");
SDL_Surface * H = IMG_Load("h.png");
SDL_Surface * I = IMG_Load("i.png");

SDL_Surface * J = IMG_Load("j.png");
SDL_Surface * K = IMG_Load("k.png");
SDL_Surface * L = IMG_Load("l.png");
SDL_Surface * M = IMG_Load("m.png");

SDL_Surface * N = IMG_Load("n.png");
SDL_Surface * O = IMG_Load("o.png");
SDL_Surface * P = IMG_Load("p.png");
SDL_Surface * Q = IMG_Load("q.png");

SDL_Surface * R = IMG_Load("r.png");
SDL_Surface * S = IMG_Load("s.png");
SDL_Surface * T = IMG_Load("t.png");
SDL_Surface * U = IMG_Load("u.png");

SDL_Surface * V = IMG_Load("v.png");
SDL_Surface * W = IMG_Load("w.png");
SDL_Surface * X = IMG_Load("x.png");

SDL_Surface * Y = IMG_Load("y.png");
SDL_Surface * Z = IMG_Load("z.png");
SDL_Surface * space = IMG_Load("space.png");
SDL_Surface * backspace = IMG_Load("delete.png");

/* **********************************
FUNCTION THAT DRAWS A SPRITE.
drawSprite( imageNAME, screen, sourceX, sourceY, destinationX, destinationY, WIDTH, HEIGHT);

************************************* */
void drawSprite( SDL_Surface* image, SDL_Surface* screen, int srcX, int srcY, int dstX, int dstY, int height, int width)
{
 //Bitmap size
  SDL_Rect source;

  source.x = srcX;
  source.y = srcY;
  source.w = width;
  source.h = height;

//Position
  SDL_Rect destination;

  destination.x = dstX;
  destination.y = dstY;
  destination.w = width;
  destination.h = height;


  //DRAW IMAGE
  SDL_BlitSurface(image, NULL, screen, &destination);

}


char record[1000000] = {""};

void deletes(){

if( Bbackspace )
delz = 1;
else if( !Bbackspace ) delz = 0;

 //if backspace is NOT selected, position (nP) will be added. otherwise, it will not.
if( delz == 0 )
 nP++; //notepad position

 //Can you delete something at position 0? no... Therefore, deletes only when nP is greater than 0
if( nP >= 0 ){
  if( delz == 1 ){
      //if words haven't started to scroll left yet
        if( nP < 6 )
          nP--;
      // if words already started to scroll left...
        if( nP == 6 )
          nP-=2;



  }

}


}

void writes()
{

//Record this to a text file
if( WRITE) {
  //records
  if( Ba )
 strcat( record, La );
  if( Bb )
 strcat( record, Lb );
  if( Bc )
 strcat( record, Lc );
  if( Bd )
 strcat( record, Ld );
  if( Be )
 strcat( record, Le );
  if( Bf )
 strcat( record, Lf );
  if( Bg )
 strcat( record, Lg );
  if( Bh )
 strcat( record, Lh );
  if( Bi )
 strcat( record, Li );
  if( Bj )
 strcat( record, Lj );
  if( Bk )
 strcat( record, Lk );
  if( Bl )
 strcat( record, Ll );
  if( Bm )
 strcat( record, Lm );
  if( Bn )
 strcat( record, Ln );
  if( Bo )
 strcat( record, Lo );
  if( Bp )
 strcat( record, Lp );
  if( Bq )
 strcat( record, Lq );
  if( Br )
 strcat( record, Lr );
  if( Bs )
 strcat( record, Ls );
  if( Bt )
 strcat( record, Lt );
  if( Bu )
 strcat( record, Lu );
  if( Bv )
 strcat( record, Lv );
  if( Bw )
 strcat( record, Lw );
  if( Bx )
 strcat( record, Lx );
  if( By )
 strcat( record, Ly );
  if( Bz )
 strcat( record, Lz );
  if( Bspace )
 strcat( record, Lspace );
 if( delz == 1 )
 strcat( record, Lasterisk );

 std::ofstream Record("record.txt");
 Record << record;
 Record.close();

}

    if( WRITE && nP == 0 )
    {
 if( Ba )
  letter = La;
 if( Bb )
  letter = Lb;
 if( Bc )
  letter = Lc;
 if( Bd )
  letter = Ld;
 if( Be )
  letter = Le;
 if( Bf )
  letter = Lf;
 if( Bg )
  letter = Lg;
 if( Bh )
  letter = Lh;
 if( Bi )
  letter = Li;
 if( Bj )
  letter = Lj;
 if( Bk )
  letter = Lk;
 if( Bl )
  letter = Ll;
 if( Bm )
  letter = Lm;
 if( Bn )
  letter = Ln;
 if( Bo )
  letter = Lo;
 if( Bp )
  letter = Lp;
 if( Bq )
  letter = Lq;
 if( Br )
  letter = Lr;
 if( Bs )
  letter = Ls;
 if( Bt )
  letter = Lt;
 if( Bu )
  letter = Lu;
 if( Bv )
  letter = Lv;
 if( Bw )
  letter = Lw;
 if( Bx )
  letter = Lx;
 if( By )
  letter = Ly;
 if( Bz )
  letter = Lz;
 if( Bspace )
  letter = Lspace;
    }

 if( WRITE && nP == 1 )
    {
 if( Ba )
  letter1 = La;
 if( Bb )
  letter1 = Lb;
 if( Bc )
  letter1 = Lc;
 if( Bd )
  letter1 = Ld;
 if( Be )
  letter1 = Le;
 if( Bf )
  letter1 = Lf;
 if( Bg )
  letter1 = Lg;
 if( Bh )
  letter1 = Lh;
 if( Bi )
  letter1 = Li;
 if( Bj )
  letter1 = Lj;
 if( Bk )
  letter1 = Lk;
 if( Bl )
  letter1 = Ll;
 if( Bm )
  letter1 = Lm;
 if( Bn )
  letter1 = Ln;
 if( Bo )
  letter1 = Lo;
 if( Bp )
  letter1 = Lp;
 if( Bq )
  letter1 = Lq;
 if( Br )
  letter1 = Lr;
 if( Bs )
  letter1 = Ls;
 if( Bt )
  letter1 = Lt;
 if( Bu )
  letter1 = Lu;
 if( Bv )
  letter1 = Lv;
 if( Bw )
  letter1 = Lw;
 if( Bx )
  letter1 = Lx;
 if( By )
  letter1 = Ly;
 if( Bz )
  letter1 = Lz;
 if( Bspace )
  letter1 = Lspace;
    }

     if( WRITE && nP == 2 )
    {
 if( Ba )
  letter2 =La;
 if( Bb )
  letter2 =Lb;
 if( Bc )
  letter2 =Lc;
 if( Bd )
  letter2 =Ld;
 if( Be )
  letter2 =Le;
 if( Bf )
  letter2 =Lf;
 if( Bg )
  letter2 =Lg;
 if( Bh )
  letter2 =Lh;
 if( Bi )
  letter2 =Li;
 if( Bj )
  letter2 =Lj;
 if( Bk )
  letter2 =Lk;
 if( Bl )
  letter2 =Ll;
 if( Bm )
  letter2 =Lm;
 if( Bn )
  letter2 =Ln;
 if( Bo )
  letter2 =Lo;
 if( Bp )
  letter2 =Lp;
 if( Bq )
  letter2 =Lq;
 if( Br )
  letter2 =Lr;
 if( Bs )
  letter2 =Ls;
 if( Bt )
  letter2 =Lt;
 if( Bu )
  letter2 =Lu;
 if( Bv )
  letter2 =Lv;
 if( Bw )
  letter2 =Lw;
 if( Bx )
  letter2 =Lx;
 if( By )
  letter2 =Ly;
 if( Bz )
  letter2 =Lz;
 if( Bspace )
  letter2 = Lspace;
    }

     if( WRITE && nP == 3 )
    {
 if( Ba )
  letter3 =La;
 if( Bb )
  letter3 =Lb;
 if( Bc )
  letter3 =Lc;
 if( Bd )
  letter3 =Ld;
 if( Be )
  letter3 =Le;
 if( Bf )
  letter3 =Lf;
 if( Bg )
  letter3 =Lg;
 if( Bh )
  letter3 =Lh;
 if( Bi )
  letter3 =Li;
 if( Bj )
  letter3 =Lj;
 if( Bk )
  letter3 =Lk;
 if( Bl )
  letter3 =Ll;
 if( Bm )
  letter3 =Lm;
 if( Bn )
  letter3 =Ln;
 if( Bo )
  letter3 =Lo;
 if( Bp )
  letter3 =Lp;
 if( Bq )
  letter3 =Lq;
 if( Br )
  letter3 =Lr;
 if( Bs )
  letter3 =Ls;
 if( Bt )
  letter3 =Lt;
 if( Bu )
  letter3 =Lu;
 if( Bv )
  letter3 =Lv;
 if( Bw )
  letter3 =Lw;
 if( Bx )
  letter3 =Lx;
 if( By )
  letter3 =Ly;
 if( Bz )
  letter3 =Lz;
 if( Bspace )
  letter3 = Lspace;
    }

     if( WRITE && nP == 4 )
    {
 if( Ba )
  letter4 =La;
 if( Bb )
  letter4 =Lb;
 if( Bc )
  letter4 =Lc;
 if( Bd )
  letter4 =Ld;
 if( Be )
  letter4 =Le;
 if( Bf )
  letter4 =Lf;
 if( Bg )
  letter4 =Lg;
 if( Bh )
  letter4 =Lh;
 if( Bi )
  letter4 =Li;
 if( Bj )
  letter4 =Lj;
 if( Bk )
  letter4 =Lk;
 if( Bl )
  letter4 =Ll;
 if( Bm )
  letter4 =Lm;
 if( Bn )
  letter4 =Ln;
 if( Bo )
  letter4 =Lo;
 if( Bp )
  letter4 =Lp;
 if( Bq )
  letter4 =Lq;
 if( Br )
  letter4 =Lr;
 if( Bs )
  letter4 =Ls;
 if( Bt )
  letter4 =Lt;
 if( Bu )
  letter4 =Lu;
 if( Bv )
  letter4 =Lv;
 if( Bw )
  letter4 =Lw;
 if( Bx )
  letter4 =Lx;
 if( By )
  letter4 =Ly;
 if( Bz )
  letter4 =Lz;
 if( Bspace )
  letter4 = Lspace;
    }

     if( WRITE && nP == 5 )
    {
 if( Ba )
  letter5 =La;
 if( Bb )
  letter5 =Lb;
 if( Bc )
  letter5 =Lc;
 if( Bd )
  letter5 =Ld;
 if( Be )
  letter5 =Le;
 if( Bf )
  letter5 =Lf;
 if( Bg )
  letter5 =Lg;
 if( Bh )
  letter5 =Lh;
 if( Bi )
  letter5 =Li;
 if( Bj )
  letter5 =Lj;
 if( Bk )
  letter5 =Lk;
 if( Bl )
  letter5 =Ll;
 if( Bm )
  letter5 =Lm;
 if( Bn )
  letter5 =Ln;
 if( Bo )
  letter5 =Lo;
 if( Bp )
  letter5 =Lp;
 if( Bq )
  letter5 =Lq;
 if( Br )
  letter5 =Lr;
 if( Bs )
  letter5 =Ls;
 if( Bt )
  letter5 =Lt;
 if( Bu )
  letter5 =Lu;
 if( Bv )
  letter5 =Lv;
 if( Bw )
  letter5 =Lw;
 if( Bx )
  letter5 =Lx;
 if( By )
  letter5 =Ly;
 if( Bz )
  letter5 =Lz;
 if( Bspace )
  letter5 = Lspace;
    }

     if( WRITE && nP >= 6 )
    {
 if( Ba )
  letter6 =La;
 if( Bb )
  letter6 =Lb;
 if( Bc )
  letter6 =Lc;
 if( Bd )
  letter6 =Ld;
 if( Be )
  letter6 =Le;
 if( Bf )
  letter6 =Lf;
 if( Bg )
  letter6 =Lg;
 if( Bh )
  letter6 =Lh;
 if( Bi )
  letter6 =Li;
 if( Bj )
  letter6 =Lj;
 if( Bk )
  letter6 =Lk;
 if( Bl )
  letter6 =Ll;
 if( Bm )
  letter6 =Lm;
 if( Bn )
  letter6 =Ln;
 if( Bo )
  letter6 =Lo;
 if( Bp )
  letter6 =Lp;
 if( Bq )
  letter6 =Lq;
 if( Br )
  letter6 =Lr;
 if( Bs )
  letter6 =Ls;
 if( Bt )
  letter6 =Lt;
 if( Bu )
  letter6 =Lu;
 if( Bv )
  letter6 =Lv;
 if( Bw )
  letter6 =Lw;
 if( Bx )
  letter6 =Lx;
 if( By )
  letter6 =Ly;
 if( Bz )
  letter6 =Lz;
 if( Bspace )
  letter6 = Lspace;
    }
}

char moveXY; //this will determine where to move...


int z;
int z1;
int z3;//for notepad letters
  void showScreen()
  {

      if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		FULLSCREEN=true;							// Windowed Mode
		  continue1 = true;
	}
	else   {
	continue1 = true;
	}


if( FULLSCREEN ) //If fullscreen was activated
//Sets video mode
{
SDL_Surface* screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF & SDL_OPENGL | SDL_FULLSCREEN );
					DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= SCREEN_WIDTH;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= SCREEN_HEIGHT;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

					// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{

				FULLSCREEN =false;		// Windowed Mode Selected.  Fullscreen = FALSE
				continue1 = true;
			}
            else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				gameRunning = false;
			}
		}
}

if( !FULLSCREEN ) //If fullscreen was not activated :
//WINDOW, ALSO AREA IN MEMORY. HSURFACE = TELLS SDL WE WILL USE THE VIDEO, DOUBLEBUF = CREATES TWO BUFFERS
   SDL_Surface* screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF & SDL_OPENGL);
  }

int main(int argc, char* argv[])
{
     showScreen();
     ShellExecute(0, "open", "http://www.intelsath.com", 0, 0, 1); //Opens only when it is not in fullscreen
    /*Optional -- Opens python listener automatically! (Use fork() to open a child process)*/
  //system("./eog.py"); //open eog.py python listener from serial port

//INITIALIZES SDL
    SDL_Init( SDL_INIT_EVERYTHING ); //initializes everything SDL_INI_VIDEO, SDL_INIT_AUDIO... ETC

//Caption
   SDL_WM_SetCaption(WINDOW_TITTLE, 0);

   //event for the keyboard
  SDL_Event event;

  SDL_Init( SDL_INIT_TIMER );

  //Initializes text
TTF_Init();
//Font used for text
TTF_Font *font  = NULL;
//Suraces
SDL_Surface *currentLetterNotepad = NULL;
SDL_Surface *currentLetterNotepad1 = NULL;
SDL_Surface *currentLetterNotepad2 = NULL;
SDL_Surface *currentLetterNotepad3 = NULL;
SDL_Surface *currentLetterNotepad4 = NULL;
SDL_Surface *currentLetterNotepad5 = NULL;
SDL_Surface *currentLetterNotepad6 = NULL;
//The color of the font
SDL_Color textColor = { NULL };         //black

//Open font
font = TTF_OpenFont( "Times.ttf", 32 );
system("xdg-open http://www.intelsath.com"); //Opens website in default browser

 while ( gameRunning )
 {

writes(); //writes text on notepad
//message

currentLetterNotepad = TTF_RenderText_Solid( font, letter , textColor);
currentLetterNotepad1 = TTF_RenderText_Solid( font, letter1 , textColor);
currentLetterNotepad2 = TTF_RenderText_Solid( font, letter2 , textColor);
currentLetterNotepad3 = TTF_RenderText_Solid( font, letter3 , textColor);
currentLetterNotepad4 = TTF_RenderText_Solid( font, letter4 , textColor);
currentLetterNotepad5 = TTF_RenderText_Solid( font, letter5 , textColor);
currentLetterNotepad6 = TTF_RenderText_Solid( font, letter6 , textColor);



     //Look for an event
     if (SDL_PollEvent(&event))
      {
             //If it was closed with the X
              if(event.type == SDL_QUIT)
              {
                gameRunning = false;
              }

             if (event.type == SDL_KEYDOWN){
                keysHeld[event.key.keysym.sym] = true;

              }

              if(event.type == SDL_KEYUP){
               keysHeld[event.key.keysym.sym] = false;
              }
      }

      //close program
      if(keysHeld[SDLK_ESCAPE])
        {
            gameRunning = false;
        }

        //This will simulate eye movements, using the arrow keys instead
        //updates chosen box with the left key -arrow position-
        if( keysHeld[SDLK_LEFT] || moveXY == '2' ){

            if( keyZ == 0){
            if ( z == 0 ) //z will avoid rapid movements of the arrow
            y++;
            z = 1;
            speedX = 0; //for notepad, restarts counter
            z3 = 0; //notepad

            if( y > 6 ) y = 0; //resets y

            x = 1; //resets inside box position letter

            keyZ = 1;
            }
        }

        if(!keysHeld[SDLK_LEFT] && moveXY != '2' ){ z = 0; keyZ = 0;} //This will restore z to cero when the user releases key


   drawSprite(eyeboard, screen, NULL, NULL, 0, 0, 65, 44); //draws background
   drawSprite(arrow, screen, NULL, NULL, 11, arrowPos[y], 65, 44); //arrow position dependant on the arrowPos array.
   drawSprite(notepad, screen, NULL, NULL, 275, 125, 65, 44); //notepad

//Checks file (LOADS)
std::ifstream MCUdata("eog.txt");
MCUdata >> moveXY; //writes data to moveXY
MCUdata.close();   //close files


if( nP == 0 ){
   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
}
if( nP == 1 ){
   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad1, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
}
if( nP == 2 ){
   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad1, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad2, screen, NULL, NULL, notepadPos[2], 182, 65, 44); //characters
}
if( nP == 3 ){
   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad1, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad2, screen, NULL, NULL, notepadPos[2], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad3, screen, NULL, NULL, notepadPos[3], 182, 65, 44); //characters
}
if( nP == 4 ){
   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad1, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad2, screen, NULL, NULL, notepadPos[2], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad3, screen, NULL, NULL, notepadPos[3], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad4, screen, NULL, NULL, notepadPos[4], 182, 65, 44); //characters
}
if( nP >= 5 ){

   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad1, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad2, screen, NULL, NULL, notepadPos[2], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad3, screen, NULL, NULL, notepadPos[3], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad4, screen, NULL, NULL, notepadPos[4], 182, 65, 44); //characters
   drawSprite(currentLetterNotepad5, screen, NULL, NULL, notepadPos[5], 182, 65, 44); //characters
}

//This function makes the words move backward everytime the end is reached... The previous letter will be the following letter and so on....
//Also, scroll letters only if the deleted button hasn't been selected...
   if( nP == 6 && WRITE && delz == 0 ){
   letter = letter1;
   drawSprite(currentLetterNotepad, screen, NULL, NULL, notepadPos[0], 182, 65, 44); //characters
   letter1 = letter2;
   drawSprite(currentLetterNotepad1, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   letter2 = letter3;
   drawSprite(currentLetterNotepad2, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   letter3 = letter4;
   drawSprite(currentLetterNotepad3, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   letter4 = letter5;
   drawSprite(currentLetterNotepad4, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   letter5 = letter6;
   drawSprite(currentLetterNotepad5, screen, NULL, NULL, notepadPos[1], 182, 65, 44); //characters
   }

//keeps tracks of time
      thisTime = SDL_GetTicks();
      deltaTime = (float)(thisTime - lastTime) / 1000;
      lastTime = thisTime;

      speedX += SPEEDX * deltaTime;

    if( speedX >= 60 ){
     if( z3 == 0 ){
     WRITE = true;
     speedX = 0;
     deletes();
     if( nP > 5) nP = 6;
     z3 = 1;
     }


    }
    else WRITE = false;


//starts at position 0
if( nPZ == 0 ){nP-=1; nPZ = 1;}
//Switch function: determine which letter is chosen, y = box, x = letter inside box
   switch ( y )
   {
       //box 1 [x,1]
       case 0:
         //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0' )
          {

              if( keyZ1 == 0 ){
              speedX = 0;
              if (z1 == 0)
              x++;
              z1 = 1;
              z3 = 0; //for notepad

              if( x > 4) x = 1;

              keyZ1 = 1;
              }


          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0' ) {z1 = 0; keyZ1 = 0; } //This will restore z1 to zero when the user releases key

          //inside box
          switch( x )
          {
              case 1:
                drawSprite(A, screen , NULL, NULL, 395, 58, 65, 44); //A letter [1,1]
                Ba = true;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              break;

              case 2:
                Ba = false;
                Bb = true;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
               drawSprite(B, screen , NULL, NULL, 395, 58, 65, 44); //B letter [2,1]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = true;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(C, screen , NULL, NULL, 395, 58, 65, 44); //c letter [3,1]
              break;

              case 4:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = true;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(D, screen , NULL, NULL, 395, 58, 65, 44); //D letter [4,1]
              break;

          }
       break;

       //box 2
       case 1:
          //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0')
          {
              if( keyZ2 == 0 ){
              if (z1 == 0)
              x++;
              z1 = 1;
              speedX = 0;
              z3 = 0; //for notepad

              if( x > 5) x = 1; //second box is the only one with 5 options

              keyZ2 = 1;
              }
          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0') {z1 = 0; keyZ2 = 0;} //This will restore z1 to cero when the user releases key

            switch( x )
          {

              case 1:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = true;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
                drawSprite(E, screen , NULL, NULL, 395, 58, 65, 44); //E letter [1,2]
              break;

              case 2:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = true;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
               drawSprite(F, screen , NULL, NULL, 395, 58, 65, 44); //F letter [2,2]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = true;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(G, screen , NULL, NULL, 395, 58, 65, 44); //G letter [3,2]
              break;

              case 4:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = true;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(H, screen , NULL, NULL, 395, 58, 65, 44); //H letter [4,2]
              break;

              case 5:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = true;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(I, screen , NULL, NULL, 395, 58, 65, 44); //I letter [5,2]
              break;
          }

       break;

       //box 3
       case 2:
       //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0')
          {
              if( keyZ3 == 0 ){
              if (z1 == 0)
              x++;
              z1 = 1;
              speedX = 0;
              z3 = 0; //for notepad

              if( x > 4) x = 1;
              keyZ3 = 1;
              }
          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0' ) {z1 = 0; keyZ3 = 0;} //This will restore z1 to cero when the user releases key

          //inside box
          switch( x )
          {
              case 1:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = true;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
                drawSprite(J, screen , NULL, NULL, 395, 58, 65, 44); //J letter [1,3]
              break;

              case 2:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = true;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
               drawSprite(K, screen , NULL, NULL, 395, 58, 65, 44); //K letter [2,3]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = true;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(L, screen , NULL, NULL, 395, 58, 65, 44); //L letter [3,3]
              break;

              case 4:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = true;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(M, screen , NULL, NULL, 395, 58, 65, 44); //M letter [4,3]
              break;

          }
       break;

       // box 4
       case 3:
        //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0' )
          {
              if( keyZ4 == 0){
              if (z1 == 0)
              x++;
              z1 = 1;
              speedX = 0;
              z3 = 0; //for notepad


              if( x > 4) x = 1;
              keyZ4 = 1;
              }
          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0' ) {z1 = 0; keyZ4 = 0;} //This will restore z1 to cero when the user releases key

          //inside box
          switch( x )
          {
              case 1:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = true;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
                drawSprite(N, screen , NULL, NULL, 395, 58, 65, 44); //N letter [1,4]
              break;

              case 2:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = true;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
               drawSprite(O, screen , NULL, NULL, 395, 58, 65, 44); //O letter [2,4]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = true;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(P, screen , NULL, NULL, 395, 58, 65, 44); //P letter [3,4]
              break;

              case 4:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = true;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(Q, screen , NULL, NULL, 395, 58, 65, 44); //Q letter [4,4]
              break;

          }
       break;

       //box 5
       case 4:
       //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0')
          {
              if( keyZ5 == 0){
              if (z1 == 0)
              x++;
              z1 = 1;
              speedX = 0;
              z3 = 0; //for notepad


              if( x > 4) x = 1;
              keyZ5 = 1;
              }
          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0' ){ z1 = 0; keyZ5 = 0;} //This will restore z1 to cero when the user releases key

          //inside box
          switch( x )
          {
              case 1:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = true;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
                drawSprite(R, screen , NULL, NULL, 395, 58, 65, 44); //R letter [1,5]
              break;

              case 2:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = true;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
               drawSprite(S, screen , NULL, NULL, 395, 58, 65, 44); //S letter [2,5]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = true;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(T, screen , NULL, NULL, 395, 58, 65, 44); //T letter [3,5]
              break;

              case 4:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = true;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(U, screen , NULL, NULL, 395, 58, 65, 44); //U letter [4,5]
              break;

          }
       break;

       //box 6
       case 5:
       //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0' )
          {
              if( keyZ6 == 0 ){
              if (z1 == 0)
              x++;
              z1 = 1;
              speedX = 0;
              z3 = 0; //for notepad


              if( x > 3) x = 1; //just 3 characters
              keyZ6 = 1;
              }
          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0') {z1 = 0; keyZ6 = 0; } //This will restore z1 to cero when the user releases key

          //inside box
          switch( x )
          {
              case 1:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = true;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
                drawSprite(V, screen , NULL, NULL, 395, 58, 65, 44); //V letter [1,6]
              break;

              case 2:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = true;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
               drawSprite(W, screen , NULL, NULL, 395, 58, 65, 44); //W letter [2,6]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = true;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
              drawSprite(X, screen , NULL, NULL, 395, 58, 65, 44); //X letter [3,6]
              break;

          }
       break;

       //box 7th
       case 6:
       //Simulates eyes with the right key
          if( keysHeld[SDLK_RIGHT] || moveXY == '0' )
          {
              if( keyZ7 == 0){
              if (z1 == 0)
              x++;
              z1 = 1;
              speedX = 0;
              z3 = 0; //for notepad


              if( x > 4) x = 1; //just 3 characters
              keyZ7 = 1;
              }
          }

          if(!keysHeld[SDLK_RIGHT] && moveXY != '0' ) {z1 = 0; keyZ7 =0;} //This will restore z1 to cero when the user releases key

          //inside box
          switch( x )
          {
              case 1:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = true;
                Bz = false;
                Bspace = false;
                Bbackspace = false;
                drawSprite(Y, screen , NULL, NULL, 395, 58, 65, 44); //Y letter [1,7]
              break;

              case 2:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = true;
                Bspace = false;
                Bbackspace = false;
               drawSprite(Z, screen , NULL, NULL, 395, 58, 65, 44); //Z letter [2,7]
              break;

              case 3:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = true;
                Bbackspace = false;
              drawSprite(space, screen , NULL, NULL, 385, 58, 65, 44); //space [3,7]
              break;

              case 4:
                Ba = false;
                Bb = false;
                Bc = false;
                Bd = false;
                Be = false;
                Bf = false;
                Bg = false;
                Bh = false;
                Bi = false;
                Bj = false;
                Bk = false;
                Bl = false;
                Bm = false;
                Bn = false;
                Bo = false;
                Bp = false;
                Bq = false;
                Br = false;
                Bs = false;
                Bt = false;
                Bu = false;
                Bv = false;
                Bw = false;
                Bx = false;
                By = false;
                Bz = false;
                Bspace = false;
                Bbackspace = true;
                drawSprite(backspace, screen , NULL, NULL, 385, 58, 65, 44); //space [3,7]
              break;

          }
       break;

   } //end of switch


   SDL_Flip(screen); //Updates screen

 } //end of while

//when file is closed a "1" will be saved.
 std::ofstream save("eog.txt");
 save << "1"; //centre
 save.close();


 SDL_FreeSurface( eyeboard );
 SDL_FreeSurface( arrow );
 SDL_FreeSurface(A);
 SDL_FreeSurface(B);
 SDL_FreeSurface(C);
 SDL_FreeSurface(D);

 SDL_FreeSurface(E);
 SDL_FreeSurface(F);
 SDL_FreeSurface(G);
 SDL_FreeSurface(H);
 SDL_FreeSurface(I);

 SDL_FreeSurface(J);
 SDL_FreeSurface(K);
 SDL_FreeSurface(L);
 SDL_FreeSurface(M);

 SDL_FreeSurface(N);
 SDL_FreeSurface(O);
 SDL_FreeSurface(P);
 SDL_FreeSurface(Q);

 SDL_FreeSurface(R);
 SDL_FreeSurface(S);
 SDL_FreeSurface(T);
 SDL_FreeSurface(U);

 SDL_FreeSurface(V);
 SDL_FreeSurface(W);
 SDL_FreeSurface(X);

 SDL_FreeSurface(Y);
 SDL_FreeSurface(Z);

 SDL_FreeSurface(notepad);
 SDL_FreeSurface(currentLetterNotepad);
 SDL_FreeSurface(currentLetterNotepad1);
 SDL_FreeSurface(currentLetterNotepad2);
 SDL_FreeSurface(currentLetterNotepad3);
 SDL_FreeSurface(currentLetterNotepad4);
 SDL_FreeSurface(currentLetterNotepad5);
 SDL_FreeSurface(currentLetterNotepad6);

 SDL_Quit();

system("notepad record.txt"); //Opens text of what was recorded!

     return 0;
}

