#include "qpcpp.hpp"
#include "safe_std.h"
#include "states.hpp"
#include <stdlib.h> // for exit()

int main() {
    QP::QF::init();
    QP::QF::onStartup();

    PRINTF_S("%s\n", "HSM Example:\n"
        "Press 'j' to switch larger states\n"
        "Press 'k' to switch smaller states in the second larger state\n"
        "Press 'ESC' to quit...");

    states->init(0U);
    
    for (;;) {
        PRINTF_S("\n", "");

        uint8_t c = (uint8_t)QP::QF_consoleWaitForKey();
        PRINTF_S("%c: ", c);

        QP::QEvt e;
        switch (c) {
            case 'j':   e.sig = J_CLICKED_SIG;  break;
            case 'k':   e.sig = K_CLICKED_SIG;  break;
            case 0x1B:  e.sig = TERMINATE_SIG;  break;
        }

        // dispatch the event into the state machine
        states->dispatch(&e, 0U);
    }

    QP::QF::onCleanup();
    return 0;
}

void QP::QF::onStartup(void) {
    QP::QF_consoleSetup();
}
void QP::QF::onCleanup(void) {
    QP::QF_consoleCleanup();
}
void QP::QF_onClockTick(void) {}

extern "C" Q_NORETURN Q_onAssert(const char * const module, int_t const location) {
    FPRINTF_S(stderr, "Assertion failed in %s, line %d", module, location);
    QP::QF::onCleanup();
    exit(-1);
}
