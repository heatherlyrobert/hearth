/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



char
gate_prompt             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_prompt    [LEN_HUND];
   char        x_key       [LEN_SHORT];
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_LOOP   yLOG_sint    (my.language);
   DEBUG_LOOP   yLOG_sint    (my.cluster);
   DEBUG_LOOP   yLOG_sint    (my.host);
   rc = ySTR_prompt (YSTR_BREADCRUMB, "", my.language, my.cluster, my.host, x_prompt, x_key);
   DEBUG_LOOP   yLOG_sint    (rc);
   if (rc <  0) {
      DEBUG_LOOP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_LOOP   yLOG_note    (x_prompt);
   /*---(clear the screen)---------------*/
   DEBUG_LOOP   yLOG_note    ("clear and write login message");
   DEBUG_LOOP   yLOG_info    ("fake_user" , my.fake_user);
   DEBUG_LOOP   yLOG_char    ("...[0]"    , my.fake_user [0]);
   clear ();
   if (my.fake_user [0] != '\0') {
      mvprintw  (0, 0, "%s %s", x_prompt, my.fake_user);
   } else {
      mvprintw (0, 0,  "%s ", x_prompt);
   }
   refresh ();
   sleep (5);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
gate__password          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_prompt    [LEN_HUND];
   char        x_key       [LEN_SHORT];
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_LOOP   yLOG_sint    (my.language);
   DEBUG_LOOP   yLOG_sint    (my.cluster);
   DEBUG_LOOP   yLOG_sint    (my.host);
   rc = ySTR_password (YSTR_BREADCRUMB, my.language, x_prompt);
   DEBUG_LOOP   yLOG_sint    (rc);
   if (rc <  0) {
      DEBUG_LOOP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_LOOP   yLOG_note    (x_prompt);
   /*---(clear the screen)---------------*/
   DEBUG_LOOP   yLOG_note    ("clear and write login message");
   tcflush (stdin, TCIFLUSH);
   printf  ("\033c");
   printf  ("%s ", x_prompt);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
gate__check             (char *a_input, char *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(defense on input)---------------*/
   DEBUG_LOOP   yLOG_spoint  (a_input);
   --rce;  if (a_input == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_snote   (a_input);
   x_len = strlen (a_input);
   DEBUG_LOOP   yLOG_sint    (x_len);
   --rce;  if (x_len != 4) {
      DEBUG_LOOP   yLOG_snote   ("must be four");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense on key)-----------------*/
   DEBUG_LOOP   yLOG_spoint  (a_key);
   --rce;  if (a_key == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_snote   (a_key);
   x_len = strlen (a_key);
   DEBUG_LOOP   yLOG_sint    (x_len);
   --rce;  if (x_len != 4) {
      DEBUG_LOOP   yLOG_snote   ("must be four");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check)--------------------------*/
   rc = strcmp (a_input, a_key);
   DEBUG_LOOP   yLOG_sint    (rc);
   --rce;  if (rc != 0) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
gate__collect           (char *a_input)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_ch        =    0;
   char        x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(defense on input)---------------*/
   DEBUG_LOOP   yLOG_spoint  (a_input);
   --rce;  if (a_input == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strcpy (a_input, "");
   /*---(gather input)-------------------*/
   --rce;  while (1) {
      DEBUG_LOOP   yLOG_sint    (x_len);
      /*---(get character)---------------*/
      x_ch = fgetc (stdin);
      switch (x_ch) {
      case -1       :
         DEBUG_LOOP   yLOG_snote   ("ERROR");
         strcpy (a_input, "");
         DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
         break;
      case G_KEY_NULL   :
         DEBUG_LOOP   yLOG_snote   ("NULL");
         strcpy (a_input, "");
         DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
         break;
      case G_KEY_RETURN :
         DEBUG_LOOP   yLOG_snote   ("return");
         if (x_len >= LEN_SHORT) {
            strcpy (a_input, "");
            DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
         return x_len;
         break;
      case '?'      :
         if (x_len > 0)  break;
         DEBUG_LOOP   yLOG_snote   ("QUESTIONS");
         x_ch = fgetc (stdin);  /* clear return char */
         sprintf (a_input, "?");
         DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
         return x_len;
         break;
      case '@'      :
         if (x_len > 0)  break;
         DEBUG_LOOP   yLOG_snote   ("ONE-TIME CODE");
         x_ch = fgetc (stdin);  /* clear return char */
         sprintf (a_input, "@");
         DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
         return x_len;
         break;
      }
      /*---(limits)----------------------*/
      if (x_len <  50)  ++x_len;
      if (x_len >= LEN_SHORT)   continue;
      /*---(process character)-----------*/
      a_input [x_len - 1] = x_ch;
      a_input [x_len    ] = '\0';
      DEBUG_LOOP   yLOG_snote   (a_input);
      /*---(done)------------------------*/
   }
   DEBUG_LOOP   yLOG_snote   (a_input);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char
gate__questions         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_input     [LEN_SHORT];
   char        x_word      [LEN_HUND];
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   tcflush (stdin, TCIFLUSH);
   printf  ("\033c");
   ySTR_word (my.language, YSTR_QUESTIONS, x_word);
   printf ("%s (english only)...\n", x_word);
   sleep (3);
   printf ("\n");
   printf ("where was your first house      : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("\n");
   printf ("who was your favorite teacher   : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("\n");
   printf ("what is your best friend's name : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("\n");
   printf ("one or more answers where not correct, continue y/n : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   return 0;
}

char
gate__sendcode          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_input     [LEN_SHORT];
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   tcflush (stdin, TCIFLUSH);
   printf  ("\033c");
   printf ("please enter the email or phone number for the one-time code below...\n");
   printf ("\n");
   printf ("email or phone      : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("\n");
   printf ("re-enter to confirm : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("\n");
   printf ("email/text sent, please check your phone...\n");
   sleep (3);
   printf ("\n");
   printf ("type your code here : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("the code does not match our records...\n");
   printf ("\n");
   sleep (3);
   printf ("type your code here : ");
   tcflush (stdin, TCIFLUSH);
   rc = gate__collect  (x_input);
   sleep (3);
   printf ("the code does not match our records...\n");
   printf ("\n");
   sleep (3);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
gate__tarpit            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_input     [LEN_SHORT];
   char        x_word      [LEN_HUND];
   int         x_loop      =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   /*---(gather input)-------------------*/
   while (1) {
      DEBUG_LOOP   yLOG_value   ("x_loop"    , x_loop);
      sleep (3);
      if (x_loop > 5)  break;
      rc = gate__password ();
      rc = gate__collect  (x_input);
      if      (rc == 0 && x_input [0] == '?') gate__questions ();
      else if (rc == 0 && x_input [0] == '@') gate__sendcode  ();
      else {
         sleep (3);
         ySTR_word (my.language, YSTR_INVALID, x_word);
         printf ("%s...\n", x_word);
      }
      ++x_loop;
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
gate_load          (char *a_user)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_senter  (__FUNCTION__);
   DEBUG_LOOP   yLOG_spoint  (a_user);
   if (a_user == NULL) {
      DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_LOOP   yLOG_snote   (a_user);
   x_len = strlen (a_user);
   DEBUG_LOOP   yLOG_sint    (x_len);
   DEBUG_TOPS   yLOG_schar   ("enter");
   ungetc ('\n', stdin);
   for (i = x_len - 1; i >= 0; --i) {
      DEBUG_TOPS   yLOG_schar   (a_user [i]);
      ungetc (a_user [i], stdin);
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return x_len;
}

char         /*--> fake lead door ------------------------[ leaf   [ ------ ]-*/
gate_main          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_len       =    0;
   char        x_prompt    [LEN_HUND];
   char        x_key       [LEN_SHORT];
   char        x_input     [LEN_SHORT];
   char        x_user      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   DEBUG_LOOP   yLOG_value   ("language"  , my.language);
   DEBUG_LOOP   yLOG_value   ("cluster"   , my.cluster);
   DEBUG_LOOP   yLOG_value   ("host"      , my.host);
   rc = ySTR_prompt (YSTR_BREADCRUMB, "", my.language, my.cluster, my.host, x_prompt, x_key);
   DEBUG_LOOP   yLOG_value   ("prompt"    , rc);
   if (rc <  0) {
      DEBUG_LOOP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_LOOP   yLOG_info    ("x_prompt"  , x_prompt);
   DEBUG_LOOP   yLOG_info    ("x_key"     , x_key);
   /*---(load stdin)---------------------*/
   strcpy (x_user, my.fake_user);
   x_len = strlen (x_user);
   if (x_len > 0) {
      rc = gate_load (x_user);
      DEBUG_LOOP   yLOG_value   ("load"      , rc);
   }
   rc = gate_prompt  ();
   DEBUG_LOOP   yLOG_value   ("prompt"    , rc);
   /*---(collect input)------------------*/
   rc = gate__collect (x_input);
   DEBUG_LOOP   yLOG_value   ("collect"   , rc);
   DEBUG_LOOP   yLOG_info    ("x_input"   , x_input);
   if (rc >= 0) {
      rc = gate__check   (x_input, x_key);
      DEBUG_LOOP   yLOG_value   ("check"     , rc);
      if (rc >= 0) {
         DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(fall into tarpit)---------------*/
   rc = gate__tarpit ();
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exitr   (__FUNCTION__, rc);
   return rc;
}



