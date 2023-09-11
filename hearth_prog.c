/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



struct cACCESSOR my;


char        g_modes     [20] = "uqfih";   /* valid fake_door modes                 */

char        user        [30];
int         veil_rpid;
int         rpid;
int         bottom            = 63;
int         center            = 63;
int         middle            = 24;
int         left              =  0;
int         left2             =  0;
int         x_knock2;   /* left of right knock     */

char        ntitle   = 14;



char      verstring    [500];








/*====================------------------------------------====================*/
/*===----                         support functions                    ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strcpy (t, "[tcc built  ]");
#elif  __GNUC__  > 0
   strcpy (t, "[gnu gcc    ]");
#elif  __CBANG__  > 0
   strcpy (t, "[cbang      ]");
#elif  __HEPH__  > 0
   strcpy (t, "[hephaestus ]");
#else
   strcpy (t, "[unknown    ]");
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return verstring;
}

char      /* [------] display usage help information ------------------*/
PROG_usage         (void)
{
   printf ("%s\n", P_ONELINE);
   printf ("   usage   : hearth [URGENTS] [OPTIONS] dev_file\n");
   printf ("   version : %s, %s, %s\n", P_VERNUM, __DATE__, P_VERTXT);
   printf ("\n");
   printf ("can be called from terminal for demonstration\n");
   printf ("   hearth --nolock --forever\n");
   printf ("   use <C-c> to exit to command prompt\n");
   exit (0);
   printf ("----------------------------------------------------------------------------------\n");
   printf ("\n");
   printf ("purpose : clean, maintainable, reliable, and secure terminal manager dispatched\n");
   printf ("          on a newly activated device to configure the terminal, administer a\n");
   printf ("          wickedly secure login cycle, and respond to appropriately.\n");
   printf ("\n");
   printf ("patron  : hestia is a major goddess and the protector of hearth and home.  she\n");
   printf ("   was represented as modest, sitting on a wooden throne, and wearing a veil.  the\n");
   printf ("   central public hearth of every city burned continuously with her fire.\n");
   printf ("\n");
   printf ("posix   : getty was never formally standardized, but it has a strong defacto\n");
   printf ("   design followed by every major replacement, agetty, ngetty, mingetty, fgetty,\n");
   printf ("   etc.  while they are different, its mostly in features, not nature.\n");
   printf ("\n");
   printf ("reason  : in order to create a new login method, trick, or cycle, you have to\n");
   printf ("   understand the guts of getty and be able to patch it.  but to really alter it\n");
   printf ("   we have to *own* it fully and take full responsibility.  so, here we are ;)\n");
   printf ("\n");
   printf("standard/consistent options implemented ------------------------------------------\n");
   printf("   --timeout <secs> set the timeout length\n");
   printf("   -t <secs>        same as --timeout\n");
   printf("\n");
   printf("standard/consistent getty options rejected ---------------------------------------\n");
   printf("   -w (built-in)    wait for carriage-return before login       (default         )\n");
   printf("   -i               not not display /etc/issue                  (standardized    )\n");
   printf("   --noissue        same as -i                                  (standardized    )\n");
   printf("   -f <file>        display a alternate /etc/issue file         (standardized    )\n");
   printf("   -l <login>       run an alternate login program              (standardized    )\n");
   printf("   --loginprog      same as -l                                  (standardized    )\n");
   printf("   -H <host>        override the host name                      (don't like      )\n");
   printf("   -n               do not prompt for a login name              (not secure      )\n");
   printf("   --noclear        do not clear the screen first               (pointless       )\n");
   printf("   --nonewline      print a new line before issue               (pointless       )\n");
   printf("   --nice <n>       set the nice level                          (can do otherways)\n");
   printf("   --delay <n>      sleep after invocation, but before start    (can do otherways)\n");
   printf("   --chdir <dir>    change to this dir before starting          (can do otherways)\n");
   printf("   --chroot <dir>   create a chroot jail first                  (can do otherways)\n");
   printf("   --autologin <s>  automatically login                         (security        )\n");
   printf("   --loginpause     wait for newline before asking for user     (pointless       )\n");
   printf("   -c               don't reset terminal control strings        (no point)\n");
   printf("   -8               set in eight-bit clean mode                 (no point)\n");
   printf("   -I <string>      custom initialization string                (no point)\n");
   printf("   -m               get baud rate from connect                  (no point)\n");
   printf("   -s               keep the existing baud rate from connect    (no point)\n");
   printf("   -L               force it to be a local line                 (no point)\n");
   printf("   -U               handle an uppercase only terminal           (no point)\n");
   printf("\n");
   printf("extended getty options -----------------------------------------------------------\n");
   printf("   --version        print a single version description line\n");
   printf("   --help, -h       print usage information\n");
   printf("\n");
   printf("heatherly debugging urgents ------------------------------------------------------\n");
   printf("   @a               verbosely traces argument parsing\n");
   printf("   @g               identify the critical numbers by highlighting\n");
   printf("   @p               verbosely traces interactive/crontab logic\n");
   printf("\n");
   exit (0);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT________o (void) {;}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return rc;
}




/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char
PROG_defaults           (void)
{
   my.timeout         = 160;
   my.lockout         = 210;
   my.after           =   0;
   my.forever         = '-';
   my.deaf            = '-';
   my.mute            = '-';
   my.show_hint       = '-';
   my.lang_save       =  -1;
   my.clus_save       =  -1;
   my.host_save       =  -1;
   strcpy (my.dev, "");
   return 0;
}

char
PROG__init              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_sid       =    0;
   /*---(logger)-------------------------*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   DEBUG_PROG   yLOG_info   ("logger"    , "logger openned successfully");
   DEBUG_PROG   yLOG_info   ("purpose"   , "light, clean, and customized getty replacement");
   DEBUG_PROG   yLOG_info   ("namesake"  , "hestia, goddess of hearth and home");
   DEBUG_PROG   yLOG_info   ("ver_num"   , P_VERNUM);
   DEBUG_PROG   yLOG_info   ("ver_txt"   , P_VERTXT);
   /*---(signals)------------------------*/
   rc = yEXEC_signal (YEXEC_SOFT, YEXEC_NO, YEXEC_NO, NULL, "stdsig");
   /*---(call whoami)--------------------*/
   rc = yEXEC_whoami (&my.pid, &my.ppid, &my.uid, NULL, &my.who, 'n');
   DEBUG_PROG   yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("pid"       , my.pid);
   DEBUG_PROG   yLOG_value   ("ppid"      , my.ppid);
   DEBUG_PROG   yLOG_value   ("uid"       , my.uid);
   DEBUG_PROG   yLOG_info    ("who"       , my.who);
   /*---(set defaults)-------------------*/
   PROG_defaults ();
   /*---(mode)---------------------------*/
   my.run_mode        = RUN_USER;
   /*---(fake)---------------------------*/
   show_init ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
}

#define    TWOARG      if (two_arg == 1)

char
PROG__args              (int a_argc, char *a_argv[])
{
   char        rce         =  -10;
   /*---(begin)------------+-----------+-*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   /*---(locals)-------------------------*/
   int         i           = 0;             /* loop iterator -- arguments     */
   char       *a           = NULL;          /* current argument               */
   int         x_len       = 0;             /* argument length                */
   char        two_arg     = 0;
   /*---(process args)-------------------*/
   DEBUG_ARGS   yLOG_value  ("a_argc"      , a_argc);
   --rce;  for (i = 1; i < a_argc; ++i) {
      a   = a_argv[i];
      if (i < a_argc - 1) two_arg = 1; else two_arg = 0;
      x_len = strlen(a);
      DEBUG_ARGS   yLOG_bullet (i           , a);
      /*---(skip debugging)--------------*/
      if      (a[0] == '@')                     continue;
      /*---(interactive)-----------------*/
      if      (strcmp (a, "--version"     ) == 0) {
         printf ("hearth (%s/%s) %s\n", P_VERNUM, __DATE__, P_VERTXT);
         exit (0);
      }
      else if (strcmp (a, "--usage"       ) == 0) { PROG_usage ();  return -1; }
      /*---(timimg)----------------------*/
      else if (strcmp (a, "--flash"       ) == 0)  my.timeout    =  20;
      else if (strcmp (a, "--quick"       ) == 0)  my.timeout    =  60;
      else if (strcmp (a, "--fast"        ) == 0)  my.timeout    = 120;
      else if (strcmp (a, "--norm"        ) == 0)  my.timeout    = 160;
      else if (strcmp (a, "--slow"        ) == 0)  my.timeout    = 200;
      else if (strcmp (a, "--glacial"     ) == 0)  my.timeout    = 300;
      else if (strcmp (a, "--nolock"      ) == 0)  my.lockout    =   0;
      else if (strcmp (a, "--fastlock"    ) == 0)  my.lockout    =  50;
      else if (strcmp (a, "--normlock"    ) == 0)  my.lockout    = 110;
      else if (strcmp (a, "--slowlock"    ) == 0)  my.lockout    = 210;
      else if (strcmp (a, "--forever"     ) == 0)  my.forever    = 'y';
      else if (strcmp (a, "--after"       ) == 0)  my.after      =   5;
      /*---(hinting options)-------------*/
      else if (strcmp (a, "--hints"       ) == 0)  my.show_hint  = 'y';
      else if (strcmp (a, "--deaf"        ) == 0)  my.deaf       = 'y';
      else if (strcmp (a, "--mute"        ) == 0)  my.mute       = 'y';
      /*---(complex)---------------------*/
      else if (strcmp (a, "--language"    ) == 0)  { TWOARG  my.lang_save = atoi (a_argv [++i]); }
      else if (strcmp (a, "--host"        ) == 0)  { TWOARG  my.host_save = atoi (a_argv [++i]); }
      else if (strcmp (a, "--cluster"     ) == 0)  { TWOARG  my.clus_save = atoi (a_argv [++i]); }
      else if (strcmp (a, "--bfly"        ) == 0)  { TWOARG  g_vals.bfly_indx = atoi (a_argv [++i]); }
      /*---(device)----------------------*/
      else if (strncmp (a, "/dev/"     , 5) == 0) {
         ystrlcpy (my.dev, a, LEN_LABEL);
      }
      else {
         printf ("command line option <%s> not understood, FATAL\n", a);
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }  /*---(done)------------------------*/
   /*---(show args)----------------------*/
   /*> printf ("bfly_indx (1) = %2d\n", g_vals.bfly_indx);                            <*/
   DEBUG_ARGS   yLOG_char    ("run_mode"  , my.run_mode);
   DEBUG_ARGS   yLOG_value   ("language"  , my.lang_save);
   DEBUG_ARGS   yLOG_value   ("cluster"   , my.clus_save);
   DEBUG_ARGS   yLOG_value   ("host"      , my.host_save);
   DEBUG_ARGS   yLOG_info    ("dev"       , my.dev);
   DEBUG_ARGS   yLOG_info    ("fake_user" , my.fake_user);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
PROG__begin             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          = 0;
   /*> int         i           = 0;                                                   <*/
   /*> tSTAT       s;                                                                 <*/
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   /*---(get the terminal)---------------*/
   if (strcmp (my.dev, "") == 0)  ystrlcpy (my.dev, ttyname (STDIN_FILENO), LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return   0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   ();
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}

char
PROG_dawn          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          = 0;
   char        x_cmd       [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   /*---(update console)---------------------*/
   rc = ySEC_open (my.dev, NULL, YEXEC_STDALL, YEXEC_NO, YEXEC_YES);
   DEBUG_PROG   yLOG_value   ("console"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(report request)---------------------*/
   rc = ySEC_request (my.dev, my.pid, my.timeout, my.lockout, my.show_hint, my.magic_num);
   DEBUG_PROG   yLOG_value   ("request"  , rc);
   /*---(force correct font)-----------------*/
   sprintf (x_cmd, "/usr/bin/setfont -C %s /usr/share/consolefonts/shrike", my.dev);
   system (x_cmd);
   /*---(clear outstanding input)------------*/
   tcflush (stdin, TCIFLUSH);
   DEBUG_PROG   yLOG_note    ("initscr");
   initscr ();       /* fire up ncurses with a default screen (stdscr)         */
   DEBUG_PROG   yLOG_note    ("raw");
   raw     ();           /* read key-by-key rather than waiting for \n (raw mode)  */
   DEBUG_PROG   yLOG_note    ("nodelay");
   nodelay (stdscr, TRUE);
   DEBUG_PROG   yLOG_note    ("noecho");
   noecho  ();        /* don't automatically echo keypresses to the screen      */
   ESCDELAY = 0;    /* so escape responds immediately                         */
   /*---(colors)----------------------*/
   DEBUG_PROG   yLOG_note    ("cursor");
   curs_set (0);
   DEBUG_PROG   yLOG_note    ("colors");
   start_color();
   use_default_colors();
   init_pair ( 1, COLOR_WHITE  , -1           );
   init_pair ( 2, COLOR_BLACK  , COLOR_WHITE  );
   init_pair ( 3, COLOR_WHITE  , COLOR_BLACK  );
   init_pair ( 4, COLOR_BLACK  , COLOR_GREEN  );
   init_pair ( 5, COLOR_WHITE  , COLOR_RED    );
   init_pair ( 6, COLOR_BLACK  , COLOR_CYAN   );
   init_pair ( 7, COLOR_BLACK  , COLOR_YELLOW );
   init_pair ( 8, COLOR_WHITE  , COLOR_MAGENTA);
   init_pair ( 9, COLOR_RED    , -1           );
   init_pair (10, COLOR_GREEN  , -1           );
   init_pair (11, COLOR_CYAN   , -1           );
   init_pair (12, COLOR_YELLOW , -1           );
   init_pair (13, COLOR_WHITE  , COLOR_BLUE   );
   init_pair (14, COLOR_BLUE   , -1           );
   init_pair (15, COLOR_WHITE  , COLOR_BLACK  );
   init_pair (16, COLOR_RED    , COLOR_BLACK  );
   init_pair (17, COLOR_YELLOW , COLOR_RED    );
   init_pair (18, COLOR_MAGENTA, -1           );
   show_sizing ();
   use_legacy_coding (2);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         runtime support                      ----===*/
/*====================------------------------------------====================*/
static void      o___RUNTIME_________________o (void) {;}

char
PROG_normal             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   my.t_beg  = my.t_end = time (NULL);
   my.t_dur  = my.t_end - my.t_beg;
   my.status = STATUS_GOOD;
   show_background   ();
   show_random (-1);
   /*---(normal)-------------------------*/
   for (i = 0; i <= my.timeout; ++i) {
      /*---(update)----------------------*/
      show_random  (i);
      show_rain    ();
      show_timer   (&i);
      show_results ();
      refresh      ();
      /*---(get char)--------------------*/
      usleep ( 100000); /* 0.1sec */
      show_getchar ();
      /*---(statuses)--------------------*/
      if (my.status == STATUS_BREAK)     break;
      if (my.status == STATUS_REFRESH)   break;
      if (my.judgement == 'Y') {
         my.status = STATUS_SUCCESS;
         break;
      }
   }
   /*---(prevent rapid cancels)----------*/
   if (i < 60 && my.status == STATUS_BREAK) {
      my.status = STATUS_FAILED;
   }
   /*---(prevent rapid refreshes)--------*/
   if (my.status == STATUS_REFRESH) {
      if (i < 60)   my.status = STATUS_FAILED;
      else          PROG_lockout ();
   }
   /*---(normal timeout)-----------------*/
   else if (i > my.timeout && my.status == STATUS_GOOD) {
      my.status = STATUS_TIMEOUT;
   }
   /*---(goodness)-----------------------*/
   else if (my.status == STATUS_SUCCESS) {
      COLORS_YELLOW;
      if (my.mute != 'y')  mvprintw (73, my.cen - 7, "[[[ %s ]]]", "YOU WON");
      COLORS_OFF;
      refresh     ();
   }
   my.t_end  = time (NULL);
   my.t_dur  = my.t_end - my.t_beg;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
PROG_lockout            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   /*---(update times)-------------------*/
   my.t_beg  = my.t_end = time (NULL);
   my.t_dur  = my.t_end - my.t_beg;
   /*---(defense)------------------------*/
   if (my.lockout <= 0)   return 0;
   /*---(cycle)--------------------------*/
   for (i = 0; i <  my.lockout; ++i) {
      show_random  (i);
      show_rain    ();
      show_lockout (i);
      show_results ();
      refresh      ();
      usleep ( 100000); /* 0.1sec */
      tcflush (stdin, TCIFLUSH);  /* ignore input, don't pass on */
   }
   /*---(update times)-------------------*/
   my.t_end  = time (NULL);
   my.t_dur  = my.t_end - my.t_beg;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
PROG_launch             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_uid       =    0;
   char        x_dir       [LEN_RECD]  = "";
   char        x_shell     [LEN_RECD]  = "";
   int         x_child     =    0;
   int         x_return    =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   /*---(get user information)-----------*/
   rc = yEXEC_userdata (my.user_fix, &x_uid, NULL, x_dir, x_shell);
   DEBUG_PROG   yLOG_complex ("user"      , "%3d, %-15.15s, %4d, %s, %s", rc, my.user_fix, x_uid, x_dir, x_shell);
   /*---(update device)------------------*/
   chown  (my.dev, x_uid, 0);
   chmod  (my.dev, 0700);
   /*---(log with security)--------------*/
   rc = ySEC_active (my.pid, my.entry_text, my.phase, my.judgement, my.status, my.result, my.user_fix);
   DEBUG_PROG   yLOG_value   ("active"   , rc);
   rc = ySEC_login  (my.dev, my.user_fix, my.pid);
   DEBUG_PROG   yLOG_value   ("login"    , rc);
   /*---(prepare session)----------------*/
   ioctl  (0, TIOCNOTTY, NULL);   /* detach, from login.c                  */
   setsid ();                     /* start new session                     */
   ioctl  (0, TIOCSCTTY,    1);
   /*---(end ncurses)--------------------*/
   clear       ();
   endwin();        /* shut down ncurses                                      */
   printf  ("\033c");
   /*---(launch)-------------------------*/
   x_child = yEXEC_full ("launching tty", my.user_fix, x_shell, YEXEC_BASH, YEXEC_FULL, YEXEC_FORK, EXEC_FILE);
   DEBUG_PROG   yLOG_value   ("x_child", x_child);
   /*---(wait)---------------------------*/
   while (1) {
      ++c;
      if ((c % 720) == 0)  DEBUG_PROG   yLOG_sync ();
      sleep (5);
      rc = yEXEC_verify ("wait for done", x_child, &x_return, NULL);
      DEBUG_PROG   yLOG_complex ("check"     , "%6d, %3d, %3d, %c", x_child, c, rc, rc);
      if (rc != YEXEC_RUNNING)   break;
   }
   /*---(wrapup)-------------------------*/
   ySEC_complete (my.pid, 'y');
   ySEC_logout   (my.dev,  "", my.pid);
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     program wrapup                           ----===*/
/*====================------------------------------------====================*/
static void      o___WRAPUP__________________o (void) {;}

char
PROG__end          (void)
{
   /*---(begin)------------+-----------+-*/
   DEBUG_PROG   yLOG_enter  (__FUNCTION__);
   clear       ();
   endwin();        /* shut down ncurses                                      */
   printf  ("\033c");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOGS_end ();
   DEBUG_PROG   yLOG_exit   (__FUNCTION__);
   return 0;
} /*======================================================*/

char             /* [------] drive the program closure activities ------------*/
PROG_shutdown           (void)
{
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_END);
   DEBUG_PROG   yLOG_enter    (__FUNCTION__);
   PROG__end ();
   DEBUG_PROG   yLOG_exit     (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   helpers for unit testing                   ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char         /*--> set up unit test without debug ----------------------------*/
prog__unit_quiet        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_argc      = 1;
   char       *x_argv [1]  = { "hearth" };
   /*---(run)----------------------------*/
   yURG_logger   (x_argc, x_argv);
   yURG_urgs     (x_argc, x_argv);
   PROG__init     ();
   PROG__args     (x_argc, x_argv);
   PROG__begin    ();
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> set up unit test with debug -------------------------------*/
prog__unit_loud         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_argc      = 2;
   char       *x_argv [2]  = { "hearth_unit", "@@kitchen"    };
   /*---(run)----------------------------*/
   yURG_logger   (x_argc, x_argv);
   yURG_urgs     (x_argc, x_argv);
   PROG__init     ();
   PROG__args     (x_argc, x_argv);
   PROG__begin    ();
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> complete unit testing -------------------------------------*/
prog__unit_end          (void)
{
   PROG_shutdown       ();
   /*---(complete)-----------------------*/
   return 0;
}

char
PROG_testuserdel     (cchar *a_name)
{
   char        rce          =  -10;
   char        rc           =    0;
   char        t            [LEN_STR  ] = "";
   --rce;  if (a_name == NULL) return rce;
   snprintf (t, LEN_STR, "userdel --remove %s >> /dev/null 2>&1", a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   return 0; 
}

char
prog_nonrandom          (void)
{
   srand (0);
   return 0;
}

char
PROG_testuseradd     (cchar *a_name, cchar *a_pass)
{
   char        rce          =  -10;
   char        rc           =    0;
   char        t            [LEN_STR  ] = "";
   --rce;  if (a_name == NULL) return rce;
   --rce;  if (a_pass == NULL) return rce;
   PROG_testuserdel (a_name);
   snprintf (t, LEN_STR, "useradd --gid nobody --create-home --no-user-group %s >> /dev/null 2>&1", a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   snprintf (t, LEN_STR, "printf \"%s\n%s\n\" | passwd %s >> /dev/null 2>&1", a_pass, a_pass, a_name);
   rc = system (t);
   --rce;  if (rc < 0)   return rce;
   return 0; 
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char        unit_answer [LEN_RECD];

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
prog__unit              (char *a_question)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        s           [LEN_DESC]  = "";
   char        t           [LEN_DESC]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "PROG unit        : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "timing"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROG timing      : %3d timeout, %3d lockout, %c forever, %3d after",
            my.timeout, my.lockout, my.forever, my.after);
   }
   else if (strcmp (a_question, "config"    )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROG config      : %2d lang, %2d clus, %2d host, %2d bfly",
            my.lang_save, my.clus_save, my.host_save, g_vals.bfly_indx);
   }
   else if (strcmp (a_question, "result"    )     == 0) {
      sprintf (s, "%2d[%.20s]", strlen (my.magic_num) , my.magic_num);
      sprintf (t, "%2d[%.20s]", strlen (my.entry_text), my.entry_text);
      snprintf (unit_answer, LEN_RECD, "PROG result      : %c  %c  %2d  %c  %-24.24s  %-24.24s  %c",
            my.phase, my.judgement, my.position, my.status, s, t, my.show_hint);
   }
   else if (strcmp (a_question, "exec"      )     == 0) {
      snprintf (unit_answer, LEN_RECD, "PROG exec        : %10db, %10de, %10dd",
            my.t_beg, my.t_end, my.t_dur);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}









/*============================[[    end-code    ]]============================*/
