#include <iostream>
#include "olcNoiseMaker.h"

using namespace std;

atomic<double> dFrequencyOutput = 0.0;

double MakeNoise(double dTime) {
	double dOutput = 0.3 * sin(220.0 * 2 * 3.14159 * dTime);
	if (dOutput > 0)
		return 0.2;
	else
		return -0.2;
}

int main() {
	
	//get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	//display findings
	for (auto d : devices) wcout << "Found output device " << d << endl;

	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	//Link noise function with sound machine
	sound.SetUserFunction(MakeNoise);

	double dOctaveBaseFrequency = 110.0;
	double d12thRootOf2 = pow(2.0 , 1.0 / 12.0);

	while (1) {

		bool bKeyPressed = false;
		for (int k = 0; k < 15; k++) {
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000) {
				dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, k);
				bKeyPressed = true;
			}
		}
		if (!bKeyPressed) {
			dFrequencyOutput = 0.0;
		}
	}
}