/*
 *  Page erase function to test spm instruction.
 *  (taken and modified from avr-libc documentation)
 */

#include "testutil.h"

void boot_erase_page(uint32_t page) {
    uint8_t sreg;

    // Disable interrupts.

    sreg = SREG;
    cli();

    eeprom_busy_wait();

    boot_page_erase(page);
    boot_spm_busy_wait();      // Wait until the memory is erased.

    // Reenable RWW-section again. We need this if we want to jump back
    // to the application after bootloading.

    boot_rww_enable();

    // Re-enable interrupts (if they were ever enabled).

    SREG = sreg;
}

// EOF
