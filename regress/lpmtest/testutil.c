/*
 *  This is a test program to test lpm instruction.
 */

#include "testutil.h"

/*
 *  Poll the specified string out the debug port.
 */
void debug_puts(const char *str) {
  const char *c;

  for(c = str; *c; c++)
    special_output_port = *c;
}

/*
 *  Poll the specified string from progspace out the debug port.
 */
void debug_puts_prog(const PGM_P strp) {
  char c;

  while(1) {
    c = pgm_read_byte(strp);
    if(c == '\0')
        break;
    special_output_port = c;
    strp++;
  }
}

void debug_nibble(unsigned long val) {
  val &= 0xf;
  if(val <= 9) {
      special_output_port = '0' + val;
  } else {
      special_output_port = 'a' + (val - 10);
  }
}

void debug_dec(unsigned long val, unsigned int num) {
    for(; num > 0; --num) {
        debug_nibble(val >> ((num - 1) * 4));
    }
}

static char _assert_1[] PROGMEM = " ok, value=0x";
static char _assert_2[] PROGMEM = " failed, expected=0x";
static char _assert_3[] PROGMEM = ", got=0x";

int assert_lpm_special(PGM_P comment, uint8_t expected, uint16_t lpmAddr) {
    uint8_t val;
    uint8_t result = 0;

    /* print test comment */
    debug_puts_prog(comment);
    debug_putc(':');

    /* get expected value */
    val = boot_lock_fuse_bits_get(lpmAddr);

    /* compare and print result */
    if(val == expected) {
        debug_puts_prog(_assert_1);
    } else {
        result = 1;
        debug_puts_prog(_assert_2);
        debug_dec(expected, 2);
        debug_puts_prog(_assert_3);
    }
    debug_dec(val, 2);

    /* return result */
    debug_putc('\n');
    return result;
}

int assert_equal(PGM_P comment, unsigned int expected, unsigned int value) {
    uint8_t result = 0;

    /* print test comment */
    debug_puts_prog(comment);
    debug_putc(':');

    /* compare and print result */
    if(value == expected) {
        debug_puts_prog(_assert_1);
    } else {
        result = 1;
        debug_puts_prog(_assert_2);
        debug_dec(expected, 4);
        debug_puts_prog(_assert_3);
    }
    debug_dec(value, 4);

    /* return result */
    debug_putc('\n');
    return result;
}
