def ft_count_harvest_iterative():
    days = int(input("Days until harvest: "))
    count = 1
    while (count <= days):
        print(f"Day {count}")
        count += 1
    print("Harvest time!")
