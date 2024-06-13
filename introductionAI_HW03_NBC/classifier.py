import csv
import re

try:
    train_csv = open('train.csv', 'r')
    test_csv = open('test.csv', 'r')
    stopwords_txt = open('stopwords.txt', 'r')
except OSError:
    print('file open fail.')

# Task 1 ready
train_rdr = csv.reader(train_csv)
test_rdr = csv.reader(test_csv)

stopwords_set = set()
frequency_dict_good = dict()
frequency_dict_bad = dict()


for line in stopwords_txt:
    stopwords_set.add(line.strip())

for line in list(train_rdr)[1:]:
    [score, text_all] = line
    score = int(score)

    for token in re.split('[0-9 !\"#$%&\'()*+,-./:;<=>?@[\]^_`{|}~\n]+', text_all.lower()):
        if token in stopwords_set or token == '':
            continue

        if score == 5:
            if token not in frequency_dict_good:
                frequency_dict_good[token] = 1
            else:
                frequency_dict_good[token] += 1

        elif score == 1:
            if token not in frequency_dict_bad:
                frequency_dict_bad[token] = 1
            else:
                frequency_dict_bad[token] += 1


frequency_list_good = list(zip(frequency_dict_good.values(), frequency_dict_good.keys()))
frequency_list_good.sort(reverse=True)
top_words_good = [i[1] for i in frequency_list_good[:1000]]
top_words_good_set = {i[1] for i in frequency_list_good[:1000]}

frequency_list_bad = list(zip(frequency_dict_bad.values(), frequency_dict_bad.keys()))
frequency_list_bad.sort(reverse=True)
top_words_bad = [i[1] for i in frequency_list_bad[:1000]]
top_words_bad_set = {i[1] for i in frequency_list_bad[:1000]}

# Task 1 done
print('=== task 1: print out the top 20-50 words ===')

print('\n=== Positive features ===\n')
for i, item in enumerate(frequency_list_good[:20]):
    print(f'{item[1]} \t({i + 1}th, appeared {item[0]} times))')
print('\n=== Negative features ===\n')
for i, item in enumerate(frequency_list_bad[:20]):
    print(f'{item[1]} \t({i + 1}th, appeared {item[0]} times))')
