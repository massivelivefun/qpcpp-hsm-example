#ifndef STATES_HPP
#define STATES_HPP

enum ButtonSignals {
    J_CLICKED_SIG = QP::Q_USER_SIG,
    K_CLICKED_SIG,
    TERMINATE_SIG,
};

class States : public QP::QHsm {
    private:
        int count = 0;

    public:
        States();

    protected:
        void incCount();
        void printCount(char const * msg);
        void resetCount();
        Q_STATE_DECL(initial);
        Q_STATE_DECL(pause);
        Q_STATE_DECL(cycle);
        Q_STATE_DECL(first);
        Q_STATE_DECL(second);
        Q_STATE_DECL(third);
        Q_STATE_DECL(final);
};

extern QP::QHsm * const states;

#endif
