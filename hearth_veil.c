/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



int         s_top       =   0;
int         s_mid       =   0;
int         s_bot       =   0;

int         s_lef       =   0;
int         s_lefplus   =   0;
int         s_cen       =   0;
int         s_rigminus  =   0;
int         s_rig       =   0;

#define     COLOR_OFF        attrset (0);
#define     COLOR_WHITE      attron (COLOR_PAIR( 1))
#define     COLOR_GREEN      attron (COLOR_PAIR(10))
#define     COLOR_CYAN       attron (COLOR_PAIR(11))
#define     COLOR_YELLOW     attron (COLOR_PAIR(12))
#define     COLOR_BLUE       attron (COLOR_PAIR(14))

int         s_conf  [9][2] =
{
   {  -1,  -1 },   /* knock  1 */
   {  -1,  -1 },   /* knock  2 */
   {  -1,  -1 },   /* knock  3 */
   {  -1,  -1 },   /* knock  4 */
   {  -1,  -1 },   /* prefix 1 */
   {  -1,  -1 },   /* prefix 2 */
   {  -1,  -1 },   /* rotation */
   {  -1,  -1 },   /* infix  1 */
   {  -1,  -1 },   /* pointer  */
};

#define     VEIL_CONF   "/etc/hearth.conf"


char         /*--> read positions from conf file ---------[ leaf   [ ------ ]-*/
VEIL_conf            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_DESC]  = "";
   int         x_len       =    0;
   int         x_line      =    0;
   int         x_count     =    0;
   int         x_row       =    0;
   char        x_text      [LEN_DESC] = "";
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   DEBUG_INPT   yLOG_note    ("open configuration file");
   DEBUG_INPT   yLOG_info    ("file"      , VEIL_CONF);
   f = fopen (VEIL_CONF, "r");
   DEBUG_INPT   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_INPT   yLOG_note    ("file could not be openned");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)---------------------------*/
   while (1) {
      /*---(get entry)-------------------*/
      fgets (x_recd, LEN_DESC, f);
      if (feof (f))  {
         DEBUG_INPT  yLOG_note    ("end of file reached");
         break;
      }
      /*---(clean)-----------------------*/
      strltrim  (x_recd, ySTR_BOTH, LEN_RECD);
      x_len = strlen (x_recd);
      DEBUG_INPT   yLOG_value   ("x_len (1)" , x_len);
      if (x_len <= 0)  {
         DEBUG_INPT  yLOG_note    ("entry is empty");
         break;
      }
      x_recd [--x_len] = '\0';
      DEBUG_INPT   yLOG_info    ("x_recd"    , x_recd);
      DEBUG_INPT   yLOG_value   ("x_len (2)" , x_len);
      if (x_len != 2)  {
         DEBUG_INPT  yLOG_note    ("entry is wrong length");
         break;
      }
      /*---(handle)----------------------*/
      DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
      /*> printf ("x_recd    = %s\n", x_recd);                                        <* 
       *> printf ("x_recd[0] = %c\n", x_recd[0]);                                     <* 
       *> printf ("x_recd[1] = %c\n", x_recd[1]);                                     <* 
       *> printf ("x_line    = %d\n", x_line);                                        <*/
      if (strchr ("0123456789", x_recd[0]) != NULL) {
         s_conf [x_line][0]  = x_recd [0] - '0';
         ++x_count;
      }
      if (strchr ("0123456789", x_recd[1]) != NULL) {
         s_conf [x_line][1]  = x_recd [1] - '0';
         ++x_count;
      }
      printf ("past assignments\n");
      /*---(done)------------------------*/
      ++x_line;
   }
   /*---(close)--------------------------*/
   DEBUG_INPT   yLOG_note    ("close configuration file");
   fclose (f);
   /*---(check success)------------------*/
   DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
   --rce;  if (x_line != 9) {
      DEBUG_INPT   yLOG_note    ("not enough lines read");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("x_count"   , x_count);
   --rce;  if (x_count != 18) {
      DEBUG_INPT   yLOG_note    ("not enough items read");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      x_row = 10;
      mvprintw (x_row++, 150,  ".------conf------.");
      sprintf  (x_text, "| knock1   = %d %d |", s_conf [0][0], s_conf [0][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| knock2   = %d %d |", s_conf [1][0], s_conf [1][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| knock3   = %d %d |", s_conf [2][0], s_conf [2][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| knock4   = %d %d |", s_conf [3][0], s_conf [3][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| prefix1  = %d %d |", s_conf [4][0], s_conf [4][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| prefix2  = %d %d |", s_conf [5][0], s_conf [5][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| rotation = %d   |", s_conf [6][0]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| infix    = %d %d |", s_conf [7][0], s_conf [7][1]);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| pointer  = %d   |", s_conf [8][0]);
      mvprintw (x_row++, 150,  "%s", x_text);
      mvprintw (x_row++, 150,  "'----------------'");
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

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

char             /* [------] create one-time login numbers -------------------*/
VEIL_sizing          (void)
{
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(locals)-----------+-----------+-*/
   int         x           = 0;
   int         y           = 0;
   char        x_text      [LEN_DESC] = "";
   /*---(get dimensions)--------------*/
   getmaxyx (stdscr, y, x);
   s_top       = 0;
   s_mid       = y / 2;
   s_bot       = y - 1;
   DEBUG_GRAF   yLOG_svalue  ("s_bot", s_bot);
   s_lef       = 0;
   s_cen       = x / 2;
   s_rig       = x;
   DEBUG_GRAF   yLOG_svalue  ("s_rig", s_rig);
   s_lefplus   = s_lef + (FONT_wide ("alligator") * 2) + FONT_wide ("dots");
   DEBUG_GRAF   yLOG_svalue  ("s_lef+", s_lefplus);
   s_rigminus  = s_rig - (FONT_wide ("goofy") * 3)     - FONT_wide ("dots");
   DEBUG_GRAF   yLOG_svalue  ("s_rig-", s_rigminus);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char             /* [------] show butterfly background -----------------------*/
VEIL_butterfly       (void)
{
   /*---(locals)-----------+-----------+-*/
   int         b           = 0;               /* butterfly index              */
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columns          */
   int         x_butter    = 0;               /* left of butterfly            */
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   yLOG_char   ("arg_butter"  , my.show_butterfly  );
   if (my.show_butterfly != 'y')  return 0;
   /*---(output)-------------------------*/
   b           = rand () % 37;
   yLOG_value  ("butterfly"   , b              );
   x_butter  = (s_rig - MAX_COL) / 2;
   yLOG_value  ("x_butter"    , x_butter       );
   COLOR_GREEN;
   for (i =  0; i <  MAX_ROW; ++i) {
      for (j =  0; j <  MAX_COL; ++j) {
         mvprintw (i, j + x_butter,  "%c", butterfly [b][i][j]);
      }
   }
   attrset (0);
   SHOW_COUNTERS {
      COLOR_WHITE;
      mvprintw (  7,  60,  ".---overall---.");
      sprintf (x_text, "| s_rig = %3d |", s_rig);
      mvprintw (  8,  60,  "%s", x_text);
      sprintf (x_text, "| s_cen = %3d |", s_cen);
      mvprintw (  9,  60,  "%s", x_text);
      sprintf (x_text, "| s_bot = %3d |", s_bot);
      mvprintw ( 10,  60,  "%s", x_text);
      sprintf (x_text, "| s_mid = %3d |", s_mid);
      mvprintw ( 11,  60,  "%s", x_text);
      mvprintw ( 12,  60,  ".-------------.");
      attrset (0);
   }
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
   /*---(read config)-----------------*/

   /*---(show table of numbers)-------*/
   for (x_row = 0; x_row < (x_nrow + 1); ++x_row) {
      for (x_col =  0; x_col <  2; ++x_col) {
         x_letter = rand () % 10 + '0';
         SHOW_HINTS   COLOR_WHITE;
         else         COLOR_YELLOW;
         if      (x_col == 1 && x_row == 0         )  entry.prefix [1] = my.magic_num [ 1] =  x_letter;
         else if (x_col == 1 && x_row == x_nrow - 1)  entry.prefix [0] = my.magic_num [ 0] =  x_letter;
         else if (x_col == 0 && x_row == 4         )  entry.infix  [0] = my.magic_num [ 2] =  x_letter;
         else {
            attrset (0);
            COLOR_YELLOW;
         }
         FONT_letter ( "alligator", x_letter, x_row * x_tall, x_col * x_wide);
         attrset (0);
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      mvprintw ( 12,   3,  ".----left-----.", x_text);
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
         SHOW_HINTS   COLOR_WHITE;
         else         COLOR_YELLOW;
         if (x_row ==  entry.pointer[0] - '0') {
            entry.suffix [x_col] = my.magic_num [ 9 + x_col] = x_letter;
         } else {
            attrset (0);
            COLOR_YELLOW;
         }
         FONT_letter ( "goofy", x_letter, x_row * x_tall, x_right + (x_col * x_wide));
         attrset (0);
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      mvprintw ( 12, x_right + 5,  ".----right----.", x_text);
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
   int         x_xpos      =    0;
   int         x_ybeg      =    0;
   int         x_ypos      =    0;
   int         x_ygap      =    4;
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
      SHOW_HINTS   COLOR_WHITE;
      else         COLOR_YELLOW;
      if      (i ==  1)  entry.knock [0] = my.magic_num [ 3 + 0] = x_letter;
      else if (i ==  8)  entry.knock [1] = my.magic_num [ 3 + 1] = x_letter;
      else if (i == 12)  entry.knock [2] = my.magic_num [ 3 + 2] = x_letter;
      else if (i ==  5)  entry.knock [3] = my.magic_num [ 3 + 3] = x_letter;
      else {
         attrset (0);
         COLOR_YELLOW;
      }
      switch ((int) trunc (i / 7)) {
      case  0 :  x_xpos = s_lefplus   - x_wide;   break;
      case  1 :  x_xpos = s_rigminus          ;  break;
      }
      x_ybeg = s_mid - ((7 * x_tall + 6 * x_ygap) / 2.0);
      x_ypos = x_ybeg + ((i % 7) * (x_tall + x_ygap));
      FONT_letter ( "dots", x_letter, x_ypos, x_xpos);
      attrset (0);
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      mvprintw ( 21, 25,  ".----knock----.");
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
   COLOR_YELLOW;
   FONT_letter ( "dots"     , my.tty_type, 10, s_cen - 11);
   FONT_letter ( "alligator", ttynum, 10, s_cen -  5);
   FONT_letter ( "dots"     , my.tty_type, 14, s_cen +  6);
   COLOR_OFF;
   /*---(external indicator)-------------*/
   if (my.show_external == 'y')      x_type = 'e';
   else                              x_type = 'i';
   COLOR_YELLOW;
   mvprintw (19, s_cen - 2,  "%c", x_type);
   mvprintw (19, s_cen    ,  "%c", x_type);
   mvprintw (19, s_cen + 2,  "%c", x_type);
   mvprintw (20, s_cen - 1,  "%c", x_type);
   mvprintw (20, s_cen + 1,  "%c", x_type);
   mvprintw (21, s_cen    ,  "%c", x_type);
   /*> FONT_letter ( "basic"    , x_type, s_mid + 10, x_mid);                       <*/
   COLOR_OFF;
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
   x_left    = s_lefplus;
   x_right   = s_rigminus;
   x_dist    = x_right - x_left;
   x_max     = (x_right - x_left) / x_wide;
   x_max    -= (x_max % 2);   /* make it even */
   x_left    = x_left + (x_dist - (x_max * x_wide)) / 2;
   x_top     = s_mid - x_tall / 2;
   /*---(output)----------------------*/
   for (x_row = 0; x_row <  2; ++x_row) {
      for (x_col = 0; x_col < x_max; x_col += 2) {
         x_letter = rand () % 26 + 'a';
         x_digit  = rand () % 10 + '0';
         SHOW_HINTS   COLOR_WHITE;
         else         COLOR_YELLOW;
         if (x_row == 0 && x_col == 2) {
            entry.rot [0]     = my.magic_num [ 7] = x_digit;
         } else if (x_row == 1 && x_col == x_max - 4) {
            entry.pointer [0] = my.magic_num [ 8] = x_digit;
         } else {
            attrset (0);
            COLOR_YELLOW;
         }
         FONT_letter ( "chunky_full", x_letter, x_top + x_row * x_tall, x_left + ((x_col + 0) * x_wide));
         FONT_letter ( "chunky_full", x_digit , x_top + x_row * x_tall, x_left + ((x_col + 1) * x_wide));
         attrset (0);
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      x_row = 45;
      mvprintw (x_row++, x_left + 5,  ".----middle-----.");
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

char             /* [------] show binary numbers at bottom -------------------*/
VEIL_binary          (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columnns         */
   int         k           = 0;               /* iterator -- blocks           */
   int         x_top       = 0;
   int         x_left      = 0;           /* left of left knock               */
   char        x_letter    = ' ';
   /*---(defense)------------------------*/
   if (my.show_binary    != 'y')   return 0;
   /*---(prepare)------------------------*/
   x_top     = s_bot - 12;
   x_left    = FONT_wide ("alligator") * 2 + 8;
   /*---(output)-------------------------*/
   COLOR_BLUE;
   for (i =  0; i <  8; i += 2) {
      for (j =  0 ; j < 8; j += 2) {
         for (k =  0 ; k < 80; k += 10) {
            x_letter = rand () % 10 + '0';
            FONT_letter ("binary", x_letter, i + x_top, j + x_left + k);
         }
      }
   }
   COLOR_OFF;
   /*---(complete)-----------------------*/
   return 0;
}

char
VEIL_counters        (void)
{
   char        x_text      [LEN_DESC] = "";
   return 0;
}

char             /* [------] print the /etc/issue file and login prompt ------*/
prompt             (char  a_tty)
{
   yLOG_enter  (__FUNCTION__);
   yLOG_value  ("tty"       , a_tty);
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   int         i           = 0;
   int         j           = 0;
   int         c           = 0;
   char        msg         [50] = " _____________________________";
   int         x_left;     /* left of alligator       */
   int         x_knock1;   /* left of left knock      */
   int         x_right;    /* left of goofy           */
   int         right;
   int         x_max       = 0;
   int         x_mid       = 0;
   char        x_done      = 'n';
   /*---(set positions)---------------*/
   VEIL_sizing ();
   x_right   = (s_lef - (8 * 3));
   x_knock1  = ((10 * 2) - 1);
   left      = x_knock1;
   left2     = x_right - 1;
   x_knock2  = x_right - 5;
   yLOG_value  ("x_right"     , x_right        );
   yLOG_value  ("x_knock1"    , x_knock1       );
   yLOG_value  ("left"        , left           );
   yLOG_value  ("left2"       , left2          );
   yLOG_value  ("x_knock2"    , x_knock2       );
   /*---(show sections)------------------*/
   VEIL_butterfly ();
   rc = VEIL_conf      ();
   VEIL_middle    ();
   VEIL_left      ();
   VEIL_right     ();
   VEIL_tty       (0, 0);
   VEIL_knocks    ();
   VEIL_binary    ();
   /*---(signin)-------------------------*/
   ctitle = rand () % ntitle;
   if (my.show_login     == 'y') {
      COLOR_BLUE;
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
      COLOR_OFF;
      attron (COLOR_PAIR(13));
      mvprintw ( s_bot  -  8, x_knock2 - 16,  "               ");
      COLOR_OFF;
   }
   /*---(complete)-----------------------*/
   yLOG_note   ("printed issue");
   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
VEIL_timer           (int a_secs)
{
   /*---(locals)-----------+-----------+-*/
   int         x_pass      = 0;
   int         x_secs      = 0;
   int         x_row       = 0;
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   if (my.show_timer != 'y')  return 0;
   /*---(assign pass)--------------------*/
   if        (a_secs <=   30) {
      x_pass  = 1;
      x_secs  = a_secs;
   } else if (a_secs <=  60) {
      x_pass  = 2;
      x_secs  = a_secs - 30;
   } else if (a_secs <=  90) {
      x_pass  = 3;
      x_secs  = a_secs - 60;
   } else if (a_secs <= 120) {
      x_pass  = 4;
      x_secs  = a_secs - 90;
   }
   /*---(display marker)-----------------*/
   COLOR_CYAN;
   switch (x_pass) {
   case 4 :  FONT_letter ( "dots", a_secs % 2 + '0', s_bot - 2, s_cen + 14 - x_secs);
             break;
   case 3 :  FONT_letter ( "dots", a_secs % 2 + '0', s_bot - 2, s_cen - 18 + x_secs);
             break;
   case 2 :  FONT_letter ( "dots", a_secs % 2 + '0', s_bot - 2, s_cen + 14 - x_secs);
             break;
   case 1 :  FONT_letter ( "dots", a_secs % 2 + '0', s_bot - 2, s_cen - 18 + x_secs);
             break;
   }
   attrset (0);
   /*---(display pass)-------------------*/
   COLOR_CYAN;
   switch (x_pass) {
   case 4 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen + 24);
   case 3 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen + 18);
   case 2 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen - 30);
   case 1 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen - 24);
   }
   attrset (0);
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = s_bot - 4;
      mvprintw (x_row++, s_lefplus + 35,  ".-----timer-----.");
      sprintf (x_text, "| a_secs  = %3d |", a_secs);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      sprintf (x_text, "| x_secs  = %3d |", x_secs);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      sprintf (x_text, "| x_pass  = %3d |", x_pass);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      mvprintw (x_row++, s_lefplus + 35,  "'---------------'");
      attrset (0);
   }
   return 0;
}

char
VEIL_status          (int a_count, char a_status, char a_part)
{
   /*---(locals)-----------+-----------+-*/
   int         x_col       = 0;               /* iterator -- columnns         */
   int         x_row       = 0;               /* iterator -- columnns         */
   int         x_left      = 0;           /* left of left knock               */
   int         x_right     = 0;           /* left of right knock              */
   int         x_dist      = 0;
   int         x_max       = 0;
   char        x_tall      = 0;
   char        x_wide      = 0;
   char        x_letter    = ' ';
   static int  x_save      = -1;
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   if (my.show_status != 'y'   )   return 0;
   if (a_count        == x_save)   return 0;
   /*---(prepare)------------------------*/
   x_tall    = FONT_tall ("basic");
   x_wide    = FONT_wide ("basic");
   x_left    = s_lefplus;
   x_right   = s_rigminus;
   x_dist    = x_right - x_left;
   x_max     = (x_right - x_left) / x_wide;
   x_left    = x_left + (x_dist - (x_max * x_wide)) / 2;
   /*---(display)------------------------*/
   for (x_col = 0; x_col < x_max; ++x_col) {
      x_letter = rand () % 25 + 'b';
      if (my.show_hint == 'y' && x_col == a_count) {
         COLOR_WHITE;
         x_letter = a_status;
      } else {
         COLOR_YELLOW;
      }
      FONT_letter ( "basic", x_letter,  0,  x_left + (x_col * x_wide));
      attrset (0);
   }
   x_save = a_count;
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = s_top + x_tall + 1;
      mvprintw (x_row++, s_lefplus + 5,  ".-----status----.");
      sprintf (x_text, "| a_count = %3d |", a_count);
      mvprintw (x_row++, s_lefplus + 5,  "%s", x_text);
      sprintf (x_text, "| a_status=  %c  |", a_status);
      mvprintw (x_row++, s_lefplus + 5,  "%s", x_text);
      sprintf (x_text, "| a_part  =  %c  |", a_part  );
      mvprintw (x_row++, s_lefplus + 5,  "%s", x_text);
      mvprintw (x_row++, s_lefplus + 5,  "'---------------'");
      attrset (0);
   }
   /*---(complete)-----------------------*/
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
   int         x_count     = 0;
   int         count_save  = -1;
   int         finish      = -1;
   int         loop        = 0;
   int         secs        = 0;
   char        indicator   [5] = "#";
   char        x_status    = 'A';
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
      VEIL_timer (secs);
      /*---(status)----------------------*/
      VEIL_status (x_count, x_status, part);
      SHOW_COUNTERS {
         mvprintw (  7, s_cen - 8,  ".--------------.");
         mvprintw (  8, s_cen - 8,  "| %s |", my.magic_num);
         mvprintw (  9, s_cen - 8,  ".--------------.");
      }
      /*> mvprintw (s_bot  - 4, s_cen - 5, "%d", x_count);                             <* 
       *> mvprintw (s_bot  - 4, s_cen + 5, "%d", finish);                            <*/
      /*---(timeout)---------------------*/
      ++loop;
      if (my.use_timer == 'y' && loop % 5 == 0) ++secs;
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
         if (x_count != finish) {
            part   = 'T';
            x_status = 'F';
         }
         break;
      }
      /*---(enter key)-------------------*/
      /*> if (x_count == 0 && ch == 12) continue;       /+ intial cr/nl             +/   <* 
       *> if (x_count == 0 && ch == 10) continue;       /+ intial cr/nl             +/   <*/
      if (ch    == '\n')  {
         part   = 'T';
         x_status = 'F';
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
         if (x_count >=  0 && x_count <  6) {
            mvprintw (s_bot  - 8, x_knock2 - 16 + x_count -  0, "*");
         }
         /*---(second line)--------------*/
         if (x_count >=  6 && x_count < 14) {
            if (x_count ==  6) {
               mvprintw (s_bot  - 7, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 7, x_knock2 - 16 + x_count -  6,  "*");
         }
         /*---(third line)---------------*/
         if (x_count >= 14 && x_count < 20) {
            if (x_count ==  14) {
               mvprintw (s_bot  - 6, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 6, x_knock2 - 16 + x_count - 14,  "*");
         }
         /*---(fourth line)--------------*/
         if (x_count >= 20 && x_count < 28) {
            if (x_count ==  20) {
               mvprintw (s_bot  - 5, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 5, x_knock2 - 16 + x_count - 20,  "*");
         }
         /*---(fifth line)---------------*/
         if (x_count >= 28 && x_count < 40) {
            if (x_count ==  28) {
               mvprintw (s_bot  - 4, x_knock2 - 16, "               ");
            }
            mvprintw (s_bot  - 4, x_knock2 - 16 + x_count - 28,  "*");
         }
         attroff(COLOR_PAIR(13));
      }
      /*---(check knock)-----------------*/
      if (x_status != 'F' && part == 'k' ) {
         if (x_count <  lknock) {
            if (ch != entry.knock  [x_count])  x_status = 'F';
         } else {
            part = 'p';
            off  = lknock;
         }
      }
      /*---(check prefix)----------------*/
      if (x_status != 'F' && part == 'p' ) {
         if (x_count <  off + 2) {
            if (ch != entry.prefix [x_count - off])  x_status = 'F';
         } else {
            part = 'u';
            off += 2;
         }
      }
      /*---(check username)--------------*/
      if (x_status != 'F' && part == 'u' ) {
         if      (ch != ' ') {
            if (x_count - off <  8) {
               entry.username [x_count - off] = ch;
               entry.username [x_count - off + 1] = '\0';
               /*> DEBUG  mvprintw ( 58,  95, "[[%s]]", entry.username);              <*/
            } else {
               x_status = 'F';
            }
         } else {
            /*---(check for root)--------*/
            if (strcmp (entry.username, "root") == 0) {
               x_status = 'F';
               strcpy (entry.user_fix, "ZZZZ");
               strcpy (entry.username, "ZZZZ");
            } else if (strcmp (entry.username, "kurios") == 0) {
               strcpy (entry.user_fix, "root");
               strcpy (entry.username, "root");
            }
            /*---(rotate)----------------*/
            len = strlen (entry.username);
            if (len < 4) {
               x_status = 'F';
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
            off  = x_count + 1;
            /*---(check)-----------------*/
            pw  = getpwnam (entry.user_fix);
            if (pw == NULL) {
               x_status = 'F';
            }
            spw = getspnam (entry.user_fix);
            if (spw == NULL) {
               x_status = 'F';
            }
         }
      }
      /*---(check infix)-----------------*/
      if (x_status != 'F' && part == 'i' ) {
         if (ch != entry.infix  [x_count - off])  x_status = 'F';
         part = 'c';
         off += 1;
      }
      /*---(check password)--------------*/
      if (x_status != 'F' && part == 'c' ) {
         if      (ch != ' ') {
            if (x_count - off <  15) {
               entry.password [x_count - off] = ch;
               entry.password [x_count - off + 1] = '\0';
               /*> DEBUG  mvprintw ( 60,  95, "[[%s]]", entry.password);              <*/
            } else {
               x_status = 'F';
            }
         } else {
            part = 'S';
            off  = x_count + 1;
            password  = strdup (spw->sp_pwdp);
            salt      = strdup (spw->sp_pwdp);
            encrypted = crypt (entry.password, salt);
            if (strcmp (encrypted, password) != 0) {
               x_status = 'F';
            }
         }
      }
      /*---(check suffix)----------------*/
      if (x_status != 'F' && part == 's' ) {
         if (x_count <  off + 3) {
            if (ch != entry.suffix [x_count - off])  x_status = 'F';
            if (x_count == off + 2) { 
               part          = 'D';
               finish        = x_count + 1;
            }
         } else {
            part          = 'D';
            off          += 3;
            finish        = x_count + 1;
         }
      }
      /*---(display)---------------------*/
      ++x_count;
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
   if (x_status == 'F') {
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
