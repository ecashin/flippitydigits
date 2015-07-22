// flippity.cpp - a simple game with flipping digits
//
// Uses CImg and Allegro libraries and xemacs sounds.

#include <chrono>
#include <iostream>
#include <random>
#include <map>

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
    Sound(const char *nam) :fnam{nam} { s = load_sample(nam); }
    int play() { return play_sample(s, 128, 128, 1000, false); }
    ~Sound() { destroy_sample(s); }
private:
    SAMPLE *s;
    string fnam;
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

int encode(int character)
{
    if (character >= 'A' && character <= 'Z')
	return (character - 'A') + 10;
    return (character - 'a') + 10 + 26;
}

char next_alphanum(int &last_alphanum, RandomInt &ri_alphanumeric)
{
    int i;

    for (;;) {
	i = ri_alphanumeric();
	if (i == last_alphanum
	    || i == encode('A')
	    || i == encode('H')
	    || i == encode('I')
	    || i == encode('M')
	    || i == encode('O')
	    || i == encode('T')
	    || i == encode('U')
	    || i == encode('V')
	    || i == encode('W')
	    || i == encode('X')
	    || i == encode('Y')
	    || i == encode('i')
	    || i == encode('l')
	    || i == encode('o')
	    || i == encode('u')
	    || i == encode('v')
	    || i == encode('w')
	    || i == encode('x'))
	    continue;
	switch (i) {
	    default:
		goto out;
	    case 8:
	    case 0:
		break;
	}
    }
out:
    last_alphanum = i;

    if (i <= 9)
	return '0' + i;
    i -= 10;
    if (i < 26)
	return i + 'A';
    i -= 26;
    return 'a' + i;
}

const char *help(int alphanum)
{
    if (alphanum <= 9)
	return "0123456789";
    if (alphanum <= 9 + 26)
	return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return "abcdefghijklmnopqrstuvwxyz";
}

void sndmap_destroy(map<char,Sound *> &sndmap)
{
    for (auto i = 'a'; i < 'z'; ++i)
	delete sndmap[i];
}

void sndmap_init(map<char,Sound *> &sndmap)
{
    for (auto i = 'a'; i < 'z'; ++i) {
	auto uc = 'A' + (i - 'a');
	string fnam = string("original_sounds/") + i + ".wav";

	sndmap[i] = sndmap[uc] = new Sound(fnam.c_str());
    }
}

int main()
{
    CImg < unsigned char >image(150, 250);
    CImgDisplay main_disp(image, "Click Inside to Start");
    unsigned char purple[] { 255, 0, 255, };
    unsigned char black[] { 0, 0, 0, };
    RandomInt ri_flip {0, 1};
    RandomInt ri_alphanumeric {0, 9 + 26 * 2};
    int n_remaining = 15;
    map<char,Sound *> sndmap;

    allegro_init();
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, 0) == -1) {
	cerr << "allegro error" << endl;
	return 1;
    }
    Sound correct { "/usr/share/xemacs21/xemacs-packages/etc/sounds/ding.wav" };
    Sound wrong { "/usr/share/xemacs21/xemacs-packages/etc/sounds/cry.wav" };
    sndmap_init(sndmap);

    correct.play();
    auto start = chrono::high_resolution_clock::now();

    auto last_alphanum = -1;
    auto i = next_alphanum(last_alphanum, ri_alphanumeric);

    for (; !main_disp.is_closed() && !main_disp.is_key(cimg::keyESC); ) {
	bool flip = ri_flip();
	auto hoff = flip ? 30 : 20;

	main_disp.wait();
	if (main_disp.is_key(cimg::keySPACE)) {
	    auto snd = sndmap.find(i);
	    if (snd != sndmap.end())
		snd->second->play();

	    if (flip)
		image.fill(0)
		    .draw_text(hoff, 10, "%c", purple, black, 1.0, 200, i)
		    .mirror('x')
		    .blur(4)
		    .display(main_disp);
	    else
		image.fill(0)
		    .draw_text(hoff, 10, "%c", purple, black, 1.0, 200, i)
		    .blur(4)
		    .display(main_disp);

	    // get the user response
	    for (;;) {
		main_disp.wait();
		if (main_disp.is_key(cimg::keyR) && snd != sndmap.end())
		    snd->second->play();
		if (main_disp.is_key(cimg::keyH)) {
		    image
			.draw_text(10, image.height() - 20, help(i),
				   purple, black, 1.0, 20)
			.display(main_disp);
		}
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
		    n_remaining = 0;
		    break;
		}
	    }
	    if (n_remaining == 0)
		break;
	    i = next_alphanum(last_alphanum, ri_alphanumeric);
	}
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "You took " << (duration / 1000.0) << " seconds" << endl;

    sndmap_destroy(sndmap);
    return 0;
}
