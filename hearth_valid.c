/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"




/*> if      (a_type == 'Z')   strcpy (msg, "timed_out");                           <* 
 *> else if (a_type == 'B')   strcpy (msg, "cancelled");                           <* 
 *> else if (a_type == 'k')   strcpy (msg, "knock");                               <* 
 *> else if (a_type == 'p')   strcpy (msg, "prefix");                              <* 
 *> else if (a_type == 'u')   strcpy (msg, "user_name");                           <* 
 *> else if (a_type == 'I')   strcpy (msg, "user_name");                           <* 
 *> else if (a_type == 'i')   strcpy (msg, "infix");                               <* 
 *> else if (a_type == 'c')   strcpy (msg, "password");                            <* 
 *> else if (a_type == 'S')   strcpy (msg, "password");                            <* 
 *> else if (a_type == 's')   strcpy (msg, "suffix");                              <* 
 *> else                      strcpy (msg, "failure");                             <*/


char         /*-> create values for magic number -------[ ------ [ -------- ]-*/
valid__magic         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         x_row       =    0;
   int         x_one       =    0;
   int         x_two       =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(lefts)--------------------------*/
   for (i = 0; i < MAX_LEFTS; ++i)      g_vals.lefts [i] = (rand () % 10) + '0';
   for (i = 2; i < MAX_LEFTS; i += 3)   g_vals.lefts [i] = '¦';
   g_vals.lefts  [MAX_LEFTS - 1] = '\0';
   /*> my.magic_num [ 0] = g_vals.lefts  [13];                                        <*/
   /*> my.magic_num [ 1] = g_vals.lefts  [ 1];                                        <*/
   /*> my.magic_num [ 2] = g_vals.lefts  [ 6];                                        <*/
   /*---(knocks)-------------------------*/
   for (i = 0; i < MAX_KNOCKS; ++i)     g_vals.knocks [i] = (rand () %  2 == 0) ? '0' : '1';
   switch (g_vals.noks_gap) {
   case 0 :
      for (i = 1; i < MAX_KNOCKS; i += 2)  g_vals.knocks [i] = '¦';
      x_one =  2;
      x_two =  6;
      break;
   case 1 :
      for (i = 1; i < MAX_KNOCKS; i += 4)  g_vals.knocks [i] = '¦';
      for (i = 2; i < MAX_KNOCKS; i += 4)  g_vals.knocks [i] = ' ';
      for (i = 3; i < MAX_KNOCKS; i += 4)  g_vals.knocks [i] = '¦';
      x_one =  4;
      x_two = 12;
      break;
   case 2 :
      for (i = 1; i < MAX_KNOCKS; i += 6)  g_vals.knocks [i] = '¦';
      for (i = 2; i < MAX_KNOCKS; i += 6)  g_vals.knocks [i] = ' ';
      for (i = 3; i < MAX_KNOCKS; i += 6)  g_vals.knocks [i] = '¦';
      for (i = 4; i < MAX_KNOCKS; i += 6)  g_vals.knocks [i] = ' ';
      for (i = 5; i < MAX_KNOCKS; i += 6)  g_vals.knocks [i] = '¦';
      x_one =  6;
      x_two = 18;
      break;
   }
   g_vals.knocks [MAX_KNOCKS - 1] = '\0';
   DEBUG_TOPS   yLOG_info    ("knocks"    , g_vals.knocks);
   /*> my.magic_num [ 3] = g_vals.knocks [x_one];                                     <*/
   /*> my.magic_num [ 4] = g_vals.knocks [MAX_KNOCKS / 2 + x_one];                    <*/
   /*> my.magic_num [ 5] = g_vals.knocks [MAX_KNOCKS / 2 + x_two];                    <*/
   /*> my.magic_num [ 6] = g_vals.knocks [x_two];                                     <*/
   /*---(mids)---------------------------*/
   for (i = 0; i < MAX_MIDS; i += 2) {
      g_vals.mids   [i + 0] = (rand () % 26) + 'a';
      g_vals.mids   [i + 1] = (rand () % 10) + '0';
   }
   my.rot     = (rand () % 4) + 1;
   my.pointer = (rand () % 4) + 1;
   g_vals.mids   [MAX_MIDS - 1] = '\0';
   /*> g_vals.mids   [ 5]               = my.magic_num [7] = my.rot + '0';            <*/
   /*> g_vals.mids   [MAX_MIDS / 2 + 3] = my.magic_num [8] = my.pointer + '0';        <*/
   /*---(rights)-------------------------*/
   for (i = 0; i < MAX_RIGHTS; ++i)     g_vals.rights [i] = (rand () % 10) + '0';
   for (i = 3; i < MAX_RIGHTS; i += 4)  g_vals.rights [i] = '¦';
   g_vals.rights [MAX_RIGHTS - 1] = '\0';
   x_row = my.pointer * 4;
   /*> my.magic_num [ 9] = g_vals.rights [x_row + 0];                                 <*/
   /*> my.magic_num [10] = g_vals.rights [x_row + 1];                                 <*/
   /*> my.magic_num [11] = g_vals.rights [x_row + 2];                                 <*/
   /*---(complete)-----------------------*/
   /*> my.magic_num  [12] = '\0';                                                     <*/
   DEBUG_TOPS   yLOG_info    ("magic_num" , my.magic_num);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
valid_init              (void)
{
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(user/pass)----------------------*/
   strlcpy (my.username, "", LEN_STR);
   strlcpy (my.password, "", LEN_STR);
   /*---(looping)------------------------*/
   my.loops   = 0;
   my.secs    = 0;
   my.chars   = 0;
   my.curr    = '·';
   /*---(input)--------------------------*/
   strlcpy (my.entry_text , "", LEN_DESC);
   /*---(status)-------------------------*/
   my.status = STATUS_GOOD;
   my.part   = PART_KNOCK;
   /*---(complete)-----------------------*/
   valid__magic    ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
valid__complete         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_which     =  '-';
   char        x_msg       [LEN_RECD];
   int         x_len       =    0;
   /*---(deal with rc)-------------------*/
   DEBUG_LOOP   yLOG_char   ("status"    , my.status);
   switch (my.status) {
   case STATUS_SUCCESS  :
      DEBUG_LOOP   yLOG_note   ("successful login");
      x_which = YSTR_PASSED;
      break;
   case STATUS_REFRESH :
      DEBUG_LOOP   yLOG_note   ("triggered a screen refresh");
      x_which = YSTR_REFRESH;
      break;
   case STATUS_TIMEOUT  :
      DEBUG_LOOP   yLOG_note   ("login timed out");
      x_which = YSTR_TIMEOUT;
      break;
   case STATUS_BREAK   :
      DEBUG_LOOP   yLOG_note   ("login cancelled");
      x_which = YSTR_CANCEL;
      break;
   case STATUS_NEWLINE :
      DEBUG_LOOP   yLOG_note   ("login failed");
      x_which = YSTR_FAILURE;
      break;
   default            :
      DEBUG_LOOP   yLOG_note   ("unknown failure");
      x_which = YSTR_FAILURE;
      break;
   }
   /*---(show message)-------------------*/
   rc = ySTR_word  (my.language, x_which, x_msg);
   show_message (x_msg);
   /*---(log true failures)--------------*/
   if (my.status != STATUS_REFRESH) {
      rc = audit_fail (my.dev, my.part);
      DEBUG_LOOP   yLOG_value  ("audit"     , rc);
      rc = ySEC_failed (my.dev + 5, my.user_fix);
      DEBUG_LOOP   yLOG_value  ("ysec"      , rc);
   }
   /*---(delay)--------------------------*/
   if (my.status == STATUS_SUCCESS)  sleep (1);
   else                              sleep (8);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit   (__FUNCTION__);
   return 0;
}

char         /*--> validate the knock ----------------------------------------*/
valid__knock            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   if (my.part != PART_KNOCK) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check input)--------------------*/
   DEBUG_USER   yLOG_value   ("my.chars"  , my.chars);
   switch (my.chars) {
   case  4 :
      DEBUG_USER   yLOG_char    ("entry [3]" , my.entry_text [3]);
      x_ch = my.entry_text [3];
      if (x_ch == '·')  x_ch = '0';
      else              x_ch = '1';
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [6]" , my.magic_num  [6]);
      if (x_ch != my.magic_num [6])  my.status = STATUS_FAILED;
   case  3 :
      DEBUG_USER   yLOG_char    ("entry [2]" , my.entry_text [2]);
      x_ch = my.entry_text [2];
      if (x_ch == '·')  x_ch = '0';
      else              x_ch = '1';
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [5]" , my.magic_num  [5]);
      if (x_ch != my.magic_num [5])  my.status = STATUS_FAILED;
   case  2 :
      DEBUG_USER   yLOG_char    ("entry [1]" , my.entry_text [2]);
      x_ch = my.entry_text [1];
      if (x_ch == '·')  x_ch = '0';
      else              x_ch = '1';
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [4]" , my.magic_num  [4]);
      if (x_ch != my.magic_num [4])  my.status = STATUS_FAILED;
   case  1 :
      DEBUG_USER   yLOG_char    ("entry [0]" , my.entry_text [0]);
      x_ch = my.entry_text [0];
      if (x_ch == '·')  x_ch = '0';
      else              x_ch = '1';
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [3]" , my.magic_num  [3]);
      if (x_ch != my.magic_num [3])  my.status = STATUS_FAILED;
   }
   DEBUG_USER   yLOG_char    ("my.status" , my.status);
   /*---(update part)--------------------*/
   if (my.status == STATUS_GOOD && my.chars == 4) {
      my.part = PART_PREFIX;
   }
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   /*---(ocmplete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__prefix           (void)
{
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   if (my.part != PART_PREFIX) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check input)--------------------*/
   DEBUG_USER   yLOG_value   ("my.chars"  , my.chars);
   switch (my.chars) {
   case  6 :
      if (my.entry_text [5] != my.magic_num [1])  my.status = STATUS_FAILED;
   case  5 :
      if (my.entry_text [4] != my.magic_num [0])  my.status = STATUS_FAILED;
   }
   DEBUG_USER   yLOG_char    ("my.status" , my.status);
   /*---(update part)--------------------*/
   if (my.status == STATUS_GOOD && my.chars == 6) {
      my.part = PART_USERNAME;
   }
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   /*---(ocmplete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__user          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         j           =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("status"    , my.status);
   if (my.status != STATUS_GOOD) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_USER   yLOG_char    ("part"      , my.part);
   if (my.part != PART_USERNAME) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_USER   yLOG_char    ("curr"      , my.curr);
   if (strchr ("· ", my.curr) == NULL) {
      DEBUG_USER   yLOG_note    ("too early to evalute user name");
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(pull user name)-----------------*/
   strcpy (my.username, my.entry_text + 6);
   x_len = strlen (my.username);
   my.username [--x_len] = '\0';
   DEBUG_USER   yLOG_info    ("username"  , my.username);
   /*---(get user name)------------------*/
   DEBUG_USER   yLOG_value   ("x_len"     , x_len);
   if (x_len < 4) {
      DEBUG_USER   yLOG_note    ("length too short (<4)");
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   if (x_len > 15) {
      DEBUG_USER   yLOG_note    ("length too long (>15)");
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   /*---(rotate)-------------------------*/
   for (i = 0; i < x_len; ++i) {
      j = i + my.rot;
      if (j <  x_len) {
         my.user_fix [ j] = my.username [i];
      } else {
         my.user_fix [ j - x_len] = my.username [i];
      }
   }
   my.user_fix [x_len] = '\0';
   DEBUG_USER   yLOG_info    ("user_fix"  , my.user_fix);
   /*---(check for root)-----------------*/
   if (strcmp (my.user_fix, "root") == 0) {
      DEBUG_USER   yLOG_note    ("can not log directly into root");
      strcpy (my.user_fix, "(root)");
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   if (strcmp (my.user_fix, "kurios") == 0) {
      DEBUG_USER   yLOG_note    ("kurios is the alias of root");
      strcpy (my.user_fix, "root");
   }
   DEBUG_USER   yLOG_info    ("user_fix"  , my.user_fix);
   /*---(check)--------------------------*/
   my.pass  = getpwnam (my.user_fix);
   DEBUG_USER   yLOG_point   ("my.pass"   , my.pass);
   if (my.pass == NULL) {
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   my.shad = getspnam (my.user_fix);
   DEBUG_USER   yLOG_point   ("my.shad"   , my.shad);
   if (my.shad == NULL) {
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   /*---(update part)--------------------*/
   my.part   = PART_INFIX;
   my.offset = my.chars;
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__infix            (void)
{
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   if (my.part != PART_INFIX) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check input)--------------------*/
   DEBUG_USER   yLOG_value   ("chars"     , my.chars);
   DEBUG_USER   yLOG_value   ("offset"    , my.offset);
   if (my.entry_text [my.offset] != my.magic_num [2])  my.status = STATUS_FAILED;
   DEBUG_USER   yLOG_char    ("my.status" , my.status);
   /*---(update part)--------------------*/
   if (my.status == STATUS_GOOD) {
      my.part = PART_PASSWORD;
   }
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   /*---(ocmplete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__pass             (void)
{
   /*---(locals)-----------+-----------+-*/
   int         x_len       =    0;
   char       *x_pass      = NULL;
   char       *x_salt      = NULL;
   char       *x_encrypt   = NULL;
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("status"    , my.status);
   if (my.status != STATUS_GOOD) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_USER   yLOG_char    ("part"      , my.part);
   if (my.part != PART_PASSWORD) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_USER   yLOG_char    ("curr"      , my.curr);
   if (strchr ("· ", my.curr) == NULL) {
      DEBUG_USER   yLOG_note    ("too early to evalute password");
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(pull password)------------------*/
   strcpy (my.password, my.entry_text + my.offset + 1);
   x_len = strlen (my.password);
   my.password [--x_len] = '\0';
   DEBUG_USER   yLOG_info    ("password"  , my.password);
   /*---(get user name)------------------*/
   DEBUG_USER   yLOG_value   ("x_len"     , x_len);
   if (x_len < 4) {
      DEBUG_USER   yLOG_note    ("length too short (<4)");
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   if (x_len > 15) {
      DEBUG_USER   yLOG_note    ("length too long (>15)");
      my.status = STATUS_FAILED;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   /*---(password)-----------------------*/
   x_pass    = strdup (my.shad->sp_pwdp);
   DEBUG_USER   yLOG_info    ("x_pass"    , x_pass);
   x_salt    = strdup (my.shad->sp_pwdp);
   DEBUG_USER   yLOG_info    ("x_salt"    , x_salt);
   x_encrypt = crypt (my.password, x_salt);
   DEBUG_USER   yLOG_point   ("x_encrypt" , x_encrypt);
   if (strcmp (x_encrypt, x_pass) != 0) {
      my.status = STATUS_FAILED;
      free (x_pass);
      free (x_salt);
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return my.status;
   }
   /*---(free)---------------------------*/
   free (x_pass);
   free (x_salt);
   /*---(update part)--------------------*/
   my.part   = PART_SUFFIX;
   my.offset = my.chars;
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__suffix           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   if (my.part != PART_SUFFIX) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check input)--------------------*/
   DEBUG_USER   yLOG_value   ("my.chars"  , my.chars);
   switch (my.chars - my.offset) {
   case  3 :
      x_ch = my.entry_text [my.offset + 2];
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [11]", my.magic_num  [11]);
      if (x_ch != my.magic_num [11])  my.status = STATUS_FAILED;
   case  2 :
      x_ch = my.entry_text [my.offset + 1];
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [10]", my.magic_num  [10]);
      if (x_ch != my.magic_num [10])  my.status = STATUS_FAILED;
   case  1 :
      x_ch = my.entry_text [my.offset + 0];
      DEBUG_USER   yLOG_char    ("x_ch"      , x_ch);
      DEBUG_USER   yLOG_char    ("magic [ 9]", my.magic_num  [ 9]);
      if (x_ch != my.magic_num [ 9])  my.status = STATUS_FAILED;
   }
   DEBUG_USER   yLOG_char    ("my.status" , my.status);
   /*---(update part)--------------------*/
   if (my.chars == my.offset + 3 && my.status == STATUS_GOOD) {
      my.part = PART_DONE;
   }
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   /*---(ocmplete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__done             (void)
{
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   if (my.part != PART_DONE) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check input)--------------------*/
   DEBUG_USER   yLOG_value   ("chars"     , my.chars);
   DEBUG_USER   yLOG_value   ("offset"    , my.offset);
   if (my.entry_text [my.offset + 3] != '¥')  my.status = STATUS_FAILED;
   DEBUG_USER   yLOG_char    ("my.status" , my.status);
   /*---(update part)--------------------*/
   if (my.status == STATUS_GOOD) {
      my.status = STATUS_SUCCESS;
      my.part   = PART_TRAILING;
   }
   DEBUG_USER   yLOG_char    ("my.part"   , my.part);
   /*---(ocmplete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char         /*-> get character from ncurses ---------------------------------*/
valid__getchar          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_ch        =    0;
   char        t           [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   /*---(get character)---------------*/
   while (1) {
      /*---(timers)----------------------*/
      ++my.loops;
      if (my.loops > 9999)  my.loops = 5001;
      if (my.secs > 9999)  my.secs = 5001;
      DEBUG_USER   yLOG_value   ("my.loops"    , my.loops);
      if (my.loops % 5 == 0) ++my.secs;
      DEBUG_USER   yLOG_value   ("my.secs"    , my.secs);
      DEBUG_USER   yLOG_value   ("my.timeout" , my.timeout);
      /*---(timeout)---------------------*/
      if (my.secs > my.timeout) {
         DEBUG_USER   yLOG_note    ("my.secs timed out");
         my.status = STATUS_TIMEOUT;
         break;
      }
      /*---(always wait)-----------------*/
      if (my.run_mode != RUN_UNIT) {
         /*> DEBUG_USER   yLOG_note    ("insert a input delay, hacker proofing");     <*/
         usleep ( 100000); /* 0.1sec */
      }
      /*---(get character)---------------*/
      x_ch = getch ();
      my.curr = x_ch;
      DEBUG_USER   yLOG_value   ("x_ch"      , x_ch);
      /*---(show screen)-----------------*/
      show_timer  ();
      refresh     ();
      /*---(didn't get a character)------*/
      if (x_ch != ERR) {
         ++my.chars;
         DEBUG_USER   yLOG_value   ("my.chars"   , my.chars);
         break;
      }
   }
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
   case  32  :
      DEBUG_USER   yLOG_note    ("space, make printable");
      x_ch = '·';
      break;
   case 33 ... 126 :
      DEBUG_USER   yLOG_note    ("normal character, append");
      break;
   case  '·' :
      DEBUG_USER   yLOG_note    ("printable space");
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
   /*---(complete)-----------------------*/
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return my.status;
}

char
valid__check            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_USER   yLOG_char    ("status"    , my.status);
   if (my.status != STATUS_GOOD) {
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(checks)-------------------------*/
   switch (my.part) {
   case PART_KNOCK    :
      rc = valid__knock  ();
      break;
   case PART_PREFIX   :
      rc = valid__prefix ();
      break;
   case PART_USERNAME :
      rc = valid__user   ();
      break;
   case PART_INFIX    :
      rc = valid__infix  ();
      break;
   case PART_PASSWORD :
      rc = valid__pass   ();
      break;
   case PART_SUFFIX   :
      rc = valid__suffix ();
      break;
   case PART_DONE     :
      rc = valid__done   ();
      break;
   case PART_TRAILING :
      DEBUG_USER   yLOG_note    ("trailing chars, skipping");
      break;
   default            :
      DEBUG_USER   yLOG_note    ("no known handler");
      break;
   }
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
valid_main              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   /*---(loop through input)-------------*/
   while (strchr (STATUSES_STOP, my.status) == NULL) {
      show_init   ();
      valid_init  ();
      show_all    ();
      refresh     ();
      while (strchr (STATUSES_CONT, my.status) != NULL) {
         /*---(update screen)---------------*/
         rc   = show_status     ();
         rc   = show_prompt     ();
         refresh ();
         /*---(gather input)----------------*/
         rc   = valid__getchar ();
         rc   = valid__check   ();
         /*---(done)------------------------*/
      }
      valid__complete ();
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char*            /* [------] unit test accessor ------------------------------*/
valid__unit          (char *a_question, int a_num)
{
   /*---(prepare)------------------------*/
   strcpy  (unit_answer, "VEIL unit        : question not understood");
   /*---(current)------------------------*/
   if      (strcmp (a_question, "status"        ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VALID status     : stat %c, part %c, chars %2d, curr %c %d", my.status, my.part, my.chars, (my.curr >= 32) ? my.curr : ' ', my.curr);
   }
   else if (strcmp (a_question, "entry"         ) == 0) {
      snprintf (unit_answer, LEN_UNIT, "VALID entry      : %2d[%s]", my.chars, my.entry_text);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}





