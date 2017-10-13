/*===============================[[ beg-code ]]===============================*/

/*===[[ HEADER ]]==============================================================#

 *   focus         : (SA) system_admin
 *   niche         : (au) authentication
 *   application   : hestia      (ancient greek goddess of hearth and home)
 *   purpose       : provide light, reliable, and secure getty services
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : ansi-c      (wicked, limitless, universal, and everlasting)
 *   dependencies  : yLOG, yEXEC
 *   size          : small       (less than 2,000 slocL)
 * 
 *   author        : the_heatherlys
 *   created       : 2012-01
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 *
 *   simplicity is prerequisite for reliability and security, but logging
 *   and unit testing can not be neglected
 * 
 */
/*===[[ SUMMARY ]]=============================================================*

 *   hestia is a light, reliable, and secure verion of the classic posix-defined
 *   getty terminal services which allows for additional logging, verification,
 *   flexiblity, and restartability.
 *
 *
 *
 *   getty is the generic name for a program which manages a terminal line,
 *   handles the login process, and protects the system from unauthorized
 *   access.
 *
 *   alternatives...
 *      -- getty        : original configured through conf file
 *      -- agetty       : alternative configured using arguments
 *      -- mingetty     : minimal version for virtual terminals only
 *      -- ngetty       : handles multiple tty in one instance
 *      -- mgetty       : more flexible to handle fax, voice, and others
 *      -- fbgetty      : adds framebuffer and image support
 *
 */

/*
 *  original
 *     - asks for username and password with simple prompts
 *
 *  minimal
 *     - input username and password without any ques at all
 *
 *  grabled
 *     - passes a small strip of digits and you must scramble also
 *
 *  complex
 *     - banner page with clues in ascii art
 *
 *
 *
 *
 *  authentication is about confirming the truth of an identity or fact
 *
 *  1st, accepting proof given by a credible person
 *  2nd, comparing attributes to what is known of objects of that origin
 *  3rd, documentation or external affirmations
 *
 *  ownership   : something the user has (id card, token, phone, bracelet ...)
 *  knowledge   : something the user knows (password, challenge-response, ...)
 *  inherence   : something the user is (biometrics, signature, voice, ...)
 *
 *  two-factor  : bankcard and pin, token and password, etc
 *
 *  authentication (Au) is proving you are who you say you are
 *  authorization  (Az) is proving you permitted to do what you are trying to do
 *
 *
 *
 */
/*
 *   the goddess hekate is the guardian of gates and doorways and is sometimes
 *   shown as triple bodied
 *
 *   the job of this piece of software is to...
 *      - open and initialize a tty line (/dev file)
 *      - read a login name
 *      - invoke /bin/login
 *
 *   hekate seeks to be a clean, simplified getty that takes out the wierd
 *   features and focuses on our normal systems.
 *      - runs as a single daemon (ngetty)
 *      - always asks for user name
 *      - has a tiny securyty extra in user name
 *      - does not use the /etc/issue file or "-f <issue_file>"
 *      - does not use /etc/ttys, /etc/gettydefs, /etc/gettytab
 *      - can not change the login program using "-l <login_program>"
 *      - only used for the local host so no "-H <host_name>"
 *      - time out is automatic so no "-t <timeout>"
 *      - always assume 8-bit clean
 *      - all terminals are assumed to be vt102 (like eterm, xterm, ...)
 *      - let login take care of the fact root can not login except using su
 *      - no modems
 *
 *
 *
 *  each time hestia prompts for a login it uses a different host name
 *
 */


/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef HEARTH
#define HEARTH loaded


/* rapidly evolving version number to aid with visual change confirmation ----*/
#define     VER_NUM          "2.0h"
#define     VER_TXT          "binary working now"


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
#include    <yURG.h>         /* CUSTOM : heatherly urgent processing          */
#include    <yLOG.h>         /* CUSTOM : heatherly program logging            */
#include    <yEXEC.h>        /* CUSTOM : heatherly execution services         */
#include    <ySEC.h>         /* CUSTOM : heatherly security logging           */
#include    <ySTR.h>         /* CUSTOM : heatherly string handling            */
#include    <yVAR.h>         /* CUSTOM : heatherly variable testing           */



#define     LOGIN       "/bin/login"
#define     MAX_ROW     64
#define     MAX_COL     180
#define     MAX_HOST    500

/*---(string length)------------------*/
#define     LEN_RECD    4000
#define     LEN_UNIT    500
#define     LEN_STR     500
#define     LEN_DESC    100
#define     LEN_LABEL   20
#define     LEN_ABBR    10
/*---(font constants)-------*/
#define     MAX_FONT       50
#define     MAX_WIDTH     400
#define     MAX_HEIGHT    400
#define     FONT_FULL      'f'       /* [a-z][0-9] */
#define     FONT_ALPHA     'a'       /* [a-z]      */
#define     FONT_NUMS      'n'       /* [0-9]      */
#define     FONT_BINARY    'b'       /* [0-1]      */


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


/*---(fonts)------------------------------------------------------------------*/
struct cFONT {
   char        name        [20];       /* name for lookup                     */
   char        range;                  /* type of symbols, alpha, nums, ...   */
   char       *ptr;                    /* pointer to font structure           */
   char        tall;                   /* height of standard symbol           */
   char        wide;                   /* width of standard symbol            */
   char        yoff;                   /* space after a row, before next      */
   char        xoff;                   /* space after a col, before next      */
   char        gap;                    /* horizontal gap in data structure    */
   char        empty;                  /* character used for empty space      */
};

extern char        hosties     [MAX_HOST][20];
extern char        butterfly   [40] [MAX_ROW] [MAX_COL];



struct cFONT       g_fonts     [50];
extern int         g_nfont;
extern int         g_cfont;




extern int         logger;
extern char        ttynum;
extern char        dev         [30];
extern char        shell       [30];
extern int         veil_rpid;
extern int         bottom;
extern int         center;
extern int         middle;
extern int         left;
extern int         left2;
extern int         x_knock2;
extern char        ctitle;
extern char        ntitle;



/*---(run modes)------------*/
char        g_modes      [20];  /* valid run modes                            */
#define     RUN_UNIT     'u'    /* unit test mode                             */
#define     RUN_QUIET    'q'    /* ncurses mode, but no screen output/waits   */
#define     RUN_FORCE    'f'    /* ncurses mode, but feed input as string     */
#define     RUN_USER     'i'    /* ncurses mode, with screen output           */
#define     RUN_HINT     'h'    /* FAKE_USER plus display a hint              */
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


struct cACCESSOR {
   /*---(mode)-------------------*/
   char        run_mode;               /* indicate test vs real               */
   /*---(fake)-------------------*/
   char        use_fake;               /* display and use fake (y/-)          */
   int         dev_num;                /* terminal device number              */
   char        host_name   [50];       /* host number and name string         */
   int         cluster;
   char        tty_type;
   char        fake_user   [50];
   char        show_counters;          /* show counters on screen             */
   /*---(veil)-------------------*/
   char        magic_num    [20];       /* magic number used on this getty     */
   char        show_butterfly;
   char        show_tty;
   char        show_external;
   char        show_knock;
   char        show_timer;
   char        show_left;
   char        show_right;
   char        show_middle;
   char        show_judgement;
   char        show_hint;
   char        show_binary;
   char        show_login;
   char        show_status;
   char        user_name   [30];
};
extern    struct cACCESSOR my;




typedef struct cENTRY tENTRY;
struct   cENTRY {
   char     knock       [ 20];
   char     prefix      [ 20];
   char     rot         [ 20];
   char     username    [ 20];
   char     user_fix    [ 20];
   char     infix       [ 20];
   char     password    [ 20];
   char     pointer     [ 20];
   char     suffix      [ 20];
};
tENTRY      entry;

typedef struct cTITLES tTITLES;
struct    cTITLES {
   char     language    [20];
   char     cluster     [20];
   char     seq         [20];
   char     date        [20];
   char     host        [20];
   char     user        [20];
   char     token       [20];
   char     password    [20];
   char     attempt     [20];
};
tTITLES     titles      [30];

char        PROG_init            (int   a_argc , char *a_argv[]);
char        PROG_urgsmass        (char  a_set  , char a_extra);
char        PROG_urgs            (int   a_argc , char *a_argv[]);
char        PROG_args            (int   a_argc , char *a_argv[]);
char        PROG_usage           (void);
char        PROG_begin           (void);
char        PROG_final           (void);

char        PROG_testloud        (void);
char        PROG_testquiet       (void);
char        PROG_testend         (void);

char        CURS_init            (void);
char        CURS_wrap            (void);

char        VEIL_init            (void);
char        VEIL_knocks          (void);
char        VEIL_knock           (void);
char        VEIL_butterfly       (int a_x, int a_y);
char        VEIL_tty             (int a_x, int a_y);
/*---(fake)--------------------*/
char        FAKE_init            (char a_mode, char *a_user);
char        FAKE_collect         (char a_mode, char *a_input, char *a_key);
char        FAKE_check           (             char *a_input, char *a_key);
char        FAKE_tarpit          (char a_mode, char *a_input, int  *a_pts);
char        FAKE_door            (void);

/*---(font)--------------------*/
char        FONT_init            (void);
char        FONT__find           (char *a_font);
char        FONT__index          (char a_range, int a_letter);
char        FONT_wide            (char *a_font);
char        FONT_tall            (char *a_font);
char        FONT_letter          (char *a_font, char a_num, int a_y, int a_x);
char*       FONT__unit           (char *a_question, int a_num);

int         audit_find         (char *a_dev, int  a_pid, int *a_pos);
char        audit_login        (char *a_dev, char *a_user, int a_rpid);
char        audit_fail         (char *a_dev, char a_type);
char        audit_logout       (char *a_dev, int a_rpid, int a_rc);
char        audit_system       (char a_type);

char*       unit_accessor      (char*, int);


extern char        dev         [30];
extern char        shell       [30];
extern int         veil_rpid;
extern int         rpid;



extern      char          unit_answer [LEN_UNIT];


#endif
/*===============================[[ end-code ]]===============================*/
