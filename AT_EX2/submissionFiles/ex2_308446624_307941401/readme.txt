AutoPlayer Algorithm:

Flow and knowledge of the auto player:
We added a file: AutoPlayerFile_playerNum.txt. 
The file contains the board at each stage as known to the auto player. 
Also, the move that the auto player performs is written to that file.

We added two new pieces types:
1. X - unknown piece: the auto player knows there is an opponent piece at this position on board, but does not know anything about this piece.
It may be anything, including the opponent's flag.
2. M - moving piece: the auto player knows there is an opponent piece at this position on board that can move.
Especially, this is not the opponent's flag.
All other representations remain the same.

Positioning the board:
The positioning is a random positioning. 
The auto player adds all the pieces he can put on board (position each piece as the amount that is defined).

Deciding the next move:
For every valid move we are calculating a score for that move. 
Cases:
1. Best case: fight with unknown opponent's piece. This may be the opponent's flag.
2. Winning a fight will get high score as well (but less then option 1).
3. losing a fight will get bad scoring.
4. if there is not a fight we will calculate the minimum distance from an unknown piece of the opponent. 
That is because we wish to come near the opponent's flag. 

 