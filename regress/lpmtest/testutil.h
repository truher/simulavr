/*
 * testutil.h
 */

#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#include <avr/pgmspace.h>

/*
 *  This port correponds to the "-W 0x20,-" command line option.
 */
#define special_output_port (*( (volatile char *)0x20))

/*
 *  This port correponds to the "-e 0x22" command line option.
 */
#define special_exit_port (*( (volatile char *)0x22))

#define debug_putc(c) (special_output_port = (c))

extern void debug_puts(const char *str);
extern void debug_puts_prog(const PGM_P str);
extern void debug_nibble(unsigned long val);
extern void debug_dec(unsigned long val, unsigned int num);
extern int assert_lpm_special(PGM_P comment, uint8_t expected, uint16_t lpmAddr, uint8_t spmcrVal);
extern int assert_equal(PGM_P comment, unsigned int expected, unsigned int value);

#endif /* TESTUTIL_H_ */
