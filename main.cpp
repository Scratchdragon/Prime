#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <chrono>
#include <fstream>

int main(int argc, char **argv) {
	remove("prime.txt");
	std::ofstream outfile;
	outfile.open("prime.txt", std::ios_base::app);

	// Variables for testing
	bool testing = false;
	long max = 1000000;
	float time = 0;

	// Check for args
	if(argc==3) {
		// Do a speed test
		if(strcmp(argv[1], "test") == 0) {
			testing = true;
			max = std::stoi(argv[2]);
		}
	}

	// Variables used to check if a number is prime
	long long n;
	long long sq_i;
	long long primes = 1;
	long long last_primes = 1;
	bool prime = false;

	// Currently selected number
	long long i = 3;

	// 2 is prime
	outfile << 2 << '\n';

	// Start measuring time
	auto begin = std::chrono::high_resolution_clock::now();

	while(true) {
		//Check if 'i' is prime

		sq_i = (long long)sqrt((double)i);
		prime = (i % 2) != 0;
		if(prime) {
			for(n=3; n<=sq_i; n+=2) {
				prime = (i % n) != 0;
				if(!prime)
					break;
			}
		}
		if(prime) {
			outfile << i << '\n';
			++primes;
		}
		
		if(i % max == 0) {
			auto end = std::chrono::high_resolution_clock::now();
    		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
			time = elapsed.count() * (1e-9);

			std::cout << "Reached " << primes << " primes in " << time * 1000 << "ms\n";
			std::cout << "Numbers: " << ((primes-last_primes) / time) << " per second\n";

			if(testing)
				break;
			begin = std::chrono::high_resolution_clock::now();
			last_primes = primes;
		}

		++i;
	}
	
	// Stop measuring time and calculate the elapsed time
    

	std::cout << "Finished in " << time * 1000 << "ms\n";
}