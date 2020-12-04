/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



struct cACCESSOR my;
char          unit_answer [LEN_UNIT];



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
   printf ("\n");
   printf ("usage   : hearth [URGENTS] [OPTIONS] dev_file\n");
   printf ("\n");
   printf ("version : %s, %s, %s\n", P_VERNUM, __DATE__, P_VERTXT);
   printf ("\n");
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
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP_________________o (void) {;}

char
PROG_init            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_sid       =    0;
   /*---(logger)-------------------------*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   DEBUG_TOPS   yLOG_info   ("logger"    , "logger openned successfully");
   DEBUG_TOPS   yLOG_info   ("purpose"   , "light, clean, and customized getty replacement");
   DEBUG_TOPS   yLOG_info   ("namesake"  , "hestia, goddess of hearth and home");
   DEBUG_TOPS   yLOG_info   ("ver_num"   , P_VERNUM);
   DEBUG_TOPS   yLOG_info   ("ver_txt"   , P_VERTXT);
   /*---(signals)------------------------*/
   rc = yEXEC_signal (YEXEC_SOFT, YEXEC_NO, YEXEC_NO, NULL, "stdsig");
   /*---(call whoami)--------------------*/
   rc = yEXEC_whoami (&my.pid, &my.ppid, &my.uid, NULL, &my.who, 'n');
   DEBUG_TOPS   yLOG_value   ("whoami"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_TOPS   yLOG_value   ("pid"       , my.pid);
   DEBUG_TOPS   yLOG_value   ("ppid"      , my.ppid);
   DEBUG_TOPS   yLOG_value   ("uid"       , my.uid);
   DEBUG_TOPS   yLOG_info    ("who"       , my.who);
   /*---(mode)---------------------------*/
   my.run_mode        = RUN_USER;
   my.status          = STATUS_GOOD;
   /*---(get the terminal)---------------*/
   strlcpy (my.dev, ttyname (STDIN_FILENO), LEN_LABEL);
   /*---(fake)---------------------------*/
   srand (time(NULL));
   yEXEC_challenge (time (NULL), my.magic_num);
   my.language        = ySTR_language ();
   my.cluster         = ySTR_cluster  (my.language, -1, NULL, NULL);
   my.host            = ySTR_host     (my.language, -1, NULL, NULL);
   g_vals.bfly_indx   = rand () % 16;
   /*---(timer options)------------------*/
   my.timeout         = 120;
   my.lockout         = 210;
   my.after           =   0;
   my.forever         = '-';
   /*---(hinting)------------------------*/
   my.show_hint       = '-';
   show_init ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   return 0;
}

#define    TWOARG      if (two_arg == 1)

char
PROG_args            (int a_argc, char *a_argv[])
{
   char        rce         =  -10;
   /*---(begin)------------+-----------+-*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
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
      else if (strcmp (a, "--show"        ) == 0)  my.run_mode   = RUN_AS_SHOW;
      else if (strcmp (a, "--hints"       ) == 0)  my.show_hint  = 'y';
      else if (strcmp (a, "--nohint"      ) == 0)  my.show_hint  = '-';
      /*---(usage/help)------------------*/
      else if (strcmp (a, "-h"            ) == 0)  PROG_usage ();
      else if (strcmp (a, "--help"        ) == 0)  PROG_usage ();
      /*---(complex)---------------------*/
      else if (strcmp (a, "--language"    ) == 0)  { TWOARG  my.language = atoi (a_argv [++i]); }
      else if (strcmp (a, "--host"        ) == 0)  { TWOARG  my.host     = atoi (a_argv [++i]); }
      else if (strcmp (a, "--cluster"     ) == 0)  { TWOARG  my.cluster  = atoi (a_argv [++i]); }
      else if (strcmp (a, "--user"        ) == 0)  { TWOARG  strcpy (my.fake_user, a_argv [++i]); }
      else if (strcmp (a, "--bfly"        ) == 0)  { TWOARG  g_vals.bfly_indx = atoi (a_argv [++i]); }
      /*---(device)----------------------*/
      else if (strncmp (a, "/dev/"     , 5) == 0) {
         strlcpy (my.dev, a, LEN_LABEL);
      }
      else {
         printf ("command line option <%s> not understood, FATAL\n", a);
         DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }  /*---(done)------------------------*/
   /*---(show args)----------------------*/
   /*> printf ("bfly_indx (1) = %2d\n", g_vals.bfly_indx);                            <*/
   DEBUG_ARGS   yLOG_char    ("run_mode"  , my.run_mode);
   DEBUG_ARGS   yLOG_value   ("language"  , my.language);
   DEBUG_ARGS   yLOG_value   ("cluster"   , my.cluster);
   DEBUG_ARGS   yLOG_value   ("host"      , my.host);
   DEBUG_ARGS   yLOG_info    ("dev"       , my.dev);
   DEBUG_ARGS   yLOG_info    ("fake_user" , my.fake_user);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
PROG_begin         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          = 0;
   /*> int         i           = 0;                                                   <*/
   /*> tSTAT       s;                                                                 <*/
   char        x_cmd       [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   /*---(update console)---------------------*/
   rc = yEXEC_tty_open (my.dev, NULL, YEXEC_STDALL, YEXEC_NO);
   DEBUG_TOPS   yLOG_value   ("console"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(force correct font)-----------------*/
   sprintf (x_cmd, "/usr/bin/setfont -C %s /usr/share/consolefonts/shrike", my.dev);
   system (x_cmd);
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   return   0;
}

char
PROG_final         (void)
{
   DEBUG_TOPS   yLOG_note    ("initscr");
   initscr ();       /* fire up ncurses with a default screen (stdscr)         */
   DEBUG_TOPS   yLOG_note    ("raw");
   raw     ();           /* read key-by-key rather than waiting for \n (raw mode)  */
   DEBUG_TOPS   yLOG_note    ("nodelay");
   nodelay (stdscr, TRUE);
   DEBUG_TOPS   yLOG_note    ("noecho");
   noecho  ();        /* don't automatically echo keypresses to the screen      */
   ESCDELAY = 0;    /* so escape responds immediately                         */
   /*---(colors)----------------------*/
   DEBUG_TOPS   yLOG_note    ("cursor");
   curs_set (0);
   DEBUG_TOPS   yLOG_note    ("colors");
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
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         runtime support                      ----===*/
/*====================------------------------------------====================*/
static void      o___RUNTIME_________________o (void) {;}

void             /* [------] receive signals ---------------------------------*/
PROG_signal        (int a_signal, siginfo_t *a_info, void *a_nada)
{
   /*---(locals)-----------+-----------+-*/
   int         status      = 0;
   int         xlink       = 0;
   int         rc          = 0;
   int         errsave     = 0;
   switch (a_signal) {
   case  SIGCHLD:
   case  SIGHUP:
   case  SIGUSR1:
   case  SIGUSR2:
      break;
   case  SIGTERM:
   case  SIGSEGV:
      ySEC_logout (my.dev + 5,  "", rpid);
      break;
   default:
      break;
   }
   /*---(complete)-----------------------*/
   return;
}



/*====================------------------------------------====================*/
/*===----                     program wrapup                           ----===*/
/*====================------------------------------------====================*/
static void      o___WRAPUP__________________o (void) {;}

char
PROG_end           (void)
{
   /*---(begin)------------+-----------+-*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   endwin();        /* shut down ncurses                                      */
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   DEBUG_TOPS   yLOGS_end   ();
   return 0;
} /*======================================================*/



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
   PROG_init     ();
   PROG_args     (x_argc, x_argv);
   PROG_begin    ();
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
   PROG_init     ();
   PROG_args     (x_argc, x_argv);
   PROG_begin    ();
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> complete unit testing -------------------------------------*/
prog__unit_end          (void)
{
   PROG_end       ();
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




/*============================[[    end-code    ]]============================*/
