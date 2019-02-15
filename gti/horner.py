def convertToN():
	print('From Decimal to any System (n > 10)')
	print('Insert Destination System Base')
	base_des = int(input())

	print('Insert Number')
	number = int(input())

	remainder, i, converted = number, 0, 0

	while remainder != 0:
		converted += (remainder % base_des) * (10 ** i)
		remainder = remainder // base_des
		i += 1

	print(converted)

def convertToDec():
	print('From any System (n > 10) to Decimal')
	print('Insert Origin System Base')
	base_ori = int(input())

	print('Insert Number')
	number = int(input())
	