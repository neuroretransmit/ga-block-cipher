#include "damerau_levenshtein.h"

#include <algorithm>
#include <vector>

/**
 * Damerau-Levenshtein distance algorithm
 * 
 * @param[in] s1 - first string for comparison
 * @param[in] s2 - second string for comparison
 * @return optimal string alignment distance
 */
int damerau_levenshtein_distance(const string& s1, const string& s2)
{
    int s1_len = s1.length();
    int s2_len = s2.length();
    int d[s1_len+1][s2_len+1];

    int i, j, cost;

    for (i = 0;i <= s1_len;i++)
        d[i][0] = i;
        
    for(j = 0; j<= s2_len; j++)
        d[0][j] = j;
    
    for (i = 1;i <= s1_len;i++) {
        for (j = 1; j<= s2_len; j++) {
            if (s1[i-1] == s2[j-1])
                cost = 0;
            else
                cost = 1;
            
            d[i][j] = min(
                d[i-1][j] + 1,          // delete
                min(d[i][j-1] + 1,      // insert
                d[i-1][j-1] + cost)     // substitution
            );
            
            if ((i > 1) && (j > 1) && (s1[i-1] == s2[j-2]) &&  (s1[i-2] == s2[j-1])) {
                d[i][j] = min(
                    d[i][j],
                    d[i-2][j-2] + cost   // transposition
                );
            }
        }
    }
    
    return d[s1_len][s2_len];
}
