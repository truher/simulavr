/*
 *  This is a test program to test lpm instruction.
 */

#define _SFR_ASM_COMPAT 1

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

#ifdef SPMCSR

#if _SFR_IO_REG_P(SPMCSR)

static uint8_t _lpm_special(uint16_t addr, uint8_t spmval) {
     return __extension__({                          \
        uint16_t __addr16 = (uint16_t)(addr); \
        uint8_t __spmval = (uint8_t)spmval;   \
        uint8_t __result;                     \
        __asm__                               \
        (                                     \
            "out %3, %2" "\n\t"               \
            "movw r30, %1" "\n\t"             \
            "lpm" "\n\t"                      \
            "mov %0, r0" "\n\t"               \
            : "=r" (__result)                 \
            : "r" (__addr16),                 \
              "r" (__spmval),                 \
              "I" (_SFR_IO_ADDR(SPMCSR))       \
            : "r30", "r31"                    \
        );                                    \
        __result;                             \
    });
}

#else

static uint8_t _lpm_special(uint16_t addr, uint8_t spmval) {
    return __extension__({                          \
        uint16_t __addr16 = (uint16_t)(addr); \
        uint8_t __spmval = (uint8_t)spmval;   \
        uint8_t __result;                     \
        __asm__                               \
        (                                     \
            "sts %3, %2" "\n\t"             \
            "movw r30, %1" "\n\t"             \
            "lpm" "\n\t"                      \
            "mov %0, r0" "\n\t"               \
            : "=r" (__result)                 \
            : "r" (__addr16),                 \
              "r" (__spmval),                  \
              "M" (_SFR_MEM_ADDR(SPMCSR))       \
            : "r30", "r31"                    \
        );                                    \
        __result;                             \
    });
}

#endif

#else

static uint8_t _lpm_special(uint16_t addr, uint8_t spmval) {
    return __extension__({
        uint16_t __addr16 = (uint16_t)(addr);
        uint8_t __spmval = (uint8_t)spmval;
        uint8_t __result;
        __asm__
        (
            "out %3, %2" "\n\t"
            "movw r30, %1" "\n\t"
            "lpm" "\n\t"
            "mov %0, r0" "\n\t"
            : "=r" (__result)
            : "r" (__addr16),
              "r" (__spmval),
              "I" (_SFR_IO_ADDR(SPMCR))
            : "r30", "r31"
        );
        __result;
    });
}

#endif

static char _assert_1[] PROGMEM = " ok, value=0x";
static char _assert_2[] PROGMEM = " failed, expected=0x";
static char _assert_3[] PROGMEM = ", got=0x";

int assert_lpm_special(PGM_P comment, uint8_t expected, uint16_t lpmAddr, uint8_t spmcrVal) {
    uint8_t val;
    uint8_t result = 0;

    /* print test comment */
    debug_puts_prog(comment);
    debug_putc(':');

    /* get expected value */
    val = _lpm_special(lpmAddr, spmcrVal);

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
