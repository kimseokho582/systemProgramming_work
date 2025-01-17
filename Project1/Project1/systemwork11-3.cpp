#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class table {
private:
	string data;
	int num;
	int labelflag;
public:

	void table_set(string d, int n, int l) {
		data = d;
		num = n;
		labelflag = l;
	}
	void table_get() {	std::cout << data << endl;	}
	string getdata() { return data; }
	int getnum() { return num; }
	int getlabelflag() { return labelflag; }
	~table() {  }
};

class Data : public table {
public:
	table list[100];
	table label[100];
	int listindex = 0;
	int labelindex = 0;
	void regi(string d, int n, int l) {
		list[listindex].table_set(d, n, l);
		listindex++;
	}
	void print() {
		for (int i = 0; i < listindex; i++)
			std::cout << list[i].getdata() << "   " << list[i].getnum() << "   " << list[i].getlabelflag() << endl;
	}
	void labelregi(string d, int n, int l) {
		label[labelindex].table_set(d, n, l);
		labelindex++;
	}
};

int main() {
	Data D;

	char instr[8][8] = { "SEGMENT","ASSUME","MOV","ADD","SUB","CMP","JNE","INT" };
	char regi[21][3] = { "AX","BX","CX","DX","AH","AL","BH","BL","CH","CL","DH","DL","CS","IP","SP","BP","SS","SI","DI","DS","ES" };

	ifstream in;
	in.open("my.asm");
	table Table[100];;
	string tmp[200];
	char ttmp;
	int tmpi = 0;
	int i = 0;
	int index = 0;
	int flag = 1;
	while (!in.eof()) {
		ttmp = in.get();
		if (ttmp != '	' && ttmp != ' ' && ttmp != ':' && ttmp != '\n') {
			if (ttmp != ',') {
				tmp[tmpi] += ttmp;
			}
		}
		else {
			if (tmp[tmpi] != "\0") {
				D.regi(tmp[tmpi], index, flag);
				flag = 0;
			}
			index = i;
			tmpi++;
		}
		if (ttmp == '\n') {
			flag = 1;
		}
		if (ttmp == '	') {
			flag = 0;
		}
		if (ttmp != '\n' && ttmp != '	' && ttmp != ' ')
			i++;
	}
	in.close();

	ifstream in2;
	string data2;
	string mp[10];
	in2.open("my.asm");
	int y = 0;
	while (!in2.eof()) {

		getline(in2, data2);

		for (int i = 0; i < data2.length(); i++) {
			if (data2[0] != '	') {
				if (data2[i] != '	')
					mp[y] += data2[i];
				else {
					y++;
					break;
				}

			}
		}
	}

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < D.listindex; j++) {
			if (mp[i] == D.list[j].getdata() && D.list[j].getlabelflag() == 1) {
				D.labelregi(mp[i], D.list[j].getnum(), flag);
				break;
			}
		}
	}
	in2.close();

	ifstream in3;
	string data3;
	in3.open("my.asm");
	int tmpget = 0;
	int get = 0;
	string ff = "[";
	string ee = "]";
	while (!in3.eof()) {
		getline(in3, data3);
		for (int i = 0; i < y; i++) {
			int length =mp[i].length();
			string change;
			change = to_string(D.label[i].getnum());
			change += ee;
			change = ff + change;
			if (data3.find(mp[i]) != string::npos) {
				tmpget = data3.find(mp[i]);
				if (data3[tmpget + mp[i].length()] >= 65 && data3[tmpget + mp[i].length()] <= 90) {

				}
				else {
					if (data3[0] >= 65 && data3[0] <= 90) {

					}
					else {
						get = data3.find(mp[i]);
						data3.replace(data3.begin() + get, data3.begin() + get + length, change.begin(), change.end());
					}
				}

			}
		}
		cout << data3<<endl;
	}

}
