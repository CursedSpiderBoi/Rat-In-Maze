#pragma once
#include<iostream>
#include<windows.h>
#include<C:\\CODES\\C++\\codes\\useable codes\\myqueue.h>
#include<stdlib.h>
/*
176---
178----
179-----
219-------s
*/
using namespace std;
struct Pos {
	int x;
	int y;
	void operator=(Pos obj) {
		x = obj.x;
		y = obj.y;
	}
	bool operator!=(Pos obj) {
		if (x != obj.x && y != obj.y) {
			return true;
		}
		return false;
	}
};
void Display(char** arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j];
		}
		cout << endl;
	}
}
template<class t>
class list {
private:
	struct Node {
		t data;
		Node* next;
		Node() {
			data = 0;
			next = NULL;
		}
		Node(t info) {
			data = info;
			next = NULL;
		}
		Node(t info, Node* pot) {
			data = info;
			next = pot;
		}
	};
	Node* head;
	Node* tail;
public:
	void Insert(t val) {
		Node* temp = new Node(val);
		if (head == NULL) {
			head = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
	}
	void Delete() {
		if (head == NULL) {
			return;
		}
		Node* temp = head;
		head = head->next;
		delete[]temp;
	}
	void Delete(t& val) {
		if (head == NULL) {
			return;
		}
		Node* temp = head;
		val = head->data;
		head = head->next;
		delete[]temp;
	}
	~list() {
	}
};
class Stack{
	Pos* arr;
	int size;
	int top;

public:
	Stack()
	{
		arr = NULL;
		size = 0;
		top = -1;
	}
	Stack(int size)
	{
		this->size = size;
		arr = new Pos[size];
		top = -1;
	}
    bool IsEmpty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }
    bool IsFull()
    {
        if (top == size)
            return true;
        else
            return false;
    }
    bool push(Pos val)
    {
        if (!IsFull())
        {
            arr[++top] = val;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool pop()
    {
        if (!IsEmpty())
        {
            arr[top--];
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Top(Pos& val)
    {
        if (!IsEmpty())
        {
            val = arr[top];
            return true;
        }
        else
            return false;
    }

    ~Stack(){ delete[] arr; }

};
struct moves {
	bool CanMove;
	bool visited;
	move() {
		CanMove = 0;
		visited = 0;
	}
};
void BackTrack(char** arr, int size, Pos Start, Pos End, moves** CanMove) {
	Stack obj(size * size);
    bool** Indexes_check = new bool* [size];
    for (int i = 0; i < size; i++)
        Indexes_check[i] = new bool[size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            Indexes_check[i][j] = false;
    }

    obj.push(Start);
    int flag = 0;
    while (Start.x != End.x || Start.y != End.y)
    {
        if (Start.y+1 < size && arr[Start.x][Start.y+1] == ' ' && Indexes_check[Start.x][Start.y+1] == false)     // Right
        {
            Indexes_check[Start.x][Start.y] = true;
            Start.y = Start.y + 1;
            arr[Start.x][Start.y+1]=(char)176;
            obj.push(Start);
            
        }
        else if (Start.x+1 < size && arr[Start.x + 1][Start.y] == ' ' && Indexes_check[Start.x + 1][Start.y] == false)        // Down
        {
            Indexes_check[Start.x][Start.y] = true;
            Start.x = Start.x + 1;
            arr[Start.x][Start.y+1]=(char)176;
            obj.push(Start);
        }
        else if (Start.y-1 >= 0 && arr[Start.x][Start.y-1] == ' ' && Indexes_check[Start.x][Start.y-1] == false)       // Left
        {
            Indexes_check[Start.x][Start.y] = true;
            Start.y = Start.y - 1;
            obj.push(Start);
        }
        else if (Start.x-1 >= 0 && arr[Start.x - 1][Start.y] == ' ' && Indexes_check[Start.x - 1][Start.y] == false)        // Up
        {
            Indexes_check[Start.x][Start.y] = true;
            Start.x = Start.x - 1;
            arr[Start.x][Start.y+1]=(char)176;
            obj.push(Start);
        }
        else
        {
            Pos temp;
            obj.Top(temp);
            obj.pop();
            arr[temp.x][temp.y] = (char)178;
            obj.Top(temp);
            Start.x = temp.x;
            Start.y = temp.y;
        }
        if (obj.IsEmpty()) {
            flag = 1;
            break;
        }
        
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}
void PrintWithNumbers(char** arr, int** movement, int n) {
	int x = 0, y = 0;
	while (y != n) {
		x = 0;
		while (x != n) {
			cout << arr[x][y];
			x++;
		}
		x = 0;
		cout << "\t\t";
		while (x != n) {
			cout << movement[x][y];
			if (y != 0 && y != n - 1) {
				cout << "  ";
			}
			else {
				cout << " ";
			}

			x++;
		}
		y++;
		cout << endl;
	}
}
void Lee(char** arr, int** numbers, int n, Pos start, Pos End) {
	int dl[] = { -1, 0, 1, 0 };
	int dc[] = { 0, 1, 0, -1 };

	queue<int> X, Y;

	X.push(start.x);
	Y.push(start.y);
	bool check = 0;
	int x, y, xx, yy;
	while (!X.isEmpty() && !Y.isEmpty())
	{
		x = X.front();
		y = Y.front();
		for (int i = 0; i < 4; i++)
		{
			xx = x + dl[i];
			yy = y + dc[i];
			if (arr[yy][xx] != (char)219 && numbers[yy][xx] == 0&&arr[yy][xx]!=(char)4)
			{
				if (yy == End.y && xx == End.x) {
					cout << "FOUNDDDDDDD!\n";
					PrintWithNumbers(arr, numbers, n);
					check = 1;
				}
				if (check == 1) {
					int go = numbers[yy][xx];
					arr[y][x]=(char)178;
					yy=y;
					xx=x;
					while(numbers[yy][xx]!=0)
					{
						for(int a=0;a<4;a++){
							xx = x + dl[a];
							yy = y + dc[a];
							if(arr[yy][xx]==(char)4){
								goto end;
							}
							if(numbers[yy][xx]==numbers[y][x]-1){
								arr[yy][xx]=(char)178;
								y=yy;
								x=xx;
								break;
							}
							
						}
					}
					goto end;
				}
				X.push(xx);
				Y.push(yy);
				numbers[yy][xx] = numbers[y][x] + 1;
			}

		}
		X.pop();
		Y.pop();
	}
end:
	PrintWithNumbers(arr, numbers, n);

}
void MakeObstacle(char** arr, moves** Move, int n) {//totally random
	int temp = 0;
	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			temp = rand() % 5;
			Move[i][j].CanMove = 1;
			if (temp == 0) {
				arr[i][j] = (char)219;
				Move[i][j].CanMove = 0;
			}
		}
	}
}
void RatInMaze() {
	int n;
	cout << "Enter Dimension for maze : ";
	cin >> n;
	const int size = n;
	char** maze = new char* [n];
	int** numbers = new int* [n];
	moves** CanMove = new moves * [n];//1 for yes,0 for no

	for (int i = 0; i < n; i++) {
		maze[i] = new char[n]; numbers[i] = new int[n];
		for (int j = 0; j < n; j++) {
			maze[i][j] = (char)32;
		}
		CanMove[i] = new moves[n];
		maze[i][0] = (char)219;
		maze[i][n - 1] = (char)219; CanMove[i][n - 1].CanMove = 0;
		numbers[i][0] = numbers[i][n - 1] = -1;
		if (i == 0 || i == n - 1) {
			for (int j = 0; j < n; j++) {
				maze[i][j] = (char)219; CanMove[i][i].CanMove = 0;
				numbers[i][j] = -1;
			}
		}
		else {
			for (int j = 1; j < n - 1; j++) {
				maze[i][j] = (char)32; numbers[i][j] = 0;
			}
		}
	}

	MakeObstacle(maze, CanMove, size);
	Display(maze, n);
	Pos Rat;
	Pos target;
	cout << "Enter starting position of Rat : "; \
		cin >> Rat.x >> Rat.y;
	Rat.x = Rat.x % n;
	Rat.y = Rat.y % n;
	if (Rat.x == 0) {
		Rat.x++;
	}
	if (Rat.x == n - 1) {
		Rat.x--;
	}
	if (Rat.y == 0) {
		Rat.y++;
	}
	if (Rat.y == n - 1) {
		Rat.y--;
	}
	maze[Rat.y][Rat.x] = (char)4;
	CanMove[Rat.y][Rat.x].CanMove = 0;
	Pos copy;
	copy.x = Rat.x;
	copy.y = Rat.y;
	if (CanMove[copy.y][copy.x + 1].CanMove == 0 && CanMove[copy.y][copy.x - 1].CanMove == 0 && CanMove[copy.y + 1][copy.x].CanMove == 0 && CanMove[copy.y - 1][copy.x].CanMove == 0) {
		if (copy.x - 1 != 0) {
			maze[copy.y][copy.x - 1] = (char)0; CanMove[copy.y][copy.x - 1].CanMove = 1;
		}
		else if (copy.x + 1 != n - 1) {
			maze[copy.y][copy.x + 1] = (char)0; CanMove[copy.y][copy.x + 1].CanMove = 1;
		}
		else if (copy.y + 1 != n - 1) {
			maze[copy.y + 1][copy.x] = (char)0; CanMove[copy.y + 1][copy.x].CanMove = 1;
		}
		else if (copy.y - 1 != 0) {
			maze[copy.y - 1][copy.x] = (char)0; CanMove[copy.y - 1][copy.x].CanMove = 1;
		}
	}
	cout << "Enter Targte Position : ";
	cin >> target.x >> target.y;
	target.x = target.x % n;
	target.y = target.y % n;
	if (target.x == 0) {
		Rat.x++;
	}
	if (target.x == n - 1) {
		target.x--;
	}
	if (target.y == 0) {
		target.y++;
	}
	if (Rat.y == n - 1) {
		target.y--;
	}
	maze[target.y][target.x] = (char)229;
	Pos Tcopy;
	Tcopy.x = target.x;
	Tcopy.y = target.y;
	if (CanMove[Tcopy.y][Tcopy.x + 1].CanMove == 0 && CanMove[Tcopy.y][Tcopy.x - 1].CanMove == 0 && CanMove[Tcopy.y + 1][Tcopy.x].CanMove == 0 && CanMove[Tcopy.y - 1][Tcopy.x].CanMove == 0) {
		if (Tcopy.x - 1 != 0) {
			maze[Tcopy.y][Tcopy.x - 1] = (char)0; CanMove[Tcopy.y][Tcopy.x - 1].CanMove = 1;
		}
		else if (Tcopy.x + 1 != n - 1) {
			maze[Tcopy.y][Tcopy.x + 1] = (char)0; CanMove[Tcopy.y][Tcopy.x + 1].CanMove = 1;
		}
		else if (Tcopy.y + 1 != n - 1) {
			maze[Tcopy.y + 1][Tcopy.x] = (char)0; CanMove[Tcopy.y + 1][Tcopy.x].CanMove = 1;
		}
		else if (copy.y - 1 != 0) {
			maze[Tcopy.y - 1][Tcopy.x] = (char)0; CanMove[Tcopy.y - 1][Tcopy.x].CanMove = 1;
		}
	}
	int op;
retry:
	cout << "which method you want to adopt : \n1: BackTracking\n2:Lee's Algorithm\n INPUT CHOICE:";
	cin >> op;
	if (op == 1) {
		//bactracking
		BackTrack(maze, n, Rat, target, CanMove);
	}
	else if (op == 2) {
		//lee's algo
		Lee(maze, numbers, n, Rat, target);
	}
	else {
		cout << "WRONG INPUT ?(._.`)\n";
		goto retry;
	}
}

