/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"

int         rpid;

int              /* [------] driver for hearth -------------------------------*/
main               (int a_argc, char **a_argv)
{
   /*---(locals)-----------+-----------+-*/
   char        rce;                    /* return code for errors              */
   char        rc;                     /* return code as char                 */
   int         ri;                     /* return code as integer              */
   int         count = 0;              /* check cycle counter                 */
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_init    (a_argc, a_argv);
   if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_args    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_begin   ();
   --rce;  if (rc <  0) {
      yLOG_exitr   (__FUNCTION__, rce);
      PROG_end ();
      return rce;
   }
   /*---(check fake door)----------------*/
   if (rc == 0)  rc = FAKE_door   ();
   --rce;  if (rc != 0) {
      yLOG_exitr   (__FUNCTION__, rce);
      PROG_end    ();
      return rce;
   }
   /*---(input)--------------------------*/
   yLOG_note   ("begin prompt/input cycle");
   while (1) {
      magic  ();
      prompt (0);
      refresh();
      ri = get_login ();
      if (ri <= 0) break;
      yLOG_note   ("refresh");
   }
   PROG_end    ();
   yLOG_note   ("done entry processing");
   yLOG_value  ("entry ri"  , ri);
   /*---(processing)---------------------*/
   if (ri == 0) {
      yLOG_note   ("handle successful login");
      /*---(log)-------------------------*/
      yLOG_note   ("write utmp entry");
      yLOG_note   ("calling shell");
      yLOG_exit   (__FUNCTION__);
      /*---(detach)----------------------*/
      ioctl (0, TIOCNOTTY, NULL);    /* detach, from login.c                  */
      setsid();                      /* start new session                     */
      ioctl (0, TIOCSCTTY,    1);
      /*---(launch)----------------------*/
      rpid = yEXEC_run   (EXEC_FILE, "launching tty", user, "/bin/bash", yEXEC_BASH, yEXEC_NORM, yEXEC_FORK);
      rc = ySEC_login  (dev + 5, entry.user_fix, rpid);
      yLOG_value   ("rc"     , rc);
      /*---(done)------------------------*/
      while (1) {
         ++count;
         if ((count % 720) == 0)  yLOG_sync ();
         sleep (5);
         ri = yEXEC_check ("wait for done", rpid);
         yLOG_pair   (count, ri);
         if (ri == 0) {
            yLOG_info   ("shell_exit", dev);
            break;
         }
      }
   } else {
      yLOG_note   ("handle FAILED login");
      yLOG_info   ("login_fail", dev);
   }
   /*---(complete)-----------------------*/
   audit_logout(dev, veil_rpid, ri);
   ySEC_logout (dev + 5,  "", rpid);
   yLOG_exit   (__FUNCTION__);
   yLOG_value  ("returning" , ri);
   yLOG_end    ();
   return ri;
}


/*============================[[    end-code    ]]============================*/
