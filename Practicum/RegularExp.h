#ifndef PRACTICUM_REGULAREXP_H
#define PRACTICUM_REGULAREXP_H


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
  int k;

  explicit RegularExp(int k) {
    prefix.assign(k + 1, INF);
    this->k = k;
  }

  void Plus(const RegularExp &alpha, const RegularExp &beta) {
    for (int i = 0; i <= k; ++i) {
      prefix[i] = min(alpha.prefix[i], beta.prefix[i]);
    }
    Recovery();
  }

  void Concat(const RegularExp &alpha, const RegularExp &beta) {
    //перебираем всевозможные (x^n).v
    int result_prefix;
    int result_word;
    for (int n = 0; n <= k; ++n) {
      if (IsXWord(alpha.prefix, n)) {
        for (int m = 0; m <= k; ++m) {
          if (WordIsExist(beta.prefix[m])) {
            // положим наверх, если слово будет длиннее, чем k
            result_prefix = n + m; //x^(n+m) кринж
            result_word = alpha.prefix[n] + beta.prefix[m]; // длина слова

            if (result_prefix <= k) {
              prefix[result_prefix] = min(prefix[result_prefix], result_word);
              //если beta - префикс-слово
              if (IsXWord(beta.prefix, m) && result_word <= k) {
                prefix[result_word] = result_word;
              }

            } else if (result_prefix > k && WordIsExist(result_prefix)) {
              prefix[k] = min(prefix[k], result_prefix);
            }
          }
        }
      }
    }
    Recovery();

    //u.v
    int min_word;
    for (int n = 0; n <= k; ++n) {
      if (!IsXWord(alpha.prefix, n) && WordIsExist(alpha.prefix[n])) {
        min_word = INF;
        //если не найдено, значит несуществует
        //конкатенируем каждое слово, несостоящее из префикса, c минимальным словом
        for (int m = 0; m <= k; ++m) {
          if (WordIsExist(beta.prefix[m])) {
            min_word = min(min_word, alpha.prefix[n] + beta.prefix[m]);
          }
        }
        prefix[n] = min(prefix[n], min_word); //префикс мог быть посчитан ранее
      }
    }
    Recovery();
  }

  void Star(const RegularExp &alpha) {
    prefix[0] = 0;
    //перенос полей
    for (int i = 1; i <= k; ++i) {
      prefix[i] = alpha.prefix[i];
    }
    //поиск реальных слов состоящих только из букв x
    for (int left = 1; left <= k; ++left) {
      int right = left + 1;
      if (IsXWord(prefix, left) && IsXWord(prefix, right)) {
        Bruteforce(left, right);
      }
    }
    Recovery();
    //прибавка к словам из x всевозможных слов, состоящих не только из х
    int result_word;
    int result_prefix;
    int min_word = INF;
    for (int m = 1; m <= k; ++m) {
      if (IsXWord(prefix, m)) {
        for (int n = 1; n <= k; ++n) {
          if (WordIsExist(prefix[n])) {
            result_prefix = m + n;
            result_word = m + prefix[n];
            if (result_prefix <= k) {
              prefix[result_prefix] = min(prefix[result_prefix], result_word);
            } else {
              //не забываем предельный случай
              min_word = min(min_word, result_word);
            }
          }
        }
        Recovery();
      }
    }
  }

private:
  bool WordIsExist(int len_word) {
    return len_word < INF;
  }

  //конкатинация всех слов длины m, n
  void Bruteforce(int m, int n) {
    int result_word;
    int min_word = INF;
    for (int a = m; a <= k; a += m) {
      for (int b = n; b <= k; b += n) {
        result_word = a + b; // длина слова
        if (result_word <= k) {
          prefix[result_word] = result_word;
        } else {
          //не забываем предельный случай
          min_word = min(min_word, result_word);
        }
      }
    }
    prefix[k] = min(prefix[k], min_word);
  }

  bool IsXWord(const vector<int> &pref, int len_word) {
    return pref[len_word] == len_word;
  }

  //если слово появилось с каким-то префиксом появилось
  void Recovery() {
    for (int i = k; i > 0; --i) {
      assert(i <= prefix[i]);
      //то все слова длиннее, но которые имеют меньший префикс должны быть заменены
      prefix[i - 1] = min(prefix[i], prefix[i - 1]);
    }
  }
};


#endif //PRACTICUM_REGULAREXP_H
