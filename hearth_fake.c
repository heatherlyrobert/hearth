/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"


/*---(general)--------------*/
char       *s_error     = "((error))";
char        s_blocked     [100]       = "";
/*---(tarpit)---------------*/
int         s_warn      =  300;
int         s_max       =  900;
char       *s_secret    = "bung";
int         s_match     =    0;


char
FAKE_init            (char a_mode, char *a_user)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_input       [100]       = "";
   char        x_prompt      [100]       = "";
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);
   /*---(create blocked)-----------------*/
   x_len = (rand () % 6) + 6;
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   for (i = 0; i < x_len; ++i) {
      s_blocked [i    ] = '*';
      s_blocked [i + 1] = '\0';
   }
   DEBUG_INPT   yLOG_info    ("s_blocked" , s_blocked);
   /*---(push user info stdin)-----------*/
   x_len = strlen (a_user);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   if (x_len > 0) {
      ungetch ('\n');
      for (i = x_len - 1; i >= 0; --i) {
         ungetch (a_user [i]);
      }
   }
   /*---(check host name)----------------*/
   DEBUG_INPT   yLOG_info    ("host_name" , my.host_name);
   if (strcmp (my.host_name, "") == 0) {
      strlcpy (my.host_name, "#96.chess_master", LEN_DESC);
      DEBUG_INPT   yLOG_info    ("host_name" , my.host_name);
   }
   IF_A_RUN_REAL {
      DEBUG_INPT   yLOG_note    ("showing prompt in real mode");
      sprintf  (x_prompt, "cluster (%02d) host <%s> login: %s", 42, my.host_name, s_blocked);
      mvprintw ( 0,  0,  "%s", x_prompt);
      refresh  ();
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FAKE_collect         (char a_mode, char *a_input, char *a_hint)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_loop      =    0;
   int         x_ch        =  ' ';
   char        x_rc        =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_INPT   yLOG_point   ("a_input"   , a_input);
   DEBUG_INPT   yLOG_point   ("a_hint"    , a_hint);
   /*---(defense)------------------------*/
   --rce;  if (a_input == NULL) {
      DEBUG_INPT   yLOG_note    ("a_input can not be null");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_input, s_error, LEN_DESC);
   DEBUG_INPT   yLOG_info    ("a_input"   , a_input);
   --rce;  if (a_hint  == NULL) {
      DEBUG_INPT   yLOG_note    ("a_hint can not be null");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_hint"    , a_hint);
   DEBUG_INPT   yLOG_info    ("g_modes"   , g_modes);
   --rce;  if (strchr (g_modes, a_mode) == NULL) {
      DEBUG_INPT   yLOG_note    ("a_mode does not in expected set");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_note    ("all defenses passed");
   /*---(display hint)-------------------*/
   if (a_mode == RUN_HINT) {
      DEBUG_INPT   yLOG_note    ("display hint");
      mvprintw ( 7,  0,  "%s", a_hint);
   }
   /*---(gather input)-------------------*/
   --rce;
   while (1) {
      DEBUG_INPT   yLOG_value   ("x_loop"    , x_loop);
      /*---(get character)---------------*/
      if (x_rc >= 0) {
         IF_A_RUN_STRING {
            DEBUG_INPT   yLOG_note    ("test mode, get character from input string");
            x_ch = a_hint [x_loop];
         } else {
            DEBUG_INPT   yLOG_note    ("interactive mode, get character from user");
            x_ch = getch ();
         }
      } else {
         DEBUG_INPT   yLOG_note    ("silent failure, input assigned space");
         x_ch = ' ';
      }
      DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
      /*---(check special chars)---------*/
      if (x_ch   == K_ESCAPE) {
         DEBUG_INPT   yLOG_note    ("escape, exit before completion");
         x_rc = rce;
         break;
      }
      if (x_ch   == K_RETURN) {
         DEBUG_INPT   yLOG_note    ("return, input complete");
         break;
      }
      if (x_ch   == K_NULL  ) {
         DEBUG_INPT   yLOG_note    ("end of input with no return, terminate");
         x_rc = rce - 1;
         break;
      }
      if (x_ch   == -1) {
         DEBUG_INPT   yLOG_note    ("error, input terminated");
         x_rc = rce - 2;
         break;
      }
      /*---(prepare)---------------------*/
      ++x_loop;
      /*---(limits)----------------------*/
      if (x_loop >= 25)  {
         DEBUG_INPT   yLOG_note    ("way too many characters, terminate");
         break;
      }
      if (x_rc <   0)  {
         DEBUG_INPT   yLOG_note    ("already in error mode, silently ignore");
         continue;
      }
      if (x_loop >=  5)  {
         DEBUG_INPT   yLOG_note    ("too many characters, input ignored silently");
         x_rc = rce - 3;
         continue;
      }
      if (x_ch < K_SPACE)  {
         DEBUG_INPT   yLOG_note    ("unknown special character, input ignored silently");
         x_rc = rce - 4;
         continue;
      }
      /*---(process character)-----------*/
      a_input [x_loop - 1] = x_ch;
      a_input [x_loop    ] = '\0';
      DEBUG_INPT   yLOG_info    ("a_input"   , a_input);
      /*---(done)------------------------*/
   }
   /*---(final defense)------------------*/
   DEBUG_INPT   yLOG_info    ("a_input"   , a_input);
   x_len = strlen (a_input);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   rce -= 10;  if (x_rc >= 0 && (x_len < 1 || strcmp (a_input, s_error) == 0)) {
      DEBUG_INPT   yLOG_note    ("return only input string, terminate");
      x_rc  = rce;
   }
   /*---(check return code)--------------*/
   DEBUG_INPT   yLOG_value   ("x_rc"      , x_rc);
   --rce;  if (x_rc < 0) {
      strlcpy (a_input, s_error, LEN_DESC);
      DEBUG_INPT   yLOG_note    ("ended in error status");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return x_rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FAKE_check           (char *a_input, char *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_point   ("a_input"   , a_input);
   DEBUG_INPT   yLOG_point   ("a_key"     , a_key);
   /*---(defense)------------------------*/
   --rce;  if (a_input == NULL) {
      DEBUG_INPT   yLOG_note    ("a_input can not be null");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_input"   , a_input);
   --rce;  if (a_key == NULL) {
      DEBUG_INPT   yLOG_note    ("a_key can not be null");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_info    ("a_key"     , a_key);
   /*---(check)--------------------------*/
   --rce;  if (strcmp (a_input, a_key) != 0) {
      DEBUG_INPT   yLOG_note    ("input does not match key");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_note    ("perfect match");
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FAKE_prompt          (int a_tries, int a_loops, int a_chars)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        x_prompt      [100]       = "";
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_senter  (__FUNCTION__);
   /*---(primary)------------------------*/
   DEBUG_INPT   yLOG_snote   ("show tarpit message");
   sprintf (x_prompt, "cluster (%02d) host <%s> login: %s", my.dev_num, my.host_name, s_blocked);
   mvprintw ( 0,  0,  "%s", x_prompt);
   /*---(secondary)----------------------*/
   for (i = 1; i < a_tries; ++i) {
      mvprintw ( i,  0,  "password: access denied");
   }
   if (a_tries > 5) {
      mvprintw ( a_tries,  0,  "account locked, please contact help desk for assistance");
   } else if (a_loops <= s_warn) {
      mvprintw ( a_tries,  0,  "password:");
   }
   if (a_loops > s_warn) {
      mvprintw ( 1 + a_tries,  0,  "suspicious activity, console locked out, SECOPS notified");
   }
   /*---(debugging)----------------------*/
   SHOW_COUNTERS {
      sprintf (x_prompt, "a_loops  = %3d", a_loops);
      mvprintw ( 1, 60,  "%s", x_prompt);
      sprintf (x_prompt, "a_tries  = %3d", a_tries);
      mvprintw ( 2, 60,  "%s", x_prompt);
      sprintf (x_prompt, "a_chars  = %3d", a_chars);
      mvprintw ( 3, 60,  "%s", x_prompt);
      sprintf (x_prompt, "s_secret = %s",  s_secret);
      mvprintw ( 4, 60,  "%s", x_prompt);
      sprintf (x_prompt, "s_match  = %3d", s_match);
      mvprintw ( 5, 60,  "%s", x_prompt);
   }
   /*---(show)---------------------------*/
   refresh ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
FAKE_tarpit          (char a_mode, char *a_input, int *a_pts)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_rc        =    0;
   char        x_prompt      [100]       = "";
   int         x_loop      =    0;
   char        x_tries     =    1;
   int         x_ch        =    0;
   int         x_chars     =    0;
   int         x_len       =    0;
   int         i           =    0;
   int         x_points    =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_INPT   yLOG_point   ("a_input"   , a_input);
   DEBUG_INPT   yLOG_point   ("a_pts"     , a_pts);
   /*---(defense)------------------------*/
   if (a_pts != NULL)  *a_pts = 0;
   --rce;  if (a_input == NULL) {
      DEBUG_INPT   yLOG_note    ("a_input can not be null");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_input);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   DEBUG_INPT   yLOG_info    ("g_modes"   , g_modes);
   --rce;  if (strchr (g_modes, a_mode) == NULL) {
      DEBUG_INPT   yLOG_note    ("a_mode does not in expected set");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(gather input)-------------------*/
   --rce;
   while (1) {
      DEBUG_INPT   yLOG_value   ("x_loop"    , x_loop);
      DEBUG_INPT   yLOG_value   ("x_tries"   , x_tries);
      ++x_loop;
      /*---(prompt)-------------------------*/
      IF_A_RUN_REAL  FAKE_prompt (x_tries, x_loop, x_chars);
      /*---(timeout)---------------------*/
      if (x_loop > s_max) {
         DEBUG_INPT   yLOG_note    ("x_loop > s_max, done");
         if (x_rc == 0)  x_rc = rce - 3;
         break;
      }
      /*---(get character)---------------*/
      IF_A_RUN_STRING {
         DEBUG_INPT   yLOG_note    ("unit/force mode, no input collected");
         if (x_loop <= x_len)  x_ch = a_input [x_loop - 1];
         else                  x_ch = ' ';
      } else {
         DEBUG_INPT   yLOG_note    ("interactive mode, get character from user");
         x_ch = getch ();
      }
      if (x_ch == -1) {
         DEBUG_INPT   yLOG_note    ("no input, short sleep");
         IF_A_RUN_REAL  usleep ( 100000);
         continue;
      }
      /*---(check special chars)---------*/
      ++x_chars;
      if (x_tries <= 5) {
         if (x_ch   == K_ESCAPE) {
            DEBUG_INPT   yLOG_note    ("escape, exit before completion");
            if (x_rc == 0)  x_rc = rce - 1;
            if (x_tries <= 5)  ++x_tries;
            IF_A_RUN_REAL   sleep (1);
            s_match = 0;
         }
         if (x_ch   == K_RETURN) {
            DEBUG_INPT   yLOG_note    ("return, input complete");
            if (x_rc == 0)  x_rc = rce - 2;
            if (x_tries <= 5)  ++x_tries;
            IF_A_RUN_REAL   sleep (1);
            s_match = 0;
         }
      }
      if (x_ch >= 32 && x_ch <= 126) {
         DEBUG_INPT   yLOG_char    ("x_ch"      , x_ch);
         if (x_ch == s_secret [s_match])  ++s_match;
         else                             s_match = 0;
         if (s_match == strlen (s_secret))  break;
      } else {
         DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
      }
      /*---(done)------------------------*/
   }
   x_points = x_loop + (x_tries * 1000);
   if (a_pts != NULL)  *a_pts = x_points;
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return x_rc;
}

char         /*--> fake lead door ------------------------[ leaf   [ ------ ]-*/
FAKE_door          (void)
{
   /*---(design notes)-------------------*/
   /*
    *  this is a simplistic test to enter the true login screen, but its a
    *  little good as it requires reading the prompt and responding.
    *
    *  all the charcters would already be in the buffer as hestia doesn't pass
    *  control until a newline is entered.
    *
    *  four letter string is expected...
    *      1) # (hash)
    *      2) second letter of host name
    *      3) second number of host number
    *      4) enter key
    *
    */
   /*---(begin)--------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(locals)-----------+-----+-----+-*/
   char        x_key       [100]       = "";
   char        x_input     [100]       = "";
   char        rc          =    0;
   /*---(setup)--------------------------*/
   DEBUG_INPT   yLOG_info    ("fake_user" , my.fake_user);
   rc = FAKE_init    (my.run_mode, my.fake_user);
   sprintf (x_key, "%c%c%c", my.host_name[0], my.host_name[5], my.host_name[2]);
   DEBUG_INPT   yLOG_info    ("x_key"     , x_key);
   /*---(collect input)------------------*/
   rc = FAKE_collect (my.run_mode, x_input, x_key);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   if (rc <  0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_INPT   yLOG_info    ("x_input"   , x_input);
   /*---(check input)--------------------*/
   rc = FAKE_check   (x_input, x_key);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   if (rc >= 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(fall into tarpit)---------------*/
   rc = FAKE_tarpit  (my.run_mode, ""     , NULL);
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}

