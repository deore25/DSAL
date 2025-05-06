# ADT Dictionary using Hashing (Open Addressing - Without Replacement)

TABLE_SIZE = 10
EMPTY = ("<EMPTY>", None)

# Hash Table Initialization
hash_table = [EMPTY for _ in range(TABLE_SIZE)]

# Hash Function
def hash_function(key):
    return hash(key) % TABLE_SIZE

# Insert key-value pair
def insert(key, value):
    index = hash_function(key)
    start_index = index

    while hash_table[index][0] != "<EMPTY>" and hash_table[index][0] != key:
        index = (index + 1) % TABLE_SIZE
        if index == start_index:
            print("Hash table is full.")
            return
    hash_table[index] = (key, value)
    print(f"Inserted ({key}, {value}) at index {index}")

# Find value by key
def find(key):
    index = hash_function(key)
    start_index = index

    while hash_table[index][0] != "<EMPTY>":
        if hash_table[index][0] == key:
            print(f"Found key '{key}' with value '{hash_table[index][1]}' at index {index}")
            return hash_table[index][1]
        index = (index + 1) % TABLE_SIZE
        if index == start_index:
            break
    print("Key not found.")
    return None

# Delete key-value pair
def delete(key):
    index = hash_function(key)
    start_index = index

    while hash_table[index][0] != "<EMPTY>":
        if hash_table[index][0] == key:
            hash_table[index] = EMPTY
            print(f"Deleted key '{key}' from index {index}")
            return True
        index = (index + 1) % TABLE_SIZE
        if index == start_index:
            break
    print("Key not found.")
    return False

# Display the hash table
def display_table():
    print("\nHash Table:")
    for i in range(TABLE_SIZE):
        key, value = hash_table[i]
        if key == "<EMPTY>":
            print(f"{i}: [Empty]")
        else:
            print(f"{i}: [{key}, {value}]")
    print()

# Main Menu
def main():
    while True:
        print("\n--- Dictionary ADT Menu ---")
        print("1. Insert")
        print("2. Find")
        print("3. Delete")
        print("4. Display Table")
        print("5. Exit")

        choice = input("Enter choice: ")

        if choice == '1':
            key = input("Enter key: ")
            value = input("Enter value: ")
            insert(key, value)
        elif choice == '2':
            key = input("Enter key to find: ")
            find(key)
        elif choice == '3':
            key = input("Enter key to delete: ")
            delete(key)
        elif choice == '4':
            display_table()
        elif choice == '5':
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Please enter 1–5.")

# Run
main()
