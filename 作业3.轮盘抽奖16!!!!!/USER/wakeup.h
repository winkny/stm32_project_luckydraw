#ifndef __WAKEUP_H
#define __WAKEUP_H
#include "sys.h"

#define WKUP_KD PAin(0)

void Sys_Standby(void);
void Sys_Enter_Standby(void);//≥ı ºªØ
u8 Check_WKUP(void) ;

    
#endif
