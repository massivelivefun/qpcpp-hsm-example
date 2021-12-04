#ifndef STATES_HPP
#define STATES_HPP

enum ButtonSignals {
    J_CLICKED_SIG = QP::Q_USER_SIG,
    K_CLICKED_SIG,
    TERMINATE_SIG,
};

extern QP::QHsm * const states;

#endif
