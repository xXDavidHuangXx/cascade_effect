README 12/23/2014 Center Goal Mission Release

Releaser(s):
Sauhaarda and Helen

Release Notes:
In this release we have made sure that the robot hits the center goal every time.
We have also disabled PID and move at full speed, when the robot is hitting the
center goal. This allows us to hit the pole at a higher speed. We have also added
a failsafe hit, that hits the center goal twice just in case our first movement
wasn't enough to hit the center goal. This can be found in the hitpole() function
at the top of the program. this program does not contain wait for start() at the
begenning use only for testing

