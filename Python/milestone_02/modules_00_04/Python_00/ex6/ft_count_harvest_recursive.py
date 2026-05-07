def ft_count_harvest_recursive(day = 1, limit = 0):
	if (limit == 0):
		days = int(input("Days until harvest: "))
		limit = days
	if (day <= limit):
		print(f"Day {day}")
		ft_count_harvest_recursive(day + 1, limit)
	if (day == limit):
		print("Harvest time!")
