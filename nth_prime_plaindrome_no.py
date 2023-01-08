def checkPlaindrome(n):
    """Function to check if the string is palindrome or not"""

    if n == n[::-1]:  # Checking if the string is equal to its reverse i.e palindrome
        return True
    else:
        return False


def checkPrime(n):
    """Function to check if the number is prime or not"""

    if n > 1:
        for i in range(2, n):
            if (n % i) == 0:  # Checking if the number is divisible by any number other than 1 and itself i.e not prime
                return False
        else:
            return True
    else:
        return False


def main():
    ch = 'y'
    print('*'*70 + "\n* Enter a number to find palindrome and prime number at nth position *\n" + '*'*70)

    while ch in 'yY':  # Looping until user enters anything other than y or Y
        n = int(input("* Enter a number: "))
        temp = n  # Storing the number in a temporary variable to use it later
        while True:
            # Checking if the number is palindrome and prime
            if checkPlaindrome(str(n)) and checkPrime(n):
                # Printing the number and the nth position
                print(
                    "* The nth number {no} is a palindrome and a prime number after n+{nth}".format(no=n, nth=n-temp))
                break
            else:
                n += 1  # Incrementing the number by 1 if it is not palindrome and prime

        # Asking user if he wants to continue
        ch = input('*'*70 + "\n* Do you want to continue? (y/n): ")
    print('*'*70 + "\n* Thank you for using the program. Have a nice day!                  *\n" + '*'*70)


if __name__ == '__main__':
    main()
