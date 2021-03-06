#include "RegularExp.cpp"

int main() {
  string polish_notation;
  char x;
  int k;
  cin >> polish_notation >> x >> k;

  int min_word = MinWordPrefixK(polish_notation, x, k);
  if (min_word == -1) {
    cout << "ERROR\n";
    return 0;
  }
  if (min_word == INF) {
    cout << "INF";
    return 0;
  }
  cout << min_word << '\n';
  return 0;
}