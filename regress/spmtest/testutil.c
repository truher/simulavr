/*
 *  Functions to test spm instruction.
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

/*
 *  Write out to special port the lowest nibble of given value
 */
void debug_nibble(unsigned long val) {
  val &= 0xf;
  if(val <= 9) {
      special_output_port = '0' + val;
  } else {
      special_output_port = 'a' + (val - 10);
  }
}

/*
 *  Write out to special port the given value as hex value with num digits
 */
void debug_dec(unsigned long val, unsigned int num) {
    for(; num > 0; --num) {
        debug_nibble(val >> ((num - 1) * 4));
    }
}

/*
 *  Write out to special port the given value as integer value with at least num digits
 *  (but not more than 8 digits)
 */
void debug_int(unsigned long val, unsigned int num) {
    unsigned char c, i;
    char buffer[8];

    // fill buffer with '0' chars
    for(i = 0; i < 8; buffer[i++] = '0');

    // convert to char
    for(i = 0; val > 0 && i < 8;) {
        c = val % 10;
        val /= 10;
        buffer[i++] = '0' + c;
    }

    // limit output
    if(i > num)
        num = i;
    if(num > 8)
        num = 8;

    // write out
    for(; num > 0;) special_output_port = buffer[--num];
}

static char _assert_1[] PROGMEM = " ok, value=0x";
static char _assert_2[] PROGMEM = " failed, expected=0x";
static char _assert_3[] PROGMEM = ", got=0x";

/*
 *  Compare expected value with value, write result message and return
 *  1, if not equal and 0 if equal.
 */
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

static char _assert_4[] PROGMEM = " ok, erased";
static char _assert_5[] PROGMEM = " failed, not erased";

/*
 *  Check if flash page is erased, write result message and return
 *  1, if not erased and 0 if erased.
 */
int assert_is_erased(PGM_P comment, const PGM_P strp) {
    uint8_t c, result = 0;
    uint16_t i;

    /* print test comment */
    debug_puts_prog(comment);
    debug_putc(':');

    /* compare and print result */
    for (i = 0; i < SPM_PAGESIZE; i++) {
      c = pgm_read_byte(strp);
      strp++;
      if(c != 0xff) {
          result = 1;
          break;
      }
    }

    if(result == 0)
        debug_puts_prog(_assert_4);
    else
        debug_puts_prog(_assert_5);

    /* return result */
    debug_putc('\n');
    return result;
}

/*
 *  Calculate checksum for flash page (size = SPM_PAGESIZE)
 */
uint16_t get_page_checksum(const PGM_P strp) {
  uint8_t sum_b, xor_b;
  uint8_t c;
  uint16_t i;

  sum_b = 0;
  xor_b = 0;

  for (i = 0; i < SPM_PAGESIZE; i++) {
    c = pgm_read_byte(strp);
    strp++;
    sum_b += c;
    xor_b ^= c;
  }

  return sum_b + (xor_b << 8);
}

/*
 *  Calculate checksum for buffer in RAM (size = SPM_PAGESIZE)
 */
uint16_t get_buffer_checksum(const uint8_t* strp) {
  uint8_t sum_b, xor_b;
  uint8_t c;
  uint16_t i;

  sum_b = 0;
  xor_b = 0;

  for (i = 0; i < SPM_PAGESIZE; i++) {
    c = *strp++;
    sum_b += c;
    xor_b ^= c;
  }

  return sum_b + (xor_b << 8);
}

/* EOF */
