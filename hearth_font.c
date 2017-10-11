/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"


/*> extern char        chunky      [MAX_HEIGHT] [MAX_WIDTH];                          <* 
 *> extern char        chunky_full [MAX_HEIGHT] [MAX_WIDTH];                          <* 
 *> extern char        alligator   [MAX_HEIGHT] [MAX_WIDTH];                          <* 
 *> extern char        goofy       [MAX_HEIGHT] [MAX_WIDTH];                          <* 
 *> extern char        binary      [MAX_HEIGHT] [MAX_WIDTH];                          <* 
 *> extern char        dots        [MAX_HEIGHT] [MAX_WIDTH];                          <* 
 *> extern char        basic       [MAX_HEIGHT] [MAX_WIDTH];                          <*/

/* to be useful, all fonts need to be monospaced so they can be arranged into
 * lines, columns, blocks, and other shapes without giving away any information
 */


/*---(font constants)-------*/
#define     MAX_FONT       50
#define     MAX_WIDTH     400
#define     MAX_HEIGHT    400
#define     FONT_FULL      'f'       /* [a-z][0-9] */
#define     FONT_ALPHA     'a'       /* [a-z]      */
#define     FONT_NUMS      'n'       /* [0-9]      */
#define     FONT_BINARY    'b'       /* [0-1]      */



char        chunky [MAX_HEIGHT][MAX_WIDTH] = {
   " ______  ____    ______  ______  _____   ______  ______  ______  ______  ______ ",
   "|      ||_   |  |__    ||__    ||  |  | |    __||    __||      ||  __  ||  __  |",
   "|  --  | _|  |_ |    __||__    ||__    ||__    ||  __  ||_     ||  __  ||__    |",
   "|______||______||______||______|   |__| |______||______|  |____||______||______|",
};

char        chunky_full  [MAX_HEIGHT][MAX_WIDTH] = {
   "        __               __          ____         __      ___     ___  __      ___                                                    ___                                                     _____  ____   _____  _____  ____   _____  ____   _____  _____  _____ ",
   ".---.-.|  |--..-----..--|  |.-----. /  __|.-----.|  |--. |___|   |___||  |--. |   | .-----..-----..-----..-----..-----..-----..-----.|   |_..--.--..--.--..-.-.-..--.--..--.--..-----.       |     ||_   | |___  ||___  |/  | | |   __||  __| |__   || ___ ||  __ |",
   "|  _  ||  _  ||  ___||  __ ||  -__||   __||  _  ||     |.|   |.  |   ||    < .|   |.|     ||     ||  _  ||  _  ||  _  ||    _||__ --||    _||  |  ||  |  || | | ||_   _||  |  ||-- __|       |  -  |._|  |.|  ___||___  ||_    ||__   || __  |   |  || ___ ||___  |",
   "|___._||_____||_____||_____||_____||__|   |___  ||__|__||_____| _|   ||__|__||_____||_|_|_||__|__||_____||   __||__   ||___|  |_____||_____||_____||____/ |_____||__.__||___  ||_____|       |_____||_____||_____||_____|  |__| |_____||_____|   |__||_____| |____|",
   "                                          |_____|              |_____|                                   |__|      |__|                                                 |_____|                                                                                    ",
};

char        alligator2 [MAX_HEIGHT][MAX_WIDTH] = {
   " ::::::::       :::      ::::::::    ::::::::       :::     ::::::::::   ::::::::   ::::::::::   ::::::::    ::::::::   ",
   ":+:   #:+:    :+:+:     :+:    :+:  :+:    :+:     :+:      :+:    :+:  :+:    :+:  :+:    :+:  :+:    :+:  :+:    :+:  ",
   "+:+  + +:+      +:+           +:+          +:+    +:+ +:+   +:+         +:+               +:+   +:+    +:+  +:+    +:+  ",
   "+#+ +  +:+      +#+         +#+         +#++:    +#+  +:+   +#++:++#+   +#++:++#+        +#+     +#++:++#    +#++:++#+  ",
   "+#+#   +#+      +#+       +#+              +#+  +#+#+#+#+#         +#+  +#+    +#+      +#+     +#+    +#+         +#+  ",
   "#+#    #+#      #+#      #+#        #+#    #+#        #+#   #+#    #+#  #+#    #+#     #+#      #+#    #+#  #+#    #+#  ",
   " ########     #######   ##########   ########         ###    ########    ########      ###       ########    ########   ",
};

char        goofy  [MAX_HEIGHT][MAX_WIDTH] = {
   " /    \\     /_   |       / _  \\     (___  \\       /   |     |  ____)     /  __)     (___   )     /    \\      /    \\     ",
   "|      |      |  |      (_/ )  )      __)  |     /    |     | |___      |  (__         /  /     (      )    (      |    ",
   "|      |      |  |         /  /      (__   |    (__    )    |___  \\     |     \\       /  /       >    <      \\__   |    ",
   "|      |     _|  |_       /  /_      ___)  |      _|  |      ___)  )    |      )     /  /       (      )      __)  |    ",
   " \\    /     (      )     (     )    (     /      (     )    (     /      \\    /     (  /         \\    /      (    /     ",
};


char        binary   [MAX_HEIGHT][MAX_WIDTH] = {
   "-- -* -- -* -- -* -- -* *- ** ",
   "-- -- -* -* *- *- ** ** -- -- ",
};

char        dots     [MAX_HEIGHT][MAX_WIDTH] = {
   "  .   .n.       ",
   " -=-  c$d       ",
   "  '   'W'       "
};


char        basic    [MAX_HEIGHT][MAX_WIDTH] = {
   "-.d8b.--d8888b.--.o88b.-d8888b.-d88888b-d88888b--d888b--db---db-d888888----d88b-db---dD-db------.8b-d8.-d8b--db--.d8b.--d8888b.--.d8b.--d8888b.-.d8888.-d88888b-db---db-db---db-db-b-db-db---db-db---db-d88888D--------",
   "d8'-`8b-88--`8D-d8P--Y8-88--`8D-88'-----88'-----88'-Y8b-88---88---`88'-----`8P'-88-,8P'-88------88YbP88-888o-88-.8P-Y8.-88--`8D-.8P-Y8.-88--`8D-88'--YP-`~~88~'-88---88-88---88-88-I-88-`8b-d8'-`8b-d8'-YP--d8'--------",
   "88ooo88-88oooY'-8P------88---88-88ooooo-88ooo---88------88ooo88----88-------88--88,8P---88------88-8-88-88V8o88-88---88-88oodD'-88---88-88oobY'-`8bo.------88---88---88-Y8---8P-88-I-88--`8d8'---`8b8'-----d8'---------",
   "88~~~88-88~~~b.-8b------88---88-88~~~~~-88~~~---88--ooo-88~~~88----88-------88--88`8b---88------88-8-88-88-V888-88---88-88~~~---88---88-88`8b-----`Y8b.----88---88---88-`8b-d8'-Y8-I-88--.dYb.-----88-----d8'----------",
   "88---88-88---8D-Y8b--d8-88--.8D-88.-----88------88.-~8~-88---88---.88.--db.-88--88-`88.-88booo.-88-8-88-88--V88-`8b-d8'-88------`8P-d8'-88-`88.-db---8D----88---88b-d88--`8b8'--`8b8d8'-.8P-Y8.----88----d8'-db--------",
   "YP---YP-Y8888P'--`Y88P'-Y8888D'-Y88888P-YP-------Y888P--YP---YP-Y888888-Y8888P--YP---YD-Y88888P-YP-Y-YP-VP---8P--`Y8P'--88-------`Y8'Y8-88---YD-`8888Y'----YP---~Y888P'----Y-----`8`8'--YP---YP----YP---d88888P--------",
};


char        banner4  [MAX_HEIGHT][MAX_WIDTH] = {
   /*23456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
   "...###....########...#######..########..########..########...######...##.....##...######........##..##....##..##........##.....##.##....##...#######..########...#######..########...######...########..##.....##.##.....##.##.....##.##.....##.##....##...########.............#####.......##.....#######...#######..##........########...#######..########...#######...#######..",
   "..##.##...##.....##.##.....##.##.....##.##........##........##....##..##.....##.....##..........##..##...##...##........###...###.###...##..##.....##.##.....##.##.....##.##.....##.##....##.....##.....##.....##.##.....##.##..-..##..##...##...##..##.........##.............##...##....####....##.....##.##.....##.##....##..##........##.....##.##....##..##.....##.##.....##.",
   ".##...##..##.....##.##........##.....##.##........##........##........##.....##.....##..........##..##..##....##........####.####.####..##..##.....##.##.....##.##.....##.##.....##.##...........##.....##.....##.##.....##.##..#..##...##.##.....####.........##.............##.....##.....##...........##........##.##....##..##........##............##....##.....##.##.....##.",
   "##.....##.########..##........##.....##.######....######....##...####.#########.....##..........##..#####.....##........##.###.##.##.##.##..##.....##.########..##.....##.########...######......##.....##.....##.##.....##.##.###.##....###.......##.........##..............##.....##.....##.....#######...#######..##....##..#######...########.....##......#######...########.",
   "#########.##.....##.##........##.....##.##........##........##....##..##.....##.....##....##....##..##..##....##........##.....##.##..####..##.....##.##........##..##.##.##...##.........##.....##.....##.....##..##...##..##.###.##...##.##......##........##...............##.....##.....##....##...............##.#########.......##..##.....##...##......##.....##........##.",
   "##.....##.##.....##.##.....##.##.....##.##........##........##....##..##.....##.....##....##....##..##...##...##........##.....##.##...###..##.....##.##........##....##..##....##..##....##.....##.....##.....##...##.##...##.###.##..##...##.....##.......##.................##...##......##....##........##.....##.......##..##....##..##.....##...##......##.....##.##.....##.",
   "##.....##.########...#######..########..########..##.........######...##.....##...######...######...##....##..########..##.....##.##....##...#######..##.........#####.##.##.....##..######......##......#######.....###.....###.###..##.....##....##......########.............#####.....######..#########..#######........##...######....#######....##.......#######...#######..",
};

char        computer [MAX_HEIGHT][MAX_WIDTH] = {
   /*234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-1234567-*/
   "8~~~~~8 8~~~~8  8~~~~~8 8~~~~~8 8~~~~~~ 8~~~~~~ 8~~~~~8 8     8  ~~8~~       8  8    8  8       8~~8~~8 8~~~~~8 8~~~~88 8~~~~~8 8~~~~~8 8~~~~8  8~~~~~8  ~~8~~  8     8 88    8 8  8  8 8    8  8    8  8~~~~~8         eeeeeee   88    eeeeeee eeeeeee  88     eeeeeee eeeeeee eeeeeee eeeeeee eeeeeee ",
   "8     8 8    8  8     ~ 8     8 8       8       8     ~ 8     8    8         8  8   8   8       8  8  8 8     8 8     8 8     8 8     8 8    8  8          8    8     8 88    8 8  8  8  8  8   8    8        8         8     8    8          8       8  88     8       8       8     8 8     8 8     8 ",
   "8eeeee8 8eeee8e 8e      8e    8 8eeee   8eeeee  8e      8eeeee8    8e        8e 8eee8   8e      8e 8  8 8e    8 8     8 8eeeee8 8     8 8eeee8e 8eeeeee    8e   8e    8 88   e8 8e 8  8   ee    8eeee8  eeeeee8         8  8  8    8    eeeeee8 eeeeee8  88  88 8eeeeee 8eee         e' 8eeeee8 eeee  8 ",
   "88    8 88    8 88      88    8 88      88      88   ee 88    8    88        88 88  8   88      88 8  8 88    8 8     8 88      8   e 8 88    8      88    88   88    8 ~8   8  88 8  8   888     88    88              8  8  8    8    e             8  88ee88       8 8  8eee    e'   88   88    8ee8  ",
   "88    8 88    8 88    e 88    8 88      88      88    8 88    8    88   e    88 88   8  88      88 8  8 88    8 8     8 88      8    88 88    8 e    88    88   88    8  8   8  88 8  8  88  8    88    88              8     8   8888  88           88      88      88 8     8  8'     88   88       8  ",
   "88    8 88eeee8 88eeee8 88eeee8 88eeeee 88      88eeee8 88    8  ee88ee 8eeee88 88    8 88eeeee 88 8  8 88    8 8eeeee8 88      8ee8888 88    8 8eeee88    88   88eeee8  8ee8e  88e8ee8 88    8   88    88eeee8         8eeeee8   8888  8eeeeee eeeee88      88 eeeeee8 8eeeee8  8      88eee88 8eeeee8  ",
};


/*---(font metadata)--------*/
typedef struct cFONT tFONT;
tFONT       g_fonts [MAX_FONT] = {
   /*---name-------   ---range---- ---pointer---- tall yoff wide xoff gap */
   { "alligator"    , FONT_NUMS   , &alligator2  ,  7 ,  0 , 10,   2,  0  },
   { "chunky"       , FONT_NUMS   , &chunky      ,  4 ,  0 ,  8,   0,  0  },
   { "goofy"        , FONT_NUMS   , &goofy       ,  5 ,  0 ,  8,   4,  0  },
   { "binary"       , FONT_NUMS   , &binary      ,  2 ,  1 ,  2,   1,  1  },
   { "basic"        , FONT_ALPHA  , &basic       ,  6 ,  1 ,  8,   0,  0  },
   { "dots"         , FONT_BINARY , &dots        ,  3 ,  1 ,  5,   0,  0  },
   { "chunky_full"  , FONT_FULL   , &chunky_full ,  5 ,  0 ,  7,   0,  0  },
   { "banner"       , FONT_FULL   , &banner4     ,  7 ,  0 ,  9,   0,  0  },
   { "computer"     , FONT_FULL   , &computer    ,  6 ,  0 ,  7,   1,  0  },
   { "end-of-fonts" , 0           , NULL         ,  0 ,  0 ,  0,   0,  0  },
};
int         g_nfont       =    0;
int         g_cfont       =   -1;


char
FONT_init            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(count)--------------------------*/
   g_nfont = 0;
   for (i = 0; i < MAX_FONT; ++i) {
      if (g_fonts [i].range == 0)   break;
      ++g_nfont;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
FONT_find            (char *a_font)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_point   ("a_font"    , a_font);
   /*---(find)---------------------------*/
   --rce;  if (a_font == NULL) {
      DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_font"    , a_font);
   /*---(shortcut)-----------------------*/
   DEBUG_GRAF   yLOG_info    ("a_font"    , a_font);
   if (g_cfont >= 0 && g_cfont < g_nfont) {
      if (strcmp (a_font, g_fonts [g_cfont].name) == 0) {
         DEBUG_GRAF   yLOG_note    ("current matches, shortcut used");
         return 0;
      }
   }
   /*---(shortcut)-----------------------*/
   DEBUG_GRAF   yLOG_note    ("does not match current, walk through fonts");
   --rce;
   g_cfont = -1;
   for (i = 0; i < g_nfont; ++i) {
      DEBUG_GRAF   yLOG_bullet  (i           , g_fonts [i].name);
      if (strcmp (a_font, g_fonts [i].name) != 0)  continue;
      DEBUG_GRAF   yLOG_note    ("found");
      g_cfont = i;
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(error)--------------------------*/
   DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char
FONT_index           (char a_range, int a_letter)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_letter    =  '-';
   /*---(prepare)------------------------*/
   DEBUG_GRAF   yLOG_senter (__FUNCTION__);
   x_letter = tolower (a_letter);
   /*---(numeric)------------------------*/
   --rce;  if (a_range == FONT_NUMS) {
      DEBUG_GRAF   yLOG_snote  ("number-type");
      if (strchr ("0123456789", x_letter) != NULL) {
         DEBUG_GRAF   yLOG_sint   (x_letter - '0');
         return x_letter - '0';
      }
      DEBUG_GRAF   yLOG_snote  ("out of range [0-9]");
      DEBUG_GRAF   yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(alpha)--------------------------*/
   --rce;  if (a_range == FONT_ALPHA) {
      DEBUG_GRAF   yLOG_snote  ("alpha-type");
      if (strchr ("abcdefghijklmnopqrstuvwxyz ", x_letter) == NULL) {
         if (x_letter == ' ')  x_letter = 'z' + 1;
         DEBUG_GRAF   yLOG_sint   (x_letter - 'a');
         return x_letter - 'a';
      }
      DEBUG_GRAF   yLOG_snote  ("out of range [a-z]");
      DEBUG_GRAF   yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(full)---------------------------*/
   --rce;  if (a_range == FONT_FULL) {
      DEBUG_GRAF   yLOG_snote  ("full-type");
      if (strchr ("abcdefghijklmnopqrstuvwxyz ", x_letter) == NULL) {
         if (x_letter == ' ')  x_letter = 'z' + 1;
         DEBUG_GRAF   yLOG_sint   (x_letter - 'a');
         return x_letter - 'a';
      }
      if (strchr ("0123456789", x_letter) != NULL) {
         DEBUG_GRAF   yLOG_sint   (x_letter - '0');
         return x_letter - '0' + 27;
      }
      DEBUG_GRAF   yLOG_snote  ("out of range [a-z0-9]");
      DEBUG_GRAF   yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(full)---------------------------*/
   --rce;  if (a_range == 'b') {
      DEBUG_GRAF   yLOG_snote  ("binary-type");
      if (strchr (" .", x_letter) != NULL) {
         DEBUG_GRAF   yLOG_sint   (x_letter - '0');
         if (x_letter == ' ')   return  0;
         if (x_letter == '.')   return  1;
      }
      DEBUG_GRAF   yLOG_snote  ("out of range [0-1]");
      DEBUG_GRAF   yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(unknown)------------------------*/
   --rce;
   DEBUG_GRAF   yLOG_snote  ("font type unknown");
   DEBUG_GRAF   yLOG_sexitr (__FUNCTION__, rce);
   return rce;
}

char
FONT_letter          (char *a_font, char a_num, int a_y, int a_x)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *x_ptr       =    0;
   char        x_range     =    0;
   int         x_tall      =    0;
   int         x_yoff      =    0;
   int         x_wide      =    0;
   int         x_gap       =    0;
   int         x_row       =    0;
   int         x_col       =    0;
   char        x_spot      =    0;
   char        x_msg       [200]       = "";
   /*---(begin)--------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_point   ("a_font"    , a_font);
   DEBUG_GRAF   yLOG_char    ("a_num"     , a_num);
   DEBUG_GRAF   yLOG_value   ("a_y"       , a_y);
   DEBUG_GRAF   yLOG_value   ("a_x"       , a_x);
   /*---(defense)------------------------*/
   --rce;  if (a_font == NULL) {
      DEBUG_GRAF   yLOG_note    ("font can not be null");
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   DEBUG_GRAF   yLOG_note    ("find font");
   rc = FONT_find (a_font);
   DEBUG_GRAF   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(font values)--------------------*/
   DEBUG_GRAF   yLOG_note    ("gather font settings");
   x_range  = g_fonts [g_cfont].range;
   x_ptr    = g_fonts [g_cfont].ptr;
   x_tall   = g_fonts [g_cfont].tall;
   x_wide   = g_fonts [g_cfont].wide;
   x_gap    = g_fonts [g_cfont].gap;
   /*---(index)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("get letter index");
   rc = FONT_index (x_range, a_num);
   DEBUG_GRAF   yLOG_value   ("rc"        , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update issue)-------------------*/
   for (x_row = 0; x_row < x_tall ; ++x_row) {
      for (x_col = 0; x_col < x_wide; ++x_col) {
         x_spot = *(x_ptr  + (x_row * 300) + ((rc * (x_wide + x_gap)) + x_col));
         sprintf (x_msg, "%c", x_spot);
         mvprintw (a_y + x_row, a_x + x_col,  "%s", x_msg);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit  (__FUNCTION__);
   return 0;
}


/*============================[[    end-code    ]]============================*/
