/*============================[[    beg-code    ]]============================*/
#include    "hearth.h"




char
FAKE_collect         (char a_mode, char *a_input, char *a_hint)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_loop      =    0;
   char        x_ch        =  ' ';
   char        x_rc        =    0;
   /*---(header)-------------------------*/
   yLOG_enter   (__FUNCTION__);
   yLOG_char    ("a_mode"    , a_mode);
   yLOG_point   ("a_info"    , a_input);
   yLOG_point   ("a_hint"    , a_hint);
   /*---(defense)------------------------*/
   --rce;  if (a_input == NULL) {
      yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_hint  == NULL) {
      yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare input)------------------*/
   strlcpy (a_input, "", LEN_DESC);
   /*---(display hint)-------------------*/
   if (a_mode == 'h') {
      yLOG_note    ("display hint");
      mvprintw ( 7,  0,  "%s", a_hint);
   }
   /*---(gather input)-------------------*/
   --rce;
   while (1) {
      yLOG_value   ("x_loop"    , x_loop);
      /*---(get character)---------------*/
      if (x_rc >= 0) {
         if (a_mode == 'i') {
            yLOG_note    ("interactive mode, get character from user");
            x_ch = getch ();
         } else {
            yLOG_note    ("test mode, get character from input string");
            x_ch = a_hint [x_loop];
         }
      } else {
         x_ch = ' ';
      }
      yLOG_value   ("x_ch"      , x_ch);
      /*---(check special chars)---------*/
      if (x_ch   == K_ESCAPE) {
         yLOG_note    ("escape, exit before completion");
         yLOG_exitr   (__FUNCTION__, rce);
         x_rc = rce;
         break;
      }
      if (x_ch   == K_RETURN) {
         yLOG_note    ("return, input complete");
         break;
      }
      if (x_ch   == K_NULL  ) {
         yLOG_note    ("end of input with no return, terminate");
         x_rc = rce - 1;
         break;
      }
      if (x_ch   == -1) {
         yLOG_note    ("error, input terminated");
         x_rc = rce - 2;
         break;
      }
      /*---(prepare)---------------------*/
      ++x_loop;
      /*---(limits)----------------------*/
      if (x_loop >= 25)  {
         yLOG_note    ("way too many characters, terminate");
         break;
      }
      if (x_rc <   0)  {
         yLOG_note    ("already in error mode, silently ignore");
         continue;
      }
      if (x_loop >=  5)  {
         yLOG_note    ("too many characters, input ignored silently");
         x_rc = rce - 3;
         continue;
      }
      if (x_ch < K_SPACE)  {
         yLOG_note    ("unknown special character, input ignored silently");
         x_rc = rce - 4;
         continue;
      }
      /*---(process character)-----------*/
      a_input [x_loop - 1] = x_ch;
      a_input [x_loop    ] = '\0';
      /*---(done)------------------------*/
   }
   /*---(final defense)------------------*/
   rce -= 10;  if (strlen (a_input) < 1) {
      yLOG_note    ("return only input string, terminate");
      x_rc  = rce;
   }
   /*---(check return code)--------------*/
   yLOG_value   ("x_rc"      , x_rc);
   if (x_rc < 0) {
      strlcpy (a_input, "((error))", LEN_DESC);
      yLOG_note    ("ended in error status");
      return x_rc;
   }
   /*---(complete)-----------------------*/
   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
FAKE_tarpit          (void)
{
}

char         /*--> fake lead door ------------------------[ leaf   [ ------ ]-*/
FAKE_door          (void)
{
   /*---(design notes)-------------------*/
   /*
    *  this is a simplistic test to enter the true login screen, but its a
    *  little good as it requires reading the prompt and responding.
    *
    *  all the charcters would already be in the buffer as hestia doesn't pass
    *  control until a newline is entered.
    *
    *  four letter string is expected...
    *      1) # (hash)
    *      2) second letter of host name
    *      3) second number of host number
    *      4) enter key
    *
    */
   /*> /+---(begin)--------------------------+/                                                 <* 
    *> yLOG_enter  (__FUNCTION__);                                                              <* 
    *> /+---(locals)-----------+-----------+-+/                                                 <* 
    *> char        ch          = ' ';                                                           <* 
    *> char        part        = '#';                                                           <* 
    *> char        status      = '-';                                                           <* 
    *> int         loop        = 0;                                                             <* 
    *> int         secs        = 0;                                                             <* 
    *> int         count       = 0;                                                             <* 
    *> int         pos_x       = 0;                                                             <* 
    *> char        prompt      [100]       = "";                                                <* 
    *> char        test        [100]       = "";                                                <* 
    *> char        input       [100]       = "";                                                <* 
    *> /+---(check initial character)--------+/                                                 <* 
    *> sprintf (test, "%c%c%c", host_name[0], host_name[5], host_name[2]);                      <* 
    *> /+> mvprintw ( 7,  0,  "%s", test);                                                <+/   <* 
    *> loop    = 0;                                                                             <* 
    *> while (1) {                                                                              <* 
    *>    ch = getch ();                                                                        <* 
    *>    if (ch ==  -1 )   break;                                                              <* 
    *>    if (ch == '\n')   break;                                                              <* 
    *>    if (loop < 20)  {                                                                     <* 
    *>       input [loop    ] = ch;                                                             <* 
    *>       input [loop + 1] = '\0';                                                           <* 
    *>    }                                                                                     <* 
    *>    ++loop;                                                                               <* 
    *> }                                                                                        <* 
    *> /+> mvprintw ( 8,  0,  "%s", input);                                               <+/   <* 
    *> if (strcmp (test, input) == 0) {                                                         <* 
    *>    part   = 'D';                                                                         <* 
    *>    status = 'A';                                                                         <* 
    *> } else {                                                                                 <* 
    *>    /+---(prompt)-------------------------+/                                              <* 
    *>    sprintf (prompt, "cluster (%02d) host <%s> login: %s", dev_num, host_name, input);    <* 
    *>    mvprintw ( 0,  0,  "%s", prompt);                                                     <* 
    *>    sprintf (prompt, "password: ");                                                       <* 
    *>    mvprintw ( 1,  0,  "%s", prompt);                                                     <* 
    *>    pos_x = strlen (prompt);                                                              <* 
    *>    /+---(loop through input)-------------+/                                              <* 
    *>    loop    = 0;                                                                          <* 
    *>    secs    = 0;                                                                          <* 
    *>    part    = 'Z';                                                                        <* 
    *>    status  = 'F';                                                                        <* 
    *>    while (1) {                                                                           <* 
    *>       /+---(get next character)----------+/                                              <* 
    *>       ch = getch ();                                                                     <* 
    *>       /+---(timeout)---------------------+/                                              <* 
    *>       ++loop;                                                                            <* 
    *>       if (loop % 5 == 0) ++secs;                                                         <* 
    *>       if ( secs >  15) {                                                                 <* 
    *>          sleep (5);                                                                      <* 
    *>          break;                                                                          <* 
    *>       }                                                                                  <* 
    *>       /+---(enter)-----------------------+/                                              <* 
    *>       if (ch == '\n') {                                                                  <* 
    *>          sleep (5);                                                                      <* 
    *>          break;                                                                          <* 
    *>       }                                                                                  <* 
    *>       /+---(wait for next)---------------+/                                              <* 
    *>       ++count;                                                                           <* 
    *>       usleep ( 100000);                                                                  <* 
    *>    }                                                                                     <* 
    *> }                                                                                        <* 
    *> /+---(complete)-----------------------+/                                                 <* 
    *> if (status == 'A')  return 0;                                                            <* 
    *> return -5;                                                                               <*/
} /*======================================================*/

