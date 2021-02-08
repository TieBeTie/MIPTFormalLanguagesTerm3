from Earley import Earley


def main():
    rules = []
    print("Задайте правила в формате A -> B, для завершения переведите строку")
    line = ' '
    while line != '':
        line = input()
        rules.append(line)
    rules.pop()

    print("Какое слово проверить?")
    earley = Earley()
    if earley.check(input(), rules):
        print('Выводится')
    else:
        print('Не выводится')


if __name__ == "__main__":
    main()
