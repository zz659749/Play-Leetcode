/// Source : https://leetcode.com/problems/unique-word-abbreviation/
/// Author : liuyubobobo
/// Time   : 2016-12-03


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
//#include <sstream>
#include <cassert>
#include <stdexcept>

using namespace std;


/// Problem
/*****************************************************************************************************
 *
 * An abbreviation of a word follows the form <first letter><number><last letter>.
 * Below are some examples of word abbreviations:
 *
 * a) it                      --> it (no abbreviation)
 *
 *      1
 * b) d|o|g --> d1g
 *
 *              18
 * c) i|nternationalizatio|n  --> i18n
 *
 *          10
 * d) l|ocalizatio|n          --> l10n
 *
 * Assume you have a dictionary and given a word,
 * find whether its abbreviation is unique in the dictionary.
 * A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
 *
 * Example:
 * Given dictionary = [ "deer", "door", "cake", "card" ]
 *
 * isUnique("dear") -> false
 *
 * isUnique("cart") -> true
 *
 * isUnique("cane") -> false
 *
 * isUnique("make") -> true
 *****************************************************************************************************/


/// Solution
/**************************************************************************************
 * Use a hashtable to store all the string's abbreviation.
 * The tricky part here is that we need another set to store all the different words.
 * For function isUnique, we need to see:
 *     - The dictionary doesn't contain the word, then it's unique
 *     - The dictionary contains exactly the same word,
 *       and no aother word's abbreviation is the same, then it's unique (tricky)
 *     - The dictionary contains other words have the same abbreviation,
 *       then it's not unique.
 *
 * Time Complexity:
 *     If there are n words and the longest word contains slen character, then
 *     the building time : O(n*slen)
 *     isUnique : O(slen)
 * Space Complexity: O(n)
 **************************************************************************************/

class ValidWordAbbr {

private:
    unordered_set<string> words;
    unordered_map<string,int> abbr_words;

    string abbr(const string &word){

        //assert( word.size() >= 2 );

        // According to the test cases,
        // If a word's length is less than 2,
        // Then the abbreviation is itself.
        if( word.size() <= 2 )
            return word;

        int num = word.substr( 1 , word.size()-2 ).size();
        return word[0] + to_string(num) + word[word.size()-1];
    }

public:
    ValidWordAbbr(vector<string> &dictionary) {

        for( int i = 0 ; i < dictionary.size() ; i ++ ){
            string word = dictionary[i];
            if( words.find( word ) == words.end() ){
                words.insert( word );
                abbr_words[ abbr(dictionary[i]) ] += 1;
            }
        }
    }

    bool isUnique(string word) {
        //assert( word.size() >= 2 );

        if( words.find(word) == words.end() )
            return abbr_words[abbr(word)] == 0;

        return abbr_words[abbr(word)] == 1;
    }

    void show(){

        cout<<"words:"<<endl;
        for(unordered_set<string>::iterator iter = words.begin() ; iter != words.end() ; iter ++ )
            cout<<"  "<<*iter<<endl;

        cout<<"abbr_words:"<<endl;
        for(unordered_map<string,int>::iterator iter = abbr_words.begin() ; iter != abbr_words.end() ; iter ++ )
            cout << "  ( " << iter->first << " , " << iter->second << " )"<<endl;

        cout<<endl;
    }
};

int main() {

    vector<string> dictionary;
    dictionary.push_back("deer");
    dictionary.push_back("door");
    dictionary.push_back("cake");
    dictionary.push_back("card");
    dictionary.push_back("hello");

    ValidWordAbbr vwa(dictionary);
    vwa.show();

    cout<<vwa.isUnique("dear")<<endl;
    cout<<vwa.isUnique("cart")<<endl;
    cout<<vwa.isUnique("cane")<<endl;
    cout<<vwa.isUnique("make")<<endl;
    cout<<vwa.isUnique("hello")<<endl;

    return 0;
}