# ----------
# User Instructions:
#
# Create a function compute_value which returns
# a grid of values. The value of a cell is the minimum
# number of moves required to get from the cell to the goal.
#
# If a cell is a wall or it is impossible to reach the goal from a cell,
# assign that cell a value of 99.
# ----------

grid = [[0, 1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0]]
goal = [len(grid) - 1, len(grid[0]) - 1]
cost = 1  # the cost associated with moving from a cell to an adjacent one

delta = [[-1, 0],  # go up
         [0, -1],  # go left
         [1, 0],  # go down
         [0, 1]]  # go right

delta_name = ['^', '<', 'v', '>']


def compute_value(grid, goal, cost):
    # ----------------------------------------
    # insert code below
    # ----------------------------------------
    path=[[99 for col in range(len(grid[0]))] for row in range(len(grid))]
    policy = [[' ' for col in range(len(grid[0]))] for row in range(len(grid))]

    change =True

    while (change):
        change=False  # change to True when actually change sth
        for x in range(len(grid)):
            for y in range(len(grid[0])):
                if goal[0]==x and goal[1]==y:
                    if path[x][y]>0:  # which is 99
                        path[x][y]=0
                        policy[x][y] = '*'  # reach the goal
                        change=True

                elif grid[x][y]==0:
                    for i in range(len(delta)):
                        # next point x2, y2
                        x2 = x + delta[i][0]
                        y2 = y + delta[i][1]
                        #next2=[x2,y2]
                        if x2 >= 0 and x2 < len(grid) and y2 >= 0 and y2 < len(grid[0]) and grid[x2][y2]==0: # inside grid and grid cell is open
                            v2=path[x2][y2]+cost

                            if v2<path[x][y]:  #if the new value < original value update
                                change=True
                                path[x][y]=v2
                                policy[x][y]=delta_name[i]
    # make sure your function returns a grid of values as
    # demonstrated in the previous video.
    #return path
    return policy

for row in compute_value(grid, goal, cost):
    print(row)

