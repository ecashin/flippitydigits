#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace pt = boost::posix_time;

#include <iostream>
#include <random>

class factor_pair {
public:
    int left;
    int right;
    factor_pair(int l, int r) :left(l), right(r) {}
};

int main(int argc, char *argv[])
{
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
    std::default_random_engine rng;

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

        std::string feedback("Correct!");
        if (answer != correct_answer) {
            feedback = "NO!";
            v.push_back(p);
        } else if (delay.total_milliseconds() <= max_seconds * 1000) {
            std::cout << "You're fast!" << std::endl;
            v.erase(std::remove_if(v.begin(), v.end(), [p](const factor_pair& f) {
                return (p.left == f.left && p.right == f.right) ||
                        (p.left == f.right && p.right == f.left);
            }), v.end());
        }
        std::cout << feedback << " " << v.size() << " remaining." << std::endl;
    }

    std::cout << "You played for " << (pt::microsec_clock::local_time() - game_begin).total_seconds()
                                   << " seconds." << std::endl;
    return 0;
}
