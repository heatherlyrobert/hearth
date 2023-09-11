/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"

/*> int         rpid;                                                                 <*/

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
   int         x, y;
   int         x_ch        =    0;
   /*---(debugging)----------------------*/
   rc = PROG_urgents (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   if (rc <  0) { PROG_shutdown (); return -1; }
   /*---(initialization)-----------------*/
   rc = PROG_startup (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("startup"   , rc);
   if (rc <  0) { PROG_shutdown (); return -2; }
   /*---(initialize)---------------------*/
   /*> if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);                              <* 
    *> if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);                              <* 
    *> if (rc >= 0)  rc = PROG_init    ();                                            <* 
    *> if (rc >= 0)  rc = PROG_args    (a_argc, a_argv);                              <* 
    *> if (rc >= 0)  rc = PROG_begin   ();                                            <*/
   if (rc >= 0)  rc = PROG_dawn   ();
   --rce;  if (rc <  0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      PROG_shutdown ();
      return rce;
   }
   /*---(prepare)------------------------*/
   g_vals.bfly_size = 'L';
   my.topplus = 5;
   /*---(normal)-------------------------*/
   while (my.status == STATUS_GOOD || my.status == STATUS_REFRESH) {
      /*> show_init ();                                                               <*/
      PROG_normal ();
   }
   /*---(failure)------------------------*/
   if (my.judgement != 'Y') {
      PROG_lockout ();
      sleep (my.after);
      clear       ();
      PROG_shutdown ();
      printf  ("\033c");
      return -1;
   }
   /*---(success)------------------------*/
   sleep (2);
   clear       ();
   printf  ("\033c");
   PROG_launch ();
   /*---(complete)-----------------------*/
   PROG_shutdown ();
   return 0;
   /*---(prepare)------------------------*/
   /*> chown  (my.dev, (my.pass)->pw_uid, 0);                                                            <* 
    *> chmod  (my.dev, 0700);                                                                            <* 
    *> strcpy (my.shell, (my.pass)->pw_shell);                                                           <* 
    *> ySEC_active (my.pid, my.entry_text, my.phase, my.judgement, my.status, my.result, my.user_fix);   <* 
    *> ySEC_login  (my.dev, my.user_fix, my.pid);                                                        <* 
    *> ioctl (0, TIOCNOTTY, NULL);    /+ detach, from login.c                  +/                        <* 
    *> setsid();                      /+ start new session                     +/                        <* 
    *> ioctl (0, TIOCSCTTY,    1);                                                                       <*/
   /*---(launch)-------------------------*/
   /*> rpid = yEXEC_run ("launching tty", my.user_fix, "/bin/bash", YEXEC_BASH, YEXEC_FULL, YEXEC_FORK, EXEC_FILE);                <* 
    *> /+> rpid = yEXEC_run   (EXEC_FILE, "launching tty", my.user_name, "/bin/bash", YEXEC_BASH, YEXEC_FULL, YEXEC_FORK);   <+/   <* 
    *> rc = ySEC_login  (my.dev + 5, my.user_fix, rpid);                                                                           <* 
    *> DEBUG_PROG   yLOG_value   ("rc"     , rc);                                                                                  <* 
    *> /+---(wait)---------------------------+/                                                                                    <* 
    *> while (1) {                                                                                                                 <* 
    *>    ++count;                                                                                                                 <* 
    *>    if ((count % 720) == 0)  DEBUG_PROG   yLOG_sync ();                                                                      <* 
    *>    sleep (5);                                                                                                               <* 
    *>    ri = yEXEC_check ("wait for done", rpid, &x_return);                                                                     <* 
    *>    DEBUG_PROG   yLOG_pair   (count, ri);                                                                                    <* 
    *>    if (ri == 0) {                                                                                                           <* 
    *>       DEBUG_PROG   yLOG_info   ("shell_exit", my.dev);                                                                      <* 
    *>       break;                                                                                                                <* 
    *>    }                                                                                                                        <* 
    *> }                                                                                                                           <* 
    *> /+---(wrapup)-------------------------+/                                                                                    <* 
    *> ySEC_complete (my.pid, 'y');                                                                                                <* 
    *> ySEC_logout   (my.dev,  "", my.pid);                                                                                        <* 
    *> PROG_end      ();                                                                                                           <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}


/*============================[[    end-code    ]]============================*/
