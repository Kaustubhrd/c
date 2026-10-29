INF = float('inf')

n = int(input("Enter number of routers: "))

cost = []

print("Enter the cost matrix (use 999 for no direct connection):")

for i in range(n):
    row = list(map(int, input().split()))
    cost.append(row)

distance = [row[:] for row in cost]
next_hop = [[-1] * n for _ in range(n)]

for i in range(n):
    distance[i][i] = 0
    next_hop[i][i] = i

    for j in range(n):
        if i != j and cost[i][j] != 999:
            next_hop[i][j] = j

print("\nInitial Cost Matrix:")
for row in cost:
    print(row)

print("\nInitial Distance Matrix:")
for row in distance:
    print(row)

updated = True

while updated:
    updated = False

    for i in range(n):
        for j in range(n):
            for k in range(n):

                if cost[i][k] != 999 and distance[k][j] != 999:
                    new_cost = cost[i][k] + distance[k][j]

                    if new_cost < distance[i][j]:
                        distance[i][j] = new_cost
                        next_hop[i][j] = k
                        updated = True

print("\nFinal Routing Tables:")

for i in range(n):
    print("\nRouter", i)
    print("Destination\tCost\tNext Hop")

    for j in range(n):
        if distance[i][j] == 999:
            print(j, "\t\tINF\t-")
        else:
            print(j, "\t\t", distance[i][j], "\t", next_hop[i][j])


source = int(input("\nEnter source router: "))
destination = int(input("Enter destination router: "))

if distance[source][destination] == 999:
    print("No path exists between the selected routers.")
else:
    print("Minimum Cost:", distance[source][destination])
    print("Shortest Path:", end=" ")

    current = source
    print(current, end="")

    while current != destination:
        current = next_hop[current][destination]
        print(" ->", current, end="")

    print()
