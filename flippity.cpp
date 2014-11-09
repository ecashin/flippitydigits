// sudo apt-get install --install-suggests liballegro4-dev
// http://cimg.sourceforge.net/reference/group__cimg__tutorial.html
//
// sudo apt-get update &&
// sudo apt-get install --install-suggests liballegro4{,-d{ev,oc}} &&
// sudo apt-get install --install-suggests cimg-{examples,d{ev,oc}} &&
// sudo apt-get install xemacs21-basesupport  # (for sounds)

#include <chrono>
#include <iostream>
#include <random>

// #include <allegro/sound.h>
#include <allegro.h>

#include "CImg.h"

using namespace std;
using namespace cimg_library;

class RandomInt {
public:
    RandomInt(int low, int high) :dist{low, high} {}
    int operator()() { return dist(re); }
private:
    default_random_engine re;
    uniform_int_distribution<> dist;
};

class Sound {
public:
    Sound(const char *nam) :fnam{nam} {
	s = load_sample(nam);
	cout << "loaded s:" << s << endl;
    }
    int play() { return play_sample(s, 128, 128, 1000, false); }
    ~Sound() { destroy_sample(s); }
private:
    SAMPLE *s;
    const char *fnam;
};

void consequences(Sound &correct, Sound &wrong, int &n_remaining, bool is_correct)
{
    if (is_correct) {
	cout << "CORRECT.   ";
	correct.play();
	--n_remaining;
    } else {
	cout << "INCORRECT. ";
	wrong.play();
	++n_remaining;
    }
    cout << n_remaining << " to go!" << endl;
}

int main()
{
    CImg < unsigned char >image(110, 200);
    CImgDisplay main_disp(image, "Click Inside to Start");
    unsigned char purple[] { 255, 0, 255, };
    unsigned char black[] { 0, 0, 0, };
    RandomInt ri_flip {0, 1};
    RandomInt ri_digit {0, 9};
    int n_remaining = 15;

    allegro_init();
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) == -1) {
	cerr << "allegro error" << endl;
	return 1;
    }
    Sound correct { "/usr/share/xemacs21/xemacs-packages/etc/sounds/ding.wav" };
    Sound wrong { "/usr/share/xemacs21/xemacs-packages/etc/sounds/cry.wav" };

    correct.play();
    auto start = chrono::high_resolution_clock::now();

    for (; !main_disp.is_closed() && !main_disp.is_key(cimg::keyESC); ) {
	bool flip = ri_flip();
	int i;

	for (;;) {
	    i = ri_digit();
	    if (i != 8 && i != 0)
		break;
	}

	main_disp.wait();
	if (main_disp.is_key(cimg::keySPACE)) {

	    if (flip)
		image.fill(0)
		    .draw_text(10, 10, "%d", purple, black, 1.0, 200, i)
		    .mirror('x')
		    .blur(4)
		    .display(main_disp);
	    else
		image.fill(0)
		    .draw_text(10, 10, "%d", purple, black, 1.0, 200, i)
		    .blur(4)
		    .display(main_disp);

	    // get the user response
	    for (;;) {
		main_disp.wait();
		if (main_disp.is_key(cimg::keyF)) {
                    consequences(correct, wrong, n_remaining, !flip);
		    break;
		}
		if (main_disp.is_key(cimg::keyB)) {
                    consequences(correct, wrong, n_remaining, flip);
		    break;
		}
		if (main_disp.is_key(cimg::keyESC)) {
		    cout << "ESC" << endl;
		    goto end;
		}
	    }
	    if (n_remaining == 0)
		break;
	}
    }
end:
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "You took " << (duration / 1000.0) << " seconds" << endl;

    return 0;
}
