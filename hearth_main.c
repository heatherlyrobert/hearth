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
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_init    (a_argc, a_argv);
   if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_args    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_begin   ();
   if (rc >= 0)  rc = PROG_final   ();
   --rce;  if (rc <  0) {
      DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
      PROG_end ();
      return rce;
   }
   /*---(check fake door)----------------*/
   if (my.use_fake == 'y') {
      if (rc == 0)  rc = FAKE_door    ();
      --rce;  if (rc != 0) {
         DEBUG_TOPS   yLOG_exitr   (__FUNCTION__, rce);
         PROG_end    ();
         return rce;
      }
   }


   /*---(input)--------------------------*/
   DEBUG_TOPS   yLOG_note   ("begin prompt/input cycle");
   while (1) {
      VEIL_init  ();
      VEIL_show  ();
      refresh();
      ri = get_login ();
      if (ri <= 0) break;
      DEBUG_TOPS   yLOG_note   ("refresh");
   }
   PROG_end    ();
   DEBUG_TOPS   yLOG_note   ("done entry processing");
   DEBUG_TOPS   yLOG_value  ("entry ri"  , ri);
   /*---(processing)---------------------*/
   if (ri == 0) {
      DEBUG_TOPS   yLOG_note   ("handle successful login");
      /*---(log)-------------------------*/
      DEBUG_TOPS   yLOG_note   ("write utmp entry");
      DEBUG_TOPS   yLOG_note   ("calling shell");
      DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
      /*---(detach)----------------------*/
      ioctl (0, TIOCNOTTY, NULL);    /* detach, from login.c                  */
      setsid();                      /* start new session                     */
      ioctl (0, TIOCSCTTY,    1);
      /*---(launch)----------------------*/
      rpid = yEXEC_run   (EXEC_FILE, "launching tty", my.user_name, "/bin/bash", yEXEC_BASH, yEXEC_NORM, yEXEC_FORK);
      rc = ySEC_login  (dev + 5, entry.user_fix, rpid);
      DEBUG_TOPS   yLOG_value   ("rc"     , rc);
      /*---(done)------------------------*/
      while (1) {
         ++count;
         if ((count % 720) == 0)  DEBUG_TOPS   yLOG_sync ();
         sleep (5);
         ri = yEXEC_check ("wait for done", rpid);
         DEBUG_TOPS   yLOG_pair   (count, ri);
         if (ri == 0) {
            DEBUG_TOPS   yLOG_info   ("shell_exit", dev);
            break;
         }
      }
   } else {
      DEBUG_TOPS   yLOG_note   ("handle FAILED login");
      DEBUG_TOPS   yLOG_info   ("login_fail", dev);
   }
   /*---(complete)-----------------------*/
   audit_logout(dev, veil_rpid, ri);
   ySEC_logout (dev + 5,  "", rpid);
   DEBUG_TOPS   yLOG_exit   (__FUNCTION__);
   DEBUG_TOPS   yLOG_value  ("returning" , ri);
   DEBUG_TOPS   yLOG_end    ();
   return ri;
}


/*============================[[    end-code    ]]============================*/
