def sum_algorisms(n):
    return sum([int(algo) for algo in str(n)])


while True:
    try:
        card = input("Number: ")
        card_sum = 0
        for index in range(len(card) % 2, len(card) - 1, 2):
            card_sum += sum_algorisms(int(card[index]) * 2)
        for index in range(1 - len(card) % 2, len(card), 2):
            card_sum += int(card[index])

        if (card_sum % 10 != 0):
            print("INVALID")
        else:
            if (len(card) == 15 and (card[0] == '3' and (card[1] == '4' or card[1] == '7'))):
                print('AMEX')
            elif (len(card) == 16 and (card[0] == '5' and (int(card[1]) >= 1 and int(card[1]) <= 5))):
                print('MASTERCARD')
            elif ((len(card) == 13 or len(card) == 16) and card[0] == '4'):
                print('VISA')
            else:
                print('INVALID')
        break
    except:
        continue
