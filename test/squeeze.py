def keccak_permutation(state):
    """
    Implémente la permutation Keccak (simplifiée pour SHA3).
    L'état doit être donné sous forme d'un tableau de 200 octets (1600 bits).
    """
    # Constantes des 24 tours
    RC = [
        0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
        0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
        0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
        0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
        0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
        0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
        0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
        0x8000000000008080, 0x0000000080000001, 0x8000000080008008
    ]

    # Convertir l'état en une matrice 5x5 de 64 bits
    A = [int.from_bytes(state[i * 8:(i + 1) * 8], "little") for i in range(25)]

    def ROL(x, n):
        """Rotation circulaire gauche."""
        return ((x << n) | (x >> (64 - n))) & 0xFFFFFFFFFFFFFFFF

    def theta(A):
        C = [A[x] ^ A[x + 5] ^ A[x + 10] ^ A[x + 15] ^ A[x + 20] for x in range(5)]
        D = [C[(x - 1) % 5] ^ ROL(C[(x + 1) % 5], 1) for x in range(5)]
        for x in range(5):
            for y in range(5):
                A[x + 5 * y] ^= D[x]

    def rho(A):
        offsets = [
            0, 1, 62, 28, 27,
            36, 44, 6, 55, 20,
            3, 10, 43, 25, 39,
            41, 45, 15, 21, 8,
            18, 2, 61, 56, 14
        ]
        for i in range(25):
            A[i] = ROL(A[i], offsets[i])

    def pi(A):
        A_tmp = A[:]
        for x in range(5):
            for y in range(5):
                A[y + 5 * ((2 * x + 3 * y) % 5)] = A_tmp[x + 5 * y]

    def chi(A):
        for y in range(5):
            A_tmp = A[y * 5:(y + 1) * 5]
            for x in range(5):
                A[x + 5 * y] ^= ~A_tmp[(x + 1) % 5] & A_tmp[(x + 2) % 5]

    def iota(A, round_index):
        A[0] ^= RC[round_index]

    # 24 tours de permutation
    for round_index in range(24):
        theta(A)
        rho(A)
        pi(A)
        chi(A)
        iota(A, round_index)

    # Reconstruire l'état en octets
    state = b"".join(A[i].to_bytes(8, "little") for i in range(25))
    return state


def keccak_squeeze(state, hash_size, rate=136):
    """
    Simule l'étape de squeeze pour SHA3-256.
    """
    hash_output = bytearray()
    bytes_extracted = 0

    while bytes_extracted < hash_size:
        to_copy = min(hash_size - bytes_extracted, rate)
        hash_output.extend(state[:to_copy])  # Extraire les octets disponibles
        bytes_extracted += to_copy

        # Appliquer une permutation si nécessaire
        if bytes_extracted < hash_size:
            state = keccak_permutation(state)  # Implémentez une permutation Keccak

    return bytes(hash_output)

def main():
    # Initialiser l'état Keccak
    state = bytearray([0] * 200)  # État initial avec tous les octets à 0

    # Définir la taille du hash pour SHA3-256
    hash_size = 32  # SHA3-256 produit un hash de 256 bits (32 octets)
    rate = 136  # SHA3-256 utilise un rate de 1088 bits (136 octets)

    # Extraire le hash
    output_hash = keccak_squeeze(state, hash_size, rate)

    # Afficher le résultat
    print("Hash généré :")
    print(output_hash.hex())

if __name__ == "__main__":
    main()
