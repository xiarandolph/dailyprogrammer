/**
 * @file 380_easy.cpp
 * 
 * @author xiarandolph
 */

#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

typedef std::vector<std::string> string_vec;

std::string smorse(const std::string& str) {
    std::string morse[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", 
        ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

    std::string ans = "";
    std::string::const_iterator it = str.begin();
    while (it != str.end()) {
        if (*it >= 'a') ans.append(morse[*it - 'a']);
        else ans.append(morse[*it - 'A']);
        it++;
    }

    return ans;
}

void load_words(string_vec& vec, const std::string& filename) {
    std::string temp = "";

    std::ifstream in("enable1.txt");
    if (!in.good()) {
        return;
    }

    while (in >> temp) {
        vec.push_back(temp);
    }
    in.close();
}

// find a smorse that is the code for 13 different words
std::string bonus_one(const string_vec& words) {
    std::unordered_map<std::string, int> counter;
    string_vec::const_iterator it;
    for (it = words.begin(); it != words.end(); it++) {
        counter[smorse(*it)]++;
    }

    std::unordered_map<std::string, int>::iterator it2 = counter.begin();
    while (it2 != counter.end()) {
        if (it2->second == 13) return it2->first;
        it2++;
    }

    return "err";
}

// find a word whose smorse is 15 dashes in a row
std::string bonus_two(const string_vec& words) {
    string_vec::const_iterator it = words.begin();
    std::string::iterator str_it;
    std::string str;
    int i, max;
    while (it != words.end()) {
        str = smorse(*it);
        str_it = str.begin();
        // count dashes in a row
        max = i = 0;
        while (str_it != str.end()) {
            if (*str_it == '.') i = 0;
            else i++;
            if (i > max) max = i;
            str_it++;
        }

        if (max == 15) return *it;

        it++;
    }
    return "err";
}

// find a 21-letter word whose smorse has same number of dots and dashes
std::string bonus_three(const string_vec& words) {
    string_vec::const_iterator it = words.begin();
    std::string::iterator str_it;
    std::string str;
    int i;
    while (it != words.end()) {
        if (it->length() != 21) {
            it++;
            continue;
        }

        i = 0;
        str = smorse(*it);
        str_it = str.begin();
        while (str_it != str.end()) {
            if (*str_it == '.') i++;
            else i--;
            str_it++;
        }

        if (i == 0 && it->compare("counterdemonstrations")) return *it;

        it++;
    }
    return "err";
}

bool is_palindrome(const std::string& str) {
    int len = str.length();
    for (int i = 0; i <= len / 2; i++) {
        if (str[i] != str[len - 1 - i]) return false;
    }
    return true;
}

// find a 13-letter word that has a palindrome smorse
std::string bonus_four(const string_vec& words) {
    string_vec::const_iterator it = words.begin();
    std::string::iterator str_it;
    std::string str;
    while (it != words.end()) {
        if (it->length() != 13) {
            it++;
            continue;
        }
        str = smorse(*it);
        if (is_palindrome(str)) return *it;
        it++;
    }
}

// find five 13-character sequences that never appear
string_vec bonus_five(const string_vec& words) {
    std::unordered_set<std::string> sequences;
    std::string str;
    // get every possible 13-character sequence
    for (int i = 0; i < pow(2, 13); i++) {
        str = "";
        for (int j = 0; j < 13; j++) {
            if (i & (int) pow(2, j)) str += '.';
            else str += '-';
        }
        sequences.insert(str);
    }

    string_vec::const_iterator it = words.begin();
    std::unordered_set<std::string>::iterator it2;
    while (it != words.end()) {
        str = smorse(*it);
        for (it2 = sequences.begin(); it2 != sequences.end(); ) {
            if (str.find(*it2) != std::string::npos) {
                it2 = sequences.erase(it2);
            } else {
                it2++;
            }
        }
        it++;
    }

    string_vec ans;
    for (std::string s : sequences) ans.push_back(s);
    return ans;
}

int main() {
    printf("smorse(\"sos\") => %s\n", smorse("sos").c_str());
    printf("smorse(\"daily\") => %s\n", smorse("daily").c_str());
    printf("smorse(\"programmer\") => %s\n", smorse("programmer").c_str());
    printf("smorse(\"bits\") => %s\n", smorse("bits").c_str());
    printf("smorse(\"three\") => %s\n", smorse("three").c_str());

    string_vec words;
    load_words(words, "enable1.txt");

    printf("bonus one: %s\n", bonus_one(words).c_str());
    printf("bonus two: %s\n", bonus_two(words).c_str());
    printf("bonus three: %s\n", bonus_three(words).c_str());
    printf("bonus four: %s\n", bonus_four(words).c_str());
    string_vec sequences = bonus_five(words);
    printf("bonus five: ");
    for (std::string s : sequences) printf("%s, ", s.c_str());
    printf("\n");

    return 0;
}