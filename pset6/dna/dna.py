import csv
import sys


def main():

    # Ensure correct usage
    if (len(sys.argv)) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read data into memory from data.csv
    data = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            data.append(row)
    
    # Record types of STR that we need to check.
    STRs = list(data[0].keys())
    STRs.pop(0)

    # Read data into memory from sequence.txt
    dna = []
    with open(sys.argv[2], "r") as file:
        dna = file.read()

    # Record repeated times of each STR in the DNA sequence.
    count_number = {}
    for STR in STRs:
        count_number[STR] = str(count_str(dna, STR))

    # Print out the name of the matching individual or no match.
    for person in data:
        flag = 0
        for STR in STRs:
            if person[STR] != count_number[STR]:
                flag = 1
                break
        if flag == 0:
            print(person['name'])
            return
    print("No match")
    
    return


def count_str(dna, STR):
    """Count the maximum number of times that the STR repeats in the DNA sequence."""
    i = 0
    count = 0
    count_max = 0
    n = len(STR)
    while i < len(dna):
        if dna[i:i+n] == STR:
            i += n
            count += 1
            while dna[i:i+n] == STR:
                i += n
                count += 1
            if count_max < count:
                count_max = count
            count = 0

        else:
            i += 1

    return count_max


if __name__ == "__main__":
    main()