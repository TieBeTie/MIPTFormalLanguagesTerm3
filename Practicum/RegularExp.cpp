#include "RegularExp.h"

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
      result.prefix[0] = 1;
      result.prefix[1] = 1;
    } else if (symbol == '1') {
      result.prefix[0] = 0;
    } else {
      result.prefix[0] = 1;
    }
    parser.push(result);
  }
  int min_word = parser.size() == 1 ? parser.top().prefix[k] : -1;
  return min_word;
}