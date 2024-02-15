import random
import string

numberOfFiles = 1000
filenameLength = (5, 20)
contentLength = (50, 100)


# Function to generate a random string of a given length
def random_string(length):
    letters = string.ascii_lowercase
    return "".join(random.choice(letters) for _ in range(length))


# Open the initialStateFile.txt for writing
with open("initialStateFile.txt", "w") as f:
    # Generate 1000 files
    for i in range(numberOfFiles):
        # Generate a random filename and a random content
        filename = random_string(random.choice(filenameLength)) + ".txt"
        content = random_string(random.choice(contentLength)).replace(
            "\n", "\\n"
        )  # Replace newline characters with \n
        # Write the filename and content to the initialStateFile.txt
        f.write(f"{filename}:{content}\n")
