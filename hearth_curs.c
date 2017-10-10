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

char
text_show          (char *a_font, char a_num, char a_row, char a_col, char a_off)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter (__FUNCTION__);
   DEBUG_GRAF   yLOG_sinfo  ("font      ", a_font);
   DEBUG_GRAF   yLOG_svalue ("entry     ", a_num);
   DEBUG_GRAF   yLOG_svalue ("row       ", a_row);
   DEBUG_GRAF   yLOG_svalue ("col       ", a_col);
   /*---(locals)-----------+-----------+-*/
   char        l;
   int         i           = 0;
   char       *p;
   char        r;
   int         v, vo;
   int         h, hs, ho;
   int         row         = 0;
   int         col         = 0;
   char        msg         [200];
   /*---(find)---------------------------*/
   if (strcmp (a_font, font [cfont].name) != 0) {
      cfont = 0;
      for (i = 0; i < nfont; ++i) {
         if (strcmp (a_font, font [i].name) != 0)  continue;
         cfont = i;
         break;
      }
   }
   /*---(font values)--------------------*/
   r  = font [cfont].r;
   p  = font [cfont].p;
   v  = font [cfont].v;
   vo = font [cfont].vo;
   h  = font [cfont].h;
   hs = font [cfont].hs;
   ho = font [cfont].ho;
   /*---(defense)------------------------*/
   if (r == 'n') {
      i = a_num;
      if (i < 0 || i > 9) {
         DEBUG_GRAF   yLOG_snote  ("num out of range (0-9)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -1;
      }
   } else if (r == 'a') {
      i = tolower (a_num);
      if ((i < 'a' || i > 'z') && i != ' ') {
         DEBUG_GRAF   yLOG_snote  ("letter out of range (a-z)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -2;
      }
      if (i == ' ') i = 'z' + 1;
      i = i - 'a';
   } else if (r == 'f') {
      i = tolower (a_num);
      if ((i < 'a' || i > 'z') && (i < '0' || i > '9')) {
         DEBUG_GRAF   yLOG_snote  ("char out of range (a-z0-9)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -2;
      }
      if (i >= 'a' && i <= 'z')  i = i - 'a';
      else                       i = i - '0' + 26;
   } else if (r == 'b') {
      i = a_num;
      if (a_num == ' ') i = 0;
      if (a_num == '.') i = 1;
      if (i <  0  || i >  1 ) {
         DEBUG_GRAF   yLOG_snote  ("binary out of range (0-1)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -2;
      }
   } else {
      DEBUG_GRAF   yLOG_snote  ("font type unknown (a,n)");
      DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
      return -3;
   }
   /*---(update issue)-------------------*/
   for (row = 0; row < v; ++row) {
      for (col = 0; col < h; ++col) {
         l = *(p  + (row * 300) + ((i * (h + hs)) + col));
         sprintf (msg, "%c", l);
         mvprintw (a_row * (v + vo) + row, a_col * (h + ho) + col + a_off,  "%s", msg);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
   return 0;
}

char
text_show_xy       (char *a_font, char a_num, int a_y, int a_x)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter (__FUNCTION__);
   DEBUG_GRAF   yLOG_sinfo  ("font      ", a_font);
   DEBUG_GRAF   yLOG_svalue ("entry     ", a_num);
   DEBUG_GRAF   yLOG_svalue ("x         ", a_x);
   DEBUG_GRAF   yLOG_svalue ("y         ", a_y);
   /*---(locals)-----------+-----------+-*/
   char        l;
   int         i           = 0;
   char       *p;
   char        r;
   int         v, vo;
   int         h, hs, ho;
   int         row         = 0;
   int         col         = 0;
   char        msg         [200];
   /*---(find)---------------------------*/
   if (strcmp (a_font, font [cfont].name) != 0) {
      cfont = 0;
      for (i = 0; i < nfont; ++i) {
         if (strcmp (a_font, font [i].name) != 0)  continue;
         cfont = i;
         break;
      }
   }
   /*---(font values)--------------------*/
   r  = font [cfont].r;
   p  = font [cfont].p;
   v  = font [cfont].v;
   vo = font [cfont].vo;
   h  = font [cfont].h;
   hs = font [cfont].hs;
   ho = font [cfont].ho;
   /*---(defense)------------------------*/
   if (r == 'n') {
      i = a_num;
      if (i < 0 || i > 9) {
         DEBUG_GRAF   yLOG_snote  ("num out of range (0-9)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -1;
      }
   } else if (r == 'a') {
      i = tolower (a_num);
      if ((i < 'a' || i > 'z') && i != ' ') {
         DEBUG_GRAF   yLOG_snote  ("letter out of range (a-z)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -2;
      }
      if (i == ' ') i = 'z' + 1;
      i = i - 'a';
   } else if (r == 'f') {
      i = tolower (a_num);
      if ((i < 'a' || i > 'z') && (i < '0' || i > '9')) {
         DEBUG_GRAF   yLOG_snote  ("char out of range (a-z0-9)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -2;
      }
      if (i >= 'a' && i <= 'z')  i = i - 'a';
      else                       i = i - '0' + 26;
   } else if (r == 'b') {
      i = a_num;
      if (a_num == ' ') i = 0;
      if (a_num == '.') i = 1;
      if (i <  0  || i >  1 ) {
         DEBUG_GRAF   yLOG_snote  ("binary out of range (0-1)");
         DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
         return -2;
      }
   } else {
      DEBUG_GRAF   yLOG_snote  ("font type unknown (a,n)");
      DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
      return -3;
   }
   /*---(update issue)-------------------*/
   for (row = 0; row < v; ++row) {
      for (col = 0; col < h; ++col) {
         l = *(p  + (row * 300) + ((i * (h + hs)) + col));
         /*> if (l == ' ') continue;                                                  <*/
         sprintf (msg, "%c", l);
         mvprintw (a_y + row, a_x + col,  "%s", msg);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
   return 0;
}
