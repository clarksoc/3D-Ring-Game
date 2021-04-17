#include "Ring.h";

using namespace std;

Donut::Donut() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->bAnswer = false;
	this->txtAnswer = "this is not a nut";
};

Donut::Donut(float x, float z, bool answer, bool draw , string txtAns, float y) {

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

const char *firstBank[50] = { "8 + 7", "13 + 9", "19 + 17", "100 + 110", "28 + 13"};
const char *firstBankAnswers[50] = { "15", "22", "36", "210", "41"};
const char *secondBank[50] = { "10 - 6", "18 - 9", "42 - 23", "100 - 90", "8 - 20"};
const char *secondBankAnswers[50] = { "4", "9", "19", "10", "-12"};
const char *thirdBank[50] = { "2 * 6", "5 * 12", "9 * 9", "13 * 15", "500 * 0"};
const char *thirdBankAnswers[50] = { "12", "60", "81", "195", "0"};
const char *fourthBank[50] = { "8 ÷ 4", "26 ÷ 2", "60 ÷ 6", "48 ÷ 12", "85 ÷ 17"};
const char *fourthBankAnswers[50] = { "2", "13", "10", "4", "5"};
const char *fifthBank[50] = { "6 + 8 * 2 - 4 ÷ 4", "50 ÷ 10 - 6 + 10 * 3", "(15 * 60 + 3 - 17 ÷ 32) * 0"};
const char *fifthBankAnswers[50] = { "21", "29", "0"};

int point = 5;
extern int score;
extern bool gameOver;

void makeDonuts(float cameraX, float cameraZ)
{
	srand(time(NULL)); 
	int i = 0;
	while(i != RING_COUNT) {
				
		// generates numbers from -47 to 47 keeping the rings within the -50/50 bounds
		int x = rand() % 94 - 47;
		int z = rand() % 94 - 47;

		ed = sqrt(pow(cameraX - x, 2) + pow(cameraZ - z, 2));

		if (!donutOnDonut(x, z) && (ed > 5)) {
			if (i == 0) {
				donuts[i] = Donut(x, z, true, true, "This is the answer");
			}
			else {
				donuts[i] = Donut(x, z, false, true, "This is the wrong answer");
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
		else return false;
	}
}

void hitDonut(float cameraX, float cameraZ) {
	for (int i = 0; i < RING_COUNT; i++) {
		ed = sqrt(pow(cameraX - donuts[i].x, 2) + pow(cameraZ - donuts[i].z, 2));
		if (ed <= 3.5) {
			if (donuts[i].bAnswer) {
				printf("add point\n");
				score += point;
				point = 5;
				makeDonuts(cameraX, cameraZ);
			}else {
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
		if(donuts[i].bDraw){
			glPushMatrix();

			glColor3f(1.0, 1.0, 0.0);
			glTranslatef(donuts[i].x, donuts[i].y, donuts[i].z);
			glRotatef(angle, 0.0f, 1.0f, 0.0f);
			glutSolidTorus(0.5f, 2.5f, 8, 32);
			glRasterPos3f(-0.05, 0, 0);

			glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)donuts[i].txtAnswer.c_str());
			glPopMatrix();
		}
	}
}
