def keccak_permutation(state):
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

    A = [int.from_bytes(state[i * 8:(i + 1) * 8], "little") for i in range(25)]

    def ROL(x, n):
        return ((x << n) | (x >> (64 - n))) & 0xFFFFFFFFFFFFFFFF

    def print_state(A, step_name, round_index):
        print(f"Étape: {step_name}, Tour: {round_index}")
        for y in range(5):
            print(" ".join(f"{A[x + 5 * y]:016x}" for x in range(5)))
        print()

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

    for round_index in range(24):
        print_state(A, "Début du tour", round_index)
        theta(A)
        print_state(A, "Après theta", round_index)
        rho(A)
        print_state(A, "Après rho", round_index)
        pi(A)
        print_state(A, "Après pi", round_index)
        chi(A)
        print_state(A, "Après chi", round_index)
        iota(A, round_index)
        print_state(A, "Après iota", round_index)

    state = b"".join(A[i].to_bytes(8, "little") for i in range(25))
    return state

def keccak_squeeze(state, hash_size, rate=136):
    hash_output = bytearray()
    bytes_extracted = 0

    while bytes_extracted < hash_size:
        to_copy = min(hash_size - bytes_extracted, rate)
        hash_output.extend(state[:to_copy])
        bytes_extracted += to_copy
        print(f"Bytes extracted: {bytes_extracted}")
        print(f"Hash size: {hash_size}")
        if bytes_extracted < hash_size:
            state = keccak_permutation(state)

    return bytes(hash_output)

def main():
    state = bytearray([0] * 200)
    hash_size = 32
    rate = 136
    output_hash = keccak_squeeze(state, hash_size, rate)
    print("Hash généré :")
    print(output_hash.hex())

if __name__ == "__main__":
    main()
