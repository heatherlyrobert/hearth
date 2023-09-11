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

char        s_lstrip      [LEN_HUND] = "";
char        s_lblock      [LEN_HUND] = "";
char        s_lknock      [LEN_HUND] = "";
char        s_rstrip      [LEN_HUND] = "";
char        s_rblock      [LEN_HUND] = "";
char        s_rknock      [LEN_HUND] = "";


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






/*====================------------------------------------====================*/
/*===----                       ystr_support                           ----===*/
/*====================------------------------------------====================*/
static void  o___YSTR____________o () { return; }

char
show_displayer   (int x, int y, char *a_text, char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_len       =    0;
   int         i           =    0;
   char        c           =  '-';

   DEBUG_PROG   yLOG_senter  (__FUNCTION__);
   DEBUG_PROG   yLOG_snote   (a_text);
   x_len = strlen (a_text);
   for (i = 0; i < x_len; ++i) {
      c = a_text [i];
      if (a_mode == YASCII_MERGE && c == ' ')  continue;
      if (my.dev [5] == 't')  switch (c) {
      case 'µ' : c = '\\';   break;
      case '´' : c = '+';    break;
      case '³' : c = '*';    break;
      case '·' : c = '-';    break;
      case '²' : c = '-';    break;
      }
      mvprintw (y, x + i,  "%c", c);
   }
   DEBUG_PROG   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

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
   if (my.rig >= 180) {
      g_vals.bfly_size = 'L';
      ystrlcpy (g_vals.lefs_font, "alligator"      , LEN_LABEL);
      ystrlcpy (g_vals.rigs_font, "goofy"          , LEN_LABEL);
      ystrlcpy (g_vals.tops_font, "basic"          , LEN_LABEL);
      ystrlcpy (g_vals.mids_font, "chunky_full"    , LEN_LABEL);
      ystrlcpy (g_vals.noks_font, "dots"           , LEN_LABEL);
      ystrlcpy (g_vals.timr_font, "dots_rnd"       , LEN_LABEL);
      g_vals.noks_gap = 2;
   } else if (my.rig > 100) {
      g_vals.bfly_size = 'm';
      ystrlcpy (g_vals.lefs_font, "chunky"         , LEN_LABEL);
      ystrlcpy (g_vals.rigs_font, "graceful"       , LEN_LABEL);
      ystrlcpy (g_vals.tops_font, "fuzzy"          , LEN_LABEL);
      ystrlcpy (g_vals.mids_font, "thick"          , LEN_LABEL);
      ystrlcpy (g_vals.noks_font, "dots_med"       , LEN_LABEL);
      ystrlcpy (g_vals.timr_font, "dots_rnd"       , LEN_LABEL);
      g_vals.noks_gap = 2;
   } else {
      g_vals.bfly_size = 's';
      ystrlcpy (g_vals.lefs_font, "tiny_dot"       , LEN_LABEL);
      ystrlcpy (g_vals.rigs_font, "amc3line"       , LEN_LABEL);
      ystrlcpy (g_vals.tops_font, "tiny_block"     , LEN_LABEL);
      ystrlcpy (g_vals.mids_font, "rob4dots2"      , LEN_LABEL);
      ystrlcpy (g_vals.noks_font, "dots_sml"       , LEN_LABEL);
      ystrlcpy (g_vals.timr_font, "dots_rnd"       , LEN_LABEL);
      g_vals.noks_gap = 1;
   }
   DEBUG_GRAF   yLOG_value   ("noks_gap"  , g_vals.noks_gap);
   /*---(left)---------------------------*/
   DEBUG_GRAF   yLOG_note    ("left spacing");
   g_vals.lefs_top  = 0;
   g_vals.lefs_lef  = 0;
   g_vals.noks_top  = 0;
   rc = yASCII_font (g_vals.lefs_font, &x_wide, NULL);
   DEBUG_GRAF   yLOG_value   ("x_wide"    , x_wide);
   rc = yASCII_font (g_vals.noks_font , &x_wideK, NULL);
   DEBUG_GRAF   yLOG_value   ("x_wideK"   , x_wideK);
   my.lefplus   = my.lef + (x_wide * 2) + x_wideK;
   DEBUG_GRAF   yLOG_value   ("s_lef+"    , my.lefplus);
   g_vals.noks_lef  = my.lef + (x_wide * 2);
   DEBUG_GRAF   yLOG_value   ("noks_lef"  , g_vals.noks_lef);
   /*---(right)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("right spacing");
   g_vals.rigs_top  = 0;
   rc = yASCII_font (g_vals.rigs_font, &x_wide, NULL);
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
   rc = yASCII_font (g_vals.mids_font, &x_wide, &x_tall);
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
   rc = yASCII_font (g_vals.tops_font, &x_wide, &x_tall);
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
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(config)----------------------*/
   DEBUG_PROG   yLOG_note    ("dislayer");
   yASCII_displayer (show_displayer);
   show_sizing    ();
   /*---(magic)--------------------------*/
   srand (time(NULL));
   ySEC_challenge (my.magic_num);
   /*---(config)-------------------------*/
   if (my.lang_save < 0)   my.lang_curr       = yASCII_language ("", NULL);
   else                    my.lang_curr       = my.lang_save;
   if (my.clus_save < 0)   my.clus_curr       = yASCII_cluster  (-1, NULL, NULL);
   else                    my.clus_curr       = my.clus_save;
   if (my.host_save < 0)   my.host_curr       = yASCII_host     (-1, NULL, NULL);
   else                    my.host_curr       = my.host_save;
   my.hexigram        = rand () % 64;
   g_vals.bfly_indx   = rand () % CNT_BFLY;
   g_vals.bfly_size   = 'L';
   /*---(statuses)-----------------------*/
   my.status          = STATUS_GOOD;
   my.chars           =   0;
   my.phase           = 'k';
   my.judgement       = 'i';
   my.position        =   0;
   ystrlcpy (my.entry_text , "", LEN_DESC);
   ystrlcpy (s_lstrip      , "", LEN_HUND);
   ystrlcpy (s_lblock      , "", LEN_HUND);
   ystrlcpy (s_lknock      , "", LEN_HUND);
   ystrlcpy (s_rstrip      , "", LEN_HUND);
   ystrlcpy (s_rblock      , "", LEN_HUND);
   ystrlcpy (s_rknock      , "", LEN_HUND);
   /*---(prepare date)-------------------*/
   x_now     = time (NULL);
   x_broke   = localtime (&x_now);
   strftime (my.rundate, LEN_DESC, "%y.%m.%d.%H.%M.%S.%w.%V.%j", x_broke);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
show_background         (void)
{
   clear             ();
   /*> show_butterfly    ();                                                          <*/
   show_rain_prep    ();
   show_left         ();
   show_right        ();
   show_block        ();
   show_prompt       ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      ornamental                              ----===*/
/*====================------------------------------------====================*/
static void  o___ORNAMENTAL______o () { return; }

static int         s_col       [LEN_HUND];
static int         s_row       [LEN_HUND];

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
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
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
   for (x_col = 0; x_col < LEN_HUND; ++x_col)    s_col [x_col] = rand () % 160 + 10;
   for (x_row = 0; x_row < LEN_HUND; ++x_row)    s_row [x_row] = rand () % x_nrow;
   /*---(complete)-----------------------*/
   return 0;
}

char
show_rain_prep   (void)
{
   int         x_row       = 0;               /* iterator -- rows             */
   int         x_col       = 0;               /* iterator -- columns          */
   int         x_ncol      =   20;
   int         x_nrow      =   20;
   switch (g_vals.bfly_size) {
   case 'L' :  x_ncol = 180; x_nrow =  65;               break;
   case 'm' :  x_ncol = 100; x_nrow =  45;               break;
   case 's' :  x_ncol =  60; x_nrow =  30;               break;
   }
   for (x_col = 0; x_col < LEN_HUND; ++x_col)    s_col [x_col] = rand () % 160 + 10;
   for (x_row = 0; x_row < LEN_HUND; ++x_row)    s_row [x_row] = rand () % x_nrow;
}

char
show_rain        (void)
{
   int         i, x, y;
   int         x_left, x_top;
   int         x_ncol, x_nrow;
   char        v           [LEN_DESC]  = "";
   char        t           [LEN_SHORT] = "";
   char        x_content   [LEN_DESC]  = "";
   int         l           =    0;
   char        b           =  '[';
   char        e           =  ']';
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   /*---(charset)------------------------*/
   if (my.dev [5] == 't')  ystrlcpy (v, "abcdefghijklmnopqrstuvwx", LEN_DESC);
   else                    ystrlcpy (v, "èéêëìíîïðñòóôõö÷øùúûüýþÿ", LEN_DESC);
   switch (g_vals.bfly_size) {
   case 'L' :  x_ncol = 180; x_nrow =  65;               break;
   case 'm' :  x_ncol = 100; x_nrow =  45;               break;
   case 's' :  x_ncol =  60; x_nrow =  30;  x_top -= 5;  break;
   }
   x_left  = my.cen - x_ncol / 2;
   x_top   = my.mid - x_nrow / 2;
   for (i = 0; i < LEN_HUND; ++i) {
      /*---(fill behind)-----------------*/
      x = s_col [i];
      y = s_row [i] - 2;
      if (y < 0) y = 0;
      move   (x_top + y, x_left + x);
      innstr (t, 1);
      if (g_bfly_lrg [g_vals.bfly_indx][y][x] != ' ') {
         COLORS_GREEN;
         mvprintw (x_top + y, x_left + x,  "%c", g_bfly_lrg [g_vals.bfly_indx][y][x]);
         COLORS_OFF;
      }
      ++s_row [i];
      if (s_row [i] >= x_nrow) {
         s_col [i] = rand () % 160 + 10;
         s_row [i] = 0;
      }
      /*---(draw new head)---------------*/
      x = s_col [i];
      y = s_row [i];
      move   (x_top + y, x_left + x);
      innstr (t, 1);
      if (g_bfly_lrg [g_vals.bfly_indx][y][x] != ' ') {
         COLORS_YELLOW;
         mvprintw (x_top + y, x_left + x,  "%c", v [rand () % 24]);
         COLORS_OFF;
      }
      /*---(done)------------------------*/
   }
   if (my.mute != 'y') {
      if (my.dev [5] != 't')   { b = 'å'; e = 'æ'; }
      mvprintw (67, my.cen - 14, "%c%s%c", b, my.rundate, e);
      yASCII_word    (YASCII_DATE    , x_content);
      ystrltrim (x_content, ySTR_BOTH, LEN_DESC);
      l = strlen (x_content) / 2;
      mvprintw (66, my.cen - l, "%s"              , x_content);
   }
   return 0;
}

char
show_random            (int a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       c           =    0;
   char        i           =    0;
   char        v           [LEN_HUND] = "";
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   /*---(defense)------------------------*/
   DEBUG_LOOP   yLOG_senter (__FUNCTION__);
   /*---(first time)---------------------*/
   if (a_count == -1) {
      DEBUG_LOOP   yLOG_snote  ("first run");
      COLORS_OFF;
      if (my.dev [5] == 't')  mvprintw (6, my.cen - 25, "--------------------------------------------------");
      else                    mvprintw (6, my.cen - 25, "··················································");
   }
   /*---(first time)---------------------*/
   if (my.dev [5] == 't')  ystrlcpy (v, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWX--------------------------------------------------", LEN_HUND);
   else                    ystrlcpy (v, "abcdefghijklmnopqrstuvwxyzèéêëìíîïðñòóôõö÷øùúûüýþÿ··················································", LEN_HUND);
   DEBUG_LOOP   yLOG_snote  (v);
   /*---(left side)----------------------*/
   COLORS_CYAN;
   c = v [rand () % 50];
   DEBUG_LOOP   yLOG_schar  (c);
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, "%c", c);
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9,  44 + rand () %  9, " ");
   COLORS_OFF;
   /*---(right side)---------------------*/
   COLORS_CYAN;
   c = v [rand () % 50];
   DEBUG_LOOP   yLOG_schar  (c);
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, "%c", c);
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   mvprintw ( 56 + rand () %  9, 173 + rand () %  9, " ");
   COLORS_OFF;
   /*---(top)----------------------------*/
   for (i = 0; i < 5; ++i) {
      mvprintw (6, my.cen - 25 + rand () % 50, "%c", v [rand () % 100]);
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit  (__FUNCTION__);
   return 0;
}

char
show_prompt             (void)
{
   char        x_title     [LEN_LABEL] = "";
   char        x_content   [LEN_DESC]  = "";
   char        t           [LEN_DESC]  = "";
   int         l           =    0;
   char        s           [LEN_LABEL] = "";
   char        b           =  '[';
   char        e           =  ']';
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   COLORS_OFF;
   if (my.dev [5] != 't')   { b = 'å'; e = 'æ'; }
   yASCII_cluster (my.clus_curr, x_title, x_content);
   sprintf (t, "%02d.%s", my.clus_curr, x_content);
   ystrlpad (t, s, '_', '<', 18);
   mvprintw ( 1,  35, "%12.12s %c%-18.18s%c", x_title, b, s, e);
   yASCII_host    (my.host_curr, x_title, x_content);
   sprintf (t, "%s.%02d", x_content, my.host_curr);
   ystrlpad (t, s, '_', '>', 18);
   mvprintw ( 1, 157, "%c%18.18s%c %-12.12s", b, s, e, x_title);
   if (my.dev [5] == 't')  ystrlcpy (t, "____________________", LEN_LABEL);
   else                    ystrlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_LABEL);
   yASCII_word    (YASCII_USERNAME, x_content);
   mvprintw (70,  70, "%c%-12.12s%c %-12.12s"   , b, t, e, x_content);
   yASCII_word    (YASCII_TOKEN   , x_content);
   ystrltrim (x_content, ySTR_BOTH, LEN_DESC);
   l = strlen (x_content) / 2;
   mvprintw (69, my.cen - l, "%s"              , x_content);
   mvprintw (70, my.cen - 4, "%c%-3.3s-%-3.3s%c"       , b, t, t, e);
   yASCII_word    (YASCII_PASSWORD, x_content);
   mvprintw (70, 130, "%12.12s %c%-12.12s%c"    , x_content, b, t, e);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     hiding content                           ----===*/
/*====================------------------------------------====================*/
static void  o___CONTENT_________o () { return; }

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
   ystrlcpy (v, "abcdefghijklmnopqrstuvwxyz0123456789", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      t [i] = v [rand () % 36];
   for (i = 1; i < LEN_HUND; i += 2)   t [i] = '¦';
   t  [LEN_HUND - 1] = '\0';
   COLORS_YELLOW;
   if (my.mute != 'y')  yASCII_display ("tiny_dot" , t, YASCII_GAPS, 0, 0, NULL, NULL, YASCII_CLEAR);
   COLORS_OFF;
   /*---(center left)--------------------*/
   ystrlcpy (v, "1234567890", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      s_lstrip [i] = v [rand () % 10];
   for (i = 2; i < LEN_HUND; i += 3)   s_lstrip [i] = '¦';
   s_lstrip  [LEN_HUND - 1] = '\0';
   s_lstrip [ 0] = my.magic_num [ 6];
   s_lstrip [27] = my.magic_num [18];
   s_lstrip [13] = my.magic_num [13];
   COLORS_YELLOW;
   if (my.mute != 'y')  yASCII_display ("alligator", s_lstrip, YASCII_GAPS, 4, 0, NULL, NULL, YASCII_CLEAR);
   COLORS_OFF;
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      yASCII_font ("alligator", &w, &h);
      COLORS_RED;
      sprintf (s_lstrip, "%c", my.magic_num [ 6]);
      if (my.mute != 'y')  yASCII_display ("alligator", s_lstrip, YASCII_GAPS, 4    , 0    , NULL, NULL, YASCII_CLEAR);
      sprintf (s_lstrip, "%c", my.magic_num [18]);
      if (my.mute != 'y')  yASCII_display ("alligator", s_lstrip, YASCII_GAPS, 4    , 9 * h, NULL, NULL, YASCII_CLEAR);
      sprintf (s_lstrip, "%c", my.magic_num [13]);
      if (my.mute != 'y')  yASCII_display ("alligator", s_lstrip, YASCII_GAPS, 4 + w, 4 * h, NULL, NULL, YASCII_CLEAR);
      COLORS_OFF;
   }
   /*---(knocks)-------------------------*/
   ystrlcpy (v, "01", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      s_lknock [i] = v [rand () %  2];
   g_vals.noks_gap = 2;
   switch (g_vals.noks_gap) {
   case 0 :
      for (i = 1; i < LEN_HUND; i += 2)  s_lknock [i] = '¦';
      a =  2;
      b =  6;
      break;
   case 1 :
      for (i = 1; i < LEN_HUND; i += 4)  s_lknock [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 4)  s_lknock [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 4)  s_lknock [i] = '¦';
      a =  4;
      b = 12;
      break;
   case 2 :
      for (i = 1; i < LEN_HUND; i += 6)  s_lknock [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 6)  s_lknock [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 6)  s_lknock [i] = '¦';
      for (i = 4; i < LEN_HUND; i += 6)  s_lknock [i] = ' ';
      for (i = 5; i < LEN_HUND; i += 6)  s_lknock [i] = '¦';
      a =  6;
      b = 30;
      break;
   }
   s_lknock [LEN_HUND - 1] = '\0';
   s_lknock [ a] = (my.magic_num [ 1] == '+') ? '1' : '0';
   s_lknock [ b] = (my.magic_num [ 4] == '+') ? '1' : '0';
   COLORS_YELLOW;
   if (my.mute != 'y')  yASCII_display ("dots", s_lknock, YASCII_GAPS, 25, 0, NULL, NULL, YASCII_MERGE);
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      yASCII_font ("dots"     , &w, &h);
      COLORS_RED;
      sprintf (s_lknock, "%c", (my.magic_num [ 1] == '+') ? '1' : '0');
      if (my.mute != 'y')  yASCII_display ("dots"     , s_lknock, YASCII_GAPS, 25   , 3  * h, NULL, NULL, YASCII_MERGE);
      sprintf (s_lknock, "%c", (my.magic_num [ 4] == '+') ? '1' : '0');
      if (my.mute != 'y')  yASCII_display ("dots"     , s_lknock, YASCII_GAPS, 25   , 15 * h, NULL, NULL, YASCII_MERGE);
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
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   /*---(prepare)------------------------*/
   yASCII_font ("goofy"    , &w, &h);
   if      (strchr ("XYZ" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'X';
   else if (strchr ("xyz" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'x';
   else if (strchr ("XYZ" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'X';
   else if (strchr ("xyz" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'x';
   else if (strchr ("XYZ" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'X';
   else if (strchr ("xyz" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'x';
   n = 25 + (x_off * 4);
   /*---(rightmost)----------------------*/
   ystrlcpy (v, "1234567890", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      s_rstrip [i] = v [rand () % 10];
   for (i = 3; i < LEN_HUND; i += 4)   s_rstrip [i] = '¦';
   s_rstrip  [LEN_HUND - 1] = '\0';
   s_rstrip [x_off * 4 + 0] = my.magic_num [n + 0];
   s_rstrip [x_off * 4 + 1] = my.magic_num [n + 1];
   s_rstrip [x_off * 4 + 2] = my.magic_num [n + 2];
   COLORS_YELLOW;
   if (my.mute != 'y')  yASCII_display ("goofy"    , s_rstrip, YASCII_GAPS, my.rig - w * 3, 0, NULL, NULL, YASCII_CLEAR);
   COLORS_OFF;
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (s_rstrip, "%c%c%c", my.magic_num [n + 0], my.magic_num [n + 1], my.magic_num [n + 2]);
      if (my.mute != 'y')  yASCII_display ("goofy"    , s_rstrip, YASCII_GAPS, my.rig - w * 3, x_off * h, NULL, NULL, YASCII_CLEAR);
      COLORS_OFF;
   }
   /*---(knocks)-------------------------*/
   ystrlcpy (v, "01", LEN_HUND);
   for (i = 0; i < LEN_HUND; ++i)      s_rknock [i] = v [rand () %  2];
   switch (g_vals.noks_gap) {
   case 0 :
      for (i = 1; i < LEN_HUND; i += 2)  s_rknock [i] = '¦';
      a =  2;
      b =  6;
      break;
   case 1 :
      for (i = 1; i < LEN_HUND; i += 4)  s_rknock [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 4)  s_rknock [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 4)  s_rknock [i] = '¦';
      a =  4;
      b = 12;
      break;
   case 2 :
      for (i = 1; i < LEN_HUND; i += 6)  s_rknock [i] = '¦';
      for (i = 2; i < LEN_HUND; i += 6)  s_rknock [i] = ' ';
      for (i = 3; i < LEN_HUND; i += 6)  s_rknock [i] = '¦';
      for (i = 4; i < LEN_HUND; i += 6)  s_rknock [i] = ' ';
      for (i = 5; i < LEN_HUND; i += 6)  s_rknock [i] = '¦';
      a =  6;
      b = 30;
      break;
   }
   s_rknock [LEN_HUND - 1] = '\0';
   s_rknock [ a] = (my.magic_num [40] == '+') ? '1' : '0';
   s_rknock [ b] = (my.magic_num [37] == '+') ? '1' : '0';
   COLORS_YELLOW;
   yASCII_font ("dots"     , &w2, &h2);
   if (my.mute != 'y')  yASCII_display ("dots", s_rknock, YASCII_GAPS, my.rig - 3 * w - w2, 0, NULL, NULL, YASCII_MERGE);
   /*---(magic)--------------------------*/
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (s_rknock, "%c", (my.magic_num [40] == '+') ? '1' : '0');
      if (my.mute != 'y')  yASCII_display ("dots"     , s_rknock, YASCII_GAPS, my.rig - 3 * w - w2, 3  * h2, NULL, NULL, YASCII_MERGE);
      sprintf (s_rknock, "%c", (my.magic_num [37] == '+') ? '1' : '0');
      if (my.mute != 'y')  yASCII_display ("dots"     , s_rknock, YASCII_GAPS, my.rig - 3 * w - w2, 15 * h2, NULL, NULL, YASCII_MERGE);
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
   yASCII_font ("chunky_full", &w, &h);
   if      (strchr ("ABCD" , my.magic_num [21]) != NULL)  x_rot = my.magic_num [21] - 'A';
   else if (strchr ("abcd" , my.magic_num [21]) != NULL)  x_rot = my.magic_num [21] - 'a';
   else if (strchr ("ABCD" , my.magic_num [22]) != NULL)  x_rot = my.magic_num [22] - 'A';
   else if (strchr ("abcd" , my.magic_num [22]) != NULL)  x_rot = my.magic_num [22] - 'a';
   else if (strchr ("ABCD" , my.magic_num [23]) != NULL)  x_rot = my.magic_num [23] - 'A';
   else if (strchr ("abcd" , my.magic_num [23]) != NULL)  x_rot = my.magic_num [23] - 'a';
   ystrlcpy (v, "abcdefghijklmnopqrstuvwxyz0123456789", LEN_HUND);
   for (i = 0; i < 15; ++i)   s_lblock [i] = v [rand () % 36];
   s_lblock [ 3] = s_lblock [ 7] = s_lblock [11] = '¦';
   s_lblock [ 5] = s_lblock [ 6] = s_lblock [ 9] = s_lblock [10] = ' ';
   s_lblock [15] = '\0';
   s_lblock [12] = x_rot + 'a';
   if (my.mute != 'y')  yASCII_display ("chunky_full" , s_lblock, YASCII_GAPS,  35, 50, NULL, NULL, YASCII_MERGE);
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (s_lblock, "%c", x_rot + 'a');
      if (my.mute != 'y')  yASCII_display ("chunky_full", s_lblock, YASCII_GAPS, 35, 50 + 3 * h, NULL, NULL, YASCII_MERGE);
      COLORS_OFF;
   }
   /*---(prepare)------------------------*/
   yASCII_font ("chunky_full", &w, &h);
   if      (strchr ("XYZ" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'X';
   else if (strchr ("xyz" , my.magic_num [21]) != NULL)  x_off = my.magic_num [21] - 'x';
   else if (strchr ("XYZ" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'X';
   else if (strchr ("xyz" , my.magic_num [22]) != NULL)  x_off = my.magic_num [22] - 'x';
   else if (strchr ("XYZ" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'X';
   else if (strchr ("xyz" , my.magic_num [23]) != NULL)  x_off = my.magic_num [23] - 'x';
   ystrlcpy (v, "abcdefghijklmnopqrstuvwxyz0123456789", LEN_HUND);
   for (i = 0; i < 15; ++i)   s_rblock [i] = v [rand () % 36];
   s_rblock [ 3] =s_rblock [ 7] = s_rblock [11] = '¦';
   s_rblock [ 4] =s_rblock [ 5] = s_rblock [ 8] = s_rblock [ 9] = ' ';
   s_rblock [15] = '\0';
   s_rblock [14] = x_off + 'x';
   if (my.mute != 'y')  yASCII_display ("chunky_full" , s_rblock, YASCII_GAPS, 170, 50, NULL, NULL, YASCII_MERGE);
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (s_rblock, "%c", x_off + 'x');
      if (my.mute != 'y')  yASCII_display ("chunky_full", s_rblock, YASCII_GAPS, 170 + 2 * w, 50 + 3 * h, NULL, NULL, YASCII_MERGE);
      COLORS_OFF;
   }
   for (i = 0; i <  3; ++i)   t [i] = rand () % 26 + 'a';
   t [ 4] = '\0';
   if (my.mute != 'y')  yASCII_display ("horzright"   , t, YASCII_GAPS, my.cen - 9 * 3 - 2,  1, NULL, NULL, YASCII_MERGE);
   for (i = 0; i <  3; ++i)   t [i] = rand () % 26 + 'a';
   t [ 4] = '\0';
   if (my.mute != 'y')  yASCII_display ("horzleft"    , t, YASCII_GAPS, my.cen + 2        ,  1, NULL, NULL, YASCII_MERGE);
   if (my.show_hint == 'y') {
      COLORS_RED;
      if (my.mute != 'y')  mvprintw ( 0, my.cen - strlen (my.magic_num) / 2, "%s", my.magic_num);
      COLORS_OFF;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      gathering input                         ----===*/
/*====================------------------------------------====================*/
static void  o___INPUT___________o () { return; }

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
   /*---(special keys)----------------*/
   switch (x_ch) {
   case '¬': case '·':
      DEBUG_USER   yLOG_note    ("unit testing spaces");
      x_ch = ' ';
      break;
   case 27 : case '¥' :
      DEBUG_USER   yLOG_note    ("escape when done");
      x_ch = '¥';
      break;
   case '\n' : case '¦' :
      DEBUG_USER   yLOG_note    ("return, mark failed and break out");
      x_ch = '¦';
      my.status = STATUS_NEWLINE;
      break;
   case  3   :
      DEBUG_USER   yLOG_note    ("<C-c>, mark break and break out");
      x_ch = '³';
      my.status = STATUS_BREAK;
      break;
   case  18  :
      DEBUG_USER   yLOG_note    ("<C-r>, mark refresh and break out");
      x_ch = 'ª';
      my.status = STATUS_REFRESH;
      break;
   case 32 ... 126 :
      DEBUG_USER   yLOG_note    ("normal character, append");
      break;
   default :
      DEBUG_USER   yLOG_note    ("weird character, save a placeholder");
      x_ch = '¤';
      break;
   }
   DEBUG_USER   yLOG_char    ("my.status"  , my.status);
   /*---(deafness)-----------------------*/
   if (my.deaf == 'y')    return 0;
   /*---(add text)-----------------------*/
   ++my.chars;
   DEBUG_USER   yLOG_value   ("my.chars"  , my.chars);
   if (my.chars <= 40)  {
      DEBUG_USER   yLOG_note    ("appending character");
      sprintf (t, "%c", x_ch);
      ystrlcat (my.entry_text, t, LEN_DESC);
   }
   DEBUG_USER   yLOG_complex ("text"      , "%2d[%s]", strlen (my.entry_text), my.entry_text);
   /*---(check)--------------------------*/
   DEBUG_USER   yLOG_complex ("magic"     , "%2d[%s]", strlen (my.magic_num), my.magic_num);
   my.result = ySEC_full (my.entry_text, &(my.phase), &(my.judgement), &(my.position), my.user_fix);
   DEBUG_USER   yLOG_value   ("result"     , my.result);
   DEBUG_USER   yLOG_char    ("phase"      , my.phase);
   DEBUG_USER   yLOG_char    ("judgement"  , my.judgement);
   DEBUG_USER   yLOG_value   ("position"   , my.position);
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
show__getstring      (void)
{
   char        rc          =    0;
   while (rc >= 0)  rc = show_getchar ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       providing feedback                     ----===*/
/*====================------------------------------------====================*/
static void  o___FEEDBACK________o () { return; }

char
show_results         (void)
{
   char        t           [LEN_DESC]  = "";
   char        v           [LEN_DESC]  = "";
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   if (my.show_hint == 'y') {
      COLORS_RED;
      sprintf (t, "%c", my.phase);
      if (my.mute != 'y')  yASCII_display ("thick"       , t, YASCII_GAPS, my.cen - 14,  8, NULL, NULL, YASCII_CLEAR);
      sprintf (t, "%c", my.judgement);
      if (my.mute != 'y')  yASCII_display ("thick"       , t, YASCII_GAPS, my.cen -  9,  8, NULL, NULL, YASCII_CLEAR);
      sprintf (t, "%02d", my.position);  
      if (my.mute != 'y')  yASCII_display ("thick"       , t, YASCII_GAPS, my.cen + 5,  8, NULL, NULL, YASCII_CLEAR);
      sprintf (t, "%2d[%s]", strlen (my.entry_text), my.entry_text);
      mvprintw (7, my.cen - 15, "%s", t);
      COLORS_OFF;
   }
   ystrlcpy (v, "0123456789abcdef", LEN_HUND);
   sprintf (t, "%c", v [g_vals.bfly_indx]);
   if (my.mute != 'y')  yASCII_display ("computer"    , t, YASCII_GAPS, my.cen - 4,  8, NULL, NULL, YASCII_CLEAR);
   sprintf (t, "%02d", my.hexigram);
   if (my.mute != 'y')  yASCII_display ("thick"       , t, YASCII_GAPS, my.cen - 5, 15, NULL, NULL, YASCII_CLEAR);
}

char
show_timer              (int *a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   char        v           [LEN_LABEL] = "";
   int         q           =    0;
   int         h           =    0;
   uchar       c           =  '-';
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   /*---(defense)------------------------*/
   DEBUG_LOOP   yLOG_senter (__FUNCTION__);
   DEBUG_LOOP   yLOG_spoint (a_count);
   --rce;  if (a_count == NULL) {
      DEBUG_LOOP   yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   n = *a_count;
   DEBUG_LOOP   yLOG_sint   (n);
   /*---(prepare)------------------------*/
   q = my.timeout / 4;
   h = my.timeout / 2;
   /*---(charset to use)-----------------*/
   if (my.dev [5] == 't')  ystrlcpy (v, "#----+----", LEN_LABEL);
   else                    ystrlcpy (v, "Ï····+····", LEN_LABEL);
   DEBUG_LOOP   yLOG_snote  (v);
   /*---(update trail)-------------------*/
   COLORS_OFF;
   c = v [n % 10];
   DEBUG_LOOP   yLOG_schar  (c);
   if (my.mute != 'y')   {
      if      (n ==  0)   mvprintw (73, my.cen -  q        ,  "%c", c);
      else if (n <   h)   mvprintw (72, my.cen -  q + n    ,  "%c", c);
      else if (n ==  h)   mvprintw (73, my.cen -  q + n    ,  "%c", c);
      else if (n < h * 2) mvprintw (74, my.cen +  h + q - n,  "%c", c);
   }
   /*---(update seconds)-----------------*/
   if (my.mute != 'y')  mvprintw (73, my.cen - 3,  "%2d sec", n / 10);
   /*---(check on forever)---------------*/
   if (n == my.timeout && my.forever == 'y') {
      DEBUG_LOOP   yLOG_snote  ("forever hit");
      n = -1;
      if (my.mute != 'y')  mvprintw (72, my.cen - q, "%*.*s", h + 1, h + 1, "                                                                                                                                      ");
      if (my.mute != 'y')  mvprintw (73, my.cen - q, "%*.*s", h + 1, h + 1, "                                                                                                                                      ");
      if (my.mute != 'y')  mvprintw (74, my.cen - q, "%*.*s", h + 1, h + 1, "                                                                                                                                      ");
      *a_count = n;
      DEBUG_LOOP   yLOG_sint   (n);
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit  (__FUNCTION__);
   return 0;
}

char
show_lockout            (int a_count)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    0;
   char        v           [LEN_LABEL] = "";
   uchar       c           =  '-';
   /*---(quick-out)----------------------*/
   if (my.mute == 'y')  return 0;
   /*---(defense)------------------------*/
   DEBUG_LOOP   yLOG_senter (__FUNCTION__);
   n = a_count;
   DEBUG_LOOP   yLOG_sint   (n);
   /*---(charset to use)-----------------*/
   if (my.dev [5] == 't')  ystrlcpy (v, " + + + + #", LEN_LABEL);
   else                    ystrlcpy (v, " · · · · ³", LEN_LABEL);
   DEBUG_LOOP   yLOG_snote  (v);
   /*---(show title)---------------------*/
   if (n == 0) {
      COLORS_RED;
      if (my.mute != 'y')  mvprintw (72, my.cen - 3,  "LOCKOUT");
      if (my.mute != 'y')  mvprintw (73, my.cen - 3,  "       ");
      COLORS_OFF;
   }
   /*---(update trail)-------------------*/
   COLORS_RED;
   c = v [n % 10];
   if (my.mute != 'y')  mvprintw (73, my.cen - (my.lockout / 10) + 1 + (n / 10) * 2, "%c", c);
   COLORS_OFF;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit  (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
show__unit              (char *a_question)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        s           [LEN_HUND]  = "";
   char        t           [LEN_RECD]  = " 0[]";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROG unit        : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "lstrip"    )     == 0) {
      if (strlen (s_lstrip) > 60) {
         ystrlcpy (t, "", LEN_RECD);
         sprintf (s, "%2d [%c] " , strlen (s_lstrip), s_lstrip [0]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-12.12s]" , s_lstrip + 1);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, " [%c] " , s_lstrip [13]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-13.13s]" , s_lstrip + 14);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, " [%c] " , s_lstrip [27]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-16.16s]" , s_lstrip + 28);
         ystrlcat (t, s, LEN_RECD);
         ystrldchg (t, '¦', '·', LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "SHOW lstrip      : %s", t);
   }
   else if (strcmp (a_question, "lknock"    )     == 0) {
      if (strlen (s_lknock) > 60) {
         ystrlcpy (t, "", LEN_RECD);
         sprintf (s, "%2d [%-6.6s]", strlen (s_lknock) , s_lknock);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, " [%c] " , s_lknock [6]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-23.23s]" , s_lknock + 7);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, " [%c] " , s_lknock [30]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-16.16s]" , s_lknock + 31);
         ystrlcat (t, s, LEN_RECD);
         ystrldchg (t, '¦', '·', LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "SHOW lknock      : %s", t);
   }
   else if (strcmp (a_question, "rstrip"    )     == 0) {
      if (strlen (s_rstrip) > 60) {
         sprintf (t, "%2d [%3.3s] · [%3.3s] · [%3.3s] · [%35.35s]" ,
               strlen (s_rstrip), s_rstrip, s_rstrip + 4, s_rstrip + 8, s_rstrip +12); 
         ystrldchg (t, '¦', '·', LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "SHOW rstrip      : %s", t);
   }
   else if (strcmp (a_question, "rknock"    )     == 0) {
      if (strlen (s_rknock) > 60) {
         ystrlcpy (t, "", LEN_RECD);
         sprintf (s, "%2d [%-6.6s]", strlen (s_rknock) , s_rknock);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, " [%c] " , s_rknock [6]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-23.23s]" , s_rknock + 7);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, " [%c] " , s_rknock [30]);
         ystrlcat (t, s, LEN_RECD);
         sprintf (s, "[%-16.16s]" , s_rknock + 31);
         ystrlcat (t, s, LEN_RECD);
         ystrldchg (t, '¦', '·', LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "SHOW rknock      : %s", t);
   }
   else if (strcmp (a_question, "lblock"    )     == 0) {
      if (strlen (s_lblock) > 10) {
         sprintf (t, "%2d [%12.12s] [%c] [%2.2s]" ,
               strlen (s_lblock), s_lblock, s_lblock [12], s_lblock + 13); 
         ystrldchg (t, '¦', '·', LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "SHOW lblock      : %s", t);
   }
   else if (strcmp (a_question, "rblock"    )     == 0) {
      if (strlen (s_rblock) > 10) {
         sprintf (t, "%2d [%14.14s] [%c]" ,
               strlen (s_rblock), s_rblock, s_rblock [14]); 
         ystrldchg (t, '¦', '·', LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "SHOW rblock      : %s", t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



