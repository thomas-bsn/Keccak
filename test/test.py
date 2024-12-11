import subprocess
import hashlib

makefile_path = "./Makefile"
binary_path = "./keccak"
test_file_path = "./test/test_file.bin"

def compile_project():
    print("Compilation en cours...")
    result = subprocess.run(["make", "-f", makefile_path], capture_output=True, text=True)
    if result.returncode != 0:
        print("Erreur lors de la compilation :")
        print(result.stderr)
        exit(1)
    print("Compilation réussie.")

def execute_binary():
    print("Exécution du binaire...")
    result = subprocess.run([binary_path, test_file_path], capture_output=True, text=True)
    if result.returncode != 0:
        print("Erreur lors de l'exécution du binaire :")
        print(result.stderr)
        exit(1)
    print("Sortie du binaire :")
    print(result.stdout)
    hash_line = result.stdout.splitlines()[-1] 
    return hash_line.strip()

def calculate_python_hash():
    print("Calcul du hash avec hashlib...")
    with open(test_file_path, "rb") as f:
        file_data = f.read()
    hash_result = hashlib.sha3_256(file_data).hexdigest()
    print(f"Hash calculé avec hashlib : {hash_result}")
    return hash_result

def compare_hashes(binary_hash, python_hash):
    print("Comparaison des résultats...")
    if binary_hash == python_hash:
        print("✅ Les deux hash correspondent.")
    else:
        print("❌ Les hash sont différents.")
        print(f"Binaire : {binary_hash}")
        print(f"Hashlib : {python_hash}")

if __name__ == "__main__":
    compile_project()
    binary_hash = execute_binary()
    python_hash = calculate_python_hash()
    compare_hashes(binary_hash, python_hash)
