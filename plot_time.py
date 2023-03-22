import matplotlib.pyplot as plt
import sys

n = int(sys.argv[1])
# x axis values
x = [i for i in range(1,n+1)]
y = []
# corresponding y axis values
file = open('timing.txt', 'r')
for each in file:
    y.append(float(each))

# plotting the points
fig1 = plt.gcf()
plt.plot(x, y, color='green', marker='o', markerfacecolor='blue')

# setting x and y axis range
# plt.ylim(1,51)
# plt.xlim(1,8)

# naming the x axis
plt.xlabel('Starting Point')
# naming the y axis
plt.ylabel('Time in Milliseconds')

# giving a title to my graph
# plt.title('Some cool customizations!')

# function to show the plot
# plt.show()

# saving as png
fig1.savefig("./" + "hand" + "/plot_" + str(n) + ".jpg", dpi = 100)
