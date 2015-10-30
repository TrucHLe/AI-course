# Reinforcement Learning NIM
This program uses reinforcement learning to learn how to play a good game of static NIM. In other words, it learns to take better moves after each game, thus eventually learning the rule of static NIM.

### Compile and Run
Please compile using C++ 11

```sh
$ g++ -std=c++11 *.cpp -o main
$ ./main
```

### Learned Data
The program reads learned moves from and updates its data to learned.txt
Change the data file to original.txt in FileManager.cpp/FileManager::getFile() to make the program learn to play NIM from scratch.