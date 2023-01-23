#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning (disable: 4996)

#define H_MAX  200
#define W_MAX  200
const char emptycell = ' ';
const char livingcell = 'M';


void delay(float number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}
void show_state(char matrix[W_MAX][H_MAX], int witdh, int height, int gen) {
	printf("Generation %d\n", gen);
	for (int row = 1; row < height + 1; row++) {
		for (int col = 1; col < witdh + 1; col++) {
			printf("%c ", matrix[col][row]);
		}
		printf("\n");
	}
}
void reset_to_value(char matrix[W_MAX][H_MAX], int width, int height, char value) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			matrix[col][row] = value;
		}
	}
}
void reset_to_x(char matrix[W_MAX][H_MAX], int width, int height) {
	int length = smallerfrom(width, height);
	for (int i = 1; i < length + 1; i++) {
		matrix[i][i] = livingcell;
		matrix[i][length - i + 1] = livingcell;
	}
	//matrix[width / 2][height - 1] = livingcell;

}
int smallerfrom(int a, int b) {
	if (a < b) {
		return a;
	}
	return b;
}
int get_number_neighbour(char matrix[W_MAX][H_MAX], int width, int height, int x, int y) {
	int num_neighbours = 0;

	if (matrix[x - 1][y - 1] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x][y - 1] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x - 1][y] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x + 1][y - 1] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x + 1][y + 1] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x - 1][y + 1] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x][y + 1] == livingcell) {
		num_neighbours++;
	}
	if (matrix[x + 1][y] == livingcell) {
		num_neighbours++;
	}


	return num_neighbours;
}
void update_state(char matrix_old[W_MAX][H_MAX], char matrix_new[W_MAX][H_MAX], int width, int height) {
	for (int row = 1; row < width + 1; row++) {
		for (int col = 1; col < height + 1; col++) {
			char new_cell_state;
			char old_cell_state = matrix_old[col][row];

			int number_neighbours = get_number_neighbour(matrix_old, width, height, row, col);

			if (old_cell_state == emptycell) {
				if (number_neighbours == 3) {
					new_cell_state = livingcell;
				}
				else {
					new_cell_state = emptycell;
				}
			}
			else {
				if (number_neighbours == 2 || number_neighbours == 3) {
					new_cell_state = livingcell;
				}
				else {
					new_cell_state = emptycell;
				}
			}
			matrix_new[row][col] = new_cell_state;
		}
	}
}
void switch_state(char** p_state_a, char** p_state_b) {
	char* temp;
	temp = *p_state_a;
	*p_state_a = *p_state_b;
	*p_state_b = temp;
}
#pragma region USER INPUT
int* numberwrite() {
	int write; 
	scanf("%d", &write);
	while (getchar() != '\n');
	return write;
}
char charwrite() {
	int write;
	scanf("%c", &write);
	while (getchar() != '\n');
	return write;
}
float floatwrite() {
	int write;
	scanf("%f", &write);
	while (getchar() != '\n');
	return write;
}
void user_input_2(int* p_width, int* p_height, int* p_gen_num, int* p_answer) {
	while (1)
	{
		/*printf("%d", *p_width);*/
		system("cls");
		printf("define width (recommend 30):\t");
		*p_width = numberwrite();
		if (*p_width < 1 || *p_width>200)
			continue;
		printf("define height (recommend 30):\t");
		*p_height = numberwrite();
		if (*p_height < 1 || *p_height>200)
			continue;
		printf("define number of generations:\t");
		*p_gen_num = numberwrite();
		if (*p_gen_num < 1 || *p_gen_num > 1000)
			continue;
		printf("given values:\n width: %d\t height: %d\t num. of gen.: %d\n", *p_width, *p_height, *p_gen_num);
		printf("dynamic animation ('1') step by step ('2')");
		*p_answer = numberwrite();
		if (*p_answer < 0 || *p_answer > 3)
			continue;
		else
			break;
	}

}
void user_input_1(int* p_gen_num, int* p_answer) {
	
	
	while (1)
	{
		printf("define number of generations:\t");
		*p_gen_num = numberwrite();
		if (*p_gen_num < 1 || *p_gen_num>1000)
			continue;
		printf("given values:\n num. of gen.: %d\n", *p_gen_num);
		printf("dynamic animation ('1') step by step ('2')\t");
		*p_answer = numberwrite();
		if (*p_answer < 0 || *p_answer > 3)
			continue;
		else
			break;
	}
}
void user_input_3(int* p_width, int* p_height, int* p_gen_num, int* p_answer, int* p_percentage) {
	
	while (1)
	{
		printf("define width (recommend 30):\t");
		*p_width = numberwrite();
		if (*p_width < 1 || *p_width>200)
			continue;
		printf("define height (recommend 30):\t");
		*p_height = numberwrite();
		if (*p_height < 1 || *p_height>200)
			continue;
		printf("define number of generations:\t");
		*p_gen_num = numberwrite();
		if (*p_gen_num < 1 || *p_gen_num>1000)
			continue;
		printf("define percentage of living cells:\t");
		*p_percentage = numberwrite();
		if (*p_percentage < 0 || *p_percentage > 100)
			continue;
		printf("given values:\n percentage of living cells: %d %%\t width: %d pixels\t height: %d pixels \t num. of gen.: %d\n", *p_percentage, *p_width, *p_height, *p_gen_num);
		printf("dynamic animation ('1') step by step ('2')\t");
		*p_answer = numberwrite();
		if (*p_answer < 0 || *p_answer > 3)
			continue;
		else
			break;
	}
}
#pragma endregion 
void read_to_matrix(char matrix[W_MAX][H_MAX], FILE* fp, int* p_height, int* p_width) {
	int x = 1, y = 1, max_x = 0, y_max_x = 0, max_y = 0;
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf(" %d ", c);
		if (c != -1) {
			if (c == 10) { // new line 
				if (x > max_x) {
					max_x = x;
					y_max_x = y;
				}
				printf("%d,%d", max_x, y_max_x);
				y++;
				x = 0;
				printf("\n");
			}
			else { // new column 
				if (c == 88) {
					matrix[x][y] = livingcell; //hier stand ehemals c 
				}
				x++;
			}
		}
	}
	if (x > max_x) {
		max_x = x;
	}
	max_x--;
	max_y = y;
	*p_width = max_x;
	*p_height = max_y;
}
void mainloop(char old_state[W_MAX][H_MAX], char new_state[W_MAX][H_MAX], int gen_num, int width, int height, int answer) {
	for (int gen = 0; gen < gen_num; gen++) {
		update_state(old_state, new_state, width, height);
		if (answer == 1) {
			delay(0.1);
		}
		else {
			int blank;
			scanf("%d", &blank);
		}
		//system("cls");
		show_state(new_state, width, height, gen + 1);
		switch_state(&new_state, &old_state);
	}
}

int main() {
	system("chcp 1252 > NIL");
	// initialise memory and variables 

	char matrix_a[W_MAX][H_MAX];
	char matrix_b[W_MAX][H_MAX];

	// define pointers for states
	char* old_state = matrix_a;
	char* new_state = matrix_b;

	int width = 31, height = 31, gen_num = 0, answer = 0, file_or_layout = 0, percentage_value = 0;
	int percentage = 0;
	time_t t;
	
	do {
		system("cls");
		printf("Read from File? '1' or Create by Layout? '2' or Create by Random? '3'\t");
		file_or_layout = numberwrite();
		if (file_or_layout == 1) {
			//ask for values
			user_input_1(&gen_num, &answer);
			//intitialise initial state 
			reset_to_value(old_state, W_MAX, H_MAX, emptycell);
			FILE* fp;
			char Dateiname[100] = "C:\\Users\\nicor\\source\\repos\\Belegarbeit\\Belegarbeit\\Matrix_A.txt";
			if ((fp = fopen(Dateiname, "r")) == NULL) {
				printf("Fehler beim Oeffnen von %s \n", Dateiname);
				return;
			}
			else {
				printf("Die Datei %s geoeffnet.\n", Dateiname);
			}
			read_to_matrix(matrix_a, fp, &height, &width);
			//char* old_state = matrix_a;
			printf("\n");
			fclose(fp);

			show_state(old_state, width, height, 0);

			// main loop 
			mainloop(old_state, new_state, width, gen_num, height, answer);
			break;
		}
		if (file_or_layout == 2) {
			user_input_2(&width, &height, &gen_num, &answer);
			// debug
			//printf("%d	%d	%d	%d", width, height, gen_num, answer);
			// initialise initial state 
			reset_to_value(old_state, W_MAX, H_MAX, emptycell);
			reset_to_x(old_state, width, height);
			show_state(old_state, width, height, 0);

			// main loop 
			mainloop(old_state, new_state, width, gen_num, height, answer);
			break;
		}
		if (file_or_layout == 3) {
			//ask for values
			user_input_3(&width, &height, &gen_num, &answer, &percentage);

			//intitialise initial state 
			reset_to_value(old_state, W_MAX, H_MAX, emptycell);

			//random number generation
			//set_random_state();
			// Vorlage: void reset_to_x(char matrix[W_MAX][H_MAX], int width, int height) {
			srand((unsigned)time(&t));
			//percentage calculing
			percentage_value = (height * width * percentage) / 100;
			int i = 0;
			int* random_row = 0, random_col = 0;
			for (i; i < percentage_value; i++) {
				while (1){
					random_row = (rand() % width) + 1;
					random_col = (rand() % height) + 1;
					if (old_state[random_col][random_row] == livingcell)
						continue;
					else 
						break;
				}
				old_state[random_col][random_row] = livingcell;
			}


			show_state(old_state, width, height, 0);

			// main loop 
			mainloop(old_state, new_state, width, gen_num, height, answer);
			break;
		}
		else
			printf("Fehler"); continue;
	} while (1);
	
}
	// to do was ich noch weiß
	// done	Sachen die im Main Loop überflüßig sind extrahieren
	// DAU Sicherheit mit While Schleifen, glaub ich, einrichten
	// Dateien mit anderen Layouts vorbereiten und implementieren, mind. 3
	// über Editor nachdenken:
	// - muss den Cursor mit einbauen (mit x und y von Cursor)
	// - Cursor muss 2 Zustände haben hovert über lebende oder tote Zelle 
	// - es muss einen Textmodus geben den man aktiviert, danach speicher auf einer Datei
	// - Tastaturinput ohne enter herausfinden 
	// GIT EINRICHTEN 
	// Programmier Aufgaben schonmal vorbereitend anfangen 
