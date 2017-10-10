/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"



struct cACCESSOR my;


int         logger   = -1;
char        ttynum   = '0';
char        ttytyp   = '0';
char        dev         [30];
int         dev_num     = 0;
char        user        [30];
char        shell       [30];
int         veil_rpid;
int         rpid;
int         bottom            = 63;
int         center            = 63;
int         middle            = 24;
int         left              =  0;
int         left2             =  0;
int         x_knock2;   /* left of right knock     */

char        ctitle   =  0;
char        ntitle   = 14;



#define   DEBUG     if (0 == 0) 
#define   NORMAL    if (0 == 1) 
/*> "-----------------------------------------------------------|-----------------------------------------------------------",   <*/






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
      ySEC_logout (dev + 5,  "", rpid);
      break;
   default:
      break;
   }
   /*---(complete)-----------------------*/
   return;
}


char      verstring    [500];

char*      /* ---- : return library versioning information -------------------*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (verstring, 100, "%s   %s : %s", t, VER_NUM, VER_TXT);
   return verstring;
}

char
PROG_init            (int   a_argc , char *a_argv[])
{
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char        rc          = 0;
   /*---(logger)-------------------------*/
   DEBUG_TOPS   logger = yLOG_lognum ();
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   DEBUG_TOPS   yLOG_info   ("logger"    , "logger openned successfully");
   DEBUG_TOPS   yLOG_info   ("purpose"   , "light, clean, and customized getty replacement");
   DEBUG_TOPS   yLOG_info   ("namesake"  , "hestia, goddess of hearth and home");
   DEBUG_TOPS   yLOG_info   ("ver_num"   , VER_NUM);
   DEBUG_TOPS   yLOG_info   ("ver_txt"   , VER_TXT);
   /*---(close extrainuous files)--------*/
   for (i = 3; i < 256; ++i) {
      if (i == logger) continue;
      close (i);
   }
   /*---(initial settings)---------------*/
   ttynum  = '0';
   ttytyp  = '0';
   my.show_butterfly  = 'y';
   my.show_tty        = 'y';
   my.show_external   = 'y';
   my.show_knock      = 'y';
   my.show_timer      = 'y';
   my.show_left       = 'y';
   my.show_right      = 'y';
   my.show_middle     = 'y';
   my.show_judgement  = 'y';
   my.show_hint       = 'y';
   my.show_binary     = 'y';
   my.show_login      = 'y';
   my.show_status     = 'y';
   /*---(signals)------------------------*/
   /*> rc = yEXEC_signal (yEXEC_SOFT, yEXEC_TYES, yEXEC_CYES, yEXEC_LOCAL);           <*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   return 0;
}

char      /* [------] display usage help information ------------------*/
PROG_usage         (void)
{
   printf ("\n");
   printf ("usage   : hearth [URGENTS] [OPTIONS] dev_file\n");
   printf ("\n");
   printf ("version : %s, %s, %s\n", VER_NUM, __DATE__, VER_TXT);
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

char
PROG_args            (int a_argc, char **a_argv)
{
   /*---(begin)------------+-----------+-*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   /*---(locals)-------------------------*/
   int         i           = 0;             /* loop iterator -- arguments     */
   char       *a           = NULL;          /* current argument               */
   int         len         = 0;             /* argument length                */
   /*---(process args)-------------------*/
   DEBUG_ARGS   yLOG_value  ("a_argc"      , a_argc);
   for (i = 1; i < a_argc; ++i) {
      a   = a_argv[i];
      len = strlen(a);
      DEBUG_ARGS   yLOG_bullet (i           , a);
      /*---(skip debugging)--------------*/
      if      (a[0] == '@')                     continue;
      /*---(interactive)-----------------*/
      else if (strcmp(a, "--version"     ) == 0) {
         printf ("hearth (%s/%s) %s\n", VER_NUM, __DATE__, VER_TXT);
         exit (0);
      }
      /*---(visual options)--------------*/
      else if (strcmp(a, "--external"    ) == 0)  my.show_external  = 'y';
      else if (strcmp(a, "--internal"    ) == 0)  my.show_external  = 'n';
      else if (strcmp(a, "--butterfly"   ) == 0)  my.show_butterfly = 'y';
      else if (strcmp(a, "--nobutterfly" ) == 0)  my.show_butterfly = 'n';
      else if (strcmp(a, "--status"      ) == 0)  my.show_status    = 'y';
      else if (strcmp(a, "--nostatus"    ) == 0)  my.show_status    = 'n';
      else if (strcmp(a, "--timer"       ) == 0)  my.show_timer     = 'y';
      else if (strcmp(a, "--notimer"     ) == 0)  my.show_timer     = 'n';
      else if (strcmp(a, "--tty"         ) == 0)  my.show_tty       = 'y';
      else if (strcmp(a, "--notty"       ) == 0)  my.show_tty       = 'n';
      else if (strcmp(a, "--knock"       ) == 0)  my.show_knock     = 'y';
      else if (strcmp(a, "--noknock"     ) == 0)  my.show_knock     = 'n';
      else if (strcmp(a, "--left"        ) == 0)  my.show_left      = 'y';
      else if (strcmp(a, "--noleft"      ) == 0)  my.show_left      = 'n';
      else if (strcmp(a, "--right"       ) == 0)  my.show_right     = 'y';
      else if (strcmp(a, "--noright"     ) == 0)  my.show_right     = 'n';
      else if (strcmp(a, "--judgement"   ) == 0)  my.show_judgement = 'y';
      else if (strcmp(a, "--nojudgement" ) == 0)  my.show_judgement = 'n';
      else if (strcmp(a, "--hint"        ) == 0)  my.show_hint      = 'y';
      else if (strcmp(a, "--shint"       ) == 0)  my.show_hint      = 's';
      else if (strcmp(a, "--nohint"      ) == 0)  my.show_hint      = 'n';
      /*---(usage/help)------------------*/
      else if (strcmp(a, "-h"            ) == 0)  PROG_usage ();
      else if (strcmp(a, "--help"        ) == 0)  PROG_usage ();
      /*---(complex)---------------------*/
      else if (strcmp(a, "--hostname"    ) == 0) {
         if (i + 1 < a_argc) {
            strcpy (my.host_name, a_argv[i + 1]);
            ++i;
         }
      }
      else if (strcmp(a, "--cluster"     ) == 0) {
         /* not used at this time   */
         if (i + 1 < a_argc) {
            ++i;
         }
      }
      /*---(device)----------------------*/
      else if (a [0] == '/') {
         ttynum  = a[strlen (a) - 1];
         if (a[5] == 'p')  ttytyp = '0';
         else              ttytyp = '1';
         strcpy (dev, a);
         DEBUG_ARGS   yLOG_info   ("tty"       , dev);
         dev_num = ttynum - '0';
      }
   }  /*---(done)------------------------*/
   /*> /+---(show args)----------------------+/                                              <* 
    *> DEBUG_ARGS  {                                                                         <* 
    *>    printf ("arguments are...\n");                                                     <* 
    *>    printf ("   --butterfly      %c   show butterfly image\n"  , my.show_butterfly);   <* 
    *>    printf ("   --status         %c   show upper status line\n", my.show_status);      <* 
    *>    printf ("   --timer          %c   show timer countdown\n"  , my.show_timer);       <* 
    *>    printf ("\n");                                                                     <* 
    *> }                                                                                     <*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   return 0;
}

char
PROG_begin         (void)
{
   /*---(begin)------------+-----------+-*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   /*---(locals)-----------+-----------+-*/
   int         i           = 0;
   char        rc          = 0;
   tSTAT       s;
   /*---(randomizer)---------------------*/
   DEBUG_PROG   yLOG_note   ("preparing randomizer seed");
   srand (time(NULL));
   /*---(test dev)-----------------------*/
   rc = lstat (dev, &s);
   if  (rc < 0) {
      DEBUG_PROG   yLOG_info   ("device"    , "FATAL, device does not exist");
      DEBUG_PROG   yLOG_exit   (__FUNCTION__);
      return -1;
   }
   /*---(fonts)--------------------------*/
   font [0].p  = &alligator;
   font [1].p  = &chunky;
   font [2].p  = &goofy;
   font [3].p  = &binary;
   font [4].p  = &basic;
   font [5].p  = &dots;
   font [6].p  = &chunky_full;
   /*---(curses)-------------------------*/
   CURS_init  ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   return   0;
}

char
PROG_end           (void)
{
   /*---(begin)------------+-----------+-*/
   DEBUG_TOPS   yLOG_enter  (__FUNCTION__);
   CURS_wrap   ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   DEBUG_TOPS   yLOG_end     ();
   return 0;
} /*======================================================*/


char       /*----: set up programgents/debugging -----------------------------*/
PROG_testquiet     (void)
{
   char       *x_args [1]  = { "hearth" };
   yURG_logger (1, x_args);
   PROG_init   (1, x_args);
   yURG_urgs   (1, x_args);
   PROG_args   (1, x_args);
   PROG_begin  ();
   return 0;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG_testloud      (void)
{
   char       *x_args [2]  = { "hearth_unit", "@@kitchen"    };
   yURG_logger (2, x_args);
   PROG_init   (2, x_args);
   yURG_urgs   (2, x_args);
   PROG_args   (2, x_args);
   PROG_begin  ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG_testend       (void)
{
   PROG_end       ();
   return 0;
}



/*============================[[    end-code    ]]============================*/
