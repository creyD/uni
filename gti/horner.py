# Horner Scheme
# Conversion from and to the decimal system from
# and to all systems with a base < 10 according to the Horner Scheme


def decToN(number, destination_base):
    remainder, i, converted = number, 0, 0

    while remainder != 0:
        converted += (remainder % destination_base) * (10 ** i)
        remainder = remainder // destination_base
        i += 1

    return converted


def nToDec(number, origin_base):
    converted = 0

    for i in range(0, len(str(number))):
        converted += int(str(number)[(len(str(number)) - 1) - i]) \
            * origin_base ** i

    return converted

print(nToDec(1010, 2))