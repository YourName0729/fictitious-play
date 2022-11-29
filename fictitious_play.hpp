#pragma once

#include <sstream>
#include <iomanip>

#include "normal_form.hpp"
#include "csv_formatter.hpp"

class FictitiousPlay {
public:
    typedef float belief;
    typedef std::array<std::array<belief, 2>, 2> belief_profile; // the other player think i has played bp[i][strat] times of strat
public:
    FictitiousPlay(const NormalForm& nf, const belief_profile bp) : nf(nf), bp(bp) {}

    CsvFormatter play(unsigned round) {
        CsvFormatter cf(7, round + 1);
        cf() = CsvFormatter::row{"Round", "1\'s action", "2\'s action", "1\'s belief", "2\'s belief", "1\'s payoff", "2\'s payoff"};

        cf[0][0] = "0";
        for (unsigned i = 0; i < round; ++i) {
            cf[i + 1][0] = std::to_string(i + 1);
            cf[i][3] = pair_float(bp[1][0], bp[1][1]);
            cf[i][4] = pair_float(bp[0][0], bp[0][1]);

            std::array<float, 2> prob0, prob1; // probi[s] is the prob of i using strat s
            prob0[0] = bp[0][0] / (bp[0][0] + bp[0][1]);
            prob0[1] = bp[0][1] / (bp[0][0] + bp[0][1]);
            prob1[0] = bp[1][0] / (bp[1][0] + bp[1][1]);
            prob1[1] = bp[1][1] / (bp[1][0] + bp[1][1]);
            cf[i][5] = pair_float(nf.utility(0, 0, prob1), nf.utility(0, 1, prob1));
            cf[i][6] = pair_float(nf.utility(1, 0, prob1), nf.utility(1, 1, prob1));

            NormalForm::strategy br0 = nf.best_response(0, prob1), br1 = nf.best_response(1, prob0);

            cf[i + 1][1] = std::to_string(br0 + 1);
            cf[i + 1][2] = std::to_string(br1 + 1);

            ++bp[0][br0];
            ++bp[1][br1];
        }
        return cf;
    }

private:
    static std::string pair_float(float a, float b) {
        std::stringstream ss;
        ss << std::setprecision(2) << a << ' ' << std::setprecision(2) << b;
        return ss.str();
    }

private:
    NormalForm nf;
    belief_profile bp;
};