#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class table {
private:
	string data;
	int num;
public:

	void table_set(string d, int n) {
		data = d;
		num = n;
	}
	void table_get() {
		cout << data << endl;
		
	}
	~table() {  }
};


int main() {


	char instr[8][8] = { "SEGMENT","ASSUME","MOV","ADD","SUB","CMP","JNE","INT" };
	char regi[21][3] = { "AX","BX","CX","DX","AH","AL","BH","BL","CH","CL","DH","DL","CS","IP","SP","BP","SS","SI","DI","DS","ES" };
	
	ifstream in;
	in.open("my.asm");
	table Table[100];;
	string tmp[200];
	char ttmp;
	int tmpi = 0;
	int i = 0;

	while (!in.eof()) {
		ttmp = in.get();
		if (ttmp != '	') {
			tmp[tmpi] += ttmp;
		}
		else {
			tmpi++;
		}
		i++;
	}
	for (int j = 0; j < tmpi; j++) {
		cout << tmp[j] << endl;
	}
	/*char div[] = { '	',' ',':' };
	int ff = 0;

		getline(in, tmp);
		cout << tmp << endl;
		for (int j = 0; j < 3; j++) {
			int get = tmp.find(div[j]);
			while (get != string::npos) {
				if (tmp.find(div[j]) != string::npos) {
					cout << get << " ";
					get = tmp.find(div[j], get + 1);
				}
			}cout << endl;
		}*/
}