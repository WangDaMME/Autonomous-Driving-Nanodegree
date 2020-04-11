# ----------
# User Instructions:
#
# Define a function, search() that returns a list
# in the form of [optimal path length, row, col]. For
# the grid shown below, your function should output
# [11, 4, 5].
#
# If there is no valid path from the start point
# to the goal, your function should return the string
# 'fail'
# ----------

# Grid format:
#   0 = Navigable space
#   1 = Occupied space


grid = [[0, 0, 1, 0, 0, 0],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 1, 1, 1, 0],
        [0, 0, 0, 0, 1, 0]]
init = [0, 0]
goal = [len(grid)-1, len(grid[0])-1]
cost = 1

delta = [[-1, 0], # go up
         [ 0,-1], # go left
         [ 1, 0], # go down
         [ 0, 1]] # go right

delta_name = ['^', '<', 'v', '>']

def search(grid,init,goal,cost):
    # ----------------------------------------
    # insert code here
    # ----------------------------------------
    closed=[[0 for row in range(len(grid[0]))] for col in range(len(grid)) ]
    closed[init[0]][init[0]]=1

    expand=[[-1 for row in range(len(grid[0]))] for col in range(len(grid)) ]
    action=[[-1 for row in range(len(grid[0]))] for col in range(len(grid)) ] # for each cell, what action it took to get there


    count =0 #count init expand step
    x=init[0]
    y=init[1]
    g=0
    open=[[g,x,y]]   # further investigation points
    expand[x][y]=count  # node trasverse
    count+=1
    while (len(open)>0):
        open.sort()  # 根据g -- 最小排
        open.reverse()
        next=open.pop()
        if next[1] is goal[0] and next[2] is goal[1]:
            path=next
            return action
        else:
            for dir in delta:
                g,x,y=next[0],next[1],next[2]
                x2=x+dir[0]
                y2=y+dir[1]
                if x2>=0 and x2<len(grid) and y2>=0 and y2<len(grid[0]):
                    if closed[x2][y2]==0 and grid[x2][y2]==0:
                        g2=g+cost
                        open.append([g2,x2,y2])
                        expand[x2][y2]=count
                        count += 1
                        action[x2][y2]=delta.index(dir) # memorize the action in action
                        closed[x2][y2]=1

    else:
        print('fail')
        path=False
    return action

print(search(grid,init,goal,cost))
print('=========Policy========')

action=search(grid,init,goal,cost)
policy=[[' ' for row in range(len(grid[0]))] for col in range(len(grid)) ]
x=goal[0]
y=goal[1]
policy[x][y]="*"
while x!=init[0] and y!=init[0]:
    x2=x-delta[action[x][y]][0]
    y2=y-delta[action[x][y]][1]
    policy[x2][y2]=delta_name[action[x][y]]
    x=x2
    y=y2

for i in range(len(grid)):
    for j in range(len(grid[0])):
        if grid[i][j]==1:
            policy[i][j]='X' #blocked

for i in range(len(policy)):
    print(policy[i])