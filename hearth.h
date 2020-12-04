/*===============================[[ beg-code ]]===============================*/
#ifndef HEARTH
#define HEARTH loaded




/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "SA (system administration)"
#define     P_NICHE     "au (authentication)"
#define     P_SUBJECT   "terminal login handler"
#define     P_PURPOSE   "simple, reliable, experimental, and secure terminal login"

#define     P_NAMESAKE  "hestia-polyolbos (full of blessings)"
#define     P_HERITAGE  "virgin goddess of hearth, home, architecture, and eternal flame"
#define     P_IMAGERY   "regal, but modestly cloaked and vieled woman with a wooden staff"
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "yEXEC, ySEC, ySTR"           

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2012-01"

#define     P_VERMAJOR  "2.-, second revision for production"
#define     P_VERMINOR  "2.1, building up new version"
#define     P_VERNUM    "2.2a"
#define     P_VERTXT    "new code is messy but working, need huge cleaning"

#define     P_USAGE     "hearth [OPTIONS]"
#define     P_DEBUG     "hearth_debug [URGENTS] [OPTIONS]"

#define     P_SUMMARY   \
 "hestia's hearth is a simple, reliable, experimental, and secure visual login¦" \
 "program called by hestia (the getty daemon) which manages display of key data,¦" \
 "gathering of input, authentication of a user, launching of a session.¦"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_SAYING    "[grow a set] and build your wings on the way down (bradbury)"

#define     P_ALTERNS   "getty, agetty, mingetty, ngetty, mgetty, fbgetty, ..."
#define     P_REMINDER  "there are many better options, but i *own* this top-to-bottom"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/



/* configuration files -------------------------------------------------------*/
#define     CONF_FILE        "/etc/hestia.conf"
#define     TEMP_FILE        "/tmp/hestia_ttys"
#define     EXEC_FILE        "/var/log/yLOG/hestia_exec"
#define     HUTMP_FILE       "/var/log/hestia.active"
#define     HWTMP_FILE       "/var/log/hestia.logging"
#define     HSTAT_FILE       "/var/log/khaos.hestia"


#include    <stdio.h>                  /* ANSI-C    i/o library               */
#include    <stdlib.h>                 /* ANSI-C    general library           */
#include    <string.h>                 /* ANSI-C    c-string library          */
#include    <signal.h>                 /* ANSI-C    singal handling           */
#include    <time.h>
#include    <fcntl.h>
#include    <poll.h>
#include    <unistd.h>                 /* stat(),crpyt()                      */
#include    <sys/types.h>              /* stat()                              */
#include    <sys/stat.h>               /* stat()                              */
#include    <termios.h>
#include    <sys/ioctl.h>
#include    <math.h>


#include    <ncurses.h>                /* XSI_STD   cursor optimization       */

#include    <pwd.h>                    /* LINUX     password access           */
#include    <shadow.h>                 /* LINIX     password shadow access    */


/*===[[ CUSTOM LIBRARIES ]]===================================================*/
#include    <yEXEC.h>        /* CUSTOM : heatherly execution services         */
#include    <yPARSE.h>       /* CUSTOM : heatherly input parser               */
#include    <yURG.h>         /* CUSTOM : heatherly urgent processing          */
#include    <yLOG.h>         /* CUSTOM : heatherly program logging            */
#include    <ySEC.h>         /* CUSTOM : heatherly security logging           */
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yVAR.h>         /* CUSTOM : heatherly variable testing           */



#define     LOGIN       "/bin/login"
#define     MAX_BFLY    50
#define     CNT_BFLY    16
#define     MAX_ROW     70
#define     MAX_COL     200
#define     MAX_HOST    500


/*---(string length)------------------*/
#define     LEN_RECD    4000
#define     LEN_UNIT    500
#define     LEN_STR     500
#define     LEN_DESC    100
#define     LEN_LABEL   20
#define     LEN_ABBR    10


typedef const char       cchar;
typedef unsigned char    uchar;
typedef struct tm        tTIME;
typedef struct stat      tSTAT;
typedef struct passwd    tPASSWD;
typedef struct spwd      tSHADOW;


#define     K_RETURN      10
#define     K_ESCAPE      27
#define     K_BS         127
#define     K_SPACE       32
#define     K_NULL         0



void             /* [------] receive signals ---------------------------------*/
PROG_signal        (int a_signal, siginfo_t *a_info, void *a_nada);



extern int         s_butter;
extern char        butterfly   [MAX_BFLY] [MAX_ROW] [MAX_COL];
extern char        g_bfly_lrg  [MAX_BFLY] [MAX_ROW] [MAX_COL];
extern char        g_bfly_med  [MAX_BFLY] [MAX_ROW] [MAX_COL];
extern char        g_bfly_sml  [MAX_BFLY] [MAX_ROW] [MAX_COL];





extern int         logger;
extern int         veil_rpid;
extern int         bottom;
extern int         center;
extern int         middle;
extern int         left;
extern int         left2;
extern int         x_knock2;
extern char        ctitle;
extern char        ntitle;
 
#define     G_TYPE_KNOCK     " .01"
#define     G_TYPE_NUM       "0123456789"
#define     G_TYPE_ALPHA     "abcdefghijklmnopqrstuvwxyz "
#define     G_TYPE_ALNUM     "0123456789abcdefghijklmnopqrstuvwxyz "
#define     G_TYPE_USER      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_- "
#define     G_TYPE_PASS      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_-?!,.%'~^;/:()=|{}[]#&_<>$+ "
#define     G_TYPE_ESCAPE    "\x1B"

#define     PART_KNOCK       'k'
#define     PART_PREFIX      'p'
#define     PART_USERNAME    'u'
#define     PART_INFIX       'i'
#define     PART_PASSWORD    'c'
#define     PART_SUFFIX      's'
#define     PART_DONE        'd'
#define     PART_TRAILING    't'

/*---(run modes)------------*/
char        g_modes     [20];  /* valid run modes                            */
#define     RUN_AS_SHOW      's'    /* show veil only                        */

#define     RUN_UNIT    'u'    /* unit test mode                             */
#define     RUN_QUIET   'q'    /* ncurses mode, but no screen output/waits   */
#define     RUN_FORCE   'f'    /* ncurses mode, but feed input as string     */
#define     RUN_USER    'i'    /* ncurses mode, with screen output           */
#define     RUN_HINT    'h'    /* FAKE_USER plus display a hint              */
/*---(fake modes)-----------*/

#define     IF_RUN_SILENT        if (my.run_mode == RUN_UNIT || my.run_mode == RUN_QUIET)
#define     IF_RUN_REAL          if (my.run_mode != RUN_UNIT && my.run_mode != RUN_QUIET)

#define     IF_A_RUN_SILENT      if (a_mode == RUN_UNIT || a_mode == RUN_QUIET)
#define     IF_A_RUN_REAL        if (a_mode != RUN_UNIT && a_mode != RUN_QUIET)
#define     IF_A_RUN_STRING      if (a_mode == RUN_UNIT || a_mode == RUN_FORCE)


#define     FAKE_TEST    't'    /* unit test mode                             */
#define     FAKE_SILENT  's'    /* ncurses mode, but no screen output/waits   */
#define     FAKE_USER    'i'    /* ncurses mode, with screen output           */
#define     FAKE_HINT    'h'    /* FAKE_USER plus display a hint              */

#define     RUN_TEST        if (my.run_mode      == 't')
#define     RUN_REAL        if (my.run_mode      == 'r')
#define     SHOW_COUNTERS   if (my.show_counters == 'y')
#define     SHOW_HINTS      if (my.show_hint     == 'y')


#define     STATUS_GOOD      'A'  /* tentatively good                         */
#define     STATUS_FAILED    'F'  /* silent failure, allow more keys          */
#define     STATUS_SUCCESS   'S'  /* evaluated as a success                   */
#define     STATUS_NEWLINE   'N'  /* used return, immediately fail            */
#define     STATUS_TIMEOUT   'Z'  /* ran out of time                          */
#define     STATUS_REFRESH   'R'  /* esed C-r, immediately refresh            */
#define     STATUS_BREAK     'B'  /* used C-c, immediately give-up            */

#define     STATUSES_CONT    "AF"
#define     STATUSES_STOP    "SNZB"
#define     STATUSES_FAIL    "NZB"


#define     COLORS_OFF       attrset (0);
#define     COLORS_WHITE     attron (COLOR_PAIR( 1))
#define     COLORS_RED       attron (COLOR_PAIR( 9))
#define     COLORS_GREEN     attron (COLOR_PAIR(10))
#define     COLORS_CYAN      attron (COLOR_PAIR(11))
#define     COLORS_YELLOW    attron (COLOR_PAIR(12))
#define     COLORS_BLUE      attron (COLOR_PAIR(14))
#define     COLORS_MAGENTA   attron (COLOR_PAIR(18))



struct cACCESSOR {
   /*---(mode)-------------------*/
   char        run_mode;               /* indicate test vs real               */
   int         pid;                         /* hearths pid                    */
   int         ppid;                        /* hearths parent pid             */
   int         uid;                         /* hearths user id                */
   int         who         [LEN_LABEL];     /* hearths user name              */
   /*---(command line)-----------*/
   int         language;                    /* language number                */
   int         cluster;                     /* number of cluster              */
   int         host;                        /* number of host                 */
   char        dev         [LEN_LABEL];     /* tty device                     */
   /*---(looping)----------------*/
   char        status;                      /* current login status           */
   char        part;                        /* current login part             */
   int         loops;                       /* number of getch's              */
   int         secs;                        /* elapsed seconds                */
   int         chars;                       /* entered characters             */
   uchar       curr;                        /* current character              */
   char        entry_text  [LEN_DESC];      /* actual text entered            */
   char        phase;
   char        result;
   char        judgement;
   char        position;  
   int         offset;                      /* username/password spacing      */
   /*---(locations)--------------*/
   int         top;
   int         mid;
   int         bot;
   int         lef;
   int         cen;
   int         rig;
   int         topplus;
   int         lefplus;
   int         rigminus;
   /*---(fake)-------------------*/
   char        tty_type;
   char        fake_user   [50];
   /*---(veil)-------------------*/
   char        magic_num   [LEN_DESC];      /* magic number used              */
   char        username    [LEN_LABEL];     /* entered username               */
   char        user_fix    [LEN_LABEL];     /* unrotated username             */
   tPASSWD    *pass;                        /* password entry                 */
   tSHADOW    *shad;                        /* shadow entry                   */
   char        password    [LEN_LABEL];     /* entry password                 */
   int         rot;                         /* username rotation              */
   int         pointer;                     /* right side pointer             */
   char        shell       [LEN_PATH];      /* entry password                 */
   /*---(timer)------------------*/
   int         timeout;                     /* deci-seconds timeout           */
   int         lockout;                     /* deci-seconds lockout           */
   char        forever;                     /* keep auto-resetting            */
   int         after;                       /* full seconds wait after        */
   /*---(hinting)----------------*/
   char        show_hint;
   /*---(temporary)--------------*/
   char        user_name   [30];
};
extern    struct cACCESSOR my;



#define     MAX_KNOCKS         120
#define     MAX_LEFTS           60
#define     MAX_RIGHTS          80
#define     MAX_MIDS            80
#define     MAX_TOPS            40

typedef struct cVALS tVALS;
struct cVALS {
   /*---(tops)-----------------*/
   char        tops_font   [LEN_LABEL];
   int         tops_top;
   int         tops_lef;
   int         tops_len;
   /*---(lefts)----------------*/
   char        lefts       [MAX_LEFTS];
   char        lefs_font   [LEN_LABEL];
   int         lefs_top;
   int         lefs_lef;
   /*---(knocks)---------------*/
   char        knocks      [MAX_KNOCKS];
   char        noks_font   [LEN_LABEL];
   int         noks_gap;
   int         noks_top;
   int         noks_lef;
   int         noks_rig;
   /*---(rights)---------------*/
   char        rights      [MAX_RIGHTS];
   char        rigs_font   [LEN_LABEL];
   int         rigs_top;
   int         rigs_lef;
   /*---(middles)--------------*/
   char        mids        [MAX_MIDS];
   char        mids_font   [LEN_LABEL];
   int         mids_top;
   int         mids_bot;
   int         mids_lef;
   int         mids_len;
   /*---(prompt)---------------*/
   int         prom_top;
   int         prom_lef;
   /*---(timer)----------------*/
   char        timr_font   [LEN_LABEL];
   int         timr_cen;
   int         timr_mid;
   /*---(butterfly)------------*/
   int         bfly_indx;
   char        bfly_size;
   /*---(done)-----------------*/
};
extern tVALS       g_vals;



char*       PROG_version         (void);
char        PROG_usage           (void);

char        PROG_init            (void);
char        PROG_args            (int   a_argc , char *a_argv[]);
char        PROG_begin           (void);
char        PROG_final           (void);

char        prog__unit_loud      (void);
char        prog__unit_quiet     (void);
char        prog__unit_end       (void);
char        PROG_testuserdel     (cchar *a_name);
char        PROG_testuseradd     (cchar *a_name, cchar *a_pass);

char        CURS_init            (void);
char        CURS_wrap            (void);

char        VEIL_conf            (void);

char        VEIL_getchar         (void);
char        VEIL_check_user      (void);
char        VEIL_check_pass      (void);
char        VEIL_check           (char a_count, char a_ch);
char        VEIL_getcheck        (cchar *a_input);

char        VEIL_knocks          (void);
char        VEIL_knock           (void);
char        VEIL_butterfly       (void);
char        VEIL_tty             (int a_x, int a_y);
/*---(unittest)----------------*/
char*       VEIL__unit           (char *a_question, int a_num);
char        VEIL__unit_set       (int a_count, int a_char);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345*/
/*---(fake)--------------------*/

char        gate_prompt             (void);
char        gate__password          (void);
char        gate__collect           (char *a_input);
char        gate__check             (char *a_input, char *a_key);
char        gate_load               (char *a_user);
char        gate_main               (void);

char        show_message            (char *a_msg);
char        show_init               (void);
char        show_status             (void);
char        show_timer              (void);
char        show_all                (void);
char        show_sizing             (void);
char        show_left               (void);
char        show_right              (void);
char        show_block              (void);
char        show_random             (void);
char        show_ascii              (void);
char        show_butterfly          (void);
char        show_rain               (void);
char        show_getchar            (void);

char        valid_init              (void);
char        valid_reset             (void);
char        valid__knock            (void);
char        valid__prefix           (void);
char        valid__user             (void);
char        valid__infix            (void);
char        valid__pass             (void);
char        valid__suffix           (void);
char        valid__done             (void);
char        valid__getchar          (void);
char        valid_main              (void);
char*       valid__unit             (char *a_question, int a_num);

char        FAKE_init            (char a_mode, char *a_user);
char        FAKE_check           (             char *a_input, char *a_key);
char        FAKE_tarpit          (char a_mode, char *a_input, int  *a_pts);


int         audit_find         (char *a_dev, int  a_pid, int *a_pos);
char        audit_login        (char *a_dev, char *a_user, int a_rpid);
char        audit_fail         (char *a_dev, char a_type);
char        audit_logout       (char *a_dev, int a_rpid, int a_rc);
char        audit_system       (char a_type);

char*       unit_accessor      (char*, int);


extern int         veil_rpid;
extern int         rpid;



extern      char          unit_answer [LEN_UNIT];


#endif
/*===============================[[ end-code ]]===============================*/
