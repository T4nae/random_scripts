# Importing the Pillow library
from PIL import Image   
from PIL import ImageDraw
from PIL import ImageFont
import os
import random

# Custom font style and font size
myFont = ImageFont.truetype(r'Fonts\HomemadeApple.ttf', 30)
imgPath = r"./pages/"
imgForPdf = []


def randPage():
    """Randomly select a page from the pages folder"""

    pages = ['paper.jpeg', 'paper2.jpeg']
    # Open an Image
    img = Image.open(imgPath + pages[random.randint(0, 1)])
    return img


def randString():
    """Generate a random string of 10 characters"""

    random_string = ''
    for _ in range(10):
        # Considering only upper and lowercase letters
        random_integer = random.randint(97, 97 + 26 - 1)
        flip_bit = random.randint(0, 1)
    # Convert to lowercase if the flip bit is on
        random_integer = random_integer - 32 if flip_bit == 1 else random_integer
    # Keep appending random characters using chr(x)
        random_string += (chr(random_integer))

    return random_string


# print(len(text))
# 45 char per line #1125 char per page

def makeImg(chunks):
    """Add text to the image and save it in the temp folder"""

    size = 0
    newPage = 1125
    img = randPage()
    I1 = ImageDraw.Draw(img)
    p = 0
    for j in range(0, len(chunks)):
        chunk = chunks[j]
        I1.text((110, 100 + p*40), chunk, font=myFont, fill='Black')
        p = p + 1
        size = size + len(chunk)
        # print(size)

        # check if page is full and go to next page
        if size == newPage:
            saveImg(img)
            img = randPage()
            I1 = ImageDraw.Draw(img)
            newPage = newPage + 1125
            p = 0
            # print(newPage)
    return img

# Display edited image
# img.show()

def saveImg(img):
    """Save the image in the temp folder"""

    if os.path.exists(r"./temp"):
        pass
    else:
        os.mkdir(r"./temp")
    save = randString() + 'save.jpeg'
    img.save(r"./temp/" + save)
    imgForPdf.append(save)
    # print(imgForPdf)


def savePdf():
    """Save the images as a pdf"""

    images = []
    for i in imgForPdf:
        im = Image.open(r"./temp/" + i)
        images.append(im)
    string = randString()
    images[0].save(string + 'save.pdf', save_all=True,
                   append_images=images[1:])


def deleteImg():
    """Delete the temp folder and all the images in it"""
    for i in imgForPdf:
        os.remove(r'./temp/' + i)
    os.rmdir(r"./temp")


def main():
    """Main function"""

    print("Enter Text or File Path")
    text = input('> ')
    chunks = []
    # try to open the text as a file
    try:
        with open(text, 'r') as file:
            text = file.readlines()
            for j in text:
                if len(j) > 45:
                    temp = [j[i:i+45] for i in range(0, len(j), 45)]
                    for k in temp:
                        chunks.append(k)
                elif j == '\n':
                    chunks.append(' '*45)
                else:
                    chunks.append(j)

    # if it fails then take it as a string
    except:
        chunkSize = 45
        chunks = [text[i:i+chunkSize] for i in range(0, len(text), chunkSize)]
    
    saveImg(makeImg(chunks))
    savePdf()
    deleteImg()


if __name__ == '__main__':
    main()
