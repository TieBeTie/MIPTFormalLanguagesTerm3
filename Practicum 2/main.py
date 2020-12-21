from Earley import Earley


def main():
    rules = ['S* -> S']
    print("Задайте правила в формате A -> B, для завершения переведите строку")
    line = ' '
    while line != '':
        line = input()
        rules.append(line)
    rules.pop()

    print("Какое слово проверить?")
    word = Earley(input())

    if word.check(rules):
        print('Слово выводится')
    else:
        print('Слово не выводится')


if __name__ == "__main__":
    main()
