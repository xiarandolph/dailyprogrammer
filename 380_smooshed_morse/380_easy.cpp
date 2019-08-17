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

    return 0;
}