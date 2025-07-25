# Mancala

## Description

Each of the two players, North and South, has six holes on their side of the board and their own pot (their "kalah"). Each hole start off with four beans in it. Players take turns making moves. A move begins with a player picking up all of the beans in one of their six holes. Then, proceeding counterclockwise, the player puts one bean in each hole and their own pot (skipping over their opponent's pot if the "sowing" gets that far), until all of the beans that were picked up have been sown. For example, if South had 4 beans in her #5 hole, she might pick them up and deposit one each in her #6 hole, her pot, and North's #6 and #5 hole. Depending on where the last bean ends up, one of three things happens:
If the last bean was placed in the player's pot, the player must take another turn.

If the last bean was placed in one of the player's own holes that was empty just a moment before, and if the opponent's hole directly opposite from that hole is not empty, then that last bean and all beans in the opponent's hole directly opposite from that hole are put into the player's pot, and the turn ends. (This is a capture.) Notice that it is not a capture if the player's last bean ends up in what was an empty hole on the opponent's side.

In all other cases, the turn ends.

Whenever the player whose turn it is can not make a move (because their side is empty), any beans remaining in their opponent's holes are put into that opponent's pot and the game is over. The winner is the player whose pot has the most beans.

## How to Run

download repository with bash command:
```shell
git clone https://github.com/max09lui/WTL-AI_Trial_Project
```

run game
```shell
make
```

Mancala UI:
```shell
North: name1
 3 3 3
0      0
 3 3 3
SOUTH: name2
```


