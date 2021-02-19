#include <iostream>

void InitializeStatus();
void ShowGrid();
int PutStone(int);
int JudgePuttable(int, int);
void ReverseStone(int, int, int);
void JudgeGame();

const int GridNum = 8;
int Status[GridNum][GridNum];
int player_flag;

void InitializeStatus(void) {
	for (int i = 0; i < GridNum; i++) {
		for (int j = 0; j < GridNum; j++) {
			Status[i][j] = 0;
		}
	}
	Status[GridNum / 2][GridNum / 2 - 1] = 1;
	Status[GridNum / 2 - 1][GridNum / 2] = 1;
	Status[GridNum / 2][GridNum / 2] = -1;
	Status[GridNum / 2 - 1][GridNum / 2 - 1] = -1;
	return;
}

void ShowGrid(void) {
	for (int i = 0; i < GridNum; i++) {
		std::cout << " ---------------------------------\n";
		for (int j = 0; j < GridNum; j++) {
			if (Status[i][j] == 1) { std::cout << " | @"; }
			else if (Status[i][j] == -1) { std::cout << " | 0"; }
			else if (JudgePuttable(i * GridNum + j, player_flag) > 1) { std::cout << " |" << i + 1 << j + 1; }
			else { std::cout << " |  "; }
		}
		std::cout << " |\n";
	}
	std::cout << " ---------------------------------\n\n";
	return;
}

int JudgePuttable(int id, int flag) {
	int res = 1;
	int row = (id - id % GridNum) / GridNum;
	int col = id % GridNum;
	if (Status[row][col] != 0) { return 0; }
	int m;
    //up
	m = 1;
	while (row + m < GridNum -1 && Status[row + m][col] == flag * -1) {
		m++;
		if (Status[row + m][col] == flag) {
			res *= 2;
			break;
		}
	}
    //down
	m = 1;
	while (row - m > 0 && Status[row - m][col] == flag * -1) {
		m++;
		if (Status[row - m][col] == flag) {
			res *= 3;
			break;
		}
	}
	//right
	m = 1;
	while (col + m < GridNum -1 && Status[row][col + m] == flag * -1) {
		m++;
		if (Status[row][col + m] == flag) {
			res *= 5;
			break;
		}
	}
	//left
	m = 1;
	while (col - m > 0 && Status[row][col - m] == flag * -1) {
		m++;
		if (Status[row][col - m] == flag) {
			res *= 7;
			break;
		}
	}
	
	//up-right
	m = 1;
	while (col + m < GridNum -1 && row + m < GridNum -1 && Status[row + m][col + m] == flag * -1) {
		m++;
		if (Status[row + m][col + m] == flag) {
			res *= 11;
			break;
		}
	}
	//down-right
	m = 1;
	while (col + m < GridNum -1 && row - m > 0 && Status[row - m][col + m] == flag * -1) {
		m++;
		if (Status[row - m][col + m] == flag) {
			res *= 13;
			break;
		}
	}
	//up-left
	m = 1;
	while (col - m > 0 && row + m < GridNum -1 && Status[row + m][col - m] == flag * -1) {
		m++;
		if (Status[row + m][col - m] == flag) {
			res *= 17;
			break;
		}
	}
    //down-left
	m = 1;
	while (col - m > 0 && row - m > 0 && Status[row - m][col - m] == flag * -1) {
		m++;
		if (Status[row - m][col - m] == flag) {
			res *= 19;
			break;
		}
	}
	return res;
}

int PutStone(int flag) {
	std::cout<<":::::::::::::::::::::::::::::::::::::::::::::\n\n";
	int pass = 0;
	int fp = 0;
	int fn = 0;
	int fz = 0;
	for (int i = 0; i < GridNum; i++) {
		for (int j = 0; j < GridNum; j++) {
			int f = JudgePuttable(i * GridNum + j, flag);
			if (Status[i][j] == 1) { fp++; }
			if (Status[i][j] == -1) { fn++; }
			if (Status[i][j] == 0) { fz++; }
			if (f > pass) { pass = f; }
		}
	}
	if (fp * fn * fz == 0) { return -2; }
	if (pass < 2) {
		std::cout << "Pass !!!\n\n";
		return -1;
	}

	int id;
	while (true) {
		if (flag == 1) { std::cout << "Player @     Choose move :"; }
		if (flag == -1) { std::cout << "Player 0     Choose move :"; }
		std::cin >> id;
		id = ((id - id % 10) / 10 - 1) * GridNum + (id % 10 - 1);
		if (JudgePuttable(id, flag) > 1) { break; }
		std::cout << "Disable !\n\n";
	}
	return id;
}

void ReverseStone(int id, int flag, int judge) {
	std::cout << judge << std::endl;
	int row = (id - id % GridNum) / GridNum;
	int col = id % GridNum;
	int m;

	if (judge % 2 == 0) {//up
		m = 0;
		while (true) {
			Status[row + m][col] = flag;
			m++;
			if (row + m == GridNum || Status[row + m][col] == flag) {
				break;
			}
		}
	}
	if (judge % 3 == 0) {//down
		m = 0;
		while (true) {
			Status[row - m][col] = flag;
			m++;
			if (row - m == -1 || Status[row - m][col] == flag) {
				break;
			}
		}
	}
	if (judge % 5 == 0) {//right
		m = 0;
		while (true) {
			Status[row][col + m] = flag;
			m++;
			if (col + m == GridNum || Status[row][col + m] == flag) {
				break;
			}
		}
	}
	if (judge % 7 == 0) {//left
		m = 0;
		while (true) {
			Status[row][col - m] = flag;
			m++;
			if (col - m == -1 || Status[row][col - m] == flag) {
				break;
			}
		}
	}
	if (judge % 11 == 0) {//up-right
		m = 0;
		while (true) {
			Status[row + m][col + m] = flag;
			m++;
			if (row + m == GridNum || col + m == GridNum || Status[row + m][col + m] == flag) {
				break;
			}
		}
	}
	if (judge % 13 == 0) {//down-right
		m = 0;
		while (true) {
			Status[row - m][col + m] = flag;
			m++;
			if (row - m == -1 || col + m == GridNum || Status[row - m][col + m] == flag) {
				break;
			}
		}
	}
	if (judge % 17 == 0) {//up-left
		m = 0;
		while (true) {
			Status[row + m][col - m] = flag;
			m++;
			if (row + m == GridNum || col - m == -1 || Status[row + m][col - m] == flag) {
				break;
			}
		}
	}
	if (judge % 19 == 0) {//down-left
		m = 0;
		while (true) {
			Status[row - m][col - m] = flag;
			m++;
			if (row - m == -1 || col - m == -1 || Status[row - m][col - m] == flag) {
				break;
			}
		}
	}
	return;
}

void JudgeGame() {
	int val = 0;
	for (int i = 0; i < GridNum; i++) {
		for (int j = 0; j < GridNum; j++) {
			val += Status[i][j];
		}
	}

	std::cout << "_/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/\n\n";
	if (val > 0) {
		std::cout << "_/ _/ _/ _/    Player @ WIN !!!!!!    _/ _/ _/ _/\n\n";
	}
	else if (val < 0) {
		std::cout << "_/ _/ _/ _/    Player 0 WIN !!!!!!    _/ _/ _/ _/\n\n";
	}
	else {
		std::cout << "_/ _/ _/ _/       Draw !!!!!!!!       _/ _/ _/ _/\n\n";
	}
	std::cout << "_/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/ _/\n\n";

	return;
}