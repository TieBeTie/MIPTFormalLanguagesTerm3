from dataclasses import dataclass

class Earley:
    def __init__(self):
        self.word = str
        self.D = {}
        self.rules = []

    # Проверка пренадлежности слова грамматике
    def check(self, word, rules):
        self.word = word
        self.D = {}
        self.rules = []
        self.parse_rules(rules)
        # Инициализация множества ситуаций D0, . . . , D|w|
        self.D[0] = set()
        self.D[0].add(States('S#', 'S', 0, 0))
        for i in range(1, len(word) + 1):
            self.D[i] = set()

        # разберём базу отдельно
        self.closure(0)
        new_len = len(self.D[0])
        while True:
            past_len = new_len
            self.closure(0)
            new_len = len(self.D[0])
            if past_len == new_len:
                break

        for i in range(1, len(self.word) + 1):
            self.scan(i - 1)
            past_len = len(self.D[i])
            self.closure(i)
            new_len = len(self.D[i])
            while new_len != past_len:
                past_len = new_len
                self.closure(i)
                new_len = len(self.D[i])

        for state in self.D[len(self.word)]:
            if state.entry == 'S#' and state.out == 'S' and \
                    state.ind == 0 and state.point == 1:
                return True
        return False

    # Конвертирование правил в удобный для использования вид
    def parse_rules(self, rules):
        self.rules.append(Rule(['S#', 'S']))
        for rule in rules:
            self.rules.append(Rule(str(rule).split(' -> ')))

    # Делает предикты и комплиты до посинения
    def closure(self, i):
        self.predict(i)
        self.complete(i)

    # Предсказание следующего правила ↓
    def predict(self, word_tale):
        insert_states = []
        for state in self.D[word_tale]:
            # Проверяем вышла ли точка за границы правила
            if state.point < len(state.out):
                # Сохраняем терминальный символ после точки
                unterminal = state.out[state.point]
                # Пытаемся предсказать каждое правило
                for rule in self.rules:
                    # Если нетерминалы равны, то добавляем новую ситуацию (•
                    if rule.entry == unterminal:
                        insert_states.append(States(unterminal, rule.out, word_tale, 0))

        for state in insert_states:
            self.add_state(state, word_tale)

    # Чтение символа →
    def scan(self, word_tale):
        # Для каждого правила, если за точкой идёт символ, который читается, то сдвигаем точку
        for state in self.D[word_tale]:
            if state.point < len(state.out) and \
                    self.word[word_tale] == state.out[state.point]:
                self.add_state(
                    States(state.entry, state.out, state.ind, state.point + 1),
                    word_tale + 1)

    # Завершение обработки нетерминала ↑
    def complete(self, word_tale):
        insert_states = []
        # Выбираем все ситуации с точками на конце, что значит, что они завершены
        for final_state in self.D[word_tale]:
            if final_state.point == len(final_state.out):
                final_unterminal = final_state.entry[0]
                # Значит все ситуации с концом слова = индексам завершенных ситуаций
                for state in self.D[final_state.ind]:
                    # и у которых точка стоит перед завершенным терминалом
                    if state.point < len(state.out) and \
                            state.out[state.point] == final_unterminal:
                        # нужно им сдвинуть свою точку вправо
                        # добавится в ситуации с концом слова = концам слов завершенных ситуаций
                        insert_states.append(
                            States(state.entry, state.out, state.ind, state.point + 1))

        for state in insert_states:
            self.add_state(state, word_tale)

    # добавление ситуации в конкретное множество ситуаций, происходит меньше, чем за O(n), хэш-таблица
    def add_state(self, retry_state, word_tale):
        is_already_added = False
        for state in self.D[word_tale]:
            if state.equals(retry_state):
                is_already_added = True
        if not is_already_added:
            self.D[word_tale].add(retry_state)


class Rule:
    def __init__(self, rule):
        # A -> B
        self.entry = rule[0]  # A
        self.out = rule[1]  # B


class States:
    def __init__(self, entry, out, index, point):
        # (A -> a•Bb, i)
        self.entry = entry  # A
        self.out = out  # a•Bb
        self.ind = index  # i
        self.point = point  # index of point

    def equals(self, other):
        return (self.entry == other.entry and
                self.out == other.out and
                self.ind == other.ind and
                self.point == other.point)
