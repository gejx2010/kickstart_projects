#python3
#Author: spgoal

DEBUG = True

import time

def solve():
  pass

t = input()
i = 1
while i <= int(t):
  # read params
  st = time.time()
  r = solve()
  ed = time.time()
  print("Case #%d: " % (i));
  if DEBUG:
    print("Solve case %d takes %s seconds." % (i, ed - st))
  i += 1
