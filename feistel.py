import matplotlib.pyplot as plt

# --- Feistel round function (same spirit as your C++) ---
def F(r, k):
    r = (r + k) & 0xFFFF
    r ^= ((r << 5) | (r >> 11)) & 0xFFFF
    r ^= (r >> 3)
    return r & 0xFFFF


# --- encode32 equivalent ---
def encode32(x, key, rounds=4):
    if len(key) == 0:
        return x

    rounds = min(rounds, len(key))

    L = (x >> 16) & 0xFFFF
    R = x & 0xFFFF

    for r in range(rounds):
        f = F(R, key[r])
        L, R = R, L ^ f

    return ((L << 16) | R) & 0xFFFFFFFF


# --- parameters ---
key = [0x1234, 0x5678, 0x9ABC, 0xDEF0]
rounds = 4

# sample range (don’t plot all 2^32!)
N = 100000
xs = list(range(N))
ys = [encode32(x, key, rounds) for x in xs]

# --- plot ---
plt.figure(figsize=(8, 6))
plt.scatter(xs, ys, s=1)
plt.title("Feistel encode32 mapping")
plt.xlabel("input x")
plt.ylabel("encoded output")
plt.grid(True)
plt.show()
