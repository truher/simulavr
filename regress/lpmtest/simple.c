/*
 *  This is a test program to test lpm instruction.
 */

#include "testutil.h"

#define TEST_STRING "This is a test string!"

char pString[] PROGMEM = TEST_STRING;
char mString[] = TEST_STRING;

char cmtString[] PROGMEM = "simple lpm transfer";

unsigned int calculate(unsigned int sum, unsigned char c) {
    unsigned char s = ((sum >> 8) & 0xff) + c;
    unsigned char x = (sum & 0xff) ^ c;

    return (s << 8) + x;
}

/*
 *  Main for test program.
 */
int main(void) {
  int result = 0;
  unsigned int sum = 0, expectedSum = 0;
  char *p, c;
  const PGM_P strp;

  /* calculate expected sum from ram string */
  for(p = mString; *p; p++)
      expectedSum = calculate(expectedSum, *p);

  /* calculate sum from flash string */
  strp = pString;
  while(1) {
    c = pgm_read_byte(strp);
    if(c == '\0')
        break;
    sum = calculate(sum, c);
    strp++;
  }

  /* compare */
  if(assert_equal(cmtString, expectedSum, sum))
      result = 1;

  special_exit_port = result;
  return 0; /* will not be arrived */
}
