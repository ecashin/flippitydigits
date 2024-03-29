#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <SFML/Audio.hpp>

namespace po = boost::program_options;
namespace pt = boost::posix_time;

#include <iostream>
#include <random>

#include "sounds/242501__gabrielaraujo__powerup-success.cc"
#include "sounds/253886__themusicalnomad__negative-beeps.cc"
#include "sounds/202498__xtrsounder__small-crowd-cheering-and-clapping-at-party-2.h"

class factor_pair {
public:
    int left;
    int right;
    factor_pair(int l, int r) :left(l), right(r) {}
};

class Player {
private:
    sf::SoundBuffer correct_buf;
    sf::SoundBuffer incorrect_buf;
    sf::SoundBuffer cheering_buf;
    sf::Sound correct;
    sf::Sound incorrect;
    sf::Sound cheering;
public:
    Player() {
        correct_buf.loadFromMemory(success_wav, success_wav_len);
        incorrect_buf.loadFromMemory(fail_wav, fail_wav_len);
        cheering_buf.loadFromMemory(cheering_wav, cheering_wav_len);
        correct.setBuffer(correct_buf);
        incorrect.setBuffer(incorrect_buf);
        cheering.setBuffer(cheering_buf);
    }
    void right() { correct.play(); }
    void wrong() { incorrect.play(); }
    void acclaim() { cheering.play(); }
    bool playing() {
        return correct.getStatus() == sf::SoundSource::Status::Playing
            || incorrect.getStatus() == sf::SoundSource::Status::Playing
            || cheering.getStatus() == sf::SoundSource::Status::Playing;
    }
};

int main(int argc, char *argv[])
{
    Player player{};
    int max_factor;
    double max_seconds;
    po::options_description description("allowed options");
    description.add_options()
            ("help", "print help message")
            ("max", po::value<int>(&max_factor)->default_value(12), "maximum factor")
            ("seconds", po::value<double>(&max_seconds)->default_value(5.0), "max seconds for response");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << std::endl;
        return 0;
    }
    std::cout << "seconds: " << max_seconds << std::endl;

    std::vector<factor_pair> v;
    std::default_random_engine rng(std::random_device{}());

    for (int i = 0; i <= max_factor; ++i) {
                for (int j = 0; j <= max_factor; ++j) {
                    for (int k = 0; k < i+j; k++) {
                                v.push_back(factor_pair(i, j));
                        }
                }
    }

    auto game_begin = pt::microsec_clock::local_time();
    while (v.size() > 0) {
        int selection = std::uniform_int_distribution<int>{0, ((int)v.size())-1}(rng);
        factor_pair p = v[selection];
        int correct_answer = p.left * p.right;
        std::string response;
        int answer;
        auto before = pt::microsec_clock::local_time();
        std::cout << p.left << " x " << p.right << std::endl;
        std::cin >> response;
        try {
            answer = boost::lexical_cast<int>(response);
        } catch (boost::bad_lexical_cast &e) {
            std::cout << "Whatever." << std::endl;
            answer = correct_answer - 1;  // Make it count as wrong.
        }
        auto delay = pt::microsec_clock::local_time() - before;
        if (std::cin.eof())
            break;

        if (answer != correct_answer) {
            std::cout << "NO!  The answer is " << correct_answer << ".  ";
            v.push_back(p);
            player.wrong();
        } else {
            if (delay.total_milliseconds() <= max_seconds * 1000) {
                std::cout << "You're fast!" << std::endl;
                v.erase(
                    std::remove_if(
                        v.begin(),
                        v.end(),
                        [p](const factor_pair& f) {
                            return (p.left == f.left && p.right == f.right) ||
                                (p.left == f.right && p.right == f.left);
                        }),
                    v.end());
                player.right();
            }
            std::cout << "Correct!  ";
        }
        std::cout << v.size() << " remaining." << std::endl;
    }

    if (v.size() == 0) {
        player.acclaim();
        while (player.playing()) {
            boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        }
    }
    std::cout
        << "You played for "
        << (pt::microsec_clock::local_time() - game_begin).total_seconds()
        << " seconds."
        << std::endl;
    return 0;
}
