from cs50 import get_string


def main():
    n = get_string("Number:")
    check(n)


def check(n):
    length = len(n)

    # check if there are 13~16 digit numbers
    if length < 13 or length > 16:
        print("INVALID")
        return 1

    # check American Express
    if (length == 15 and (n[:2] == '34' or n[:2] == '37')):
        if (algorithm(n) == 0):
            print("AMEX")
            return 0
        else:
            print("INVALID")
            return 1

    # check MasterCard
    elif (length == 16 and (int(n[:2]) >= 51 and int(n[:2]) <= 55)):
        if (algorithm(n) == 0):
            print("MASTERCARD")
            return 0
        else:
            print("INVALID")
            return 1

    # check VISA
    elif n[0] == '4':
        if (algorithm(n) == 0):
            print("VISA")
            return 0
        else:
            print("INVALID")
            return 1

    else:
        print("INVALID")
        return 1


def algorithm(n):
    numbers = list(n)
    numbers = [int(x) for x in numbers]
    flag = 0
    sum = 0
    for j in range(len(n)-1, -1, -1):
        if flag == 0:
            sum += numbers[j]
            flag = 1
        elif flag == 1:
            temp = numbers[j] * 2
            while temp > 0:
                sum += temp % 10
                temp //= 10
            flag = 0

    if sum % 10 == 0:
        return 0
    else:
        return 1


if __name__ == "__main__":
    main()