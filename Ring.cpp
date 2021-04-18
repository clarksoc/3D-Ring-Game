#include "Ring.h";

using namespace std;

Donut::Donut() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->bAnswer = false;
	this->txtAnswer = "this is not a nut";
};

Donut::Donut(float x, float z, bool answer, bool draw, string txtAns, float y) {

	this->x = x;
	this->y = y;
	this->z = z;
	this->bAnswer = answer;
	this->bDraw = draw;
	this->txtAnswer = txtAns;

}

float ed;

const int RING_COUNT = 5;

Donut donuts[RING_COUNT];

string question;


const char* firstBank[50] = { "8 + 7", "13 + 9", "19 + 17", "100 + 110", "28 + 13" };
const char* firstBankAnswers[50] = { "15", "22", "36", "210", "41" };
const char* firstBankWrongOne[50] = { "16", "17", "14", "13" };
const char* firstBankWrongTwo[50] = { "20", "21", "19", "25" };
const char* firstBankWrongThree[50] = { "34", "37", "32", "33" };
const char* firstBankWrongFour[50] = { "200", "205", "190", "220" };
const char* firstBankWrongFive[50] = { "40", "42", "44", "39" };

const char* secondBank[50] = { "10 - 6", "18 - 9", "42 - 23", "100 - 90", "8 - 20" };
const char* secondBankAnswers[50] = { "4", "9", "19", "10", "-12" };
const char* secondBankWrongOne[50] = { "2", "6", "5", "3" };
const char* secondBankWrongTwo[50] = { "10", "8", "11", "7" };
const char* secondBankWrongThree[50] = { "18", "17", "20", "21" };
const char* secondBankWrongFour[50] = { "9", "20", "30", "18" };
const char* secondBankWrongFive[50] = { "-10", "-8", "-16", "-14" };

const char* thirdBank[50] = { "2 * 6", "5 * 12", "9 * 9", "13 * 15", "500 * 0" };
const char* thirdBankAnswers[50] = { "12", "60", "81", "195", "0" };
const char* thirdBankWrongOne[50] = { "16", "13", "10", "8" };
const char* thirdBankWrongTwo[50] = { "65", "55", "70", "80" };
const char* thirdBankWrongThree[50] = { "72", "90", "83", "91" };
const char* thirdBankWrongFour[50] = { "200", "210", "225", "240" };
const char* thirdBankWrongFive[50] = { "50", "5000", "500", "1000" };

const char* fourthBank[50] = { "8 ÷ 4", "26 ÷ 2", "60 ÷ 6", "48 ÷ 12", "85 ÷ 17" };
const char* fourthBankAnswers[50] = { "2", "13", "10", "4", "5" };
const char* fourthBankWrongOne[50] = { "4", "1", "6", "0" };
const char* fourthBankWrongTwo[50] = { "12", "24", "14", "10" };
const char* fourthBankWrongThree[50] = { "6", "54", "20", "30" };
const char* fourthBankWrongFour[50] = { "6", "8", "2", "12" };
const char* fourthBankWrongFive[50] = { "8", "7", "68", "3" };

const char* fifthBank[50] = { "6 + 8 * 2 - 4 ÷ 4", "50 ÷ 10 - 6 + 10 * 3", "(15 * 60 + 3 - 17 ÷ 32) * 0", "5 * 5 - 2 + 18 ÷ 2", "2 - 6 ÷ 2 + 11 * 3" };
const char* fifthBankAnswers[50] = { "21", "29", "0", "32", "32" };
const char* fifthBankWrongOne[50] = { "22", "34", "6", "-7" };
const char* fifthBankWrongTwo[50] = { "27", "30", "18", "20" };
const char* fifthBankWrongThree[50] = { "90", "902", "102", "510" };
const char* fifthBankWrongFour[50] = { "20", "18", "40", "15" };
const char* fifthBankWrongFive[50] = { "39", "35", "28", "20" };

int point = 5;
int roundNum = 0;
extern int score;
extern bool gameOver;

void makeDonuts(float cameraX, float cameraZ)
{
	srand(time(NULL));
	int i = 0;

	int qNum = rand() % 5;
	string ans;
	string wrong1 = "";
	string wrong2 = "";
	string wrong3 = "";
	string wrong4 = "";


	switch (roundNum) {
	case 0:
		question = firstBank[qNum];
		ans = firstBankAnswers[qNum];
		switch (qNum) {
		case 0:
			wrong1 = firstBankWrongOne[0];
			wrong2 = firstBankWrongOne[1];
			wrong3 = firstBankWrongOne[2];
			wrong4 = firstBankWrongOne[3];
			break;
		case 1:
			wrong1 = firstBankWrongTwo[0];
			wrong2 = firstBankWrongTwo[1];
			wrong3 = firstBankWrongTwo[2];
			wrong4 = firstBankWrongTwo[3];
			break;
		case 2:
			wrong1 = firstBankWrongThree[0];
			wrong2 = firstBankWrongThree[1];
			wrong3 = firstBankWrongThree[2];
			wrong4 = firstBankWrongThree[3];
			break;
		case 3:
			wrong1 = firstBankWrongFour[0];
			wrong2 = firstBankWrongFour[1];
			wrong3 = firstBankWrongFour[2];
			wrong4 = firstBankWrongFour[3];
			break;
		case 4:
			wrong1 = firstBankWrongFive[0];
			wrong2 = firstBankWrongFive[1];
			wrong3 = firstBankWrongFive[2];
			wrong4 = firstBankWrongFive[3];
			break;
		}
		break;
	case 1:
		question = secondBank[qNum];
		ans = secondBankAnswers[qNum];
		switch (qNum) {
		case 0:
			wrong1 = secondBankWrongOne[0];
			wrong2 = secondBankWrongOne[1];
			wrong3 = secondBankWrongOne[2];
			wrong4 = secondBankWrongOne[3];
			break;
		case 1:
			wrong1 = secondBankWrongTwo[0];
			wrong2 = secondBankWrongTwo[1];
			wrong3 = secondBankWrongTwo[2];
			wrong4 = secondBankWrongTwo[3];
			break;
		case 2:
			wrong1 = secondBankWrongThree[0];
			wrong2 = secondBankWrongThree[1];
			wrong3 = secondBankWrongThree[2];
			wrong4 = secondBankWrongThree[3];
			break;
		case 3:
			wrong1 = secondBankWrongFour[0];
			wrong2 = secondBankWrongFour[1];
			wrong3 = secondBankWrongFour[2];
			wrong4 = secondBankWrongFour[3];
			break;
		case 4:
			wrong1 = secondBankWrongFive[0];
			wrong2 = secondBankWrongFive[1];
			wrong3 = secondBankWrongFive[2];
			wrong4 = secondBankWrongFive[3];
			break;
		}
		break;
	case 2:
		question = thirdBank[qNum];
		ans = thirdBankAnswers[qNum];
		switch (qNum) {
		case 0:
			wrong1 = thirdBankWrongOne[0];
			wrong2 = thirdBankWrongOne[1];
			wrong3 = thirdBankWrongOne[2];
			wrong4 = thirdBankWrongOne[3];
			break;
		case 1:
			wrong1 = thirdBankWrongTwo[0];
			wrong2 = thirdBankWrongTwo[1];
			wrong3 = thirdBankWrongTwo[2];
			wrong4 = thirdBankWrongTwo[3];
			break;
		case 2:
			wrong1 = thirdBankWrongThree[0];
			wrong2 = thirdBankWrongThree[1];
			wrong3 = thirdBankWrongThree[2];
			wrong4 = thirdBankWrongThree[3];
			break;
		case 3:
			wrong1 = thirdBankWrongFour[0];
			wrong2 = thirdBankWrongFour[1];
			wrong3 = thirdBankWrongFour[2];
			wrong4 = thirdBankWrongFour[3];
			break;
		case 4:
			wrong1 = thirdBankWrongFive[0];
			wrong2 = thirdBankWrongFive[1];
			wrong3 = thirdBankWrongFive[2];
			wrong4 = thirdBankWrongFive[3];
			break;
		}
		break;
	case 3:
		question = fourthBank[qNum];
		ans = fourthBankAnswers[qNum];
		switch (qNum) {
		case 0:
			wrong1 = fourthBankWrongOne[0];
			wrong2 = fourthBankWrongOne[1];
			wrong3 = fourthBankWrongOne[2];
			wrong4 = fourthBankWrongOne[3];
			break;
		case 1:
			wrong1 = fourthBankWrongTwo[0];
			wrong2 = fourthBankWrongTwo[1];
			wrong3 = fourthBankWrongTwo[2];
			wrong4 = fourthBankWrongTwo[3];
			break;
		case 2:
			wrong1 = fourthBankWrongThree[0];
			wrong2 = fourthBankWrongThree[1];
			wrong3 = fourthBankWrongThree[2];
			wrong4 = fourthBankWrongThree[3];
			break;
		case 3:
			wrong1 = fourthBankWrongFour[0];
			wrong2 = fourthBankWrongFour[1];
			wrong3 = fourthBankWrongFour[2];
			wrong4 = fourthBankWrongFour[3];
			break;
		case 4:
			wrong1 = fourthBankWrongFive[0];
			wrong2 = fourthBankWrongFive[1];
			wrong3 = fourthBankWrongFive[2];
			wrong4 = fourthBankWrongFive[3];
			break;
		}
		break;
	case 4:
		question = fifthBank[qNum];
		ans = fifthBankAnswers[qNum];
		switch (qNum) {
		case 0:
			wrong1 = fifthBankWrongOne[0];
			wrong2 = fifthBankWrongOne[1];
			wrong3 = fifthBankWrongOne[2];
			wrong4 = fifthBankWrongOne[3];
			break;
		case 1:
			wrong1 = fifthBankWrongTwo[0];
			wrong2 = fifthBankWrongTwo[1];
			wrong3 = fifthBankWrongTwo[2];
			wrong4 = fifthBankWrongTwo[3];
			break;
		case 2:
			wrong1 = fifthBankWrongThree[0];
			wrong2 = fifthBankWrongThree[1];
			wrong3 = fifthBankWrongThree[2];
			wrong4 = fifthBankWrongThree[3];
			break;
		case 3:
			wrong1 = fifthBankWrongFour[0];
			wrong2 = fifthBankWrongFour[1];
			wrong3 = fifthBankWrongFour[2];
			wrong4 = fifthBankWrongFour[3];
			break;
		case 4:
			wrong1 = fifthBankWrongFive[0];
			wrong2 = fifthBankWrongFive[1];
			wrong3 = fifthBankWrongFive[2];
			wrong4 = fifthBankWrongFive[3];
			break;
		}
		break;
	}

	while (i != RING_COUNT) {

		// generates numbers from -47 to 47 keeping the rings within the -50/50 bounds
		int x = rand() % 94 - 47;
		int z = rand() % 94 - 47;

		ed = sqrt(pow(cameraX - x, 2) + pow(cameraZ - z, 2));

		if (!donutOnDonut(x, z) && (ed > 5)) {
			if (i == 0) {
				donuts[i] = Donut(x, z, true, true, ans);
			}
			else {
				switch (i - 1) {
				case 0:
					donuts[i] = Donut(x, z, false, true, wrong1);
					break;
				case 1:
					donuts[i] = Donut(x, z, false, true, wrong2);
					break;
				case 2:
					donuts[i] = Donut(x, z, false, true, wrong3);
					break;
				case 3:
					donuts[i] = Donut(x, z, false, true, wrong4);
					break;
				}

			}
			i++;
		}
	}
}

bool donutOnDonut(int x, int z) {
	for (int i = 0; i < RING_COUNT; i++) {
		ed = sqrt(pow(x - donuts[i].x, 2) + pow(z - donuts[i].z, 2));

		if (ed <= 10) {
			return true;
		}
	}
	return false;
}

void hitDonut(float cameraX, float cameraZ) {
	for (int i = 0; i < RING_COUNT; i++) {
		ed = sqrt(pow(cameraX - donuts[i].x, 2) + pow(cameraZ - donuts[i].z, 2));
		if (ed <= 3.5) {
			if (donuts[i].bAnswer) {
				printf("add point\n");
				score += point;
				point = 5;
				roundNum++;
				if (roundNum == 5) {
					gameOver = true;
					roundNum = 0;
				}
				else
				{
					makeDonuts(cameraX, cameraZ);
				}
			}
			else {
				donuts[i].bDraw = false;
				donuts[i].x = 100.0f;
				donuts[i].z = 100.0f;
				point -= 1;
				printf("remove point\n");
			}
		}
	}
}

void drawDonuts() {

	for (int i = 0; i < RING_COUNT; i++) {
		if (donuts[i].bDraw) {
			glPushMatrix();

			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(donuts[i].x, donuts[i].y, donuts[i].z);
			glRotatef(angle, 0.0f, 1.0f, 0.0f);
			glutSolidTorus(0.5f, 2.5f, 8, 32);
			glRasterPos3f(0, 0, 0);

			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)donuts[i].txtAnswer.c_str());
			glPopMatrix();
		}
	}
}