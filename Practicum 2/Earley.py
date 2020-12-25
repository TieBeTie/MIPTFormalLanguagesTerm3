class Earley:
    def __init__(self, word, rules):
        self.word = word
        self.D = {}
        self.rules = []
        self.parse_rules(rules)
        # Инициализация множества ситуаций D0, . . . , D|w|
        self.D[0] = set()
        self.D[0].add(Situation('S#', 'S', 0, 0))
        for i in range(1, len(word) + 1):
            self.D[i] = set()

    # Проверка пренадлежности слова грамматике
    def check(self):
        # разберём базу отдельно
        past_len = len(self.D[0])
        self.predict(0)
        self.complete(0)
        new_len = len(self.D[0])
        while past_len != new_len:
            past_len = new_len
            self.predict(0)
            self.complete(0)
            new_len = len(self.D[0])

        for i in range(1, len(self.word) + 1):
            self.scan(i - 1)
            past_len = len(self.D[i])
            self.predict(i)
            self.complete(i)
            new_len = len(self.D[i])
            while new_len != past_len:
                past_len = new_len
                self.predict(i)
                self.complete(i)
                new_len = len(self.D[i])

        for situation in self.D[len(self.word)]:
            if situation.entry == 'S#' and situation.out == 'S' and \
                    situation.ind == 0 and situation.point == 1:
                return 'Выводится'
        return 'Не выводится'

    # Конвертирование правил в удобный для использования вид
    def parse_rules(self, rules):
        self.rules.append(Rule(['S#', 'S']))
        for rule in rules:
            self.rules.append(Rule(str(rule).split(' -> ')))

    # Предсказание следующего правила ↓
    def predict(self, word_tale):
        insert_situations = []
        for situation in self.D[word_tale]:
            # Проверяем вышла ли точка за границы правила
            if situation.point < len(situation.out):
                # Сохраняем терминальный символ после точки
                unterminal = situation.out[situation.point]
                # Пытаемся предсказать каждое правило
                for rule in self.rules:
                    # Если нетерминалы равны, то добавляем новую ситуацию (•
                    if rule.entry == unterminal:
                        insert_situations.append(Situation(unterminal, rule.out, word_tale, 0))

        for situation in insert_situations:
            self.add_situation(situation, word_tale)

    # Чтение символа →
    def scan(self, word_tale):
        # Для каждого правила, если за точкой идёт символ, который читается, то сдвигаем точку
        for situation in self.D[word_tale]:
            if situation.point < len(situation.out) and \
                    self.word[word_tale] == situation.out[situation.point]:
                self.add_situation(
                    Situation(situation.entry, situation.out, situation.ind, situation.point + 1),
                    word_tale + 1)

    # Завершение обработки нетерминала ↑
    def complete(self, word_tale):
        insert_situations = []
        # Выбираем все ситуации с точками на конце, что значит, что они завершены
        for final_situation in self.D[word_tale]:
            if final_situation.point == len(final_situation.out):
                final_unterminal = final_situation.entry[0]
                # Значит все ситуации с концом слова = индексам завершенных ситуаций
                for situation in self.D[final_situation.ind]:
                    # и у которых точка стоит перед завершенным терминалом
                    if situation.point < len(situation.out) and \
                            situation.out[situation.point] == final_unterminal:
                        # нужно им сдвинуть свою точку вправо
                        # добавится в ситуации с концом слова = концам слов завершенных ситуаций
                        insert_situations.append(
                            Situation(situation.entry, situation.out, situation.ind, situation.point + 1))

        for situation in insert_situations:
            self.add_situation(situation, word_tale)

    # добавление ситуации в конкретное множество ситуаций, происходит меньше, чем за O(n), хэш-таблица
    def add_situation(self, retry_situation, word_tale):
        is_already_added = False
        for situation in self.D[word_tale]:
            if (situation.out == retry_situation.out and situation.entry == retry_situation.entry
                    and situation.point == retry_situation.point and situation.ind == retry_situation.ind):
                is_already_added = True
        if not is_already_added:
            self.D[word_tale].add(retry_situation)


class Rule:
    def __init__(self, rule):
        # A -> B
        self.entry = rule[0]  # A
        self.out = rule[1]  # B


class Situation:
    def __init__(self, entry, out, index, point):
        # (A -> a•Bb, i)
        self.entry = entry  # A
        self.out = out  # a•Bb
        self.ind = index  # i
        self.point = point  # index of point
