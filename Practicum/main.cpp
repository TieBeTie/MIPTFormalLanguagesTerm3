#include "main.h"

int main() {
  string polish_notation;
  char x;
  int k;
  cout << "Enter the regular expression in RPN\n";
  cin >> polish_notation;
  cout << "Letter\n";
  cin >> x;
  cout << "Len of searching prefix\n";
  cin >> k;

  int min_word = MinWordPrefixK(polish_notation, x, k);
  if (min_word == -1) {
    cout << "Error: Incorrect expression!\n";
    return 0;
  }
  if (min_word == INF) {
    cout << "INF";
    return 0;
  }
  cout << "Len of word is\n" << min_word;
  return 0;
}