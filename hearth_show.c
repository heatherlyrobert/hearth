/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"

/* my.magic_num   [LLM....LRRR]
 *
 *   0  left-side  , 1st-row, right (2nd number)
 *   1  left-side  , 7th-row, right (2nd number)
 *   2  left-side  , 4th-row, left  (1st number)
 *   3  middle-area, top-row, 3rd from left
 *   4  middle-area, top-row, 3rd from left
 *
 *
 *
 */


tVALS       g_vals;


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/



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




char
show_message            (char *a_msg)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_senter  (__FUNCTION__);
   /*---(display)------------------------*/
   COLORS_RED;
   DEBUG_TOPS   yLOG_snote   (a_msg);
   x_len = strlen (a_msg);
   mvprintw (my.bot, my.cen - (x_len / 2), a_msg);
   refresh ();
   COLORS_OFF;
   /*---(clear color)--------------------*/
   DEBUG_TOPS   yLOG_snote   ("reset");
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
show_displayer   (int x, int y, char *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       =    0;
   int         i           =    0;
   char        c           =  '-';

   DEBUG_TOPS   yLOG_senter  (__FUNCTION__);
   DEBUG_TOPS   yLOG_snote   (a_text);
   x_len = strlen (a_text);
   for (i = 0; i < x_len; ++i) {
      c = a_text [i];
      if (c == ' ')  continue;
      if (my.dev [5] == 't')  switch (c) {
      case 'µ' : c = '\\';   break;
      case '´' : c = '+';    break;
      case '³' : c = '*';    break;
      case '·' : c = '-';    break;
      case '²' : c = '-';    break;
      }
      mvprintw (y, x + i,  "%c", c);
   }
   DEBUG_TOPS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char             /* [------] create one-time login numbers -------------------*/
show_sizing          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x           =    0;
   int         y           =    0;
   int         x_right     =    0;
   int         x_dist      =    0;
   int         x_tall      =    0;
   int         x_wide      =    0;
   int         x_wideK     =    0;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get dimensions)--------------*/
   getmaxyx (stdscr, y, x);
   my.top      = 0;
   my.mid      = y / 2;
   my.bot      = y - 1;
   my.lef      = 0;
   my.cen      = x / 2;
   my.rig      = x;
   DEBUG_GRAF   yLOG_value   ("top"       , my.top);
   DEBUG_GRAF   yLOG_value   ("mid"       , my.mid);
   DEBUG_GRAF   yLOG_value   ("bot"       , my.bot);
   DEBUG_GRAF   yLOG_value   ("lef"       , my.lef);
   DEBUG_GRAF   yLOG_value   ("cen"       , my.cen);
   DEBUG_GRAF   yLOG_value   ("rig"       , my.rig);
   /*---(fonts)--------------------------*/
   if (my.rig > 180) {
      g_vals.bfly_size = 'm';
      strlcpy (g_vals.lefs_font, "alligator"      , LEN_LABEL);
      strlcpy (g_vals.rigs_font, "goofy"          , LEN_LABEL);
      strlcpy (g_vals.tops_font, "basic"          , LEN_LABEL);
      strlcpy (g_vals.mids_font, "chunky_full"    , LEN_LABEL);
      strlcpy (g_vals.noks_font, "dots"           , LEN_LABEL);
      strlcpy (g_vals.timr_font, "dots_rnd"       , LEN_LABEL);
      g_vals.noks_gap = 2;
   } else if (my.rig > 100) {
      g_vals.bfly_size = 'm';
      strlcpy (g_vals.lefs_font, "chunky"         , LEN_LABEL);
      strlcpy (g_vals.rigs_font, "graceful"       , LEN_LABEL);
      strlcpy (g_vals.tops_font, "fuzzy"          , LEN_LABEL);
      strlcpy (g_vals.mids_font, "thick"          , LEN_LABEL);
      strlcpy (g_vals.noks_font, "dots_med"       , LEN_LABEL);
      strlcpy (g_vals.timr_font, "dots_rnd"       , LEN_LABEL);
      g_vals.noks_gap = 2;
   } else {
      g_vals.bfly_size = 's';
      strlcpy (g_vals.lefs_font, "tiny_dot"       , LEN_LABEL);
      strlcpy (g_vals.rigs_font, "amc3line"       , LEN_LABEL);
      strlcpy (g_vals.tops_font, "tiny_block"     , LEN_LABEL);
      strlcpy (g_vals.mids_font, "rob4dots2"      , LEN_LABEL);
      strlcpy (g_vals.noks_font, "dots_sml"       , LEN_LABEL);
      strlcpy (g_vals.timr_font, "dots_rnd"       , LEN_LABEL);
      g_vals.noks_gap = 1;
   }
   DEBUG_GRAF   yLOG_value   ("noks_gap"  , g_vals.noks_gap);
   /*---(left)---------------------------*/
   DEBUG_GRAF   yLOG_note    ("left spacing");
   g_vals.lefs_top  = 0;
   g_vals.lefs_lef  = 0;
   g_vals.noks_top  = 0;
   rc = ySTR_font (g_vals.lefs_font, &x_wide, NULL);
   DEBUG_GRAF   yLOG_value   ("x_wide"    , x_wide);
   rc = ySTR_font (g_vals.noks_font , &x_wideK, NULL);
   DEBUG_GRAF   yLOG_value   ("x_wideK"   , x_wideK);
   my.lefplus   = my.lef + (x_wide * 2) + x_wideK;
   DEBUG_GRAF   yLOG_value   ("s_lef+"    , my.lefplus);
   g_vals.noks_lef  = my.lef + (x_wide * 2);
   DEBUG_GRAF   yLOG_value   ("noks_lef"  , g_vals.noks_lef);
   /*---(right)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("right spacing");
   g_vals.rigs_top  = 0;
   rc = ySTR_font (g_vals.rigs_font, &x_wide, NULL);
   DEBUG_GRAF   yLOG_value   ("x_wide"    , x_wide);
   g_vals.rigs_lef = (my.rig - (x_wide * 3));
   DEBUG_GRAF   yLOG_value   ("rigs_lef"  , g_vals.rigs_lef);
   my.rigminus  = my.lef + (x_wide * 2) + x_wideK;
   my.rigminus  = my.rig - (x_wide * 3) - x_wideK;
   DEBUG_GRAF   yLOG_value   ("s_rig-"    , my.rigminus);
   g_vals.noks_rig  = my.rigminus;
   DEBUG_GRAF   yLOG_value   ("noks_rig"  , g_vals.noks_rig);
   /*---(middle)-------------------------*/
   DEBUG_GRAF   yLOG_note    ("middle spacing");
   rc = ySTR_font (g_vals.mids_font, &x_wide, &x_tall);
   DEBUG_GRAF   yLOG_value   ("x_wide"    , x_wide);
   DEBUG_GRAF   yLOG_value   ("x_tall"    , x_tall);
   g_vals.mids_lef  = my.lefplus;
   x_right     = my.rigminus;
   x_dist      = x_right - g_vals.mids_lef;
   g_vals.mids_len  = (x_right - g_vals.mids_lef) / x_wide;
   g_vals.mids_len -= (g_vals.mids_len % 2);   /* make it even */
   g_vals.mids_lef  = g_vals.mids_lef + (x_dist - (g_vals.mids_len * x_wide)) / 2;
   g_vals.mids_top  = my.mid - x_tall;
   g_vals.mids_bot  = g_vals.mids_top + x_tall;
   DEBUG_GRAF   yLOG_value   ("mids_top"  , g_vals.mids_top);
   DEBUG_GRAF   yLOG_value   ("mids_bot"  , g_vals.mids_bot);
   DEBUG_GRAF   yLOG_value   ("mids_lef"  , g_vals.mids_lef);
   DEBUG_GRAF   yLOG_value   ("mids_len"  , g_vals.mids_len);
   /*---(top spacing)--------------------*/
   DEBUG_GRAF   yLOG_note    ("top spacing");
   g_vals.tops_top  = 0;
   rc = ySTR_font (g_vals.tops_font, &x_wide, &x_tall);
   g_vals.tops_lef  = my.lefplus;
   x_right     = my.rigminus;
   x_dist      = x_right - g_vals.tops_lef;
   g_vals.tops_len  = (x_right - g_vals.tops_lef) / x_wide;
   g_vals.tops_lef  = g_vals.tops_lef + (x_dist - (g_vals.tops_len * x_wide)) / 2;
   DEBUG_GRAF   yLOG_value   ("x_tall"    , x_tall);
   my.topplus  = my.top + x_tall + 4;
   DEBUG_GRAF   yLOG_value   ("top+"      , my.topplus);
   /*---(prompt)-------------------------*/
   DEBUG_GRAF   yLOG_note    ("prompt spacing");

   g_vals.prom_lef  = my.rigminus - 35;
   g_vals.prom_top  = my.bot - 10;
   DEBUG_GRAF   yLOG_value   ("prom_lef"  , g_vals.prom_lef);
   /*---(timer)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("timer spacing");
   g_vals.timr_cen  = my.lefplus + 10;
   g_vals.timr_mid  = my.bot - 7;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] create one-time login numbers -------------------*/
show_init            (void)
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;        /* loop iterator                       */
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(initialize)------------------*/
   /*---(config)----------------------*/
   DEBUG_TOPS   yLOG_note    ("dislayer");
   ySTR_displayer (show_displayer);
   show_sizing    ();
   /*> g_vals.bfly_indx = rand () % CNT_BFLY;                                         <*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

static int         s_col       [LEN_TITLE];
static int         s_row       [LEN_TITLE];

char             /* [------] show butterfly background -----------------------*/
show_butterfly         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         b           = 0;               /* butterfly index              */
   int         x_row       = 0;               /* iterator -- rows             */
   int         x_col       = 0;               /* iterator -- columns          */
   char        x_text      [LEN_DESC] = "";
   int         x_ncol      =   20;
   int         x_nrow      =   20;
   int         x_left      =    0;
   int         x_top       =    0;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(output)-------------------------*/
   x_top = my.topplus;
   switch (g_vals.bfly_size) {
   case 'L' :  x_ncol = 180; x_nrow =  65;               break;
   case 'm' :  x_ncol = 100; x_nrow =  45;               break;
   case 's' :  x_ncol =  60; x_nrow =  30;  x_top -= 5;  break;
   }
   DEBUG_LOOP   yLOG_value  ("butterfly"   , g_vals.bfly_indx       );
   /*> x_left  = (my.rig - x_ncol) / 2;                                               <*/
   x_left  = my.cen - x_ncol / 2;
   x_top   = my.mid - x_nrow / 2;
   DEBUG_LOOP   yLOG_value  ("x_left"    , x_left       );
   COLORS_GREEN;
   for (x_row =  0; x_row <  x_nrow; ++x_row) {
      for (x_col =  0; x_col <  x_ncol; ++x_col) {
         switch (g_vals.bfly_size) {
         case 'L' :
            mvprintw (x_top + x_row, x_col + x_left,  "%c", g_bfly_lrg [g_vals.bfly_indx][x_row][x_col]);
            break;
         case 'm' :
            mvprintw (x_top + x_row, x_col + x_left,  "%c", g_bfly_med [g_vals.bfly_indx][x_row][x_col]);
            break;
         case 's' :
            mvprintw (x_top + x_row, x_col + x_left,  "%c", g_bfly_sml [g_vals.bfly_indx][x_row][x_col]);
            break;
         }
      }
   }
   COLORS_OFF;
   for (x_col = 0; x_col < LEN_TITLE; ++x_col)    s_col [x_col] = rand () % 160 + 10;
   for (x_row = 0; x_row < LEN_TITLE; ++x_row)    s_row [x_row] = rand () % x_nrow;
   /*---(complete)-----------------------*/
   return 0;
}

char
show_rain    (void)
{
   int         i, x, y;
   int         x_left, x_top;
   int         x_ncol, x_nrow;
   char        v           [LEN_DESC] = "";
   if (my.dev [5] == 't')  strlcpy (v, "abcdefghijklmnopqrstuvw", LEN_DESC);
   else                    strlcpy (v, "èéêëìíîïðñòóôõö÷øùúûüýþÿ", LEN_DESC);
   switch (g_vals.bfly_size) {
   case 'L' :  x_ncol = 180; x_nrow =  65;               break;
   case 'm' :  x_ncol = 100; x_nrow =  45;               break;
   case 's' :  x_ncol =  60; x_nrow =  30;  x_top -= 5;  break;
   }
   x_left  = my.cen - x_ncol / 2;
   x_top   = my.mid - x_nrow / 2;
   for (i = 0; i < LEN_TITLE; ++i) {
      x = s_col [i];
      y = s_row [i] - 3;
      if (y < 0) y = 0;
      if (g_bfly_lrg [g_vals.bfly_indx][y][x] != ' ') {
         COLORS_GREEN;
         mvprintw (x_top + y, x_left + x,  "%c", g_bfly_lrg [g_vals.bfly_indx][y][x]);
         COLORS_OFF;
      }
      ++s_row [i];
      if (s_row [i] >= x_nrow) {
         COLORS_GREEN;
         for (y = 0; y < x_nrow; ++y) {
            if (g_bfly_lrg [g_vals.bfly_indx][y][x] != ' ') {
               mvprintw (x_top + y, x_left + x,  "%c", g_bfly_lrg [g_vals.bfly_indx][y][x]);
            }
         }
         COLORS_OFF;
         s_col [i] = rand () % 160 + 10;
         s_row [i] = 0;
      }
      x = s_col [i];
      y = s_row [i];
      if (g_bfly_lrg [g_vals.bfly_indx][y][x] != ' ') {
         COLORS_YELLOW;
         mvprintw (x_top + y, x_left + x,  "%c", v [rand () % 24]);
         COLORS_OFF;
      }
   }
   return 0;
}

char
show_left              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_HUND];
   char        v           [LEN_HUND];
   int         h, w;
   int         a, b;
   /*---(leftmost)-----------------------*/
   strlcpy (v, "abcdefghijklmnopqrstuvwxyz0123456789", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      t [i] = v [rand () % 36];
   for (i = 1; i < LEN_HUND; i += 2)   t [i] = '¦';
   t  [LEN_HUND - 1] = '\0';
   COLORS_YELLOW;
   ySTR_display ("tiny_dot" , t, YSTR_GAPS, 0, 0, NULL, NULL);
   COLORS_OFF;
   /*---(center left)--------------------*/
   strlcpy (v, "1234567890", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      t [i] = v [rand () % 10];
   for (i = 2; i < LEN_HUND; i += 3)   t [i] = '¦';
   t  [LEN_HUND - 1] = '\0';
   t [ 0] = my.magic_num [ 6];
   t [27] = my.magic_num [18];
   t [13] = my.magic_num [13];
   COLORS_YELLOW;
   ySTR_display ("alligator", t, YSTR_GAPS, 4, 0, NULL, NULL);
   COLORS_OFF;
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      ySTR_font ("alligator", &w, &h);
      COLORS_RED;
      sprintf (t, "%c", my.magic_num [ 6]);
      ySTR_display ("alligator", t, YSTR_GAPS, 4    , 0    , NULL, NULL);
      sprintf (t, "%c", my.magic_num [18]);
      ySTR_display ("alligator", t, YSTR_GAPS, 4    , 9 * h, NULL, NULL);
      sprintf (t, "%c", my.magic_num [13]);
      ySTR_display ("alligator", t, YSTR_GAPS, 4 + w, 4 * h, NULL, NULL);
      COLORS_OFF;
   }
   /*---(knocks)-------------------------*/
   strlcpy (v, "01", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      t [i] = v [rand () %  2];
   switch (g_vals.noks_gap) {
   case 0 :
      for (i = 1; i < LEN_HUND; i += 2)  t [i] = '¦';
      a =  2;
      b =  6;
      break;
   case 1 :
      for (i = 1; i < LEN_HUND; i += 4)  t [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 4)  t [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 4)  t [i] = '¦';
      a =  4;
      b = 12;
      break;
   case 2 :
      for (i = 1; i < LEN_HUND; i += 6)  t [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 6)  t [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 6)  t [i] = '¦';
      for (i = 4; i < LEN_HUND; i += 6)  t [i] = ' ';
      for (i = 5; i < LEN_HUND; i += 6)  t [i] = '¦';
      a =  6;
      b = 30;
      break;
   }
   t [LEN_HUND - 1] = '\0';
   t [ a] = (my.magic_num [ 1] == '+') ? '1' : '0';
   t [ b] = (my.magic_num [ 4] == '+') ? '1' : '0';
   COLORS_YELLOW;
   ySTR_display ("dots", t, YSTR_GAPS, 25, 0, NULL, NULL);
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      ySTR_font ("dots"     , &w, &h);
      COLORS_RED;
      sprintf (t, "%c", (my.magic_num [ 1] == '+') ? '1' : '0');
      ySTR_display ("dots"     , t, YSTR_GAPS, 25   , 3  * h, NULL, NULL);
      sprintf (t, "%c", (my.magic_num [ 4] == '+') ? '1' : '0');
      ySTR_display ("dots"     , t, YSTR_GAPS, 25   , 15 * h, NULL, NULL);
      COLORS_OFF;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
show_right             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        t           [LEN_HUND];
   char        v           [LEN_HUND];
   int         h, w;
   int         h2, w2;
   int         x_off       =    0;
   int         n           =    0;
   int         a, b;
   /*---(prepare)------------------------*/
   ySTR_font ("goofy"    , &w, &h);
   if      (strchr ("XYZ" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'X';
   else if (strchr ("xyz" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'x';
   else if (strchr ("XYZ" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'X';
   else if (strchr ("xyz" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'x';
   else if (strchr ("XYZ" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'X';
   else if (strchr ("xyz" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'x';
   n = 25 + (x_off * 4);
   /*---(rightmost)----------------------*/
   strlcpy (v, "1234567890", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      t [i] = v [rand () % 10];
   for (i = 3; i < LEN_HUND; i += 4)   t [i] = '¦';
   t  [LEN_HUND - 1] = '\0';
   t [x_off * 4 + 0] = my.magic_num [n + 0];
   t [x_off * 4 + 1] = my.magic_num [n + 1];
   t [x_off * 4 + 2] = my.magic_num [n + 2];
   COLORS_YELLOW;
   ySTR_display ("goofy"    , t, YSTR_GAPS, my.rig - w * 3, 0, NULL, NULL);
   COLORS_OFF;
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (t, "%c%c%c", my.magic_num [n + 0], my.magic_num [n + 1], my.magic_num [n + 2]);
      ySTR_display ("goofy"    , t, YSTR_GAPS, my.rig - w * 3, x_off * h, NULL, NULL);
      COLORS_OFF;
   }
   /*---(knocks)-------------------------*/
   strlcpy (v, "01", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      t [i] = v [rand () %  2];
   switch (g_vals.noks_gap) {
   case 0 :
      for (i = 1; i < LEN_HUND; i += 2)  t [i] = '¦';
      a =  2;
      b =  6;
      break;
   case 1 :
      for (i = 1; i < LEN_HUND; i += 4)  t [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 4)  t [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 4)  t [i] = '¦';
      a =  4;
      b = 12;
      break;
   case 2 :
      for (i = 1; i < LEN_HUND; i += 6)  t [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 6)  t [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 6)  t [i] = '¦';
      for (i = 4; i < LEN_HUND; i += 6)  t [i] = ' ';
      for (i = 5; i < LEN_HUND; i += 6)  t [i] = '¦';
      a =  6;
      b = 30;
      break;
   }
   t [LEN_HUND - 1] = '\0';
   t [ a] = (my.magic_num [40] == '+') ? '1' : '0';
   t [ b] = (my.magic_num [37] == '+') ? '1' : '0';
   COLORS_YELLOW;
   ySTR_font ("dots"     , &w2, &h2);
   ySTR_display ("dots", t, YSTR_GAPS, my.rig - 3 * w - w2, 0, NULL, NULL);
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (t, "%c", (my.magic_num [40] == '+') ? '1' : '0');
      ySTR_display ("dots"     , t, YSTR_GAPS, my.rig - 3 * w - w2, 3  * h2, NULL, NULL);
      sprintf (t, "%c", (my.magic_num [37] == '+') ? '1' : '0');
      ySTR_display ("dots"     , t, YSTR_GAPS, my.rig - 3 * w - w2, 15 * h2, NULL, NULL);
      COLORS_OFF;
   }
   return 0;
}

char
show_block             (void)
{
   int         i           =  0;
   char        t           [LEN_LABEL] = "";
   char        v           [LEN_HUND];
   int         x_off       =    0;
   char        x_rot       =  0;
   char        w, h;
   COLORS_OFF;
   ySTR_font ("chunky_full", &w, &h);
   if      (strchr ("ABCD" , my.magic_num [21]) != NULL)  x_rot = my.magic_num [21] - 'A';
   else if (strchr ("abcd" , my.magic_num [21]) != NULL)  x_rot = my.magic_num [21] - 'a';
   else if (strchr ("ABCD" , my.magic_num [22]) != NULL)  x_rot = my.magic_num [22] - 'A';
   else if (strchr ("abcd" , my.magic_num [22]) != NULL)  x_rot = my.magic_num [22] - 'a';
   else if (strchr ("ABCD" , my.magic_num [23]) != NULL)  x_rot = my.magic_num [23] - 'A';
   else if (strchr ("abcd" , my.magic_num [23]) != NULL)  x_rot = my.magic_num [23] - 'a';
   strlcpy (v, "abcdefghijklmnopqrstuvwxyz0123456789", LEN_HUND);
   for (i = 0; i < 15; ++i)   t [i] = v [rand () % 36];
   t [ 3] =t [ 7] = t [11] = '¦';
   t [ 5] =t [ 6] = t [ 9] = t [10] = ' ';
   t [15] = '\0';
   t [12] = x_rot + 'a';
   ySTR_display ("chunky_full" , t, YSTR_GAPS,  35, 50, NULL, NULL);
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (t, "%c", x_rot + 'a');
      ySTR_display ("chunky_full", t, YSTR_GAPS, 35, 50 + 3 * h, NULL, NULL);
      COLORS_OFF;
   }
   /*---(prepare)------------------------*/
   ySTR_font ("chunky_full", &w, &h);
   if      (strchr ("XYZ" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'X';
   else if (strchr ("xyz" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'x';
   else if (strchr ("XYZ" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'X';
   else if (strchr ("xyz" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'x';
   else if (strchr ("XYZ" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'X';
   else if (strchr ("xyz" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'x';
   strlcpy (v, "abcdefghijklmnopqrstuvwxyz0123456789", LEN_HUND);
   for (i = 0; i < 15; ++i)   t [i] = v [rand () % 36];
   t [ 3] =t [ 7] = t [11] = '¦';
   t [ 4] =t [ 5] = t [ 8] = t [ 9] = ' ';
   t [15] = '\0';
   t [14] = x_off + 'x';
   ySTR_display ("chunky_full" , t, YSTR_GAPS, 170, 50, NULL, NULL);
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (t, "%c", x_off + 'x');
      ySTR_display ("chunky_full", t, YSTR_GAPS, 170 + 2 * w, 50 + 3 * h, NULL, NULL);
      COLORS_OFF;
   }
   for (i = 0; i <  3; ++i)   t [i] = rand () % 26 + 'a';
   t [ 4] = '\0';
   ySTR_display ("horzright"   , t, YSTR_GAPS, my.cen - 9 * 3 - 2,  1, NULL, NULL);
   for (i = 0; i <  3; ++i)   t [i] = rand () % 26 + 'a';
   t [ 4] = '\0';
   ySTR_display ("horzleft"    , t, YSTR_GAPS, my.cen + 2        ,  1, NULL, NULL);
   if (my.show_hint == 'y') {
      COLORS_RED;
      mvprintw ( 0, my.cen - 21, "%s", my.magic_num);
      COLORS_OFF;
   }
   strlcpy (v, "0123456789abcdef", LEN_HUND);
   sprintf (t, "%c", v [g_vals.bfly_indx]);
   ySTR_display ("computer"    , t, YSTR_GAPS, my.cen - 4,  8, NULL, NULL);
   return 0;
}

char
show_random            (void)
{
   uchar       c           =    0;
   char        i           =    0;
   char        v           [LEN_HUND] = "";
   if (my.dev [5] == 't')  strlcpy (v, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwy--------------------------------------------------", LEN_HUND);
   else                    strlcpy (v, "abcdefghijklmnopqrstuvwxyzèéêëìíîïðñòóôõö÷øùúûüýþÿ··················································", LEN_HUND);
   COLORS_CYAN;
   c = v [rand () % 50];
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, "%c", c);
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   c = v [rand () % 50];
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, "%c", c);
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   COLORS_OFF;
   for (i = 0; i < 5; ++i) {
      mvprintw (6, my.cen - 25 + rand () % 50, "%c", v [rand () % 100]);
   }
   return 0;
}

char
show_ascii             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_DESC];
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(left)---------------------------*/
   COLORS_YELLOW;
   DEBUG_TOPS   yLOG_note    ("lefts");
   /*> ySTR_display (g_vals.lefs_font, g_vals.lefts , YSTR_GAPS, g_vals.lefs_lef, g_vals.lefs_top, NULL, NULL);   <*/
   ySTR_display (g_vals.lefs_font, g_vals.lefts , YSTR_GAPS, 5              , g_vals.lefs_top, NULL, NULL);
   COLORS_OFF;
   /*---(right)--------------------------*/
   COLORS_YELLOW;
   DEBUG_TOPS   yLOG_note    ("rights");
   ySTR_display (g_vals.rigs_font, g_vals.rights, YSTR_GAPS, g_vals.rigs_lef, g_vals.rigs_top, NULL, NULL);
   COLORS_OFF;
   /*---(middle)-------------------------*/
   COLORS_MAGENTA;
   DEBUG_TOPS   yLOG_note    ("mid top");
   strncpy (t, g_vals.mids, g_vals.mids_len);
   DEBUG_TOPS   yLOG_info    ("t"         , t);
   ySTR_display (g_vals.mids_font, t, YSTR_GAPS, g_vals.mids_lef, g_vals.mids_top, NULL, NULL);
   DEBUG_TOPS   yLOG_note    ("mid bot");
   strncpy (t, g_vals.mids + (MAX_MIDS / 2), g_vals.mids_len);
   DEBUG_TOPS   yLOG_info    ("t"         , t);
   ySTR_display (g_vals.mids_font, t, YSTR_GAPS, g_vals.mids_lef, g_vals.mids_bot, NULL, NULL);
   COLORS_OFF;
   /*---(knock)--------------------------*/
   COLORS_YELLOW;
   DEBUG_TOPS   yLOG_note    ("knock left");
   strncpy (t, g_vals.knocks, MAX_KNOCKS / 2 - 1);
   DEBUG_TOPS   yLOG_info    ("t"         , t);
   /*> ySTR_display (g_vals.noks_font, t, YSTR_GAPS, g_vals.noks_lef, g_vals.noks_top, NULL, NULL);   <*/
   DEBUG_TOPS   yLOG_note    ("knock right");
   strcpy  (t, g_vals.knocks + (MAX_KNOCKS / 2));
   DEBUG_TOPS   yLOG_info    ("t"         , t);
   ySTR_display (g_vals.noks_font, t, YSTR_GAPS, g_vals.noks_rig, g_vals.noks_top, NULL, NULL);
   COLORS_OFF;
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
show_status             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_DESC];
   int         i           = 0;
   int         x_count     = 0;
   char        x_valid     [LEN_DESC] = "cdeghijklmnopqtuvwxy";
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(status)-------------------------*/
   DEBUG_TOPS   yLOG_note    ("top");
   for (i = 0; i < g_vals.tops_len; ++i)    t [i] = x_valid [rand () % 20];
   t [i] = '\0';
   x_count = my.chars % g_vals.tops_len;
   t [x_count] = my.status;
   DEBUG_TOPS   yLOG_info    ("t"         , t);
   COLORS_YELLOW;
   ySTR_display (g_vals.tops_font, t, YSTR_GAPS, g_vals.tops_lef, g_vals.tops_top, NULL, NULL);
   COLORS_OFF;
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
show_prompt             (void)
{
   char        x_text      [LEN_DESC] = "";
   int         x_left      = 0;
   int         x_right     = 0;
   int         x_row       = 0;
   int         x_col       = 0;
   int         x_gmt_off   = 0;
   int         i           = 0;
   x_right   = my.rigminus;
   x_left    = x_right - 35;
   yLOG_value  ("x_right"     , x_right);
   DEBUG_LOOP   yLOG_value  ("x_left"      , x_left );
   /*---(fake input)------------------*/
   COLORS_RED;
   x_col = g_vals.prom_lef + 12 + 2;
   for (i = 0; i < my.chars; ++i) {
      if      (i < 12)    mvprintw (g_vals.prom_top + 4, x_col + i -  0, "*");
      else if (i < 18)    mvprintw (g_vals.prom_top + 5, x_col + i - 12, "*");
      else if (i < 35)    mvprintw (g_vals.prom_top + 6, x_col + i - 18, "*");
   }
   COLORS_OFF;
   return 0;
}

char         /*-> get character from ncurses ---------------------------------*/
show_getchar           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_ch        =    0;
   char        t           [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(get character)---------------*/
   x_ch = getch ();
   my.curr = x_ch;
   DEBUG_USER   yLOG_value   ("x_ch"      , x_ch);
   /*---(didn't get a character)------*/
   --rce;  if (x_ch == ERR) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   ++my.chars;
   /*---(special keys)----------------*/
   switch (x_ch) {
   case 27 :
      DEBUG_USER   yLOG_note    ("escape when done");
      x_ch = '¥';
      break;
   case '\n' :
      DEBUG_USER   yLOG_note    ("return, mark failed and break out");
      x_ch = '¦';
      my.status = STATUS_NEWLINE;
      break;
   case  3   :
      DEBUG_USER   yLOG_note    ("<C-c>, mark break and break out");
      x_ch = 'Ô';
      my.status = STATUS_BREAK;
      break;
   case  18  :
      DEBUG_USER   yLOG_note    ("<C-r>, mark refresh and break out");
      x_ch = 'Ó';
      my.status = STATUS_REFRESH;
      break;
   case 32 ... 126 :
      DEBUG_USER   yLOG_note    ("normal character, append");
      break;
   default :
      DEBUG_USER   yLOG_note    ("weird character, mark failed and break out");
      x_ch = '¤';
      my.status = STATUS_FAILED;
      break;
   }
   DEBUG_USER   yLOG_char    ("my.status"  , my.status);
   /*---(add text)-----------------------*/
   sprintf (t, "%c", x_ch);
   strlcat (my.entry_text, t, LEN_DESC);
   DEBUG_USER   yLOG_info    ("text"      , my.entry_text);
   /*---(check)--------------------------*/
   my.result = yEXEC_response (my.entry_text, &(my.phase), &(my.judgement), &(my.position));
   if (my.show_hint == 'y') {
      COLORS_RED;
      mvprintw ( 8, my.cen - 19, "          ");
      mvprintw ( 9, my.cen - 19, "          ");
      mvprintw (10, my.cen - 19, "          ");
      mvprintw (11, my.cen - 19, "          ");
      sprintf (t, "%c", rand () % 10 + '0');
      ySTR_display ("thick"       , t, YSTR_GAPS, my.cen - 19,  8, NULL, NULL);
      sprintf (t, "%c", rand () % 10 + '0');
      ySTR_display ("thick"       , t, YSTR_GAPS, my.cen - 14,  8, NULL, NULL);
      sprintf (t, "%c", my.phase);
      ySTR_display ("thick"       , t, YSTR_GAPS, my.cen -  9,  8, NULL, NULL);
      sprintf (t, "%c", my.judgement);
      ySTR_display ("thick"       , t, YSTR_GAPS, my.cen +  5,  8, NULL, NULL);
      mvprintw ( 8, my.cen + 10, "          ");
      mvprintw ( 9, my.cen + 10, "          ");
      mvprintw (10, my.cen + 10, "          ");
      mvprintw (11, my.cen + 10, "          ");
      sprintf (t, "%02d", my.position);  
      ySTR_display ("thick"       , t, YSTR_GAPS, my.cen + 10,  8, NULL, NULL);
      sprintf (t, "%2d[%s]", strlen (my.entry_text), my.entry_text);
      mvprintw (7, my.cen - 15, "%s", t);
      COLORS_OFF;
   }
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char             /* [------] print the /etc/issue file and login prompt ------*/
show_all             (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   char        x_date      [LEN_DESC] = "";
   /*---(header)----------------------*/
   DEBUG_LOOP   yLOG_enter  (__FUNCTION__);
   /*---(set positions)---------------*/
   show_sizing ();
   clear       ();
   mvprintw    (0, 0,  "                                                                            ");
   /*---(show sections)------------------*/
   rc = show_butterfly ();
   rc = show_ascii     ();
   strl4time (time (NULL), x_date, 0, 'T', LEN_DESC);
   COLORS_BLUE;
   ySTR_prompt_box (my.language, my.cluster, my.host, x_date, g_vals.prom_lef, g_vals.prom_top);
   COLORS_OFF;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_note   ("printed issue");
   DEBUG_LOOP   yLOG_exit   (__FUNCTION__);
   return 0;
}

static int s_x  [32] = {  0,  2,  4,  6,  7,  8,  9, 10, 10, 10,  9,  8,  7,  6,  4,  2,  0, -2, -4, -6, -7, -8, -9,-10,-10,-10, -9, -8, -7, -6, -4, -2 };
static int s_y  [32] = {  5,  5,  5,  4,  4,  3,  2,  1,  0, -1, -2, -3, -4, -4, -5, -5, -5, -5, -5, -4, -4, -3, -2, -1,  0,  1,  2,  3,  4,  4,  5,  5 };

char
show_timer           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_secs      =    0;
   int         x, y;
   /*---(assign pass)--------------------*/
   if      (my.secs <=  32)   COLORS_GREEN;
   else if (my.secs <=  64)   COLORS_MAGENTA;
   else if (my.secs <=  98)   COLORS_YELLOW;
   else                       COLORS_RED;
   /*---(clear marker)-------------------*/
   if (my.secs > 0) {
      x_secs = (my.secs - 1) % 32;
      x = g_vals.timr_cen + s_x [x_secs];
      y = g_vals.timr_mid + s_y [x_secs];
      ySTR_display (g_vals.timr_font, " ", YSTR_NOGAPS, x, y, NULL, NULL);
   }
   /*---(show marker)--------------------*/
   x_secs = my.secs % 32;
   x = g_vals.timr_cen + s_x [x_secs];
   y = g_vals.timr_mid + s_y [x_secs];
   ySTR_display (g_vals.timr_font, "1", YSTR_NOGAPS, x, y, NULL, NULL);
   COLORS_OFF;
   /*---(complete)-----------------------*/
   return 0;
}



