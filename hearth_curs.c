/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



/*====================------------------------------------====================*/
/*===----                         program level                        ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char             /* [------] initialize ncurses screen handling --------------*/
CURS_init          (void)
{
   /*---(initialize)------------------*/
   initscr();       /* fire up ncurses with a default screen (stdscr)         */
   raw();           /* read key-by-key rather than waiting for \n (raw mode)  */
   nodelay (stdscr, TRUE);
   noecho();        /* don't automatically echo keypresses to the screen      */
   ESCDELAY = 0;    /* so escape responds immediately                         */
   /*---(colors)----------------------*/
   curs_set (0);
   start_color();
   use_default_colors();
   init_pair( 1, COLOR_WHITE  , -1           );
   init_pair( 2, COLOR_BLACK  , COLOR_WHITE  );
   init_pair( 3, COLOR_WHITE  , COLOR_BLACK  );
   init_pair( 4, COLOR_BLACK  , COLOR_GREEN  );
   init_pair( 5, COLOR_WHITE  , COLOR_RED    );
   init_pair( 6, COLOR_BLACK  , COLOR_CYAN   );
   init_pair( 7, COLOR_BLACK  , COLOR_YELLOW );
   init_pair( 8, COLOR_WHITE  , COLOR_MAGENTA);
   init_pair( 9, COLOR_RED    , -1           );
   init_pair(10, COLOR_GREEN  , -1           );
   init_pair(11, COLOR_CYAN   , -1           );
   init_pair(12, COLOR_YELLOW , -1           );
   init_pair(13, COLOR_WHITE  , COLOR_BLUE   );
   init_pair(14, COLOR_BLUE   , -1           );
   init_pair(15, COLOR_WHITE  , COLOR_BLACK  );
   init_pair(16, COLOR_RED    , COLOR_BLACK  );
   init_pair(17, COLOR_YELLOW , COLOR_RED    );
   /*---(complete)--------------------*/
   return 0;
}

char             /* [------] shutdown ncurses --------------------------------*/
CURS_wrap          (void)
{
   endwin();        /* shut down ncurses                                      */
   /*---(complete)--------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       ascii-art text                         ----===*/
/*====================------------------------------------====================*/
static void      o___ASCIIART________________o (void) {;}


