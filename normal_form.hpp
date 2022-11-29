#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
#include <array>
#include <random>

class NormalForm {
public:
    typedef float payoff;
    typedef std::array<std::array<std::array<payoff, 2>, 2>, 2> matrix;
    typedef unsigned short player;
    typedef unsigned short strategy;
    typedef std::array<strategy, 2> profile;
public:
    NormalForm(const matrix& val) : mat(val) {
        std::random_device rd;
        gen.seed(rd());
    }

public:
    // public helper function
    static matrix make_matrix(const std::array<payoff, 8>& arr) {
        matrix mat;
        mat[0][0][0] = arr[0], mat[0][0][1] = arr[1], mat[0][1][0] = arr[2], mat[0][1][1] = arr[3];
        mat[1][0][0] = arr[4], mat[1][0][1] = arr[5], mat[1][1][0] = arr[6], mat[1][1][1] = arr[7];
        return mat;
    }

public:
    payoff utility(player p, const profile& pf) const {
        return mat[pf[0]][pf[1]][p];
    }

    payoff utility(player p, strategy s, const std::array<float, 2>& prob) const {
        // utility of p given p's strat s and (p^1)'s prob of strat
        return prob[0] * utility(p, make_profile(p, s, 0)) + prob[1] * utility(p, make_profile(p, s, 1));
    }

    strategy best_response(player p, const std::array<float, 2>& prob) {
        payoff p0 = utility(p, 0, prob), p1 = utility(p, 1, prob);
        if (p0 != p1) return p0 < p1? 1 : 0;
        std::uniform_int_distribution<> dis(0, 1);
        strategy s[] = {0, 1};
        return s[dis(gen)];
    }

private:
    // private helper function
    static profile make_profile(player p, strategy a, strategy b) {
        profile pf;
        pf[p] = a;
        pf[p ^ 1] = b;
        return pf;
    }

private:
    matrix mat;
    std::default_random_engine gen;
};