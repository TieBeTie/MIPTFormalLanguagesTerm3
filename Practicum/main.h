#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::cin;
using std::cout;
using std::stack;
using std::string;
using std::min;

const int INF = 100000000;

class RegularExp {
public:
    vector<int> prefix;
    vector<int> word;
    int k;

    explicit RegularExp(int k) {
        prefix.assign(k + 1, INF);
        word.assign(k + 1, INF);
        this->k = k;
    }

    void Plus(const RegularExp &alpha, const RegularExp &beta) {
        for (int i = 0; i <= k; ++i) {
            prefix[i] = min(alpha.prefix[i], beta.prefix[i]);
            word[i] = min(alpha.word[i], beta.word[i]);
        }
    }

    void Concat(const RegularExp &alpha, const RegularExp &beta) {
        //перебираем всевозможные x^n.x^m
        int min_word = word[k]; //наибольшее слово из k букв
        for (int n = 0; n <= k; ++n) {
            // ищем минимальное слово, которое положим наверх, если слово будет длиннее, чем k
            for (int m = 0; m <= k; ++m) {
                int bruteforce = alpha.word[n] + beta.word[m]; //x^(n+m) кринж
                if (bruteforce <= k && WordIsExist(bruteforce)) {
                    word[bruteforce] = min(bruteforce, word[bruteforce]);
                }
                if (bruteforce > k && WordIsExist(bruteforce)) {
                    min_word = min(min_word, bruteforce);
                }
            }
        }
        word[k] = min(min_word, word[k]);
        Recovery();
        //x^n u . x^m v, x^n u . x^m
        for (int answer = 0; answer <= k; ++answer) {
            if (alpha.prefix[answer] != answer && WordIsExist(alpha.prefix[answer])) {
                min_word = INF;       //если не найдено, значит несуществует
                //конкатенируем каждое слово, несостоящее из префикса, c минимальным словом
                for (int i = 0; i <= k; ++i) {
                    if (WordIsExist(alpha.prefix[answer] + beta.prefix[i])) {
                        min_word = min(min_word, alpha.prefix[answer] + beta.prefix[i]);
                    }
                }
                prefix[answer] = min(min_word, prefix[answer]); //префикс мог быть посчитан ранее
            }
        }
        //x^n . x^m v
            //просто перебираем подходящие под условия слова,
            // если встретили, слово меньше, чем уже есть запоминаем его
        for (int n = 0; n <= k; ++n) {
            for (int m = 0; m <= k; ++m) {
                min_word = INF;
                int prefix_result = n + m;
                if (alpha.prefix[n] == n && beta.prefix[m] != m &&
                n + m <= k && WordIsExist(alpha.prefix[n] + beta.prefix[m])) {
                    min_word = min(min_word, alpha.prefix[n] + beta.prefix[m]);
                }
                if (prefix_result <= k) {
                    prefix[prefix_result] = min(min_word, prefix[prefix_result]);
                    //не забываем, что префикс мог быть посчитан
                }
            }
        }
        Recovery();
    }

    void Star(const RegularExp &alpha) {
        word[0] = 0;  //может быть пустым словом
        prefix[0] = 0;
        for (int i = 1; i <= k; ++i) { //перенос полей
            word[i] = alpha.word[i];
            prefix[i] = alpha.prefix[i];
        }
        //перебор всех слов, поиск минимального,
        // слово существует и оно нужно для тогда и только когда, его префикс не равен бесконечности
        //prefix[orbit] = u -> prefix[orbit * 2] = u^2 -> ... -> prefix[orbit * order] = u^order,
        // так происходит перебор
        //при расставлении префиксов необходимо учитывать,
        // что слово с префиксом n может получится меньше,
        //чем слово с меньшим префиксом, поэтому выполняем
        int min_word = INF;
        for (int orbit = 1; orbit <= k; ++orbit) {
            if (WordIsExist(prefix[orbit])) {
                for (int order = 2; orbit * order <= k; order++) {
                    prefix[orbit * order] = min(prefix[orbit * order], prefix[orbit] * order);
                    if (prefix[orbit * order] == orbit * order) {
                        word[orbit * order] = orbit * order;
                    }
                    if (orbit * (order + 1) > k) {
                        min_word = min(min_word, prefix[orbit] * (order + 1));
                    }
                }
            }
        }
        prefix[k] = min(min_word, prefix[k]);
        word[k] = min(min_word, word[k]);
        //учитываем, что большее слово может выйти за границы
        Recovery();
    }

private:
    static bool WordIsExist(int len_word) {
        return len_word < INF;
    }

    void Recovery() {
        for (int i = 0; i <= k; ++i) {
            if (word[i] == i) {
                prefix[i] = word[i];
            }
            assert(i <= prefix[i]);
        }
        int min_word = word[k];
        for (int i = k - 1; i >= 0; --i) {
            word[i] = min(word[i], min_word);
            min_word = min(word[i], min_word);
        }
        min_word = prefix[k];
        for (int i = k - 1; i >= 0; --i) {
            if (WordIsExist(prefix[i])) {
                prefix[i] = min(prefix[i], min_word);
                min_word = min(prefix[i], min_word);
            }
        }
    }
};

bool IsCorrectSymbol(char symbol) {
    string correct_symbol = "abc1.+*";
    return correct_symbol.find(symbol) != std::string::npos;
}

int MinWordPrefixK(const string &expression, const char x, int k) {
    stack<RegularExp> parser;
    RegularExp alpha(k);
    RegularExp beta(k);
    RegularExp result(k);

    for (char symbol : expression) {
        if (!IsCorrectSymbol(symbol)) {
            return -1;
        }
        result = RegularExp(k);
        if (symbol == '+' || symbol == '.' || symbol == '*') {
            if (parser.empty()) {
                return -1;
            }
            beta = parser.top();   //обработать
            parser.pop();
            if (symbol == '*') {
                result.Star(beta);
            } else {
                if (parser.empty()) {
                    return -1;
                }
                alpha = parser.top();
                parser.pop();
                if (symbol == '+') {
                    result.Plus(alpha, beta);
                } else {
                    result.Concat(alpha, beta);
                }
            }
        } else if (symbol == x) {
            result.prefix[1] = 1;
            result.word[0] = 1;
            result.word[1] = 1;
        } else if (symbol == '1') {
            result.prefix[0] = 0;
            result.word[0] = 0;
        } else {
            result.prefix[0] = 1;
        }
        parser.push(result);
    }
    int min_word = parser.size() == 1 ? parser.top().prefix[k] : -1;
    return min_word;
}