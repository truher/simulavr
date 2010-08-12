/*
 *  This is a test program to test spm instruction. (erase and write a page)
 */

#include "testutil.h"

uint8_t buffer[SPM_PAGESIZE] = P2_NAME;

uint8_t test_page[] __attribute__ ((section(".testpage"))) = P1_NAME;

char _msg_1[] PROGMEM = "page before";
char _msg_2[] PROGMEM = "buffer";
char _msg_3[] PROGMEM = "page after";

int main(void) {
  uint8_t result = 0;
  
  debug_puts("page size: ");
  debug_int(SPM_PAGESIZE / 2, 0);
  debug_puts(" words\n");

  if(assert_equal(_msg_1, P1_CHKSUM, get_page_checksum(test_page)))
      result = 1;
  
  if(assert_equal(_msg_2, P2_CHKSUM, get_buffer_checksum(buffer)))
      result = 1;
  
  boot_program_page((uint16_t)test_page, buffer);
  
  if(assert_equal(_msg_3, P2_CHKSUM, get_page_checksum(test_page)))
      result = 1;
  
  special_exit_port = 0;
  return 0; /* will not be arrived */
}
