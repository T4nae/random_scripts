"""
Q. write a python script that generates an acronym word from a given sentence.
    - Take multiple strings as input in the form of list.
    - Add the first letter of each string to output.
    - Iterate over the complete string and add every next letter to space to output.
    - Change the output to uppercase (required acronym).
    - You have to generate acronyms for all given strings.
"""


class acronym:
    def __init__(self, text):  # constructor

        self.text = text
        self.acronym = self.get_acronym()

    def get_acronym(self):  # function to generate acronym
        """
        This function generates an acronym word from a given sentence.
        """
        # splits the string into list of words then iterates over each word and adds the first letter to new list after converting it to uppercase and then joins the list to form a string
        # driver code
        return ' '.join([word[0].upper() for word in self.text.split()])

    def __str__(self):  # string representation of the class object when printed
        """
        This function returns the acronym word.
        """
        return self.acronym
    # iterate over the complete string and add every next letter to space to output


def main():
    ch = 'y'  # choice variable
    print('*'*70 + "\n*                Enter Phrase's to find its acronym                  *\n" + '*'*70)
    while ch in 'yY':  # loop to continue until user wants to exit
        text = input("* Enter a phrase: ")  # input phrase
        print('* Acronym generated from given Phrase: \"{p}\" is \"{a}\"'.format(
            a=acronym(text), p=text))  # print the acronym
        # ask user if he wants to continue
        ch = input('*'*70 + "\n* Do you want to continue? (y/n): ")
    # exit message
    print('*'*70 + "\n* Thank you for using the program. Have a nice day!                  *\n" + '*'*70)


if __name__ == '__main__':
    main()
