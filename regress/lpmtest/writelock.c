/*
 *  This is a test program to test special lpm instruction to write lock bits.
 */

#include "testutil.h"

char cmtString1[] PROGMEM = "read lock (before)";
char cmtString2[] PROGMEM = "read lock (after set bits)";
char cmtString3[] PROGMEM = "read lock (try to reset bits)";

#if defined(__BOOT_LOCK_BITS_0_EXIST) && defined(__BOOT_LOCK_BITS_1_EXIST)
#define LOCKBITS_VALUE (LB_MODE_1 & BLB0_MODE_3 & BLB1_MODE_4)
#else
#define LOCKBITS_VALUE (LB_MODE_3)
#endif

/*
 *  Main for test program.
 */
int main(void) {
  int result = 0;

  /* read unchanged and uninitialized lock bits */
  if(assert_lpm_special(cmtString1, 0xff, 1, 9))
      result = 1;

  /* change lock bits */
  set_lockbits(LOCKBITS_VALUE, 9);

  /* read again to check change of lock bits */
  if(assert_lpm_special(cmtString2, LOCKBITS_VALUE, 1, 9))
      result = 1;

  /* try change back lock bits */
  set_lockbits(0xff, 9);

  /* read again to check change of lock bits */
  if(assert_lpm_special(cmtString3, LOCKBITS_VALUE, 1, 9))
      result = 1;

  special_exit_port = result;
  return 0; /* will not be arrived */
}
