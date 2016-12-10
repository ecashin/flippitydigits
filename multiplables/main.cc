#include <boost/program_options.hpp>

namespace po = boost::program_options;

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
    po::options_description description("allowed options");
    description.add_options()
            ("help", "print help message")
            ("max", po::value<int>(&max_factor)->default_value(12), "maximum factor");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << description << std::endl;
        return 0;
    }

    std::vector<factor_pair> v;
    std::default_random_engine rng;

    for (int i = 0; i <= max_factor; ++i) {
		for (int j = 0; j <= max_factor; ++j) {
		    for (int k = 0; k < i+j; k++) {
				v.push_back(factor_pair(i, j));
			}
		}
    }

    for (;;) {
	int selection = std::uniform_int_distribution<int>{0, ((int)v.size())-1}(rng);
	factor_pair& p = v[selection];
	int correct_answer = p.left * p.right;
	int answer;
	std::cout << p.left << " x " << p.right << std::endl;
	std::cin >> answer;
	if (std::cin.eof())
	    break;
	if (!std::cin.good()) {
	    std::cout << "Whatever." << std::endl;
	    continue;
	}
	std::string feedback("Correct!");
	if (answer != correct_answer) {
	    feedback = "NO!";
	    v.push_back(p);
	}
	std::cout << feedback << std::endl;
    }

    return 0;
}
