/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"

int         rpid;

int              /* [------] driver for hearth -------------------------------*/
main               (int a_argc, char **a_argv)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;     /* return code for errors              */
   char        rc          =    0;     /* return code as char                 */
   int         ri          =    0;     /* return code as integer              */
   int         count       =    0;     /* check cycle counter                 */
   int         x_return    =    0;
   int         i           =    0;
   int         j           =    0;
   uchar       c           =  '-';
   char        x_title     [LEN_LABEL] = "";
   char        x_content   [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   int         q, h;
   int         x, y;
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   char        x_date      [LEN_DESC]  = "";
   int         x_ch        =    0;
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);
   if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_init    ();
   if (rc >= 0)  rc = PROG_args    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   --rce;  if (rc <  0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      PROG_end ();
      return rce;
   }

   /*---(gate one)-----------------------*/
   strlcpy (my.entry_text, "", LEN_DESC);
   tcflush (stdin, TCIFLUSH);
   valid_init  ();
   g_vals.bfly_size = 'L';
   my.topplus = 5;
   /*> my.timeout =  120;                                                             <*/
   /*> my.lockout =  210;                                                             <*/
   clear       ();
   show_butterfly    ();
   show_left         ();
   show_right        ();
   show_block        ();
   /*> COLORS_MAGENTA;                                                                <*/
   my.cluster = ySTR_cluster (my.language, -1, x_title, x_content);
   sprintf (t, "%02d.%s", my.cluster, x_content);
   mvprintw ( 1,  35, "%12.12s [%-18.18s]", x_title, t);
   my.host    = ySTR_host    (my.language, -1, x_title, x_content);
   sprintf (t, "%s.%02d", x_content, my.host);
   mvprintw ( 1, 157, "[%18.18s] %-12.12s", t, x_title);
   if (my.dev [5] == 't')  strlcpy (t, "____________________", LEN_LABEL);
   else                    strlcpy (t, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬", LEN_LABEL);
   ySTR_word    (my.language, YSTR_USERNAME, x_content);
   mvprintw (70,  70, "%12.12s [%-12.12s]"    , x_content, t);
   ySTR_word    (my.language, YSTR_TOKEN   , x_content);
   mvprintw (70, 100, "%12.12s [%-6.6s]"      , x_content, t);
   ySTR_word    (my.language, YSTR_PASSWORD, x_content);
   mvprintw (70, 130, "%12.12s [%-12.12s]"    , x_content, t);
   x_now     = time (NULL);
   x_broke   = localtime (&x_now);
   strftime(x_date, LEN_DESC, "%y.%m.%d.%H.%M.%S.%w.%V.%j", x_broke);
   COLORS_OFF;

   /*> mvprintw (10, my.cen - 25, "¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬");   <*/
   if (my.dev [5] == 't')  mvprintw (6, my.cen - 25, "--------------------------------------------------");
   else                    mvprintw (6, my.cen - 25, "··················································");

   /*> my.timeout =  20;                                                              <*/
   /*> my.lockout =  20;                                                              <*/


   q = my.timeout / 4;
   h = my.timeout / 2;
   if (my.dev [5] == 't')  strlcpy (t, "#----+----", LEN_LABEL);
   else                    strlcpy (t, "Ï····+····", LEN_LABEL);
   for (i = 0; i <= my.timeout; ++i) {
      /*> show_ascii        ();                                                          <*/
      x_ch = getch ();
      c = t [i % 10];
      if      (i ==  0)   mvprintw (73, my.cen -  q        ,  "%c", c);
      else if (i <   h)   mvprintw (72, my.cen -  q + i    ,  "%c", c);
      else if (i ==  h)   mvprintw (73, my.cen -  q + i    ,  "%c", c);
      else if (i < h * 2) mvprintw (74, my.cen +  h + q - i,  "%c", c);
      mvprintw (73, my.cen - 3,  "%2d sec", i / 10);
      show_random ();
      show_rain ();
      mvprintw (68, my.cen - 14, "[%s]", x_date);
      if (my.judgement == 'Y') {
         COLORS_YELLOW;
         mvprintw (73, my.cen - 7, "[[[ %s ]]]", "YOU WON");
         COLORS_OFF;
         refresh     ();
         break;
      }
      refresh     ();
      usleep ( 100000); /* 0.1sec */
      show_getchar ();
      if (my.status == STATUS_BREAK) {
         clear       ();
         PROG_end    ();
         printf  ("\033c");
         return 0;
      }
      if (i == my.timeout && my.forever == 'y') {
         i = -1;
         mvprintw (72, my.cen - q, "%*.*s", h + 1, h + 1, "                                                                                                                                      ");
         mvprintw (73, my.cen - q, "%*.*s", h + 1, h + 1, "                                                                                                                                      ");
         mvprintw (74, my.cen - q, "%*.*s", h + 1, h + 1, "                                                                                                                                      ");
      }
   }
   if (my.judgement != 'Y' && my.lockout > 0) {
      COLORS_RED;
      mvprintw (73, my.cen - 3,  "       ");
      mvprintw (72, my.cen - 3,  "LOCKOUT");
      COLORS_OFF;
      if (my.dev [5] == 't')  strlcpy (t, " + + + + #", LEN_LABEL);
      else                    strlcpy (t, " · · · · ³", LEN_LABEL);
      for (i = 0; i <  my.lockout; ++i) {
         show_random ();
         show_rain ();
         mvprintw (68, my.cen - 14, "[%s]", x_date);
         COLORS_RED;
         c = t [i % 10];
         mvprintw (73, my.cen - (my.lockout / 10) + 1 + (i / 10) * 2, "%c", c);
         COLORS_OFF;
         refresh     ();
         usleep ( 100000); /* 0.1sec */
      }
      COLORS_OFF;
   }
   sleep (my.after);
   clear       ();
   PROG_end    ();
   printf  ("\033c");
   return 0;

   /*---(gate one)-----------------------*/
   DEBUG_TOPS   yLOG_info    ("fake_user" , my.fake_user);
   rc = gate_main    ();
   --rce;  if (rc <  0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      PROG_end ();
      return rce;
   }
   printf ("pause...\n\n");
   sleep (3);
   /*> printf  ("\033c");                                                             <*/
   /*---(gate two)-----------------------*/
   DEBUG_TOPS   yLOG_note   ("begin prompt/input cycle");
   rc = valid_main  ();
   --rce;  if (my.status != STATUS_SUCCESS) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      PROG_end ();
      return rce;
   }
   /*---(prepare)------------------------*/
   chown  (my.dev, (my.pass)->pw_uid, 0);
   chmod  (my.dev, 0700);
   strcpy (my.shell, (my.pass)->pw_shell);
   veil_rpid = getpid();
   audit_login (my.dev, my.user_fix, veil_rpid);
   ioctl (0, TIOCNOTTY, NULL);    /* detach, from login.c                  */
   setsid();                      /* start new session                     */
   ioctl (0, TIOCSCTTY,    1);
   /*---(launch)-------------------------*/
   rpid = yEXEC_run ("launching tty", my.user_fix, "/bin/bash", YEXEC_BASH, YEXEC_FULL, YEXEC_FORK, EXEC_FILE);
   /*> rpid = yEXEC_run   (EXEC_FILE, "launching tty", my.user_name, "/bin/bash", YEXEC_BASH, YEXEC_FULL, YEXEC_FORK);   <*/
   rc = ySEC_login  (my.dev + 5, my.user_fix, rpid);
   DEBUG_TOPS   yLOG_value   ("rc"     , rc);
   /*---(wait)---------------------------*/
   while (1) {
      ++count;
      if ((count % 720) == 0)  DEBUG_TOPS   yLOG_sync ();
      sleep (5);
      ri = yEXEC_check ("wait for done", rpid, &x_return);
      DEBUG_TOPS   yLOG_pair   (count, ri);
      if (ri == 0) {
         DEBUG_TOPS   yLOG_info   ("shell_exit", my.dev);
         break;
      }
   }
   /*---(wrapup)-------------------------*/
   audit_logout (my.dev, veil_rpid, ri);
   ySEC_logout  (my.dev + 5,  "", rpid);
   PROG_end    ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOGS_end    ();
   return 0;
}


/*============================[[    end-code    ]]============================*/
