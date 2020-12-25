import unittest
from Earley import Earley
from Earley import Situation


class CheckTest(unittest.TestCase):
    def test_1(self):
        word = Earley('a', ['S -> a'])
        self.assertEqual(word.check(), 'Выводится')

    def test_2(self):
        word = Earley('ab', ['S -> a', 'S -> aA', 'A -> b'])
        self.assertEqual(word.check(), 'Выводится')

    def test_3(self):
        word = Earley('aaaaaaaaaab', ['S -> a', 'S -> aS', 'S -> b'])
        self.assertEqual(word.check(), 'Выводится')

    def test_4(self):
        word = Earley('ab', ['S -> a', 'S -> aA', 'A -> b'])
        self.assertNotEqual(word.check(), 'aa')

    def test_5(self):
        word = Earley('(a+a)', ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        self.assertEqual(word.check(), 'Выводится')

    def test_6(self):
        word = Earley('(a+(a*a))', ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        self.assertEqual(word.check(), 'Выводится')

    def test_7(self):
        word = Earley('(a+(a*a)+a*(a*a*a*a))', ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        self.assertEqual(word.check(), 'Выводится')

    def test_8(self):
        word = Earley('((a+(a*(a))+a*((((a*a*a)))*a)))',
                      ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        self.assertEqual(word.check(), 'Выводится')

    def test_9(self):
        word = Earley('(((a+(a*(a))+a*((((a*((a)*a))))*a))))',
                      ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        self.assertEqual(word.check(), 'Выводится')


class PredictTest(unittest.TestCase):
    def test_1(self):
        word = Earley('a', ['S -> a'])
        word.predict(0)

        is_added = False
        add = Situation('S', 'a', 0, 0)
        for situation in word.D[0]:
            if (situation.entry == add.entry and situation.out == add.out and
                    situation.ind == add.ind and situation.point == add.point):
                is_added = True

        self.assertEqual(is_added, True)

    def test_2(self):
        word = Earley('(a+a)', ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        word.predict(0)

        is_added = False
        add = Situation('S', 'T', 0, 0)
        for situation in word.D[0]:
            if (situation.entry == add.entry and situation.out == add.out and
                    situation.ind == add.ind and situation.point == add.point):
                is_added = True

        self.assertEqual(is_added, True)

    def test_3(self):
        word = Earley('(a+a)', ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        word.predict(0)

        is_added = False
        add = Situation('S', 'T+S', 0, 0)
        for situation in word.D[0]:
            if (situation.entry == add.entry and situation.out == add.out and
                    situation.ind == add.ind and situation.point == add.point):
                is_added = True

        self.assertEqual(is_added, True)


class ScanTest(unittest.TestCase):
    def test_1(self):
        word = Earley('a', ['S -> a'])
        word.D[0].add(Situation('S', 'a', 0, 0))
        word.scan(0)

        is_added = False
        add = Situation('S', 'a', 0, 1)
        for situation in word.D[1]:
            if (situation.entry == add.entry and situation.out == add.out and
                    situation.ind == add.ind and situation.point == add.point):
                is_added = True

        self.assertEqual(is_added, True)

    def test_2(self):
        word = Earley('(a+a)', ['S -> T+S', 'S -> T', 'T -> F*T', 'T -> F', 'F -> (S)', 'F -> a'])
        word.D[2].add(Situation('S', 'T+S', 1, 1))
        word.scan(2)

        is_added = False
        add = Situation('S', 'T+S', 1, 2)
        for situation in word.D[3]:
            if (situation.entry == add.entry and situation.out == add.out and
                    situation.ind == add.ind and situation.point == add.point):
                is_added = True

        self.assertEqual(is_added, True)


if __name__ == '__main__':
    unittest.main()
