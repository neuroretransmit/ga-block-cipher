#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../util/types.h"
#include "../util/log.h"

using namespace std;


namespace crypto
{
    /// Pluggable interface for feistel-based ciphers
    // TODO: Implement a feistel-based cipher and feistel variants (unbalanced, modified like RC6)
    template<typename BlockSize>
    class Feistel : CipherInterface<BlockSize> {
    protected:
        unsigned rounds;
        vector<BlockSize> block;
        vector<u8> key;

    public:
        Feistel(unsigned rounds, vector<u8> key) : 
            rounds(rounds), 
            key(key)
        {
            this->schedule_keys(key);
        }
        
        vector<BlockSize> encrypt(vector<BlockSize>& plaintext)
        {	
            if (block.size() % 2)
                log::fatal("Block size was not divisible by 2");

            vector<BlockSize> ciphertext(plaintext.size());
            auto half_len = block.size() / 2;
            auto L = vector<BlockSize>(block.begin(), block.end() - half_len);
            auto R = vector<BlockSize>(block.end() - half_len, block.end());
            auto key_schedule = schedule_keys(); 

            if (key_schedule.size() < rounds)
                log::fatal("Key schedule length less than rounds");

            auto prev_L = L;
            auto prev_R = R;
            
            for (unsigned r = 1; r < this->rounds; r++) {
                L = prev_R;
                R = prev_L ^ round(prev_R, key_schedule[r]);
                prev_R = R;
                prev_L = L;
            }
        }

        vector<BlockSize> decrypt(vector<BlockSize>& ciphertext) 
        {
            if (block.size() % 2) {
                log::fatal("Block size was not divisible by 2");
            }

            vector<BlockSize> plaintext(ciphertext.size());
            auto half_len = block.size() / 2;
            auto L = vector<BlockSize>(block.begin(), block.end() - half_len);
            auto R = vector<BlockSize>(block.end() - half_len, block.end());
            auto key_schedule = schedule_keys(); 

            if (key_schedule.size() < rounds) {
                log::fatal("Key schedule length less than rounds");
            }

            auto prev_L = L;
            auto prev_R = R;
            
            for (unsigned r = this->rounds; r <= 0; r++) {
                
                L = prev_R;
                R = prev_L ^ round(prev_R, key_schedule[r]);
                prev_R = R;
                prev_L = L;
            }
        }

        // TODO: Implement round function on implementing class
        virtual void round(vector<BlockSize>& R);
        // TODO: Implement key schedule on implementing class
        virtual vector<vector<u8>> schedule_keys(const vector<u8>& key);
    };
}

