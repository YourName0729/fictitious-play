#include <fstream>

#include "fictitious_play.hpp"

NormalForm::matrix games[] = {
    NormalForm::make_matrix({-1, -1, 1, 0, 0, 1, 3, 3}),
    NormalForm::make_matrix({2, 2, 1, 0, 0, 1, 3, 3}),
    NormalForm::make_matrix({1, 1, 0, 0, 0, 0, 0, 0}),
    NormalForm::make_matrix({0, 1, 2, 0, 2, 0, 0, 4}),
    NormalForm::make_matrix({0, 1, 1, 0, 1, 0, 0, 1}),
    NormalForm::make_matrix({10, 10, 0, 0, 0, 0, 10, 10}),
    NormalForm::make_matrix({0, 0, 1, 1, 1, 1, 0, 0}),
    NormalForm::make_matrix({3, 2, 0, 0, 0, 0, 2, 3}),
    NormalForm::make_matrix({3, 3, 0, 2, 2, 0, 1, 1}),
    NormalForm::make_matrix({0, 0, 0, 10, 10, 0, -100, -100})
};

int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "wrong argc\n";
        return 1;
    }

    std::ofstream fout(argv[1]);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<float> dis(0.001, 10);
    FictitiousPlay::belief_profile bp{{{dis(gen), dis(gen)}, {dis(gen), dis(gen)}}};
    FictitiousPlay fp(games[std::atoi(argv[2])], bp);
    fout << fp.play(200);
    fout.close();

    return 0;
}