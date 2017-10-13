/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"


int         s_top       =   0;
int         s_mid       =   0;
int         s_bot       =   0;

int         s_lef       =   0;
int         s_cen       =   0;
int         s_rig       =   0;

char             /* [------] create one-time login numbers -------------------*/
VEIL_init            (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;        /* loop iterator                       */
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(prefix)-------------------------*/
   entry.prefix [0] = my.magic_num [ 0] =  '0' + rand () % 10;
   entry.prefix [1] = my.magic_num [ 1] =  '0' + rand () % 10;
   entry.prefix [2] = '\0';
   /*---(infix)--------------------------*/
   entry.infix  [0] = my.magic_num [ 2] =  '0' + rand () % 10;
   entry.infix  [1] = '\0';
   /*---(knock)--------------------------*/
   for (i = 0; i < 4; ++i) {
      entry.knock [i] = my.magic_num [ 3 + i] =  (rand () % 2 == 0) ? ' ' : '.';
   }
   entry.knock [4] = '\0';
   /*---(special)------------------------*/
   entry.rot     [0] = my.magic_num [ 7] = '0' + rand () % 3 + 1;
   entry.pointer [0] = my.magic_num [ 8] = '0' + rand () % 10;
   entry.rot     [1] = entry.pointer [1] = '\0';
   /*---(suffix)-------------------------*/
   entry.suffix [0] = my.magic_num [ 9] = '0' + rand () % 10;
   entry.suffix [1] = my.magic_num [10] = '0' + rand () % 10;
   entry.suffix [2] = my.magic_num [11] = '0' + rand () % 10;
   entry.suffix [3] = '\0';
   /*---(wrap-up)------------------------*/
   my.magic_num[12] = '\0';
   DEBUG_PROG   yLOG_info    ("magic_num" , my.magic_num);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] show butterfly background -----------------------*/
VEIL_butterfly     (int a_x, int a_y)
{
   /*---(locals)-----------+-----------+-*/
   int         b           = 0;               /* butterfly index              */
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columns          */
   int         x_butter    = 0;               /* left of butterfly            */
   /*---(defense)------------------------*/
   yLOG_char   ("arg_butter"  , my.show_butterfly  );
   if (my.show_butterfly != 'y')  return 0;
   /*---(output)-------------------------*/
   b           = rand () % 37;
   yLOG_value  ("butterfly"   , b              );
   x_butter  = (a_x - MAX_COL) / 2;
   yLOG_value  ("x_butter"    , x_butter       );
   attron (COLOR_PAIR(10));
   for (i =  0; i <  MAX_ROW; ++i) {
      for (j =  0; j <  MAX_COL; ++j) {
         mvprintw (i, j + x_butter,  "%c", butterfly [b][i][j]);
      }
   }
   attroff(COLOR_PAIR(10));
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show left column of numbers ---------------------*/
VEIL_left            (void)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----+-----+-*/
   int         x_row       =    0;               /* iterator -- rows             */
   int         x_col       =    0;               /* iterator -- columns          */
   int         x_tall      =    0;     /* height of letters                   */
   int         x_wide      =    0;     /* height of letters                   */
   int         x_nrow      =    0;     /* number of rows to fill screen       */
   char        x_letter    =  '-';
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   yLOG_char   ("my.show_left"    , my.show_left       );
   if (my.show_left      != 'y')  return 0;
   /*---(get max characters)----------*/
   x_tall  = FONT_tall ("alligator");
   x_nrow  = trunc (s_bot / x_tall);
   x_wide  = FONT_wide ("alligator");
   /*---(show table of numbers)-------*/
   for (x_row = 0; x_row < (x_nrow + 1); ++x_row) {
      for (x_col =  0; x_col <  2; ++x_col) {
         x_letter = rand () % 10 + '0';
         SHOW_HINTS   attron (COLOR_PAIR( 1));
         else         attron (COLOR_PAIR(12));
         if      (x_col == 1 && x_row == 0         )  entry.prefix [1] = my.magic_num [ 1] =  x_letter;
         else if (x_col == 1 && x_row == x_nrow - 1)  entry.prefix [0] = my.magic_num [ 0] =  x_letter;
         else if (x_col == 0 && x_row == 4         )  entry.infix  [0] = my.magic_num [ 2] =  x_letter;
         else {
            attrset (0);
            attron (COLOR_PAIR(12));
         }
         FONT_letter ( "alligator", x_letter, x_row * x_tall, x_col * x_wide);
         attrset (0);
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      mvprintw ( 12,   3,  ".-------------.", x_text);
      sprintf (x_text, "| x_tall = %2d |", x_tall);
      mvprintw ( 13,   3,  "%s", x_text);
      sprintf (x_text, "| x_wide = %2d |", x_wide);
      mvprintw ( 14,   3,  "%s", x_text);
      sprintf (x_text, "| x_nrow = %2d |", x_nrow);
      mvprintw ( 15,   3,  "%s", x_text);
      sprintf (x_text, "| ptr    = %2d |", 4);
      mvprintw ( 16,   3,  "%s", x_text);
      mvprintw ( 17,   3,  "'-------------'", x_text);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show right column of numbers --------------------*/
VEIL_right           (void)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         x_row       =    0;               /* iterator -- rows             */
   int         x_col       =    0;               /* iterator -- columns          */
   int         x_tall      =    0;     /* height of letters                   */
   int         x_wide      =    0;     /* height of letters                   */
   int         x_nrow      =    0;     /* number of rows to fill screen       */
   int         x_right     =    0;
   char        x_letter    =  '-';
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   yLOG_char   ("my.show_right"   , my.show_right      );
   if (my.show_right     != 'y')  return 0;
   /*---(get max characters)----------*/
   x_tall  = FONT_tall ("goofy");
   x_nrow  = trunc (s_bot / x_tall);
   x_wide  = FONT_wide ("goofy");
   /*---(calculate locations)---------*/
   x_right = (s_rig - (x_wide * 3));
   /*---(output)----------------------*/
   for (x_row = 0; x_row < (x_nrow + 1); ++x_row) {
      for (x_col = 0; x_col < 3; ++x_col) {
         x_letter = rand () % 10 + '0';
         SHOW_HINTS   attron (COLOR_PAIR( 1));
         else         attron (COLOR_PAIR(12));
         if (x_row ==  entry.pointer[0] - '0') {
            entry.suffix [x_col] = my.magic_num [ 9 + x_col] = x_letter;
         } else {
            attrset (0);
            attron (COLOR_PAIR(12));
         }
         FONT_letter ( "goofy", x_letter, x_row * x_tall, x_right + (x_col * x_wide));
         attrset (0);
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      mvprintw ( 12, x_right + 5,  ".-------------.", x_text);
      sprintf (x_text, "| x_tall = %2d |", x_tall);
      mvprintw ( 13, x_right + 5,  "%s", x_text);
      sprintf (x_text, "| x_wide = %2d |", x_wide);
      mvprintw ( 14, x_right + 5,  "%s", x_text);
      sprintf (x_text, "| x_nrow = %2d |", x_nrow);
      mvprintw ( 15, x_right + 5,  "%s", x_text);
      sprintf (x_text, "| ptr    = %2d |", entry.pointer [0] - '0');
      mvprintw ( 16, x_right + 5,  "%s", x_text);
      mvprintw ( 17, x_right + 5,  "'-------------'", x_text);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
VEIL_knock_place     (char a_letter, int a_col, int a_row)
{
   char        rce         =  -10;
   int         x_xpos      =    0;
   int         x_tall      =    0;
   int         x_ygap      =    4;
   int         x_ybeg      =    0;
   int         x_ypos      =    0;
   /*---(x-coord)------------------------*/
   --rce;  switch (a_col) {
   case  0 :  x_xpos = ((FONT_wide ("alligator") * 2) + 0);       break;
   case  1 :  x_xpos = (s_rig - (FONT_wide ("goofy") * 3)) - 5;   break;
   default :  return rce;
   }
   /*---(y-coord)------------------------*/
   x_tall = FONT_tall ("dots");
   x_ybeg = s_mid - ((7 * (x_tall + x_ygap)) / 2.0);
   x_ypos = x_ybeg + (a_row * (x_tall + x_ygap));
   /*---(display)------------------------*/
   FONT_letter ( "dots", a_letter, x_ypos, x_xpos);
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show knock dots ---------------------------------*/
VEIL_knocks        (void)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         knock_spacing;
   char        x_knocks    [15]  = "";
   char        x_letter    = ' ';
   int         x_tall      =    0;
   int         x_wide      =    0;
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   if (my.show_knock  != 'y')  return 0;
   /*---(prepare)------------------------*/
   knock_spacing = 4;
   if (s_mid <  20) knock_spacing = 3;
   for (i = 0; i < 14; ++i) {
      x_letter = rand () % 2;
      switch (x_letter) {
      case 0 : x_knocks [i] = ' ';   break;
      case 1 : x_knocks [i] = '.';   break;
      }
      x_knocks [i + 1] = 0;
   }
   x_tall = FONT_tall ("dots");
   x_wide = FONT_wide ("dots");
   /*---(output)-------------------------*/
   for (i = 0; i < 14; ++i) {
      x_letter = x_knocks [i];
      SHOW_HINTS   attron (COLOR_PAIR( 1));
      else         attron (COLOR_PAIR(12));
      if      (i ==  1)  entry.knock [0] = my.magic_num [ 3 + 0] = x_letter;
      else if (i ==  8)  entry.knock [1] = my.magic_num [ 3 + 1] = x_letter;
      else if (i == 12)  entry.knock [2] = my.magic_num [ 3 + 2] = x_letter;
      else if (i ==  5)  entry.knock [3] = my.magic_num [ 3 + 3] = x_letter;
      else {
         attrset (0);
         attron (COLOR_PAIR(12));
      }
      VEIL_knock_place (x_letter, trunc (i / 7), i % 7);
      attrset (0);
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      mvprintw ( 21, 25,  ".-------------.");
      sprintf (x_text, "| x_tall = %2d |", x_tall);
      mvprintw ( 22, 25,  "%s", x_text);
      sprintf (x_text, "| x_wide = %2d |", x_wide);
      mvprintw ( 23, 25,  "%s", x_text);
      mvprintw ( 24, 25,  "'-------------'");
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show terminal indicator -------------------------*/
VEIL_tty           (int a_x, int a_y)
{
   /*---(locals)-----------+-----------+-*/
   char        x_type      = 'e';
   /*---(defense)------------------------*/
   if (my.show_tty    != 'y')  return 0;
   /*---(show terminal number)-----------*/
   attron (COLOR_PAIR(12));
   FONT_letter ( "dots"     , ttytyp  - '0', 10, s_cen - 11);
   FONT_letter ( "alligator", ttynum  - '0', 10, s_cen -  5);
   FONT_letter ( "dots"     , ttytyp  - '0', 14, s_cen +  6);
   attroff(COLOR_PAIR(12));
   /*---(external indicator)-------------*/
   if (my.show_external == 'y')      x_type = 'e';
   else                              x_type = 'i';
   attron (COLOR_PAIR(12));
   mvprintw (19, s_cen - 2,  "%c", x_type);
   mvprintw (19, s_cen    ,  "%c", x_type);
   mvprintw (19, s_cen + 2,  "%c", x_type);
   mvprintw (20, s_cen - 1,  "%c", x_type);
   mvprintw (20, s_cen + 1,  "%c", x_type);
   mvprintw (21, s_cen    ,  "%c", x_type);
   /*> FONT_letter ( "basic"    , x_type, s_mid + 10, x_mid);                       <*/
   attroff(COLOR_PAIR(12));
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show chunky numbers in middle -------------------*/
VEIL_middle          (void)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         x_row       = 0;               /* iterator -- rows             */
   int         x_col       = 0;               /* iterator -- columnns         */
   int         x_max       = 0;
   int         x_mid       = 0;
   int         x_left      = 0;           /* left of left knock               */
   int         x_right     = 0;           /* left of right knock              */
   int         x_dist      = 0;
   char        x_done      = 'n';             /* flag -- already handled      */
   int         x_tall      = 0;
   int         x_wide      = 0;
   char        x_letter    = ' ';
   char        x_digit     = ' ';
   char        x_text      [LEN_DESC] = "";
   int         x_top       = 0;
   /*---(prepare)------------------------*/
   x_tall    = FONT_tall ("chunky_full");
   x_wide    = FONT_wide ("chunky_full");
   x_left    = (FONT_wide ("alligator") * 2)       + FONT_wide ("dots");
   x_right   = (s_rig - (FONT_wide ("goofy") * 3)) - FONT_wide ("dots");
   x_dist    = x_right - x_left;
   x_max     = (x_right - x_left) / x_wide;
   x_max    += (x_max % 2);   /* make it even */
   x_left    = x_left + (x_dist - (x_max * x_wide)) / 2;
   x_top     = s_mid - x_tall / 2;
   /*---(output)----------------------*/
   for (x_row = 0; x_row <  2; ++x_row) {
      for (x_col = 0; x_col < x_max; x_col += 2) {
         x_letter = rand () % 26 + 'a';
         x_digit  = rand () % 10 + '0';
         SHOW_HINTS   attron (COLOR_PAIR( 1));
         else         attron (COLOR_PAIR(12));
         if (x_row == 0 && x_col == 2) {
            entry.rot [0]     = my.magic_num [ 7] = x_digit;
         } else if (x_row == 1 && x_col == x_max - 4) {
            entry.pointer [0] = my.magic_num [ 8] = x_digit;
         } else {
            attrset (0);
            attron (COLOR_PAIR(12));
         }
         FONT_letter ( "chunky_full", x_letter, x_top + x_row * x_tall, x_left + ((x_col + 0) * x_wide));
         FONT_letter ( "chunky_full", x_digit , x_top + x_row * x_tall, x_left + ((x_col + 1) * x_wide));
         attrset (0);
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      x_row = 45;
      mvprintw (x_row++, x_left + 5,  ".---------------.");
      sprintf (x_text, "| x_tall  = %3d |", x_tall);
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| x_wide  = %3d |", x_wide);
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| x_dist  = %3d |", x_dist);
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| x_max   = %3d |", x_max);
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| x_right = %3d |", x_right);
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| x_left  = %3d |", x_left);
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| rot     = %3d |", entry.rot     [0] - '0');
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      sprintf (x_text, "| ptr     = %3d |", entry.pointer [0] - '0');
      mvprintw (x_row++, x_left + 5,  "%s", x_text);
      mvprintw (x_row++, x_left + 5,  "'---------------'");
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show grid information ---------------------------*/
show_grid          (int a_x, int a_y)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columnns         */
   int         x_max       = 0;
   int         x_mid       = 0;
   int         x_knock1;                  /* left of left knock               */
   int         x_knock2;                  /* left of right knock              */
   char        x_done      = 'n';             /* flag -- already handled      */
   char        letter      = 0;
   int         count       = 0;
   /*---(prepare)------------------------*/
   x_knock1  = ((10 * 2) - 1);
   x_knock2  = (a_x - (8 * 3)) - 5;
   x_max = (x_knock2 - x_knock1 - 5) / 7;
   x_mid = s_cen - ((x_max / 2.0) * 7) - 2;
   /*---(output)-------------------------*/
   for (i = 0; i <  1; ++i) {
      for (j = 0; j < x_max; ++j) {
         /*---(prepare)------------------*/
         x_done = 'n';
         /*---(normal)-------------------*/
         if (count % 2 == 0)  letter =  rand () % 26 + 'a';
         else                 letter =  rand () % 10 + '0';
         attron (COLOR_PAIR( 9));
         FONT_letter ( "chunky_full", letter, i * 5 + s_mid +  4, x_mid + (j * 7));
         attroff(COLOR_PAIR( 9));
         /*---(done)---------------------*/
         ++count;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show binary numbers at bottom -------------------*/
show_binary        (int a_x, int a_y)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columnns         */
   int         x_knock1;                  /* left of left knock               */
   /*---(defense)------------------------*/
   if (my.show_binary    != 'y')   return 0;
   /*---(prepare)------------------------*/
   x_knock1  = ((10 * 2) - 1);
   /*---(output)-------------------------*/
   attron (COLOR_PAIR(14));
   for (i =  0; i <  3; ++i) {
      for (j =  0 ; j < 3; ++j) {
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 +  6);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 14);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 22);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 30);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 38);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 46);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 54);
         FONT_letter ("binary",  rand () % 10, (i * 2) + s_bot  - 9, (j * 2) + x_knock1 + 62);
      }
   }
   attroff(COLOR_PAIR(14));
   /*---(complete)-----------------------*/
   return 0;
}

char
VEIL_counters        (void)
{
   char        x_text      [LEN_DESC] = "";
   SHOW_COUNTERS {
      mvprintw (  7,  60,  ".-------------.");
      sprintf (x_text, "| s_rig = %3d |", s_rig);
      mvprintw (  8,  60,  "%s", x_text);
      sprintf (x_text, "| s_cen = %3d |", s_cen);
      mvprintw (  9,  60,  "%s", x_text);
      sprintf (x_text, "| s_bot = %3d |", s_bot);
      mvprintw ( 10,  60,  "%s", x_text);
      sprintf (x_text, "| s_mid = %3d |", s_mid);
      mvprintw ( 11,  60,  "%s", x_text);
      mvprintw ( 12,  60,  ".-------------.");
   }
   return 0;
}

char             /* [------] print the /etc/issue file and login prompt ------*/
prompt             (char  a_tty)
{
   yLOG_enter  (__FUNCTION__);
   yLOG_value  ("tty"       , a_tty);
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   int         j           = 0;
   int         c           = 0;
   char        msg         [50] = " _____________________________";
   int         y;
   int         x;
   int         x_left;     /* left of alligator       */
   int         x_knock1;   /* left of left knock      */
   int         x_right;    /* left of goofy           */
   int         left_c;     /* left of chunky          */
   int         count_a;    /* count of aligator       */
   int         mid_a;      /* middle of aligator      */
   int         count_c;    /* count of chunky         */
   int         right;
   int         x_max       = 0;
   int         x_mid       = 0;
   char        x_done      = 'n';
   /*---(get dimensions)--------------*/
   getmaxyx (stdscr, y, x);
   s_top       = 0;
   s_mid       = y / 2;
   s_bot       = y - 1;
   s_lef       = 0;
   s_cen       = x / 2;
   s_rig       = x;
   /*---(set positions)---------------*/
   x_left    = 0;
   x_right   = (x - (8 * 3));
   x_knock1  = (x_left + (10 * 2) - 1);
   left      = x_knock1;
   left2     = x_right - 1;
   x_knock2  = x_right - 5;
   left_c    = s_cen - ((int) ((s_cen - x_knock1) / 8) * 8);
   count_c   = ((int) ((s_cen - x_knock1) / 8) * 2);
   yLOG_value  ("x_left"      , x_left         );
   yLOG_value  ("x_right"     , x_right        );
   yLOG_value  ("x_knock1"    , x_knock1       );
   yLOG_value  ("left"        , left           );
   yLOG_value  ("left2"       , left2          );
   yLOG_value  ("x_knock2"    , x_knock2       );
   yLOG_value  ("left_c"      , left_c         );
   yLOG_value  ("count_c"     , count_c        );
   /*---(show sections)------------------*/
   VEIL_butterfly (x, 0);
   VEIL_middle    ();
   VEIL_left      ();
   VEIL_right     ();
   VEIL_tty       (x, y);
   VEIL_knocks    ();
   show_binary    (x, y);
   /*> show_grid      (x, y);                                                         <*/
   /*---(signin)-------------------------*/
   ctitle = rand () % ntitle;
   if (my.show_login     == 'y') {
      attron (COLOR_PAIR(14));
      mvprintw ( s_bot  - 12, x_knock2 - 30,  "%-12.12s                   " , " ");
      mvprintw ( s_bot  - 11, x_knock2 - 30,  "%-12.12s [%-15d]"            , titles[ctitle].cluster, my.dev_num);
      mvprintw ( s_bot  - 10, x_knock2 - 30,  "%-12.12s [%c%c             ]", titles[ctitle].seq    , my.host_name[1], my.host_name[2]);
      mvprintw ( s_bot  -  9, x_knock2 - 30,  "%-12.12s [%-15.15s]"         , titles[ctitle].host   , my.host_name + 4);
      mvprintw ( s_bot  -  8, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].date);
      mvprintw ( s_bot  -  7, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].host);
      mvprintw ( s_bot  -  6, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].user);
      mvprintw ( s_bot  -  5, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].token);
      mvprintw ( s_bot  -  4, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].password);
      mvprintw ( s_bot  -  3, x_knock2 - 30,  "%-12.12s                   " , " ");
      attroff(COLOR_PAIR(14));
      attron (COLOR_PAIR(13));
      mvprintw ( s_bot  -  8, x_knock2 - 16,  "               ");
      attroff(COLOR_PAIR(13));
   }
   VEIL_counters ();
   /*---(complete)-----------------------*/
   yLOG_note   ("printed issue");
   yLOG_exit   (__FUNCTION__);
   return 0;
}


char
get_login          (void)
{
   /*---(design notes)-------------------*/
   /*
    *  part       k    = knock
    *             p    = prefix
    *             u/I  = username       (I is tentative username done)
    *             i    = infix
    *             c/S  = code/password  (S is tentative password done)
    *             s    = suffix
    *             d    = done
    *             R    = refresh request
    *             B    = break/ctrl-c
    *             T    = trailing characters
    *
    *  status     A    = good
    *             F    = failed
    *
    */
   /*---(begin)--------------------------*/
   yLOG_enter  (__FUNCTION__);
   /*---(locals)-----------+-----------+-*/
   char        input       [200] = "";
   char        ch          = ' ';
   int         count       = 0;
   int         count_save  = -1;
   int         finish      = -1;
   int         loop        = 0;
   int         secs        = 0;
   char        indicator   [5] = "#";
   char        status      = 'A';
   int         len;
   int         clen;
   int         off         = 0;
   char        part        = 'k';
   int         lknock      = 0;
   int         i           = 0;
   int         j           = 0;
   tPASSWD    *pw          = NULL;
   tSHADOW    *spw         = NULL;
   char       *salt        = NULL;
   char       *password    = NULL;
   char       *encrypted   = NULL;
   char        msg         [200];
   char        rc          = 0;
   int         x_max       = 0;
   int         x_mid       = 0;
   /*---(prepare)------------------------*/
   lknock = strlen (entry.knock);
   yLOG_note   ("entering initial key clearing loop");
   yLOG_note   ("beginning normal key processing");
   /*---(loop through input)-------------*/
   while (1) {
      /*---(get next character)----------*/
      ch = getch ();
      /*---(timer visual)----------------*/
      if (my.show_timer == 'y') {
         if        (secs <=   30) {
            attron (COLOR_PAIR(11));
            FONT_letter ( "dots"     , secs % 2,  s_bot  - 2, s_cen - 18 + (secs -   0));
            attroff(COLOR_PAIR(11));
         } else if (secs <=  60) {
            attron (COLOR_PAIR(11));
            FONT_letter ( "dots"     , secs % 2,  s_bot  - 2, s_cen + 14 - (secs -  30));
            attroff(COLOR_PAIR(11));
         } else if (secs <=  90) {
            attron (COLOR_PAIR(11));
            FONT_letter ( "dots"     , secs % 2,  s_bot  - 2, s_cen - 18 + (secs -  60));
            attroff(COLOR_PAIR(11));
         } else if (secs <= 120) {
            attron (COLOR_PAIR(11));
            FONT_letter ( "dots"     , secs % 2,  s_bot  - 2, s_cen + 14 - (secs -  90));
            attroff(COLOR_PAIR(11));
         }
      }
      /*---(status)----------------------*/
      if (count != count_save && my.show_status == 'y') {
         x_max = (left2 - left - 2) / 8;
         x_mid = s_cen - ((x_max / 2.0) * 8) - 2;
         attron (COLOR_PAIR(12));
         for (i = 0; i < x_max; ++i) {
            FONT_letter ( "basic"    , rand() % 25 + 'b' ,   0,  x_mid + (i * 8));
         }
         attroff(COLOR_PAIR(12));
         if (my.show_hint   == 'y' || my.show_hint == 's') attron (COLOR_PAIR( 1));
         else                                      attron (COLOR_PAIR(12));
         i = x_mid + ((count % x_max) * 8);
         FONT_letter ( "basic"    , status ,   0,  i);
         if (my.show_hint   == 'y' || my.show_hint == 's') attroff(COLOR_PAIR( 1));
         else                                      attroff(COLOR_PAIR(12));
         /*> attron (COLOR_PAIR(12));                                                                   <* 
          *> FONT_letter ( "basic"    , toupper(part) ,   0 * 7,  (((count - 1) % 20) + 4) * 8 + 5);   <* 
          *> attroff(COLOR_PAIR(12));                                                                   <*/
         count_save = count;
      }
      SHOW_COUNTERS {
         mvprintw (  7, s_cen - 8,  ".--------------.");
         mvprintw (  8, s_cen - 8,  "| %s |", my.magic_num);
         mvprintw (  9, s_cen - 8,  ".--------------.");
      }
      /*> mvprintw (s_bot  - 4, s_cen - 5, "%d", count);                             <* 
       *> mvprintw (s_bot  - 4, s_cen + 5, "%d", finish);                            <*/
      /*---(timeout)---------------------*/
      ++loop;
      if (loop % 5 == 0) ++secs;
      if ( secs > 120) {
         part = 'Z';
         break;
      }
      /*---(didn't get a character)------*/
      if (ch == ERR) {
         usleep ( 100000);
         refresh();
         continue;
      }
      /*---(final escape)----------------*/
      if (ch    == 27)  {
         if (count != finish) {
            part   = 'T';
            status = 'F';
         }
         break;
      }
      /*---(enter key)-------------------*/
      /*> if (count == 0 && ch == 12) continue;       /+ intial cr/nl             +/   <* 
       *> if (count == 0 && ch == 10) continue;       /+ intial cr/nl             +/   <*/
      if (ch    == '\n')  {
         part   = 'T';
         status = 'F';
         break;
      }
      /*---(special requests)------------*/
      if (ch    == 3 )            { part = 'B'; break; }  /* C-c quit         */
      if (ch    == 18)            { part = 'R'; break; }  /* C-r refresh      */
      /*---(defense)---------------------*/
      if (ch    <  32  || ch > 126)   continue;   /* weird characters         */
      /*---(fake input)------------------*/
      if (my.show_login == 'y') {
         attron (COLOR_PAIR(13));
         /*---(first line)---------------*/
         if (count >=  0 && count <  6) {
            mvprintw (s_bot  - 8, x_knock2 - 16 + count -  0, "*");
         }
         /*---(second line)--------------*/
         if (count >=  6 && count < 14) {
            if (count ==  6) {
               mvprintw (s_bot  - 7, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 7, x_knock2 - 16 + count -  6,  "*");
         }
         /*---(third line)---------------*/
         if (count >= 14 && count < 20) {
            if (count ==  14) {
               mvprintw (s_bot  - 6, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 6, x_knock2 - 16 + count - 14,  "*");
         }
         /*---(fourth line)--------------*/
         if (count >= 20 && count < 28) {
            if (count ==  20) {
               mvprintw (s_bot  - 5, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 5, x_knock2 - 16 + count - 20,  "*");
         }
         /*---(fifth line)---------------*/
         if (count >= 28 && count < 40) {
            if (count ==  28) {
               mvprintw (s_bot  - 4, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 4, x_knock2 - 16 + count - 28,  "*");
         }
         attroff(COLOR_PAIR(13));
      }
      /*---(check knock)-----------------*/
      if (status != 'F' && part == 'k' ) {
         if (count <  lknock) {
            if (ch != entry.knock  [count])  status = 'F';
         } else {
            part = 'p';
            off  = lknock;
         }
      }
      /*---(check prefix)----------------*/
      if (status != 'F' && part == 'p' ) {
         if (count <  off + 2) {
            if (ch != entry.prefix [count - off])  status = 'F';
         } else {
            part = 'u';
            off += 2;
         }
      }
      /*---(check username)--------------*/
      if (status != 'F' && part == 'u' ) {
         if      (ch != ' ') {
            if (count - off <  8) {
               entry.username [count - off] = ch;
               entry.username [count - off + 1] = '\0';
               /*> DEBUG  mvprintw ( 58,  95, "[[%s]]", entry.username);              <*/
            } else {
               status = 'F';
            }
         } else {
            /*---(check for root)--------*/
            if (strcmp (entry.username, "root") == 0) {
               status = 'F';
               strcpy (entry.user_fix, "ZZZZ");
               strcpy (entry.username, "ZZZZ");
            } else if (strcmp (entry.username, "kurios") == 0) {
               strcpy (entry.user_fix, "root");
               strcpy (entry.username, "root");
            }
            /*---(rotate)----------------*/
            len = strlen (entry.username);
            if (len < 4) {
               status = 'F';
            }
            strcpy (entry.user_fix, "            ");
            for (i = 0; i < len; ++i) {
               j = i + (entry.rot[0] - '0');
               if (j <  len) {
                  entry.user_fix [ j] = entry.username [i];
               } else {
                  entry.user_fix [ j - len] = entry.username [i];
               }
            }
            entry.user_fix [len] = '\0';
            strcpy (entry.user_fix, entry.username);
            /*---(display)---------------*/
            /*> DEBUG  mvprintw ( 59,  95, "[[%s]]", entry.user_fix);                 <*/
            part = 'I';
            off  = count + 1;
            /*---(check)-----------------*/
            pw  = getpwnam (entry.user_fix);
            if (pw == NULL) {
               status = 'F';
            }
            spw = getspnam (entry.user_fix);
            if (spw == NULL) {
               status = 'F';
            }
         }
      }
      /*---(check infix)-----------------*/
      if (status != 'F' && part == 'i' ) {
         if (ch != entry.infix  [count - off])  status = 'F';
         part = 'c';
         off += 1;
      }
      /*---(check password)--------------*/
      if (status != 'F' && part == 'c' ) {
         if      (ch != ' ') {
            if (count - off <  15) {
               entry.password [count - off] = ch;
               entry.password [count - off + 1] = '\0';
               /*> DEBUG  mvprintw ( 60,  95, "[[%s]]", entry.password);              <*/
            } else {
               status = 'F';
            }
         } else {
            part = 'S';
            off  = count + 1;
            password  = strdup (spw->sp_pwdp);
            salt      = strdup (spw->sp_pwdp);
            encrypted = crypt (entry.password, salt);
            if (strcmp (encrypted, password) != 0) {
               status = 'F';
            }
         }
      }
      /*---(check suffix)----------------*/
      if (status != 'F' && part == 's' ) {
         if (count <  off + 3) {
            if (ch != entry.suffix [count - off])  status = 'F';
            if (count == off + 2) { 
               part          = 'D';
               finish        = count + 1;
            }
         } else {
            part          = 'D';
            off          += 3;
            finish        = count + 1;
         }
      }
      /*---(display)---------------------*/
      ++count;
      refresh ();
      /*---(prepare)---------------------*/
      if (part == 'I' )  part = 'i';
      if (part == 'S' )  part = 's';
      usleep ( 100000);
      /*---(done)------------------------*/
   }
   yLOG_char   ("part"       , part);
   /*---(failed due to timeout)----------*/
   if (part == 'Z') {
      /* translation > fuck you window licker ;)  */
      strcpy (msg, "irrumabo vos fenestram lingent");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("timed out, login failed");
      audit_fail (dev, part);
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -1;
   }
   /*---(refresh request)----------------*/
   if (part == 'R') {
      /* translation > once more into the breech  */
      strcpy (msg, "iterum, in confractione");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("triggered a screen refresh");
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return  1;
   }
   /*---(cancel request)-----------------*/
   if (part == 'B') {
      /* translation > i came into a place void of all light -- dante                       */
      strcpy (msg, "lo venne in loco d'ogne luce muto");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("login cancelled");
      audit_fail (dev, part);
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -2;
   }
   /*---(general failure)----------------*/
   if (status == 'F') {
      /* translation > all hope abandon, ye who enter in -- dante                           */
      strcpy (msg, "lasciate ogne speranza, voi ch'intrate");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("login failed");
      audit_fail (dev, part);
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -1;
   }
   /*---(check password)-----------------*/
   pw  = getpwnam (entry.user_fix);
   if (pw == NULL) {
      /* translation > all hope abandon, ye who enter in -- dante                           */
      strcpy (msg, "lasciate ogne speranza, voi ch'intrate");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("can not find user name in password database");
      audit_fail (dev, 'u');
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -3;
   }
   spw = getspnam (entry.user_fix);
   if (spw == NULL) {
      /* translation > all hope abandon, ye who enter in -- dante                           */
      strcpy (msg, "lasciate ogne speranza, voi ch'intrate");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("can not find user name in shadow database");
      audit_fail (dev, 'u');
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -3;
   }
   password  = strdup (spw->sp_pwdp);
   salt      = strdup (spw->sp_pwdp);
   encrypted = crypt (entry.password, salt);
   if (strcmp (encrypted, password) != 0) {
      /* translation > all hope abandon, ye who enter in -- dante                           */
      strcpy (msg, "lasciate ogne speranza, voi ch'intrate");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("password incorrect");
      audit_fail (dev, 'u');
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      free (password);
      free (salt);
      free (encrypted);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -4;
   }
   chown (dev, pw->pw_uid, 0);
   chmod (dev, 0700);
   /*---(save key information)-----------*/
   strcpy (my.user_name, entry.user_fix);
   strcpy (shell, pw->pw_shell);
   /*---(message)------------------------*/
   free (password);
   free (salt);
   free (encrypted);
   /* translation > here must all distrust be left behind -- dante                          */
   strcpy (msg, "qui si convien lasciare ogne sospettoo");
   len = strlen (msg);
   if (my.show_judgement == 'y') {
      mvprintw ( s_bot ,  s_cen - (len / 2), msg);
      refresh ();
   }
   yLOG_note   ("successful login");
   /*---(log the openning)---------------*/
   veil_rpid = getpid();
   audit_login (dev, entry.user_fix, veil_rpid);
   sleep (1);
   /*---(complete)-----------------------*/
   yLOG_exit   (__FUNCTION__);
   return 0;
}
