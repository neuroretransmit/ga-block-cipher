#include <iostream>

#include "algo/damerau_levenshtein.h"
#include "algo/ga/genepool.h"

using namespace std;

int main()
{
	auto s1 = "abcdefghijklmnopqrstuvwxyz";
	auto s2 = "zyxwvutsrqponmlkjihgfedcbac";
    // Damerau-Levenshtein solves for different length strings
	auto osa_distance = damerau_levenshtein_distance(s1, s2);
	cout << "S1: '" << s1 << "'\n";
	cout << "S2: '" << s2 << "'\n";
    cout << "OSA distance: " << osa_distance << "\n\n";
    // Force population to evolve encoding to 'ev0lv3', verification of GA only
    auto dna1 = DNA("DNA_#2333");
    auto dna2 = DNA("DNA_#1");
    auto genepool = GenePool(dna1, dna2, "ev0lv3");
    genepool.evolve();
}
