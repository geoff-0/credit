class Card:
    def __init__(self, company, prefixes, lengths):
        self.company = company
        self.prefixes = prefixes
        self.lengths = lengths

        def __str__(card):
            return self.company

# Card types declaration
card_types = [Card("AMERICAN EXPRESS", [32, 37], [15]), Card("MASTERCARD", [51, 52, 53, 54, 55], [16]), Card("VISA", [4], [13, 16])]


### Functions ###

# Function that gets the card type of an inputted number
def card_type(n):
    for i in range(len(card_types)):
        for j in range(len(card_types[i].prefixes)):
            if (cut_number(n, 2) == card_types[i].prefixes[j]):
                for o in range(len(card_types[i].lengths)):
                    if len(str(n)) == card_types[i].lengths[o]:
                        return card_types[i].company
            
    return "INVALID"

def luhn(n):
    addedProduct = 0
    a = []

    a = [x * 2 for x in str(n)[::2]]

    for i in range(len(a) - 1):
        a[i] = int(a[i])
    
    a = [int(str(n)[1::2])]
    for i in range(len(a) - 1):
        addedProduct += a[i]

    if addedProduct % 10 == 0:
        return True
    elif addedProduct % 10 != 0:
        return False

# Cuts number from an inputted place
def cut_number(number, place):
    while number >= pow(10, place):
        number /= 10

    return int(number)

# Gets digit from number
def get_digit(number, place):
    while number >= pow(10, place):
        number /= 10

    return int(number % 10)

credit_number = int(input("Number: "))

if luhn(credit_number) == True:
    print(card_type(credit_number))
elif luhn(credit_number) != True:
    print("INVALID")


