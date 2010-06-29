/*
 *  This is a test program to test special lpm instruction to read fuse bytes.
 */

#include "testutil.h"

char cmtString1[] PROGMEM = "fuse low";
char cmtString2[] PROGMEM = "fuse high";
char cmtString3[] PROGMEM = "fuse ext";

FUSES =
{
    .low = LFUSE_DEFAULT,
#if FUSE_MEMORY_SIZE == 2
    .high = HFUSE_DEFAULT,
#if FUSE_MEMORY_SIZE == 3
    .extended = EFUSE_DEFAULT,
#endif
#endif
};

/*
 *  Main for test program.
 */
int main(void) {
  int result = 0;

  if(assert_lpm_special(cmtString1, LFUSE_DEFAULT, 0, 9))
      result = 1;

#if FUSE_MEMORY_SIZE == 2
  if(assert_lpm_special(cmtString2, HFUSE_DEFAULT, 3, 9))
      result = 1;

#if FUSE_MEMORY_SIZE == 3
  if(assert_lpm_special(cmtString3, EFUSE_DEFAULT, 2, 9))
      result = 1;
#endif
#endif

  special_exit_port = result;
  return 0; /* will not be arrived */
}
