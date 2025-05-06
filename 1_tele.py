# Hashing and collision resolution techndique 


def linear(tel, size): 
    hash_table = [None] * size 
    for num in tel: 
        index = num % size 
        ori_idx = index 
        while hash_table[index] is not None: 
            index = (index + 1) % size 
            if index == ori_idx: 
                print("Hash table is full......XXXXXXXX") 
                return hash_table 
        hash_table[index] = num 
    return hash_table 


def quadratic(tel, size): 
    hash_table = [None] * size 
    for num in tel: 
        index = num % size 
        ori_idx = index 
        i = 1 
        while hash_table[index] is not None: 
            index = (ori_idx + i**2) % size 
            i += 1 
            if i == size: 
                print("Hash table is full......XXXXXXXX") 
                return hash_table 
        hash_table[index] = num 
    return hash_table 


def double(tel, size):
    hash_table = [None] * size

    def second_hash(x):
        return 7 - (x % 7)  # Secondary hash function

    for num in tel:
        index = num % size
        step = second_hash(num)
        ori_idx = index
        attempts = 0

        while hash_table[index] is not None:
            index = (index + step) % size
            attempts += 1
            if attempts == size:
                print("Hash table is full......XXXXXXXX")
                return hash_table
        hash_table[index] = num

    return hash_table


# Input Section
n = int(input("Number of Clients: ")) 
tel = [] 
for i in range(n): 
    m = int(input(f"Enter the telephone number of client {i + 1}: ")) 
    tel.append(m) 

print("Telephone Numbers:", tel) 
size = int(input("Enter the Size of the Hash Table: ")) 

# Looping Menu
while True:
    print("\n             _MENU_      ") 
    print("              1. Linear Probing") 
    print("              2. Quadratic Probing") 
    print("              3. Double Hashing") 
    print("              4. Exit") 
    ch = int(input("Enter your choice: ")) 

    if ch == 1: 
        table = linear(tel, size) 
        print("\nHash Table (Linear Probing):")
    elif ch == 2: 
        table = quadratic(tel, size) 
        print("\nHash Table (Quadratic Probing):")
    elif ch == 3: 
        table = double(tel, size) 
        print("\nHash Table (Double Hashing):")
    elif ch == 4: 
        print("Exit") 
        break
    else: 
        print("You have entered the wrong choice.")
        continue

    # Common display for all methods
    for i in range(size): 
        print(f"Index {i} : {table[i] if table[i] is not None else -1}")
