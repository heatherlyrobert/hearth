/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



char             /* [------] create one-time login numbers -------------------*/
magic              (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;        /* loop iterator                       */
   /*---(prefix)-------------------------*/
   entry.prefix [0] = my.magicnum [ 0] =  '0' + rand () % 10;
   entry.prefix [1] = my.magicnum [ 1] =  '0' + rand () % 10;
   entry.prefix [2] = '\0';
   /*---(infix)--------------------------*/
   entry.infix  [0] = my.magicnum [ 2] =  '0' + rand () % 10;
   entry.infix  [1] = '\0';
   /*---(knock)--------------------------*/
   for (i = 0; i < 4; ++i) {
      entry.knock [i] = my.magicnum [ 3 + i] =  (rand () % 2 == 0) ? ' ' : '.';
   }
   entry.knock [4] = '\0';
   /*---(special)------------------------*/
   entry.rot     [0] = my.magicnum [ 7] = '0' + rand () % 3 + 1;
   entry.pointer [0] = my.magicnum [ 8] = '0' + rand () % 10;
   entry.rot     [1] = entry.pointer [1] = '\0';
   /*---(suffix)-------------------------*/
   entry.suffix [0] = my.magicnum [ 9] = '0' + rand () % 10;
   entry.suffix [1] = my.magicnum [10] = '0' + rand () % 10;
   entry.suffix [2] = my.magicnum [11] = '0' + rand () % 10;
   entry.suffix [3] = '\0';
   /*---(wrap-up)------------------------*/
   my.magicnum[12] = '\0';
   /*---(complete)-----------------------*/
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
show_left          (int a_x, int a_y)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columns          */
   char        x_done      = 'n';             /* flag -- already handled      */
   int         count_a;                       /* count of aligator rows       */
   int         mid_a;                         /* middle of aligator rows      */
   /*---(defense)------------------------*/
   yLOG_char   ("my.show_left"    , my.show_left       );
   if (my.show_left      != 'y')  return 0;
   /*---(calculate locations)---------*/
   count_a = trunc (a_y / 7) - 1;
   mid_a   = count_a / 2;
   /*---(show table of numbers)-------*/
   for (i = 0; i <  15; ++i) {
      for (j =  0; j <  2; ++j) {
         /*---(reset)-----------------*/
         x_done = 'n';
         /*---(check for hinting)-----*/
         if (my.show_hint   == 'y') attron (COLOR_PAIR( 1));
         else                   attron (COLOR_PAIR(12));
         if (i ==  count_a &&  j ==  1) {
            text_show_xy ( "alligator", entry.prefix [0] - '0', count_a * 7,  1 * 10);
            x_done = 'y';
         }
         if (i ==  0 &&  j ==  1) {
            text_show_xy ( "alligator", entry.prefix [1] - '0', 0       * 7,  1 * 10);
            x_done = 'y';
         }
         if (i ==  mid_a &&  j ==  0) {
            text_show_xy ( "alligator", entry.infix  [0] - '0', mid_a   * 7,  0 * 10);
            x_done = 'y';
         }
         if (my.show_hint   == 'y') attroff(COLOR_PAIR( 1));
         else                   attroff(COLOR_PAIR(12));
         if (x_done == 'y')  continue;
         /*---(normal)----------------*/
         attron (COLOR_PAIR(12));
         text_show_xy ( "alligator", rand () % 10, i * 7, j * 10);
         attroff(COLOR_PAIR(12));
         /*---(done)------------------*/
      }
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
   text_show_xy ( "dots"     , ttytyp  - '0', 10, center - 11);
   text_show_xy ( "alligator", ttynum  - '0', 10, center -  5);
   text_show_xy ( "dots"     , ttytyp  - '0', 14, center +  6);
   attroff(COLOR_PAIR(12));
   /*---(external indicator)-------------*/
   if (my.show_external == 'y')      x_type = 'e';
   else                              x_type = 'i';
   attron (COLOR_PAIR(12));
   mvprintw (19, center - 2,  "%c", x_type);
   mvprintw (19, center    ,  "%c", x_type);
   mvprintw (19, center + 2,  "%c", x_type);
   mvprintw (20, center - 1,  "%c", x_type);
   mvprintw (20, center + 1,  "%c", x_type);
   mvprintw (21, center    ,  "%c", x_type);
   /*> text_show_xy ( "basic"    , x_type, middle + 10, x_mid);                       <*/
   attroff(COLOR_PAIR(12));
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show knock dots ---------------------------------*/
show_knock         (int a_x, int a_y)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         knock_spacing;
   int         x_knock1;                  /* left of left knock               */
   int         x_knock2;                  /* left of right knock              */
   char        x_done      = 'n';             /* flag -- already handled      */
   /*---(defense)------------------------*/
   if (my.show_knock  != 'y')  return 0;
   /*---(prepare)------------------------*/
   knock_spacing = 4;
   if (middle <  20) knock_spacing = 3;
   x_knock1  = ((10 * 2) - 1);
   x_knock2  = (a_x - (8 * 3)) - 5;
   /*---(output)-------------------------*/
   for (i = 3; i < 10; ++i) {
      /*---(prepare)------------------*/
      x_done = 'n';
      /*---(hinting)------------------*/
      if (my.show_hint   == 'y') attron (COLOR_PAIR( 1));
      else                   attron (COLOR_PAIR(12));
      if (i ==  4) {
         text_show_xy ( "dots"     , entry.knock [0],  (middle - (6 * knock_spacing) - 1) + (4 * knock_spacing), x_knock1);
         text_show_xy ( "dots"     , entry.knock [1],  (middle - (6 * knock_spacing) - 1) + (4 * knock_spacing), x_knock2);
         x_done = 'y';
      }
      if (i ==  8) {
         text_show_xy ( "dots"     , entry.knock [2],  (middle - (6 * knock_spacing) - 1) + (8 * knock_spacing), x_knock2);
         text_show_xy ( "dots"     , entry.knock [3],  (middle - (6 * knock_spacing) - 1) + (8 * knock_spacing), x_knock1);
         x_done = 'y';
      }
      if (my.show_hint   == 'y') attroff(COLOR_PAIR( 1));
      else                   attroff(COLOR_PAIR(12));
      if (x_done == 'y')  continue;
      /*---(normal)-------------------*/
      attron (COLOR_PAIR(12));
      text_show_xy ( "dots"     , rand () % 2,  (middle - (6 * knock_spacing) - 1) + (i * knock_spacing), x_knock1);
      text_show_xy ( "dots"     , rand () % 2,  (middle - (6 * knock_spacing) - 1) + (i * knock_spacing), x_knock2);
      attroff(COLOR_PAIR(12));
      /*---(done)---------------------*/
   }
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show chunky numbers in middle -------------------*/
show_chunky        (int a_x, int a_y)
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
   /*---(prepare)------------------------*/
   x_knock1  = ((10 * 2) - 1);
   x_knock2  = (a_x - (8 * 3)) - 5;
   x_max = (x_knock2 - x_knock1 - 5) / 8;
   x_mid = center - ((x_max / 2.0) * 8) - 2;
   /*---(output)-------------------------*/
   for (i = 0; i <  1; ++i) {
      for (j = 0; j < x_max; ++j) {
         /*---(prepare)------------------*/
         x_done = 'n';
         /*---(hinting)------------------*/
         if (my.show_hint   == 'y' || my.show_hint   == 's') attron (COLOR_PAIR( 1));
         else                                        attron (COLOR_PAIR( 9));
         if (i ==  0 && j == 2) {
            text_show_xy ( "chunky", entry.rot     [0] - '0',  middle, x_mid + (8 * 2));
            x_done = 'y';
         }
         if (i ==  0 && j == x_max - 3) {
            text_show_xy ( "chunky", entry.pointer [0] - '0',  middle, x_mid + (x_max - 3) * 8);
            x_done = 'y';
         }
         if (my.show_hint   == 'y' || my.show_hint   == 's') attroff(COLOR_PAIR( 1));
         else                                        attroff(COLOR_PAIR( 9));
         if (x_done == 'y')  continue;
         /*---(normal)-------------------*/
         attron (COLOR_PAIR( 9));
         text_show_xy ( "chunky", rand () % 10, i * 4 + middle, x_mid + (j * 8));
         attroff(COLOR_PAIR( 9));
         /*---(done)---------------------*/
      }
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
   x_mid = center - ((x_max / 2.0) * 7) - 2;
   /*---(output)-------------------------*/
   for (i = 0; i <  1; ++i) {
      for (j = 0; j < x_max; ++j) {
         /*---(prepare)------------------*/
         x_done = 'n';
         /*---(normal)-------------------*/
         if (count % 2 == 0)  letter =  rand () % 26 + 'a';
         else                 letter =  rand () % 10 + '0';
         attron (COLOR_PAIR( 9));
         text_show_xy ( "chunky_full", letter, i * 5 + middle +  4, x_mid + (j * 7));
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
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 +  6);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 14);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 22);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 30);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 38);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 46);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 54);
         text_show_xy ("binary",  rand () % 10, (i * 2) + bottom - 9, (j * 2) + x_knock1 + 62);
      }
   }
   attroff(COLOR_PAIR(14));
   /*---(complete)-----------------------*/
   return 0;
}

char             /* [------] show right column of numbers --------------------*/
show_right         (int a_x, int a_y)
{
   /*---(design notes)-------------------*/
   /*
    *  these numbers must be printed in perfect order so a clever hacker
    *  can not analyze the order of the printing or overprinting for meaning.
    */
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;               /* iterator -- rows             */
   int         j           = 0;               /* iterator -- columns          */
   char        x_done      = 'n';             /* flag -- already handled      */
   int         x_right     = 0;
   /*---(defense)------------------------*/
   yLOG_char   ("my.show_right"   , my.show_right      );
   if (my.show_right     != 'y')  return 0;
   /*---(calculate locations)---------*/
   x_right   = (a_x - (8 * 3));
   /*---(output)----------------------*/
   for (i = 0; i <  15; ++i) {
      for (j = 0; j < 3; ++j) {
         /*---(prepare)---------------*/
         x_done = 'n';
         /*---(hinting)---------------*/
         if (my.show_hint   == 'y' || my.show_hint   == 's') attron (COLOR_PAIR( 1));
         else                                        attron (COLOR_PAIR(12));
         if (i ==  entry.pointer[0] - '0' + 1) {
            text_show_xy ( "goofy", entry.suffix [0] - '0',  (entry.pointer [0] - '0' + 1) * 5, x_right + (0 * 8));
            text_show_xy ( "goofy", entry.suffix [1] - '0',  (entry.pointer [0] - '0' + 1) * 5, x_right + (1 * 8));
            text_show_xy ( "goofy", entry.suffix [2] - '0',  (entry.pointer [0] - '0' + 1) * 5, x_right + (2 * 8));
            j = 10;
            x_done = 'y';
         }
         if (my.show_hint   == 'y' || my.show_hint   == 's') attroff(COLOR_PAIR( 1));
         else                                        attroff(COLOR_PAIR(12));
         if (x_done == 'y')  continue;
         /*---(normal)----------------*/
         attron (COLOR_PAIR(12));
         text_show_xy ( "goofy"    , rand () % 10, i * 5,  x_right + (j * 8));
         attroff(COLOR_PAIR(12));
         /*---(done)------------------*/
      }

   }
   /*---(complete)-----------------------*/
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
   bottom    = y - 1;
   center    = x / 2;
   middle    = y / 2;
   /*---(set positions)---------------*/
   x_left    = 0;
   x_right   = (x - (8 * 3));
   x_knock1  = (x_left + (10 * 2) - 1);
   left      = x_knock1;
   left2     = x_right - 1;
   x_knock2  = x_right - 5;
   left_c    = center - ((int) ((center - x_knock1) / 8) * 8);
   count_c   = ((int) ((center - x_knock1) / 8) * 2);
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
   show_left      (x, y);
   VEIL_tty       (x, y);
   show_knock     (x, y);
   show_chunky    (x, y);
   show_binary    (x, y);
   show_grid      (x, y);
   show_right     (x, y);
   /*---(signin)-------------------------*/
   ctitle = rand () % ntitle;
   if (my.show_login     == 'y') {
      attron (COLOR_PAIR(14));
      mvprintw ( bottom - 12, x_knock2 - 30,  "%-12.12s                   " , " ");
      mvprintw ( bottom - 11, x_knock2 - 30,  "%-12.12s [%-15d]"            , titles[ctitle].cluster, dev_num);
      mvprintw ( bottom - 10, x_knock2 - 30,  "%-12.12s [%c%c             ]", titles[ctitle].seq    , my.host_name[1], my.host_name[2]);
      mvprintw ( bottom -  9, x_knock2 - 30,  "%-12.12s [%-15.15s]"         , titles[ctitle].host   , my.host_name + 4);
      mvprintw ( bottom -  8, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].date);
      mvprintw ( bottom -  7, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].host);
      mvprintw ( bottom -  6, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].user);
      mvprintw ( bottom -  5, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].token);
      mvprintw ( bottom -  4, x_knock2 - 30,  "%-12.12s [               ] " , titles[ctitle].password);
      mvprintw ( bottom -  3, x_knock2 - 30,  "%-12.12s                   " , " ");
      attroff(COLOR_PAIR(14));
      attron (COLOR_PAIR(13));
      mvprintw ( bottom -  8, x_knock2 - 16,  "               ");
      attroff(COLOR_PAIR(13));
   }
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
            text_show_xy ( "dots"     , secs % 2,  bottom - 2, center - 18 + (secs -   0));
            attroff(COLOR_PAIR(11));
         } else if (secs <=  60) {
            attron (COLOR_PAIR(11));
            text_show_xy ( "dots"     , secs % 2,  bottom - 2, center + 14 - (secs -  30));
            attroff(COLOR_PAIR(11));
         } else if (secs <=  90) {
            attron (COLOR_PAIR(11));
            text_show_xy ( "dots"     , secs % 2,  bottom - 2, center - 18 + (secs -  60));
            attroff(COLOR_PAIR(11));
         } else if (secs <= 120) {
            attron (COLOR_PAIR(11));
            text_show_xy ( "dots"     , secs % 2,  bottom - 2, center + 14 - (secs -  90));
            attroff(COLOR_PAIR(11));
         }
      }
      /*---(status)----------------------*/
      if (count != count_save && my.show_status == 'y') {
         x_max = (left2 - left - 2) / 8;
         x_mid = center - ((x_max / 2.0) * 8) - 2;
         attron (COLOR_PAIR(12));
         for (i = 0; i < x_max; ++i) {
            text_show_xy ( "basic"    , rand() % 25 + 'b' ,   0,  x_mid + (i * 8));
         }
         attroff(COLOR_PAIR(12));
         if (my.show_hint   == 'y' || my.show_hint == 's') attron (COLOR_PAIR( 1));
         else                                      attron (COLOR_PAIR(12));
         i = x_mid + ((count % x_max) * 8);
         text_show_xy ( "basic"    , status ,   0,  i);
         if (my.show_hint   == 'y' || my.show_hint == 's') attroff(COLOR_PAIR( 1));
         else                                      attroff(COLOR_PAIR(12));
         /*> attron (COLOR_PAIR(12));                                                                   <* 
          *> text_show_xy ( "basic"    , toupper(part) ,   0 * 7,  (((count - 1) % 20) + 4) * 8 + 5);   <* 
          *> attroff(COLOR_PAIR(12));                                                                   <*/
         count_save = count;
      }
      /*> mvprintw (bottom - 4, center - 5, "%d", count);                             <* 
       *> mvprintw (bottom - 4, center + 5, "%d", finish);                            <*/
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
            mvprintw (bottom - 8, x_knock2 - 16 + count -  0, "*");
         }
         /*---(second line)--------------*/
         if (count >=  6 && count < 14) {
            if (count ==  6) {
               mvprintw (bottom - 7, x_knock2 - 16, "               ");
            }
            mvprintw (bottom - 7, x_knock2 - 16 + count -  6,  "*");
         }
         /*---(third line)---------------*/
         if (count >= 14 && count < 20) {
            if (count ==  14) {
               mvprintw (bottom - 6, x_knock2 - 16, "               ");
            }
            mvprintw (bottom - 6, x_knock2 - 16 + count - 14,  "*");
         }
         /*---(fourth line)--------------*/
         if (count >= 20 && count < 28) {
            if (count ==  20) {
               mvprintw (bottom - 5, x_knock2 - 16, "               ");
            }
            mvprintw (bottom - 5, x_knock2 - 16 + count - 20,  "*");
         }
         /*---(fifth line)---------------*/
         if (count >= 28 && count < 40) {
            if (count ==  28) {
               mvprintw (bottom - 4, x_knock2 - 16, "               ");
            }
            mvprintw (bottom - 4, x_knock2 - 16 + count - 28,  "*");
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
         mvprintw ( bottom,  center - (len / 2), msg);
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
   strcpy (user , entry.user_fix);
   strcpy (shell, pw->pw_shell);
   /*---(message)------------------------*/
   free (password);
   free (salt);
   free (encrypted);
   /* translation > here must all distrust be left behind -- dante                          */
   strcpy (msg, "qui si convien lasciare ogne sospettoo");
   len = strlen (msg);
   if (my.show_judgement == 'y') {
      mvprintw ( bottom,  center - (len / 2), msg);
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
