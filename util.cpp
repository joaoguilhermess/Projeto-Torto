#include "util.h"

std::random_device device;
std::mt19937 seed(device());
std::uniform_real_distribution<> generate(0.0, 1.0);

int inteiroAleatorio(int min, int max) {
	return (max - min) * generate(seed) + min;
}