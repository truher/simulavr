/*
 *  This is a test program to test spm instruction. (erase a page)
 */

#include "testutil.h"

uint8_t test_page[] __attribute__ ((section(".testpage"))) = P1_NAME;

char _msg_1[] PROGMEM = "page before";
char _msg_2[] PROGMEM = "page erase";

int main(void) {
  uint8_t result = 0;
  
  debug_puts("page size: ");
  debug_int(SPM_PAGESIZE / 2, 0);
  debug_puts(" words\n");

  if(assert_equal(_msg_1, P1_CHKSUM, get_page_checksum(test_page)))
      result = 1;
  
  boot_erase_page((uint16_t)test_page);
  
  if(assert_is_erased(_msg_2, test_page))
      result = 1;
  
  special_exit_port = 0;
  return 0; /* will not be arrived */
}
