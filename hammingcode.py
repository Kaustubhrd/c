
def encode(data):
    code = [0] * 8

    # Place data bits at positions 3, 5, 6 and 7
    code[3], code[5], code[6], code[7] = map(int, data)

    # Calculate even-parity bits
    code[1] = code[3] ^ code[5] ^ code[7]
    code[2] = code[3] ^ code[6] ^ code[7]
    code[4] = code[5] ^ code[6] ^ code[7]

    return code


def syndrome(code):
    s1 = code[1] ^ code[3] ^ code[5] ^ code[7]
    s2 = code[2] ^ code[3] ^ code[6] ^ code[7]
    s4 = code[4] ^ code[5] ^ code[6] ^ code[7]

    return s1 + 2 * s2 + 4 * s4


def show(code):
    return ''.join(str(code[i]) for i in range(1, 8))


def decode(code):
    return ''.join(str(code[i]) for i in [3, 5, 6, 7])


data = "1011"
code = encode(data)

# Transmitter
print("Original data:", data)
print("Transmitted codeword:", show(code))

# Receiver: correct transmission
received = code.copy()

print("\n--- Correct Reception ---")
error = syndrome(received)

if error == 0:
    print("No error detected.")

print("Decoded data:", decode(received))

# Receiver: introduce an error at bit position 6
received = code.copy()
received[6] ^= 1

print("\n--- Error Reception ---")
print("Received codeword:", show(received))

error = syndrome(received)

if error != 0:
    print("Error at bit position:", error)
    received[error] ^= 1

print("Corrected codeword:", show(received))
print("Decoded data:", decode(received))
