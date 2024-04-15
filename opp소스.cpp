#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int countMatchedNumberLetterInString(const char* str, int digit)
{
	int i = 0;
	int coin = 0;						  // 해당 숫자가 나온 개수
	char typecast = digit + '0';			  // digit는 정수형으로 고정이기 때문에 따로 타입캐스팅을 통해 str문자열을 검사할 수 있게 함
	while (str[i] != NULL)				  // 문자열이 끝날때가지 지속
	{
		if (str[i] == typecast)				 //변수명을 지을 때 의미있게 짓기 
		{
			coin++;
		}
		i++;
	}
	return coin;						  // 개수 반환
}

void quiz1()
{
	int count = 0;
	const char numcharacter[100] = { 0 };
	printf("숫자만 입력하시오: ");
	scanf("%s", numcharacter);			  
	count = countMatchedNumberLetterInString(numcharacter, 4);   //작동 되지 않는 상황에서의 대처도 생각해보기
	printf("%d\n", count);
}

//=======================================================================

void excludeRedundantLetters(char* str)
{
	char nstr[100] = { 0 };					// 중복된 문자를 없앤 문자열을 저장하는 배열
	nstr[0] = str[0];
	int count_nstr = 1;						// nstr에 저장할 문자의 인덱스
	int i = 1;
	int	check_redundant = 0;					// 중복인지 아닌지를 체크  변수
	while (str[i] != NULL)						// null이 나올때까지 반복, *null이 가장 먼저 나오는 경우를 생각해야함
	{
		for (int j = 0; j < i; j++)				//*c에서는 for문안에서 지역변수를 선언할 수 없다.
		{
			if (str[j] == str[i])
			{
				check_redundant++;
			}
		}
		if (check_redundant == 0)			//check_redundant가 0이면 nstr에 복사
		{
			nstr[count_nstr] = str[i];
			count_nstr++;
		}

		check_redundant = 0;
		i++;
	}
	for (int k = 0; k < 100; k++)			// 예시에서 data를 출력해야 하기 때문에 문자열을 하나하나 복사 (strcpy)도 사용 가능
	{
		str[k] = nstr[k];
	}

}

void quiz2()
{
	char data[100] = { 0 };
	printf("문자를 입력하시오: ");
	scanf("%[^\n]s", data);			   //^없이 쓰면 해당 문자만 받는것이고 ^쓰면 해당 문자가 나올 때 까지 문자열로 리턴
	excludeRedundantLetters(data);
	printf("%s", data);

}
//===========================================================================



int countWords(char* str)
{
	int i = 0;
	int isspace = 0;					   //0을 ready상태라고 정의 * isspace라는 함수가 존재하기때문에 다른 함수
	int check_words = 0;
	while (str[i] != NULL)
	{
		if (isspace == 0)					   //isspace가 0이고 영어가 나오면 check_words++하고 isspace가 1
		{
			if (str[i] != ' ' && str[i] != '\t')
			{
				check_words++;
				isspace = 1;
			}
		}
		else if (isspace == 1)			   //1인 상태에서 공백이나 탭이 나오면 isspace가 준비상태로 돌아가고 다시 단어를 셀 준비에 돌입
		{
			if (str[i] == ' ' || str[i] == '\t')
				isspace = 0;
		}
		i++;
	}
	return check_words;
}

void quiz3()
{
	char sentence[100];
	printf("문장을 입력하시오: ");
	scanf("%[^\n]s", sentence);
	int nWords = countWords(sentence);
	printf("%d", nWords);

}

//===========================================================================

bool examineParenthesis(const char* isparenthesis)
{
	int i = 0;
	bool iscorrect = true;
	int rightparen = 0;
	int leftparen = 0;
	while (isparenthesis[i] != NULL)
	{
		if (isparenthesis[i] == '(')
			leftparen++;
		else if (isparenthesis[i] == ')')
			rightparen++;

		if (leftparen < rightparen)			 //')'이 '("보다 많으면 괄호의 성립이 되지 않음
		{
			iscorrect = false;
			break;
		}
		i++;
	}

	return iscorrect;						 // bool값 반환
}

void quiz4()
{
	char parenthesis[] = "()()()()";		 //)(를 생각하지 못함
	bool result = examineParenthesis(parenthesis);
	printf("%s", result == true ? "true" : "false");

}

//===========================================================================

void convertString(char* str)
{
	int i = 0;
	char nstr[200] = { 0 };
	int nstr_count = 0;						 // nstr에 겹쳐서 복사된는걸 제어하기 위한 인덱스 정수
	char addstr[4] = "%20";					 // %20가 저장되어 있는 문자열을 따로 만듬
	while (str[i] != NULL)
	{
		if (str[i] != ' ')
		{
			nstr[nstr_count] = str[i];		 // 문자가 나오면 nstr에 저장하고 nstr의 인덱스+1
			nstr_count++;
		}
		else
		{
			strcat(nstr, addstr);			 // 공백이 나오면 addstr을 이어붙이기 
			nstr_count = nstr_count + 3;	 // %20은 nstr에 3칸만큼 차지하니 기존 count에 +3을 하여 겹쳐지지 않고 복사
		}
		i++;
	}
	strcpy(str, nstr);						 // stirng.h를 썼으니 strcpy도 활용 만약 쓰지 않았다면 for문으로 복사

}

void quiz5()
{
	char input[200] = { 0 };
	printf("문장을 입력하시오: ");
	scanf("%[^\n]s", input);
	convertString(input);
	printf("%s", input);
}

//===========================================================================


int main()
{
	//quiz1();								 //작동o
	//quiz2();								 //작동o
	//quiz3();								 //작동o
	//quiz4();								 //작동o, false 도 가능
	//quiz5();								 //작동o

	return 0;
}