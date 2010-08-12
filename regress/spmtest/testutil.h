/*
 * testutil.h
 */

#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#include <avr/pgmspace.h>
#include <avr/boot.h>
#include <avr/interrupt.h>

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
extern void debug_int(unsigned long val, unsigned int num);
extern int assert_equal(PGM_P comment, unsigned int expected, unsigned int value);
extern int assert_is_erased(PGM_P comment, const PGM_P strp);
extern uint16_t get_page_checksum(const PGM_P strp);
extern uint16_t get_buffer_checksum(const uint8_t* strp);

extern void boot_program_page(uint32_t page, uint8_t *buf) BOOTLOADER_SECTION;
extern void boot_erase_page(uint32_t page) BOOTLOADER_SECTION;

/* support pattern and checksums for pages */
#include "page_pattern.h"

#if (SPM_PAGESIZE == 32)
# define P1_NAME PAGE_PATTERN_1_32
# define P2_NAME PAGE_PATTERN_2_32
# define P1_CHKSUM CHKSUM_PATTERN_1_32
# define P2_CHKSUM CHKSUM_PATTERN_2_32
#elif (SPM_PAGESIZE == 64)
# define P1_NAME PAGE_PATTERN_1_64
# define P2_NAME PAGE_PATTERN_2_64
# define P1_CHKSUM CHKSUM_PATTERN_1_64
# define P2_CHKSUM CHKSUM_PATTERN_2_64
#elif (SPM_PAGESIZE == 128)
# define P1_NAME PAGE_PATTERN_1_128
# define P2_NAME PAGE_PATTERN_2_128
# define P1_CHKSUM CHKSUM_PATTERN_1_128
# define P2_CHKSUM CHKSUM_PATTERN_2_128
#elif (SPM_PAGESIZE == 256)
# define P1_NAME PAGE_PATTERN_1_256
# define P2_NAME PAGE_PATTERN_2_256
# define P1_CHKSUM CHKSUM_PATTERN_1_256
# define P2_CHKSUM CHKSUM_PATTERN_2_256
#else
# error Pattern size not available!
#endif

#endif /* TESTUTIL_H_ */
