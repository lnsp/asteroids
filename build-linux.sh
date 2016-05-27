sudo apt-get install libsfml-dev build-essential -y
rm *.o asteroids -f
g++ -c -std=c++11 *.cpp
g++ *.o -o asteroids -lsfml-graphics -lsfml-window -lsfml-system
echo Enter ./asteroids to run the game!
