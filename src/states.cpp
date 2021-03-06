#include "qpcpp.hpp"
#include "safe_std.h"
#include "states.hpp"
#include <stdlib.h>

static States l_states;
QP::QHsm * const states = &l_states;

States::States()
    : QHsm(Q_STATE_CAST(&States::initial))
{}

void States::incCount() {
    count += 1;
}

void States::printCount(char const * msg) {
    PRINTF_S("%s: %d\n", msg, count);
}

void States::resetCount() {
    count = 0;
}

Q_STATE_DEF(States, initial) {
    QP::QState status_;
    (void)e; // unused transition parameter
    resetCount();
    printCount("initial");

    QS_FUN_DICTIONARY(&States::pause);
    QS_FUN_DICTIONARY(&States::cycle);
    QS_FUN_DICTIONARY(&States::first);
    QS_FUN_DICTIONARY(&States::second);
    QS_FUN_DICTIONARY(&States::third);
    QS_FUN_DICTIONARY(&States::final);

    status_ = tran(&pause);
    return status_;
}

Q_STATE_DEF(States, pause) {
    QP::QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s\n", "entry-pause");
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_EXIT_SIG: {
            PRINTF_S("%s\n", "exit-pause");
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_INIT_SIG: {
            PRINTF_S("%s\n", "init-pause");
            status_ = Q_RET_HANDLED;
            break;
        }
        case J_CLICKED_SIG: {
            PRINTF_S("%s\n", "j-clicked-pause");
            status_ = tran(&cycle);
            break;
        }
        case TERMINATE_SIG: {
            PRINTF_S("%s\n", "terminate-pause");
            status_ = tran(&final);
            break;
        }
        default: {
            PRINTF_S("%s\n", "default-pause");
            status_ = super(&top);
            break;
        }
    }
    return status_;
}

Q_STATE_DEF(States, cycle) {
    QP::QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            resetCount();
            printCount("cycle");
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_EXIT_SIG: {
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_INIT_SIG: {
            status_ = tran(&first);
            break;
        }
        case J_CLICKED_SIG: {
            PRINTF_S("%s\n", "j-clicked");
            status_ = tran(&pause);
            break;
        }
        case TERMINATE_SIG: {
            PRINTF_S("%s\n", "terminate");
            status_ = tran(&final);
            break;
        }
        default: {
            status_ = super(&top);
        }
    }
    return status_;
}

Q_STATE_DEF(States, first) {
    QP::QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            incCount();
            printCount("first");
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_INIT_SIG: {
            status_ = Q_RET_HANDLED;
            break;
        }
        case K_CLICKED_SIG: {
            PRINTF_S("%s\n", "k-clicked-first");
            status_ = tran(&second);
            break;
        }
        default: {
            status_ = super(&cycle);
            break;
        }
    }
    return status_;
}

Q_STATE_DEF(States, second) {
    QP::QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            incCount();
            printCount("second");
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_INIT_SIG: {
            status_ = Q_RET_HANDLED;
            break;
        }
        case K_CLICKED_SIG: {
            PRINTF_S("%s\n", "k-clicked-second");
            status_ = tran(&third);
            break;
        }
        default: {
            status_ = super(&cycle);
            break;
        }
    }
    return status_;
}

Q_STATE_DEF(States, third) {
    QP::QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            incCount();
            printCount("third");
            status_ = Q_RET_HANDLED;
            break;
        }
        case Q_INIT_SIG: {
            status_ = Q_RET_HANDLED;
            break;
        }
        case K_CLICKED_SIG: {
            PRINTF_S("%s\n", "k-clicked-third");
            status_ = tran(&first);
            break;
        }
        default: {
            status_ = super(&cycle);
            break;
        }
    }
    return status_;
}

Q_STATE_DEF(States, final) {
    QP::QState status_;
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            PRINTF_S("%s\n", "final");
            QP::QF::onCleanup();
            exit(0);
            status_ = Q_RET_HANDLED;
            break;
        }
        default: {
            status_ = super(&top);
            break;
        }
    }
    return status_;
}
