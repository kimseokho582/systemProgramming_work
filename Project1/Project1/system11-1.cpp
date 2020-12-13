#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	char instr[11][9] = { "SEGMENT","SEGMENTS","ASSUME","MOV","ADD","SUB","CMP","JNE","INT" ,"DW","DL" };
	char regi[21][3] = { "AX","BX","CX","DX","AH","AL","BH","BL","CH","CL","DH","DL","CS","IP","SP","BP","SS","SI","DI","DS","ES" };
	ifstream in;
	ifstream in2;
	string again;
	char tmp;
	char data[1000] = "";
	int dataNum[1000];
	fill_n(dataNum, 1000, -1);
	in.open("my.asm");

	int i = 0;
	int j = 0;
	int count = 0;
	while (!in.eof()) {

		tmp = in.get();
		data[i] = tmp;
		if (tmp != '	'&&tmp!='\n'&&tmp!=' ') {
			dataNum[i] = count;
		}
		else {
			count--;
		}
		if (tmp == ':')
			dataNum[i] = -1;
		count++;
		i++;
	}

	for (j = 0; j < i; j++) {

		//cout << dataNum[j] << " ";


	}
	in.close();


	in2.open("my.asm");
	int g = 0;
	while (!in2.eof()) {
		getline(in2, again);
		cout << again<<endl;
		for (g;g<j &&data[g] != '\n'; g++) {
			if (dataNum[g]==0||dataNum[g - 1]== - 1) {
				if (dataNum[g] != -1) {
					cout << dataNum[g] << "	";
				}
			}
		}g++;
		cout << endl;
	}

}
