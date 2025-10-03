/*
    CoderPad Sandbox question: Pig Latin

    Intro
    To solve this challenge, feel free to use any and all resources available to you. Once you start the exercise, you’ll have two hours to complete and submit your solution.

    Challenge - Pig Latin
    Pig Latin is a farcical “language” used to entertain children, but also to teach them some valuable language concepts along the way.  Translating English to Pig Latin is simple:

        1. Take the first consonant (or cluster of consonants) of a word, move it to the end of the word, and add a suffix of “ay”

        2. If a word begins with a vowel, just add “way” at the end

        3. For the sake of readability, separate the Pig Latin-ized parts of the word with a dash -

    Your challenge is to implement the method pigLatinize that takes a string phrase and translates it to Pig Latin. You’re free to add additional classes, variables, and methods if you would like.

    The input phrase could be as short as a single word, or as long as multiple sentences or paragraphs. Whitespace, capitalization, and punctuation should be honored and maintained in your final answer.

    Examples

        1. “pig” => “ig-pay”

        2. “pig latin” => “ig-pay atin-lay”

        3. “Pig Latin” => “ig-Pay atin-Lay”
*/

#include <iostream>
#include <sstream>  // For isstringstream
#include <string>
#include <vector>
#include "../Utils/assertEqual.h"   // For ASSERT_STR_EQ(a, b)

using namespace std;

class Solution {
public:
    static string pigLatinize(const string& phrase) {
        string plPhrase = "";

        if (phrase.length() == 0)
            return "";

        auto words = getWords(phrase);

        for (const auto& w : words)
            plPhrase += pigLatinizeWord(w) + " ";

        return plPhrase.substr(0, plPhrase.length() - 1);
    }

protected:
    static string pigLatinizeWord(const string& word) {
        if (word.length() == 0)
            return "";
        if (isVowel(word[0]) || isdigit(word[0]))
            return word + "-way";
        else {
            string prefix(1, word[0]);
            for (int i = 1; i < int(word.length()); i++) {
                if (isVowel(word[i]) || isdigit(word[i]))
                    break;
                else
                    prefix += word[i];
            }
            return word.substr(prefix.length(), word.length() - prefix.length() + 1) + "-" + prefix + "ay";
        }
    }

    static vector<string> getWords(const string& phrase) {
        istringstream stream(phrase);
        string word;
        vector<string> words;
        while (stream >> word)
            words.push_back(word);
        return words;
    }

    static bool isVowel(const char c) {
        switch (tolower(c)) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }
};

int main() {
    Solution sol;   // Allocated on the stack, no need to manually delete it
    ASSERT_STR_EQ(sol.pigLatinize("pig"), "ig-pay");
    ASSERT_STR_EQ(sol.pigLatinize("apple"), "apple-way");
    ASSERT_STR_EQ(sol.pigLatinize("smile"), "ile-smay");
    ASSERT_STR_EQ(sol.pigLatinize("I"), "I-way");
    ASSERT_STR_EQ(sol.pigLatinize("string"), "ing-stray");
    ASSERT_STR_EQ(sol.pigLatinize(""), "");
    ASSERT_STR_EQ(sol.pigLatinize("123"), "123-way");
    ASSERT_STR_EQ(sol.pigLatinize("Egg"), "Egg-way");
    ASSERT_STR_EQ(sol.pigLatinize("Crab"), "ab-Cray");
    ASSERT_STR_EQ(sol.pigLatinize("pig latin"), "ig-pay atin-lay");
    ASSERT_STR_EQ(sol.pigLatinize("Pig Latin"), "ig-Pay atin-Lay");
    return 0;
}