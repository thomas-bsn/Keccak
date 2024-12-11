import hashlib
import subprocess
import os

def run_binary():
    print("Exécution du binaire pour générer le fichier first_block.txt...")
    result = subprocess.run(["./keccak", "test/test_file.bin"], capture_output=True, text=True)
    if result.returncode != 0:
        print("Erreur lors de l'exécution du binaire :")
        print(result.stderr)
        exit(1)
    print("Binaire exécuté avec succès.")

def load_block_from_file(filename):
    with open(filename, "r") as file:
        return [int(line.strip(), 16) for line in file.readlines()]

def generate_reference_block(filename, rate=136):
    with open(filename, "rb") as f:
        data = f.read()
    block = data[:rate]
    return [int.from_bytes(block[i:i+8], "little") for i in range(0, len(block), 8)]

def compare_blocks(file_block, reference_block):
    if file_block == reference_block:
        print("✅ Les blocs sont identiques.")
    else:
        print("❌ Les blocs sont différents.")
        print("\nBloc extrait (C) :")
        print(file_block)
        print("\nBloc de référence (Python) :")
        print(reference_block)

def main():
    run_binary()
    file_block = load_block_from_file("test/first_block.txt")
    reference_block = generate_reference_block("test/test_file.bin")
    compare_blocks(file_block, reference_block)

if __name__ == "__main__":
    main()
