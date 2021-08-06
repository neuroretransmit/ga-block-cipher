#include "dna.h"

#include <cstdlib>
#include <iostream>

#include "../damerau_levenshtein.h"
#include "../../util/random.h"

DNA::DNA(const string& encoding) :
		encoding(encoding) {}

bool DNA::operator< (const DNA& other) const
{
	return fitness < other.fitness;
}

DNA DNA::crossover(DNA dna)
{
	DNA offspring = *this;
	size_t split_idx = rand() % min(this->encoding.length(), dna.encoding.length());
	int which = rand() % 2;
	string swap;

	cout << "P1 Encoding:\t" << this->encoding << endl;
	cout << "P2 Encoding:\t" << dna.encoding << endl;

	if (which == 0) {
		offspring.encoding.replace(0, split_idx, dna.encoding.substr(0, split_idx));
	} else {
		size_t len = dna.encoding.length();
		offspring.encoding.replace(split_idx, len, dna.encoding.substr(split_idx, len));
	}

	cout << "Crossover:\t" << offspring.encoding << endl;
	return offspring;
}

void DNA::mutate()
{
	cout << "Mutation:\t";
	size_t flip_idx = rand() % this->encoding.length();
	this->encoding[flip_idx] = util::random::ascii();
    
    if (rand() % 2) {
        string new_encoding(encoding.begin(), encoding.end() - 1);
        if (rand() % 2)
            this->encoding = new_encoding;
    } else {
        if (rand() % 2)
            this->encoding += util::random::ascii();
    }
    
	cout << this->encoding << endl << endl;
}

void DNA::mutate(DNA& other)
{
	cout << "Mutation:\t";
    size_t encoding_len = this->encoding.length();
    size_t other_encoding_len = other.encoding.length();
    
    if (encoding_len < other_encoding_len) {
        encoding += util::random::ascii();
    } else if (other_encoding_len < encoding_len) {
        encoding = encoding.substr(0, encoding_len - 1);
    }
    
	size_t flip_idx = rand() % encoding_len;
	this->encoding[flip_idx] = util::random::ascii();
    
	cout << this->encoding << endl << endl;
}

unsigned DNA::get_fitness()
{
	return this->fitness;
}

void DNA::rate_fitness(string target)
{
	this->fitness = damerau_levenshtein_distance(this->encoding, target);
    this->fitness += abs((long) (target.length() - this->encoding.length()));
}
