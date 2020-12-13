#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
struct reg
{
	char reg_name[3];
	char reg_num[4];
} Reg[20];     // 레지스터에 대한 이름과 번호를 저장하는 구조체
struct ins
{
	char instruct[6];
	char dest[2];
	char sour[2];
	char word_type[2];
	char ins_code[3];
	char ins_len[2];
	char mod_reg[9];
} Instr[100];     // 각 인스트럭션의 정보를 보관하는 구조체

int MaxI;

struct symbol_tbl
{
	char symbol[10];
	char word_type[2];
	int lc;
	char data[10];
} Symbol[20];     // 심볼 테이블

int MaxS;

struct sentence
{
	char label[10];
	char _operator[10];
	char operand[3][10];
} Sen;

int LC;

// 화일에서 레지스터와 인스트럭션의 정보를 읽는다
void Initialize()
{
	int i = 0, j = 1;
	FILE* regi, * inst;
	regi = fopen("reg_tbl.txt", "r"); // 레지스터 테이블 읽음 
	inst = fopen("inst_tbl.txt", "r"); // 명령어 테이블 읽음

	while (!feof(regi)) // 레지스터 테이블 끝까지 읽음 feof는 마지막에 true값을 리턴함 즉, 마지막에 true리턴받으면 false가 되서 멈추는거임
	{
		fscanf(regi, "%s%s\n", Reg[i].reg_name, Reg[i].reg_num); //  이름과 번호로 나눠서 저장
		i++;
	}     // 레지스터 테이블을 작성한다
	while (!feof(inst))
	{
		fscanf(inst, "%6s%2s%2s%4s%3s%2s%9s\n", Instr[j].instruct, // 이름 , 목표 , 출발점, 8바이트인지 4바인트인지, ins_code ===> 값을 직접 쓰는건데 1바이트 값이 들어감, 코드길이(이거 중요함), r/m
			Instr[j].dest, Instr[j].sour,
			Instr[j].word_type, Instr[j].ins_code,
			Instr[j].ins_len, Instr[j].mod_reg);
		j++;
	}     // 명령어 테이블을 작성한다.
	MaxI = j - 1; // 명령어 테이블 크기 저장
	fclose(regi);
	fclose(inst);
}
int Analyze(char* operand)
{
	int i = 0;
	const char* regist[] = { "AX","BX","CX","DX","AL","BL","CL","DL","AH","BH","CH","DH",0x00 };     // 레지스터의 이름을 저장

	if (isdigit(operand[0])) return 0;      // immediate 어드레스 모드를 지정
	else
		while (regist[i] != 0x00)
			if (!strcmp(operand, regist[i]))
			{
				if (i < 4) return 1;
				else return 2;
			}
			else i++;
	return 3;
}
#define MAX_INS 1     // 명령어의 최대 개수를 지정
int Add_Chk(char* sen)     // 오퍼랜드의 어드레스 모드를 판정
{
	register int k = MaxI; //명령어 테이블에 작성된 테이블 개수
	int i = 0, j = 0, l = 0, wp = 0;
	char op[5][10];
	const char *opcode[] = { "mov","" };
	
	while (sen[wp] != '\n') // MOV AX, BX가 넘어왔다 치면 한글자씩 끈어서 개행( 끝문자)면 그만
	{
		while (sen[wp] == ' ' || sen[wp] == '\t' || sen[wp] == ',') wp++;     // 공백, 탭, 콤마는 통과

		while (sen[wp] != ' ' && sen[wp] != '\t' && sen[wp] != '\n' && sen[wp] != ',')
		{
			*(op[j] + i) = sen[wp]; // 한글자씩 넣는중
			//printf("[%c]이거 뭐지?  [%d]  ", sen[wp],wp);
			
			i++;
			wp++;
		}
		*(op[j] + i) = '\0'; //마지막칸에 null넣음 op[i]에 단어씩 끊어서 들어감 예를 들면 op[0]=MOV	 op[1]=AL
		i = 0;
		j++;
	}
	i = 0;

	//printf("[%s]", opcode[1]);
	while (strcmp(opcode[i], "")) { //strcmp는 같으면 0리턴 즉 같으면 멈춤,  i=0일때 mov임 안멈춤,  즉 레이블이 아닌거임
		if (stricmp(opcode[i], op[0])) { //처음 들어왔을때 opcode[i]=mov고 op[0]=mov임 같음 같으면 0이라서 이거 안돌아감 sum같은게 들어와야함
			i++; // 이게 되려면 명령어가 아니고 레이블인거임 SUM같은 MOV는 else로감
		}
		else
		{
			strcpy(Sen._operator, op[0]); //MOV면? Sen._operator에 넣음 근데 기존 코드에서는 mov만 들어감
			//printf("Sen._operator: [%s], op[0]: [%s] \n", Sen._operator, op[0]);
			for (l = 1; l < j; l++) { 
				strcpy(Sen.operand[l - 1], op[l]); 
				//printf("Sen.operand[%d]: [%s], op[l]: [%s]\n",l-1, Sen.operand[l - 1],op[l]);
			}
			break;
		}
	}
	if (i == MAX_INS)
	{
		strcpy(Sen.label, op[0]);
		strcpy(Sen._operator, op[1]);

		for (l = 2; l < j; l++) strcpy(Sen.operand[l - 2], op[1]);
	}     // 한 문장을 분석하여 레이블, 오퍼레이터와 오퍼랜드로 분류한다
	strcpy(Instr[0].instruct, op[0]);     // OP코드를 저장, bug????

	switch (Analyze(op[1]))
	{
	case 0: strcpy(Instr[0].dest, "i");
		break;
	case 1: strcpy(Instr[0].dest, "r");
		strcpy(Instr[0].word_type, "w");
		break;
	case 2: strcpy(Instr[0].dest, "r");
		strcpy(Instr[0].word_type, "b");
		break;
	case 3: strcpy(Instr[0].dest, "m");
		break;
	}
	switch (Analyze(op[2]))
	{
	case 0: strcpy(Instr[0].sour, "i");
		break;
	case 1: strcpy(Instr[0].sour, "r");
		strcpy(Instr[0].word_type, "w");
		break;
	case 2: strcpy(Instr[0].sour, "r");
		strcpy(Instr[0].word_type, "b");
		break;
	case 3: strcpy(Instr[0].sour, "m");
		break;
	}

	while (stricmp(Instr[k].instruct, Instr[0].instruct)
		|| strcmp(Instr[k].dest, Instr[0].dest)
		|| strcmp(Instr[k].sour, Instr[0].sour)
		|| strcmp(Instr[k].word_type, Instr[0].word_type))
	{
		k--;

	}
	strcpy(Instr[0].mod_reg, Instr[k].mod_reg);
	return k; // k == 0 : symbol
}
void PassI(char* buf)
{
	int i;
	static int j = 0;
	i = Add_Chk(buf);

	if (i)
	{
		printf("%04X: %s", LC, buf);
		LC += atoi(Instr[i].ins_len);
	}
	else
	{
		if (!stricmp(Sen._operator, "dw"))
			strcpy(Symbol[j].word_type, "w");
		else if (!stricmp(Sen._operator, "db"))
			strcpy(Symbol[j].word_type, "b");
		strcpy(Symbol[j].symbol, Sen.label);
		strcpy(Symbol[j].data, Sen.operand[0]);
		Symbol[j].lc = LC;
		printf("%04X: %s", LC, buf);
		if (*Symbol[j].word_type == 'w')   LC += 2;
		else if (*Symbol[j].word_type == 'b') LC += 1;
		j++;
	}
}
int btoi(char* dig)
{
	register int i = 0, ret = 0;
	while (*(dig + i) != '\0')
	{
		if (*(dig + i) == '1') ret += pow((double)2, (double)strlen(dig + i) - 1);
		i++;
	}
	return ret;
}
void PassII(char* buf)
{
	int i, j = 0, k = 0;

	i = Add_Chk(buf);

	if (i)
	{
		printf("%04x: %3s", LC, Instr[i].ins_code);
		if (!strcmp(Instr[i].dest, "r"))
		{
			while (stricmp(Reg[j].reg_name, Sen.operand[0]))
				j++;
			strncpy(strchr(Instr[0].mod_reg, '?'), Reg[j].reg_num, 3);
		}
		j = 0;
		if (!strcmp(Instr[i].sour, "r"))
		{
			while (stricmp(Reg[j].reg_name, Sen.operand[1]))
				j++;
			strncpy(strchr(Instr[0].mod_reg, '?'), Reg[j].reg_num, 3);
		}
		if (strcmp(Instr[i].dest, "m") && strcmp(Instr[i].sour, "m"))
			printf("%02X %s", btoi(Instr[0].mod_reg), buf);
		else
		{
			if (!strcmp(Instr[i].dest, "m"))
				while (strcmp(Symbol[k].symbol, Sen.operand[0]))k++;

			else if (!strcmp(Instr[i].sour, "m"))
				while (strcmp(Symbol[k].symbol, Sen.operand[1]))k++;
			printf(" %02X %04X %s", btoi(Instr[0].mod_reg), Symbol[k].lc, buf);
		}
		LC += atoi(Instr[i].ins_len);
	}
	//printf("%02X%02X %s", Symbol[k].lc, btoi(Instr[0].mod_reg), buf);

	else
	{
		k = 0;
		while (strcmp(Symbol[k].symbol, Sen.label))k++;
		if (!strcmp(Symbol[k].word_type, "w"))
			printf("%04X:%04X %20s", LC, atoi(Symbol[k].data), buf);
		if (!strcmp(Symbol[k].word_type, "b"))
			printf("%04X: %02X %20s", LC, atoi(Symbol[k].data), buf);
		if (*Symbol[k].word_type == 'w')  LC += 2;
		else if (*Symbol[k].word_type == 'b') LC += 1;
	}
}
void main()
{
	char buf[50];
	FILE* in;
	in = fopen("test1.asm", "r");  //  in으로 test1.asm 읽어옴
	Initialize(); // 첫번째 함수 실행( 레지스터, 명령어 테이블 저장하는 함수임)
	printf("\nPass1:\n");
	while (1)
	{
		fgets(buf, 30, in); //한줄씩 읽음
		if (feof(in))break;
		PassI(buf); // 한줄씩 읽어서 바로바로 출력함 이 함수에서 예를 들면 MOV AX, BX가 들어감
	}
	rewind(in);
	LC = 0;
	printf("\nPass2:\n");

	while (1)
	{
		fgets(buf, 30, in);
		if (feof(in)) break;
		PassII(buf);
	}
	fclose(in);

	getchar();
}