/*
 *  This is a test program to test special lpm instruction to read lock bits.
 */

#include "testutil.h"

char cmtString[] PROGMEM = "lock";

#if defined(__BOOT_LOCK_BITS_0_EXIST) && defined(__BOOT_LOCK_BITS_1_EXIST)
#define LOCKBITS_VALUE (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4)
#else
#define LOCKBITS_VALUE (LB_MODE_3)
#endif
LOCKBITS = LOCKBITS_VALUE;

/*
 *  Main for test program.
 */
int main(void) {
  int result = 0;

  if(assert_lpm_special(cmtString, LOCKBITS_VALUE, GET_LOCK_BITS))
      result = 1;

  special_exit_port = result;
  return 0; /* will not be arrived */
}
