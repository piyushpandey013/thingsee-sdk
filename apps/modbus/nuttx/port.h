/****************************************************************************
 * apps/modbus/nuttx/port.h
 *
 * FreeModbus Library: NuttX Port
 * Copyright (c) 2006 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __APPS_MODBUS_NUTTX_PORT_H
#define __APPS_MODBUS_NUTTX_PORT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define INLINE
#define PR_BEGIN_EXTERN_C  extern "C" {
#define PR_END_EXTERN_C    }

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

#define ENTER_CRITICAL_SECTION( ) vMBPortEnterCritical()
#define EXIT_CRITICAL_SECTION( ) vMBPortExitCritical()

#ifndef true
#  define true   true
#endif

#ifndef false
#  define false  false
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

typedef enum
{
  MB_LOG_ERROR = 0,
  MB_LOG_WARN  = 1,
  MB_LOG_INFO  = 2,
  MB_LOG_DEBUG = 3
} eMBPortLogLevel;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void vMBPortEnterCritical(void);
void vMBPortExitCritical(void);
void vMBPortLog(eMBPortLogLevel eLevel, const char *szModule,
                const char *szFmt, ...);
void vMBPortTimerPoll(void);
bool xMBPortSerialPoll(void);
bool xMBPortSerialSetTimeout(uint32_t dwTimeoutMs);

#ifdef __cplusplus
PR_END_EXTERN_C
#endif

#endif /* __APPS_MODBUS_NUTTX_PORT_H */
