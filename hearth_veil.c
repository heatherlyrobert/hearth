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

/*  s_part     k    = knock
 *             p    = prefix
 *             u/I  = username       (I is tentative username done)
 *             i    = infix
 *             c/S  = code/password  (S is tentative password done)
 *             s    = suffix
 *             d    = done
 *             T    = trailing characters
 *
 *  s_status   A    = good
 *             F    = failed
 *             Z    = timed out
 *             R    = refresh request
 *             B    = break/ctrl-c
 */

#define     STATUS_GOOD      'A'
#define     STATUS_SUCCESS   'S'
#define     STATUS_FAILED    'F'
#define     STATUS_TIMEOUT   'Z'
#define     STATUS_REFRESH   'R'
#define     STATUS_BREAK     'B'

#define     PART_KNOCK       'k'
#define     PART_PREFIX      'p'
#define     PART_USERNAME    'u'
#define     PART_INFIX       'i'
#define     PART_PASSWORD    'c'
#define     PART_SUFFIX      's'
#define     PART_DONE        'd'
#define     PART_TRAILING    't'


char        s_status    = STATUS_GOOD;
char        s_cpart     = 'k';
int         s_loop      =   0;
int         s_secs      =   0;
int         s_count     =   0;
char        s_ch        =   0;


#define     MAX_PART       10
struct   cPARTS {
   char        part;
   short       beg;
   short       cnt;
   short       end;
   char        valid       [LEN_STR];
   char       *check;
   char        sign;
   char        next;
} s_parts      [MAX_PART] = {
   { PART_KNOCK    ,  1,  4,  4,  G_TYPE_KNOCK    , entry.knock    , '#', PART_PREFIX   },
   { PART_PREFIX   ,  5,  2,  6,  G_TYPE_NUM      , entry.prefix   , '#', PART_USERNAME },
   { PART_USERNAME ,  7, 99, 99,  G_TYPE_USER     , NULL           , ' ', PART_INFIX    },
   { PART_INFIX    ,  0,  1, 99,  G_TYPE_NUM      , entry.infix    , '#', PART_PASSWORD },
   { PART_PASSWORD ,  0, 99, 99,  G_TYPE_PASS     , NULL           , ' ', PART_SUFFIX   },
   { PART_SUFFIX   ,  0,  3, 99,  G_TYPE_NUM      , entry.suffix   , '#', PART_DONE     },
   { PART_DONE     ,  0,  1, 99,  G_TYPE_ESCAPE   , entry.done     , '#', PART_TRAILING },
   { PART_TRAILING ,  0, 99, 99,  ""              , NULL           , '-', '-'           },
   { '-'           ,  0,  0, 99,  ""              , NULL           , '-', '-'           },
   { '-'           ,  0,  0, 99,  ""              , NULL           , '-', '-'           },
};



#define     COLOR_OFF        attrset (0);
#define     COLOR_WHITE      attron (COLOR_PAIR( 1))
#define     COLOR_GREEN      attron (COLOR_PAIR(10))
#define     COLOR_CYAN       attron (COLOR_PAIR(11))
#define     COLOR_YELLOW     attron (COLOR_PAIR(12))
#define     COLOR_BLUE       attron (COLOR_PAIR(14))

int         s_conf  [10][2] =
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
   {  -1,  -1 },   /* language */
};

#define     VEIL_CONF   "/etc/hearth.conf"


char             /* [------] create one-time login numbers -------------------*/
VEIL_init            (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;        /* loop iterator                       */
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   VEIL_reset    ();
   /*---(user/pass)----------------------*/
   strlcpy (entry.username, "", LEN_STR);
   strlcpy (entry.password, "", LEN_STR);
   /*---(prefix)-------------------------*/
   entry.prefix  [0] = my.magic_num [ 0] =  '0' + rand () % 10;
   entry.prefix  [1] = my.magic_num [ 1] =  '0' + rand () % 10;
   entry.prefix  [2] = '\0';
   /*---(infix)--------------------------*/
   entry.infix   [0] = my.magic_num [ 2] =  '0' + rand () % 10;
   entry.infix   [1] = '\0';
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
   entry.suffix  [0] = my.magic_num [ 9] = '0' + rand () % 10;
   entry.suffix  [1] = my.magic_num [10] = '0' + rand () % 10;
   entry.suffix  [2] = my.magic_num [11] = '0' + rand () % 10;
   entry.suffix  [3] = '\0';
   /*---(done)---------------------------*/
   entry.done    [0] = '\x1B';
   entry.done    [1] = '\0';
   /*---(wrap-up)------------------------*/
   my.magic_num  [12] = '\0';
   DEBUG_PROG   yLOG_info    ("magic_num" , my.magic_num);
   /*---(language)-----------------------*/
   my.language = rand () % ntitle;
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

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
   int         x_off       =    0;
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
   x_off = (my.dev_num * 3) + 11;
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
      if (x_len <  x_off + 1)  {
         DEBUG_INPT  yLOG_note    ("entry is wrong length");
         break;
      }
      /*---(handle)----------------------*/
      DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
      /*> printf ("x_recd    = %s\n", x_recd);                                        <* 
       *> printf ("x_recd[0] = %c\n", x_recd[0]);                                     <* 
       *> printf ("x_recd[1] = %c\n", x_recd[1]);                                     <* 
       *> printf ("x_line    = %d\n", x_line);                                        <*/
      if (strchr ("0123456789", x_recd[x_off + 0]) != NULL) {
         s_conf [x_line][0]  = x_recd [x_off + 0] - '0';
         ++x_count;
      }
      if (strchr ("0123456789", x_recd[x_off + 1]) != NULL) {
         s_conf [x_line][1]  = x_recd [x_off + 1] - '0';
         ++x_count;
      }
      /*---(done)------------------------*/
      ++x_line;
   }
   /*---(close)--------------------------*/
   DEBUG_INPT   yLOG_note    ("close configuration file");
   fclose (f);
   /*---(check success)------------------*/
   DEBUG_INPT   yLOG_value   ("x_line"    , x_line);
   --rce;  if (x_line != 10) {
      DEBUG_INPT   yLOG_note    ("not enough lines read");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("x_count"   , x_count);
   --rce;  if (x_count != 20) {
      DEBUG_INPT   yLOG_note    ("not enough items read");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(assign)-------------------------*/
   my.language = s_conf [9][0];
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = 10;
      mvprintw (x_row++, 150,  ".------conf------.");
      sprintf  (x_text, "| dev_num  = %-3d |", my.dev_num);
      mvprintw (x_row++, 150,  "%s", x_text);
      sprintf  (x_text, "| x_off    = %-3d |", x_off);
      mvprintw (x_row++, 150,  "%s", x_text);
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
      sprintf  (x_text, "| lang     = %-3d |", s_conf [9][0]);
      mvprintw (x_row++, 150,  "%s", x_text);
      mvprintw (x_row++, 150,  "'----------------'");
      COLOR_OFF;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
VEIL_reset           (void)
{
   s_status    = STATUS_GOOD;
   s_cpart     = 'k';
   s_loop      =   0;
   s_secs      =   0;
   s_count     =   0;
   s_ch        =   0;
   strlcpy (my.entry_text , "", LEN_DESC);
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
   COLOR_OFF;
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
      COLOR_OFF;
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
            COLOR_OFF;
            COLOR_YELLOW;
         }
         FONT_letter ( "alligator", x_letter, x_row * x_tall, x_col * x_wide);
         COLOR_OFF;
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
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
      COLOR_OFF;
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
            COLOR_OFF;
            COLOR_YELLOW;
         }
         FONT_letter ( "goofy", x_letter, x_row * x_tall, x_right + (x_col * x_wide));
         COLOR_OFF;
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
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
      COLOR_OFF;
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
         COLOR_OFF;
         COLOR_YELLOW;
      }
      switch ((int) trunc (i / 7)) {
      case  0 :  x_xpos = s_lefplus   - x_wide;   break;
      case  1 :  x_xpos = s_rigminus          ;  break;
      }
      x_ybeg = s_mid - ((7 * x_tall + 6 * x_ygap) / 2.0);
      x_ypos = x_ybeg + ((i % 7) * (x_tall + x_ygap));
      FONT_letter ( "dots", x_letter, x_ypos, x_xpos);
      COLOR_OFF;
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      mvprintw ( 21, 25,  ".----knock----.");
      sprintf (x_text, "| x_tall = %2d |", x_tall);
      mvprintw ( 22, 25,  "%s", x_text);
      sprintf (x_text, "| x_wide = %2d |", x_wide);
      mvprintw ( 23, 25,  "%s", x_text);
      mvprintw ( 24, 25,  "'-------------'");
      COLOR_OFF;
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
   FONT_letter ( "alligator", my.tty_num, 10, s_cen -  5);
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
            x_digit = entry.rot [0];
         } else if (x_row == 1 && x_col == x_max - 4) {
            x_digit = entry.pointer [0];
         } else {
            COLOR_OFF;
            COLOR_YELLOW;
         }
         FONT_letter ( "chunky_full", x_letter, x_top + x_row * x_tall, x_left + ((x_col + 0) * x_wide));
         FONT_letter ( "chunky_full", x_digit , x_top + x_row * x_tall, x_left + ((x_col + 1) * x_wide));
         COLOR_OFF;
      }
   }
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
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
      COLOR_OFF;
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
VEIL_prompt          (void)
{
   char        x_text      [LEN_DESC] = "";
   int         x_left      = 0;
   int         x_right     = 0;
   int         x_row       = 0;
   int         x_col       = 0;
   int         x_gmt_off   = 0;
   int         i           = 0;
   x_right   = s_rigminus;
   x_left    = x_right - 35;
   yLOG_value  ("x_right"     , x_right);
   yLOG_value  ("x_left"      , x_left );
   if (my.show_login     != 'y') return 0;
   x_row = s_bot - 12;
   x_gmt_off = g_titles [my.language].gmt_off * 60 * 60;
   strl4time (time (NULL) + x_gmt_off, x_text, 0, 'T', LEN_DESC);
   COLOR_BLUE;
   mvprintw (x_row++, x_left,  "%-12.12s [%-15d     ]"            , g_titles [my.language].cluster , my.dev_num);
   mvprintw (x_row++, x_left,  "%-12.12s [%c%c                  ]", g_titles [my.language].seq     , my.host_name[1], my.host_name[2]);
   mvprintw (x_row++, x_left,  "%-12.12s [%-15.15s     ]"         , g_titles [my.language].host    , my.host_name + 4);
   mvprintw (x_row++, x_left,  "%-12.12s [%-19.19s ] " , g_titles [my.language].date, x_text);
   mvprintw (x_row++, x_left,  "%-12.12s [                    ] " , g_titles [my.language].user    );
   mvprintw (x_row++, x_left,  "%-12.12s [                    ] " , g_titles [my.language].token   );
   mvprintw (x_row++, x_left,  "%-12.12s [                    ] " , g_titles [my.language].password);
   mvprintw (x_row++, x_left,  "%-12.12s [%1d                   ] " , g_titles [my.language].attempt, 0 );
   COLOR_OFF;
   /*---(fake input)------------------*/
   COLOR_BLUE;
   x_row = s_bot - 8;
   x_col = x_left + 12 + 2;
   for (i = 0; i < s_count; ++i) {
      if      (i < 12)    mvprintw (x_row + 0, x_col + i -  0, "*");
      else if (i < 18)    mvprintw (x_row + 1, x_col + i - 12, "*");
      else if (i < 35)    mvprintw (x_row + 2, x_col + i - 18, "*");
   }
   COLOR_OFF;
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = s_bot - 11;
      mvprintw (x_row++, x_left - 35,  ".----prompt----------------------.");
      sprintf (x_text, "| my.lang = %-3d                  |", my.language);
      mvprintw (x_row++, x_left - 35,  "%s", x_text);
      sprintf (x_text, "| name    = %-20.20s |", g_titles [my.language].language);
      mvprintw (x_row++, x_left - 35,  "%s", x_text);
      sprintf (x_text, "| gmt_off = %-3d                  |", g_titles [my.language].gmt_off);
      mvprintw (x_row++, x_left - 35,  "%s", x_text);
      mvprintw (x_row++, x_left - 35,  "'--------------------------------'");
      COLOR_OFF;
   }
   return 0;
}

char             /* [------] print the /etc/issue file and login prompt ------*/
VEIL_show            (void)
{
   yLOG_enter  (__FUNCTION__);
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(set positions)---------------*/
   VEIL_sizing ();
   /*---(show sections)------------------*/
   rc = VEIL_butterfly ();
   rc = VEIL_conf      ();
   rc = VEIL_middle    ();
   rc = VEIL_left      ();
   rc = VEIL_right     ();
   rc = VEIL_tty       (0, 0);
   rc = VEIL_knocks    ();
   rc = VEIL_binary    ();
   rc = VEIL_prompt    ();
   /*---(complete)-----------------------*/
   yLOG_note   ("printed issue");
   yLOG_exit   (__FUNCTION__);
   return 0;
}

char         /*-> display timer on screen ----------------[ berry  [ ------ ]-*/
VEIL_timer           (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_pass      = 0;
   int         x_secs      = 0;
   int         x_row       = 0;
   char        x_text      [LEN_DESC] = "";
   /*---(defense)------------------------*/
   if (my.show_timer != 'y')  return 0;
   /*---(assign pass)--------------------*/
   if        (s_secs <=   30) {
      x_pass  = 1;
      x_secs  = s_secs;
   } else if (s_secs <=  60) {
      x_pass  = 2;
      x_secs  = s_secs - 30;
   } else if (s_secs <=  90) {
      x_pass  = 3;
      x_secs  = s_secs - 60;
   } else if (s_secs <= 120) {
      x_pass  = 4;
      x_secs  = s_secs - 90;
   }
   /*---(display marker)-----------------*/
   COLOR_CYAN;
   switch (x_pass) {
   case 4 :  FONT_letter ( "dots", s_secs % 2 + '0', s_bot - 2, s_cen + 14 - x_secs);
             break;
   case 3 :  FONT_letter ( "dots", s_secs % 2 + '0', s_bot - 2, s_cen - 18 + x_secs);
             break;
   case 2 :  FONT_letter ( "dots", s_secs % 2 + '0', s_bot - 2, s_cen + 14 - x_secs);
             break;
   case 1 :  FONT_letter ( "dots", s_secs % 2 + '0', s_bot - 2, s_cen - 18 + x_secs);
             break;
   }
   COLOR_OFF;
   /*---(display pass)-------------------*/
   COLOR_CYAN;
   switch (x_pass) {
   case 4 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen + 24);
   case 3 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen + 18);
   case 2 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen - 30);
   case 1 :  FONT_letter ( "dots", '1'             , s_bot - 2, s_cen - 24);
   }
   COLOR_OFF;
   /*---(display messeage)---------------*/
   COLOR_CYAN;
   mvprintw (s_bot - 3, s_cen - strlen (g_titles [my.language].timer) / 2,  "%s" , g_titles [my.language].timer );
   COLOR_OFF;
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = s_bot - 5;
      mvprintw (x_row++, s_lefplus + 35,  ".------timer------.");
      sprintf (x_text, "| s_loop  = %-5d |", s_loop);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      sprintf (x_text, "| s_secs  = %-3d   |", s_secs);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      sprintf (x_text, "| x_secs  = %-3d   |", x_secs);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      sprintf (x_text, "| x_pass  = %-3d   |", x_pass);
      mvprintw (x_row++, s_lefplus + 35,  "%s", x_text);
      mvprintw (x_row++, s_lefplus + 35,  "'----------------'");
      COLOR_OFF;
   }
   return 0;
}

char
VEIL_status          (void)
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
   int         x_count     = 0;
   /*---(defense)------------------------*/
   if (my.show_status != 'y'   )   return 0;
   if (s_count        == x_save)   return 0;
   /*---(prepare)------------------------*/
   x_tall    = FONT_tall ("basic");
   x_wide    = FONT_wide ("basic");
   x_left    = s_lefplus;
   x_right   = s_rigminus;
   x_dist    = x_right - x_left;
   x_max     = (x_right - x_left) / x_wide;
   x_left    = x_left + (x_dist - (x_max * x_wide)) / 2;
   /*---(display)------------------------*/
   x_count = s_count % x_max;
   for (x_col = 0; x_col < x_max; ++x_col) {
      x_letter = rand () % 25 + 'b';
      if (my.show_hint == 'y' && x_col == x_count) {
         COLOR_WHITE;
         x_letter = s_status;
      } else {
         COLOR_YELLOW;
      }
      FONT_letter ( "basic", x_letter,  0,  x_left + (x_col * x_wide));
      COLOR_OFF;
   }
   x_save = s_count;
   /*---(show counters)------------------*/
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = s_top + x_tall + 1;
      mvprintw (x_row++, s_lefplus + 5,  ".-----status----.");
      sprintf (x_text, "| s_count = %3d |", s_count);
      mvprintw (x_row++, s_lefplus + 5,  "%s", x_text);
      sprintf (x_text, "| s_status=  %c  |", s_status);
      mvprintw (x_row++, s_lefplus + 5,  "%s", x_text);
      sprintf (x_text, "| s_cpart =  %c  |", s_cpart );
      mvprintw (x_row++, s_lefplus + 5,  "%s", x_text);
      mvprintw (x_row++, s_lefplus + 5,  "'---------------'");
      COLOR_OFF;
   }
   SHOW_COUNTERS {
      COLOR_WHITE;
      x_row = 7;
      mvprintw (++x_row, s_cen - 17,  ".--------------------------------.");
      mvprintw (++x_row, s_cen - 17,  "| %-30.30s |", my.entry_text);
      mvprintw (++x_row, s_cen - 17,  "|          %-12.12s          |", my.magic_num);
      mvprintw (++x_row, s_cen - 17,  ".--------------------------------.");
      COLOR_OFF;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /*-> get character from ncurses ---------[ leaf-- [ ------ ]-*/
VEIL_getchar         (void)
{  /*---(design notes)-------------------*/
   /*  -- updates loop, seconds, and character counter
    *  -- integrates basic delay, timeout, and calls timer display
    *  -- gathers a character and evaluates basic response
    *  -- updates full input string for later use
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_ch        =    0;
   char        t           [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(get character)---------------*/
   while (1) {
      /*---(timers)----------------------*/
      ++s_loop;
      DEBUG_USER   yLOG_value   ("s_loop"    , s_loop);
      if (my.use_timer == 'y' && s_loop % 5 == 0) ++s_secs;
      DEBUG_USER   yLOG_value   ("s_secs"    , s_secs);
      /*---(timeout)---------------------*/
      if (s_secs > 120) {
         DEBUG_USER   yLOG_note    ("s_secs timed out");
         s_status = STATUS_TIMEOUT;
         break;
      }
      /*---(always wait)-----------------*/
      if (my.run_mode != RUN_UNIT) {
         DEBUG_USER   yLOG_note    ("insert a input delay, hacker proofing");
         usleep ( 100000);
      }
      /*---(get character)---------------*/
      x_ch = getch ();
      s_ch = x_ch;
      DEBUG_USER   yLOG_value   ("x_ch"      , x_ch);
      /*---(show screen)-----------------*/
      VEIL_timer     ();
      refresh ();
      /*---(didn't get a character)------*/
      if (x_ch == ERR) {
         DEBUG_USER   yLOG_note    ("no input, try again");
         continue;
      }
      ++s_count;
      DEBUG_USER   yLOG_value   ("s_count"   , s_count);
      /*---(special keys)----------------*/
      if (x_ch    ==  27 )  { /* escape          */
         DEBUG_USER   yLOG_note    ("escape, break out");
         break;
      }
      if (x_ch    == '\n')  { /* enter           */
         DEBUG_USER   yLOG_note    ("return, mark failed and break out");
         s_status = STATUS_FAILED;
         break;
      }
      if (x_ch    ==   3 )  {  /* C-c quit         */
         DEBUG_USER   yLOG_note    ("<C-c>, mark break and break out");
         s_status = STATUS_BREAK;
         break;
      }
      if (x_ch    ==  18 )  {  /* C-r refresh      */
         DEBUG_USER   yLOG_note    ("<C-r>, mark refresh and break out");
         s_status = STATUS_REFRESH;
         break;
      }
      /*---(weird chars)-----------------*/
      if (x_ch    <  32  || x_ch > 126) {
         DEBUG_USER   yLOG_note    ("weird characters, mark failed and break out");
         s_status = STATUS_FAILED;
         break;
      }
      /*---(normal)----------------------*/
      break;
   }
   DEBUG_USER   yLOG_char    ("s_status"  , s_status);
   /*---(error checking)-----------------*/
   --rce;  if (s_status == STATUS_TIMEOUT) {
      DEBUG_USER   yLOG_note    ("found timeout, leave");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_status == STATUS_BREAK  ) {
      DEBUG_USER   yLOG_note    ("found break, leave");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_status == STATUS_REFRESH) {
      DEBUG_USER   yLOG_note    ("found refresh, leave");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (s_status == STATUS_FAILED ) {
      DEBUG_USER   yLOG_note    ("failed, leave");
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add text)-----------------------*/
   sprintf (t, "%c", x_ch);
   DEBUG_USER   yLOG_note    ("make hidden characters printable");
   switch (t [0]) {
   case 27 : t [0] = G_CHAR_ESCAPE;  break;
   case 32 : t [0] = G_CHAR_SPACE;   break;
   }
   strlcat (my.entry_text, t, LEN_DESC);
   DEBUG_USER   yLOG_info    ("text"      , my.entry_text);
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return x_ch;
}

char
VEIL_check_user      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   int         x_len       =    0;
   tPASSWD    *pw          = NULL;
   tSHADOW    *spw         = NULL;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   DEBUG_USER   yLOG_info    ("username"  , entry.username);
   /*---(defense)------------------------*/
   x_len = strlen (entry.username);
   DEBUG_USER   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 4) {
      DEBUG_USER   yLOG_note    ("length too short");
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 15) {
      DEBUG_USER   yLOG_note    ("length too long");
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(rotate)-------------------------*/
   strcpy (entry.user_fix, "            ");
   for (i = 0; i < x_len; ++i) {
      j = i + (entry.rot[0] - '0');
      if (j <  x_len) {
         entry.user_fix [ j] = entry.username [i];
      } else {
         entry.user_fix [ j - x_len] = entry.username [i];
      }
   }
   entry.user_fix [x_len] = '\0';
   DEBUG_USER   yLOG_info    ("user_fix"  , entry.user_fix);
   /*---(check for root)-----------------*/
   --rce;  if (strcmp (entry.user_fix, "root") == 0) {
      DEBUG_USER   yLOG_note    ("can not log directly into root");
      strcpy (entry.user_fix, "(root)");
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (strcmp (entry.user_fix, "kurios") == 0) {
      DEBUG_USER   yLOG_note    ("kurios is the alias of root");
      strcpy (entry.user_fix, "root");
   }
   DEBUG_USER   yLOG_info    ("user_fix"  , entry.user_fix);
   /*---(check)--------------------------*/
   pw  = getpwnam (entry.user_fix);
   DEBUG_USER   yLOG_point   ("pw"        , pw);
   --rce;  if (pw == NULL) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   spw = getspnam (entry.user_fix);
   DEBUG_USER   yLOG_point   ("spw"       , pw);
   --rce;  if (spw == NULL) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
VEIL_check_pass      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         j           =    0;
   int         x_len       =    0;
   tPASSWD    *pw          = NULL;
   tSHADOW    *spw         = NULL;
   char       *salt        = NULL;
   char       *password    = NULL;
   char       *encrypted   = NULL;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_info    ("password"  , entry.password);
   /*---(defense)------------------------*/
   x_len = strlen (entry.password);
   DEBUG_USER   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 4) {
      DEBUG_USER   yLOG_note    ("length too short");
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len > 15) {
      DEBUG_USER   yLOG_note    ("length too long");
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   pw  = getpwnam (entry.user_fix);
   DEBUG_USER   yLOG_point   ("pw"        , pw);
   --rce;  if (pw == NULL) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   spw = getspnam (entry.user_fix);
   DEBUG_USER   yLOG_point   ("spw"       , pw);
   --rce;  if (spw == NULL) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(password)-----------------------*/
   password  = strdup (spw->sp_pwdp);
   DEBUG_USER   yLOG_info    ("password"  , password);
   salt      = strdup (spw->sp_pwdp);
   DEBUG_USER   yLOG_info    ("salt"      , salt);
   encrypted = crypt (entry.password, salt);
   DEBUG_USER   yLOG_point   ("encrypted" , encrypted);
   --rce;  if (strcmp (encrypted, password) != 0) {
      free (password);
      free (salt);
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   free (password);
   free (salt);
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
VEIL_check           (char a_count, char a_ch)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_part      =    0;
   int         x_pos       =    0;
   int         x_cnt       =    0;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_value   ("a_count"   , a_count);
   DEBUG_USER   yLOG_value   ("a_ch"      , a_ch);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("s_status"  , s_status);
   --rce;  if (s_status != STATUS_GOOD) {
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check part)---------------------*/
   DEBUG_USER   yLOG_char    ("s_cpart"   , s_cpart);
   for (i = 0; i < MAX_PART; ++i) {
      if (s_parts [i].part != s_cpart)  continue;
      x_part = i;
      break;
   }
   DEBUG_USER   yLOG_value   ("x_part"    , x_part);
   --rce;  if (x_part < 0) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check position)-----------------*/
   DEBUG_USER   yLOG_value   ("beg"       , s_parts [x_part].beg);
   --rce;  if (a_count < s_parts [x_part].beg) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_USER   yLOG_value   ("end"       , s_parts [x_part].end);
   --rce;  if (a_count > s_parts [x_part].end) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check validity)-----------------*/
   DEBUG_USER   yLOG_info    ("valid"     , s_parts [x_part].valid);
   --rce;  if (strchr (s_parts [x_part].valid, a_ch) == NULL) {
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_pos = a_count - s_parts [x_part].beg;
   DEBUG_USER   yLOG_value   ("x_pos"     , x_pos);
   DEBUG_USER   yLOG_char    ("sign"      , s_parts [x_part].sign);
   /*---(check bad part)-----------------*/
   --rce;  if (s_parts [x_part].sign == '-') {
      DEBUG_USER   yLOG_note    ("bad sign");
      s_status = STATUS_FAILED;
      DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check instant)------------------*/
   --rce;  if (s_parts [x_part].sign == '#') {
      DEBUG_USER   yLOG_note    ("check instant");
      if (a_ch != s_parts [x_part].check[x_pos]) {
         s_status = STATUS_FAILED;
         DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_USER   yLOG_note    ("character accepted");
      if (a_count == s_parts [x_part].end) {
         DEBUG_USER   yLOG_note    ("end of field, update part");
         if (s_cpart == PART_DONE) {
            DEBUG_USER   yLOG_note    ("completed 'done' part");
            s_status = STATUS_SUCCESS;
            DEBUG_USER   yLOG_char    ("s_status"  , s_status);
            DEBUG_USER   yLOG_exit    (__FUNCTION__);
            return 0;
         }
         s_cpart  = s_parts [x_part].next;
         DEBUG_USER   yLOG_char    ("s_cpart"   , s_cpart);
         ++x_part;
         DEBUG_USER   yLOG_value   ("x_part"    , x_part);
         DEBUG_USER   yLOG_char    ("part"      , s_parts [x_part].part);
         if (s_parts [x_part].sign == ' ')   s_parts [x_part].cnt = 99;
         x_cnt = s_parts [x_part].cnt;
         DEBUG_USER   yLOG_value   ("x_cnt"     , x_cnt);
         s_parts [x_part].beg = a_count + 1;
         s_parts [x_part].end = s_parts [x_part].beg + x_cnt - 1;
         if (s_parts [x_part].end > 99)  s_parts [x_part].end = 99;
         DEBUG_USER   yLOG_value   ("beg"       , s_parts [x_part].beg);
         DEBUG_USER   yLOG_value   ("cnt"       , s_parts [x_part].cnt);
         DEBUG_USER   yLOG_value   ("end"       , s_parts [x_part].end);
         DEBUG_USER   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(check saved)--------------------*/
   --rce;  if (s_parts [x_part].sign == ' ') {
      DEBUG_USER   yLOG_note    ("check saved");
      if (x_pos > 15) {
         DEBUG_USER   yLOG_note    ("x_pos too big");
         s_status = STATUS_FAILED;
         DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (s_cpart == PART_USERNAME) {
         DEBUG_USER   yLOG_note    ("checking username");
         if (a_ch == ' ') {
            DEBUG_USER   yLOG_note    ("found the trailing space");
            rc = VEIL_check_user ();
            DEBUG_USER   yLOG_value   ("rc"        , rc);
            if (rc < 0) {
               s_status = STATUS_FAILED;
               DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
            }
         } else {
            DEBUG_USER   yLOG_note    ("append character");
            entry.username [x_pos    ] = a_ch;
            entry.username [x_pos + 1] = '\0';
            DEBUG_USER   yLOG_info    ("username"  , entry.username);
            DEBUG_USER   yLOG_exit    (__FUNCTION__);
            return 0;
         }
      }
      if (s_cpart == PART_PASSWORD) {
         DEBUG_USER   yLOG_note    ("checking password");
         if (a_ch == ' ') {
            DEBUG_USER   yLOG_note    ("found the trailing space");
            rc = VEIL_check_pass ();
            DEBUG_USER   yLOG_value   ("rc"        , rc);
            if (rc < 0) {
               s_status = STATUS_FAILED;
               DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
               return rce;
            }
         } else {
            DEBUG_USER   yLOG_note    ("append character");
            entry.password [x_pos    ] = a_ch;
            entry.password [x_pos + 1] = '\0';
            DEBUG_USER   yLOG_info    ("password"  , entry.password);
            DEBUG_USER   yLOG_exitr   (__FUNCTION__, rce);
            return 0;
         }
      }
      if (a_ch == ' ') {
         DEBUG_USER   yLOG_note    ("handle moving to next part");
         s_parts [x_part    ].end = a_count;
         s_parts [x_part    ].cnt = s_parts [x_part + 1].end - s_parts [x_part + 1].beg + 1;
         s_parts [x_part + 1].beg = a_count + 1;
         s_parts [x_part + 1].end = s_parts [x_part + 1].beg + s_parts [x_part + 1].cnt - 1;
         if (s_parts [x_part + 1].end > 99)  s_parts [x_part + 1].end = 99;
         s_cpart  = s_parts [x_part].next;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
VEIL_getcheck        (cchar *a_input)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_ch        =  -10;
   int         x_len       =    0;
   int         i           =    0;
   --rce;  if (a_input == NULL)  return rce;
   x_len = strlen (a_input);
   for (i = 0; i < x_len; ++i) {
      x_ch = VEIL_getchar ();
      VEIL_check   (s_count, x_ch);
   }
   return 0;
}

char
get_login          (void)
{
   /*---(design notes)-------------------*/
   /*
    *
    */
   /*---(begin)--------------------------*/
   yLOG_enter  (__FUNCTION__);
   /*---(locals)-----------+-----------+-*/
   char        x_ch        = ' ';
   int         len;
   int         clen;
   int         off         = 0;
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
      /*---(update screen)---------------*/
      rc   = VEIL_status    ();
      x_ch = VEIL_getchar   ();
      rc   = VEIL_prompt    ();
      refresh ();
      /*---(check parts)-----------------*/
      rc   = VEIL_check     (s_count, x_ch);
      /*---(check major changes)---------*/
      if (s_status == STATUS_SUCCESS)  break;
      if (s_status == STATUS_TIMEOUT)  break;
      if (s_status == STATUS_REFRESH)  break;
      if (s_status == STATUS_BREAK)    break;
      /*---(done)------------------------*/
   }
   /*---(failed due to timeout)----------*/
   if (s_cpart == STATUS_TIMEOUT) {
      /* translation > fuck you window licker ;)  */
      strcpy (msg, "irrumabo vos fenestram lingent");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("timed out, login failed");
      audit_fail (dev, s_cpart);
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -1;
   }
   /*---(refresh request)----------------*/
   if (s_cpart == STATUS_REFRESH) {
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
   if (s_cpart == STATUS_BREAK) {
      /* translation > i came into a place void of all light -- dante                       */
      strcpy (msg, "lo venne in loco d'ogne luce muto");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("login cancelled");
      audit_fail (dev, s_cpart);
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -2;
   }
   /*---(not success)--------------------*/
   if (s_status != STATUS_SUCCESS) {
      strcpy (msg, "lasciate ogne speranza, voi ch'intrate");
      len = strlen (msg);
      if (my.show_judgement == 'y') {
         mvprintw ( s_bot ,  s_cen - (len / 2), msg);
         refresh ();
      }
      yLOG_note   ("login failed");
      audit_fail (dev, s_cpart);
      rc = ySEC_failed (dev + 5, entry.user_fix);
      yLOG_value  ("rc"        , rc);
      yLOG_exit   (__FUNCTION__);
      sleep (5);
      return -1;
   }
   /*---(success)------------------------*/
   pw  = getpwnam (entry.user_fix);
   spw = getspnam (entry.user_fix);
   chown (dev, pw->pw_uid, 0);
   chmod (dev, 0700);
   /*---(save key information)-----------*/
   strcpy (my.user_name, entry.user_fix);
   strcpy (shell, pw->pw_shell);
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



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /* [------] unit test accessor ------------------------------*/
VEIL__unit           (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_part      =   -1;
   int         i           =    0;
   /*---(prepare)------------------------*/
   strcpy  (unit_answer, "VEIL unit        : question not understood");
   /*---(check part)---------------------*/
   for (i = 0; i < MAX_PART; ++i) {
      if (s_parts [i].part != s_cpart)  continue;
      x_part = i;
      break;
   }
   /*---(current)------------------------*/
   if      (strcmp (a_question, "status"        ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VEIL status      : status = %c, part = %c, count = %3d, char = %3d", s_status, s_cpart, s_count, s_ch);
   }
   else if (strcmp (a_question, "range"         ) == 0) {
      if (x_part < 0)  snprintf (unit_answer, LEN_UNIT, "VEIL range       : part = %c, beg = %02d, cnt = %02d, end = %02d", s_cpart, -1, -1, -1);
      else             snprintf (unit_answer, LEN_UNIT, "VEIL range       : part = %c, beg = %02d, cnt = %02d, end = %02d", s_cpart, s_parts [x_part].beg, s_parts [x_part].cnt, s_parts [x_part].end);
   }
   else if (strcmp (a_question, "knock"         ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VEIL knock       : 1 = %c , 2 = %c , 3 = %c , 4 = %c", entry.knock [0], entry.knock [1], entry.knock [2], entry.knock [3]);
   }
   else if (strcmp (a_question, "prefix"        ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VEIL prefix      : 1 = %c , 2 = %c"                  , entry.prefix [0], entry.prefix [1]);
   }
   else if (strcmp (a_question, "user"          ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VEIL user        : %02d:%-20.20s, %02d:%s"           , strlen (entry.username), entry.username, strlen (entry.user_fix), entry.user_fix);
   }
   else if (strcmp (a_question, "infix"         ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VEIL infix       : 1 = %c"                           , entry.infix [0]);
   }
   else if (strcmp (a_question, "pass"          ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VEIL pass        : %02d:%s"                          , strlen (entry.password), entry.password);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

char
VEIL__unit_set       (int a_count, int a_char)
{
   s_count = a_count;
   s_ch    = a_char;
   return 0;
}




