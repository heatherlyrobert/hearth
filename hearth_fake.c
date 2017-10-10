/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"


char       *s_modes     = "tsih";   /* valid fake_door modes                  */
char       *s_error     = "((error))";


char
FAKE_setup           (char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);

   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FAKE_clear           (char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);

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
   DEBUG_INPT   yLOG_info    ("s_modes"   , s_modes);
   --rce;  if (strchr (s_modes, a_mode) == NULL) {
      DEBUG_INPT   yLOG_note    ("a_mode does not in expected set");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_note    ("all defenses passed");
   /*---(display hint)-------------------*/
   if (a_mode == FAKE_HINT) {
      DEBUG_INPT   yLOG_note    ("display hint");
      mvprintw ( 7,  0,  "%s", a_hint);
   }
   /*---(gather input)-------------------*/
   --rce;
   while (1) {
      DEBUG_INPT   yLOG_value   ("x_loop"    , x_loop);
      /*---(get character)---------------*/
      if (x_rc >= 0) {
         if (a_mode != FAKE_TEST) {
            DEBUG_INPT   yLOG_note    ("interactive mode, get character from user");
            x_ch = getch ();
         } else {
            DEBUG_INPT   yLOG_note    ("test mode, get character from input string");
            x_ch = a_hint [x_loop];
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
FAKE_check           (char a_mode, char *a_input, char *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);
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
   DEBUG_INPT   yLOG_info    ("s_modes"   , s_modes);
   --rce;  if (strchr (s_modes, a_mode) == NULL) {
      DEBUG_INPT   yLOG_note    ("a_mode does not in expected set");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_note    ("all defenses passed");
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FAKE_tarpit          (char a_mode, char *a_input, int *a_points)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_rc        =    0;
   char        x_prompt      [100]       = "";
   char        x_loop      =    0;
   char        x_tries     =    1;
   int         x_ch        =    0;
   int         x_len       =    0;
   int         i           =    0;
   int         x_points    =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_INPT   yLOG_char    ("a_mode"    , a_mode);
   DEBUG_INPT   yLOG_point   ("a_input"   , a_input);
   /*---(defense)------------------------*/
   --rce;  if (a_input == NULL) {
      DEBUG_INPT   yLOG_note    ("a_input can not be null");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_input);
   DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
   DEBUG_INPT   yLOG_info    ("s_modes"   , s_modes);
   --rce;  if (strchr (s_modes, a_mode) == NULL) {
      DEBUG_INPT   yLOG_note    ("a_mode does not in expected set");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(gather input)-------------------*/
   --rce;
   while (1) {
      DEBUG_INPT   yLOG_value   ("x_loop"    , x_loop);
      ++x_loop;
      /*---(prompt)-------------------------*/
      if (a_mode != FAKE_TEST && a_mode != FAKE_SILENT) {
         DEBUG_INPT   yLOG_note    ("show tarpit message");
         sprintf (x_prompt, "cluster (%02d) host <%s> login: %s", dev_num, my.host_name, a_input);
         mvprintw ( 0,  0,  "%s", x_prompt);
         for (i = 1; i < x_tries; ++i) {
            mvprintw ( i,  0,  "password: access denied (%d)", i);
         }
         if (x_tries < 5)  mvprintw ( x_tries,  0,  "password:");
         else              mvprintw ( x_tries,  0,  "password: account locked, contact system admin");
      }
      /*---(get character)---------------*/
      if (a_mode != FAKE_TEST) {
         DEBUG_INPT   yLOG_note    ("interactive mode, get character from user");
         x_ch = getch ();
      } else {
         DEBUG_INPT   yLOG_note    ("test mode, no input collected");
         if (x_loop < x_len)  x_ch = a_input [x_loop];
         else                 x_ch = ' ';
      }
      DEBUG_INPT   yLOG_value   ("x_ch"      , x_ch);
      /*---(check special chars)---------*/
      if (x_ch   == K_ESCAPE) {
         DEBUG_INPT   yLOG_note    ("escape, exit before completion");
         if (x_rc == 0)  x_rc = rce - 1;
         ++x_tries;
         if (a_mode != FAKE_TEST && a_mode != FAKE_SILENT)  sleep (1);
      }
      if (x_ch   == K_RETURN) {
         DEBUG_INPT   yLOG_note    ("return, input complete");
         if (x_rc == 0)  x_rc = rce - 2;
         ++x_tries;
         if (a_mode != FAKE_TEST && a_mode != FAKE_SILENT)  sleep (1);
      }
      /*---(timeout)---------------------*/
      if (a_mode != FAKE_TEST && a_mode != FAKE_SILENT)  usleep ( 100000);
      if (x_loop > 50) {
         DEBUG_INPT   yLOG_note    ("x_loop > 50, done");
         if (x_rc == 0)  x_rc = rce - 3;
         break;
      }
      if (x_tries > 5) {
         DEBUG_INPT   yLOG_note    ("x_tries > 5, done");
         if (x_rc == 0)  x_rc = rce - 4;
         break;
      }
      /*---(done)------------------------*/
   }
   x_points = x_loop + (x_tries * 100);
   /*---(freeze)-------------------------*/
   rce -= 10;
   DEBUG_INPT   yLOG_note    ("freezing to waste user time");
   if (a_mode != FAKE_TEST && a_mode != FAKE_SILENT) {
      mvprintw ( 1 + x_tries,  0,  "suspicious activity, console locked, administrator notified");
      sleep (60);
   }
   x_points += 1000;
   if (a_points != NULL)  *a_points = x_points;
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

   /*> char        ch          = ' ';                                                 <* 
    *> char        part        = '#';                                                 <* 
    *> char        status      = '-';                                                 <* 
    *> int         loop        = 0;                                                   <* 
    *> int         secs        = 0;                                                   <* 
    *> int         count       = 0;                                                   <* 
    *> int         pos_x       = 0;                                                   <* 
    *> char        prompt      [100]       = "";                                      <*/
   /*---(check initial character)--------*/
   sprintf (x_key, "%c%c%c", my.host_name[0], my.host_name[5], my.host_name[2]);
   DEBUG_INPT   yLOG_info    ("x_key"     , x_key);
   rc = FAKE_collect (FAKE_USER, x_input, x_key);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   if (rc <  0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_INPT   yLOG_info    ("x_input"   , x_input);
   rc = FAKE_check   (FAKE_USER, x_input, x_key);
   DEBUG_INPT   yLOG_value   ("rc"        , rc);
   if (rc >= 0) {
      DEBUG_INPT   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   rc = FAKE_tarpit  (FAKE_USER, ""     , NULL);
   DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rc);
   return rc;

   /*> mvprintw ( 7,  0,  "%s", x_hint);                                                <*/
   /*> loop    = 0;                                                                               <* 
    *> while (1) {                                                                                <* 
    *>    ch = getch ();                                                                          <* 
    *>    if (ch ==  -1 )   break;                                                                <* 
    *>    if (ch == '\n')   break;                                                                <* 
    *>    if (loop < 20)  {                                                                       <* 
    *>       x_input [loop    ] = ch;                                                             <* 
    *>       x_input [loop + 1] = '\0';                                                           <* 
    *>    }                                                                                       <* 
    *>    ++loop;                                                                                 <* 
    *> }                                                                                          <* 
    *> /+> mvprintw ( 8,  0,  "%s", x_input);                                               <+/   <* 
    *> if (strcmp (x_hint, x_input) == 0) {                                                       <* 
    *>    part   = 'D';                                                                           <* 
    *>    status = 'A';                                                                           <* 
    *> } else {                                                                                   <* 
    *>    /+---(prompt)-------------------------+/                                                <* 
    *>    sprintf (prompt, "cluster (%02d) host <%s> login: %s", dev_num, my.host_name, x_input);    <* 
    *>    mvprintw ( 0,  0,  "%s", prompt);                                                       <* 
    *>    sprintf (prompt, "password: ");                                                         <* 
    *>    mvprintw ( 1,  0,  "%s", prompt);                                                       <* 
    *>    pos_x = strlen (prompt);                                                                <* 
    *>    /+---(loop through input)-------------+/                                                <* 
    *>    loop    = 0;                                                                            <* 
    *>    secs    = 0;                                                                            <* 
    *>    part    = 'Z';                                                                          <* 
    *>    status  = 'F';                                                                          <* 
    *>    while (1) {                                                                             <* 
    *>       /+---(get next character)----------+/                                                <* 
    *>       ch = getch ();                                                                       <* 
    *>       /+---(timeout)---------------------+/                                                <* 
    *>       ++loop;                                                                              <* 
    *>       if (loop % 5 == 0) ++secs;                                                           <* 
    *>       if ( secs >  15) {                                                                   <* 
    *>          sleep (5);                                                                        <* 
    *>          break;                                                                            <* 
    *>       }                                                                                    <* 
    *>       /+---(enter)-----------------------+/                                                <* 
    *>       if (ch == '\n') {                                                                    <* 
    *>          sleep (5);                                                                        <* 
    *>          break;                                                                            <* 
    *>       }                                                                                    <* 
    *>       /+---(wait for next)---------------+/                                                <* 
    *>       ++count;                                                                             <* 
    *>       usleep ( 100000);                                                                    <* 
    *>    }                                                                                       <* 
    *> }                                                                                          <* 
    *> /+---(complete)-----------------------+/                                                   <* 
    *> if (status == 'A')  return 0;                                                              <* 
    *> return -5;                                                                                 <*/
} /*======================================================*/

