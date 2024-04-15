#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int countMatchedNumberLetterInString(const char* str, int digit)
{
	int i = 0;
	int coin = 0;						  // �ش� ���ڰ� ���� ����
	char typecast = digit + '0';			  // digit�� ���������� �����̱� ������ ���� Ÿ��ĳ������ ���� str���ڿ��� �˻��� �� �ְ� ��
	while (str[i] != NULL)				  // ���ڿ��� ���������� ����
	{
		if (str[i] == typecast)				 //�������� ���� �� �ǹ��ְ� ���� 
		{
			coin++;
		}
		i++;
	}
	return coin;						  // ���� ��ȯ
}

void quiz1()
{
	int count = 0;
	const char numcharacter[100] = { 0 };
	printf("���ڸ� �Է��Ͻÿ�: ");
	scanf("%s", numcharacter);			  
	count = countMatchedNumberLetterInString(numcharacter, 4);   //�۵� ���� �ʴ� ��Ȳ������ ��ó�� �����غ���
	printf("%d\n", count);
}

//=======================================================================

void excludeRedundantLetters(char* str)
{
	char nstr[100] = { 0 };					// �ߺ��� ���ڸ� ���� ���ڿ��� �����ϴ� �迭
	nstr[0] = str[0];
	int count_nstr = 1;						// nstr�� ������ ������ �ε���
	int i = 1;
	int	check_redundant = 0;					// �ߺ����� �ƴ����� üũ  ����
	while (str[i] != NULL)						// null�� ���ö����� �ݺ�, *null�� ���� ���� ������ ��츦 �����ؾ���
	{
		for (int j = 0; j < i; j++)				//*c������ for���ȿ��� ���������� ������ �� ����.
		{
			if (str[j] == str[i])
			{
				check_redundant++;
			}
		}
		if (check_redundant == 0)			//check_redundant�� 0�̸� nstr�� ����
		{
			nstr[count_nstr] = str[i];
			count_nstr++;
		}

		check_redundant = 0;
		i++;
	}
	for (int k = 0; k < 100; k++)			// ���ÿ��� data�� ����ؾ� �ϱ� ������ ���ڿ��� �ϳ��ϳ� ���� (strcpy)�� ��� ����
	{
		str[k] = nstr[k];
	}

}

void quiz2()
{
	char data[100] = { 0 };
	printf("���ڸ� �Է��Ͻÿ�: ");
	scanf("%[^\n]s", data);			   //^���� ���� �ش� ���ڸ� �޴°��̰� ^���� �ش� ���ڰ� ���� �� ���� ���ڿ��� ����
	excludeRedundantLetters(data);
	printf("%s", data);

}
//===========================================================================



int countWords(char* str)
{
	int i = 0;
	int isspace = 0;					   //0�� ready���¶�� ���� * isspace��� �Լ��� �����ϱ⶧���� �ٸ� �Լ�
	int check_words = 0;
	while (str[i] != NULL)
	{
		if (isspace == 0)					   //isspace�� 0�̰� ��� ������ check_words++�ϰ� isspace�� 1
		{
			if (str[i] != ' ' && str[i] != '\t')
			{
				check_words++;
				isspace = 1;
			}
		}
		else if (isspace == 1)			   //1�� ���¿��� �����̳� ���� ������ isspace�� �غ���·� ���ư��� �ٽ� �ܾ �� �غ� ����
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
	printf("������ �Է��Ͻÿ�: ");
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

		if (leftparen < rightparen)			 //')'�� '("���� ������ ��ȣ�� ������ ���� ����
		{
			iscorrect = false;
			break;
		}
		i++;
	}

	return iscorrect;						 // bool�� ��ȯ
}

void quiz4()
{
	char parenthesis[] = "()()()()";		 //)(�� �������� ����
	bool result = examineParenthesis(parenthesis);
	printf("%s", result == true ? "true" : "false");

}

//===========================================================================

void convertString(char* str)
{
	int i = 0;
	char nstr[200] = { 0 };
	int nstr_count = 0;						 // nstr�� ���ļ� ����ȴ°� �����ϱ� ���� �ε��� ����
	char addstr[4] = "%20";					 // %20�� ����Ǿ� �ִ� ���ڿ��� ���� ����
	while (str[i] != NULL)
	{
		if (str[i] != ' ')
		{
			nstr[nstr_count] = str[i];		 // ���ڰ� ������ nstr�� �����ϰ� nstr�� �ε���+1
			nstr_count++;
		}
		else
		{
			strcat(nstr, addstr);			 // ������ ������ addstr�� �̾���̱� 
			nstr_count = nstr_count + 3;	 // %20�� nstr�� 3ĭ��ŭ �����ϴ� ���� count�� +3�� �Ͽ� �������� �ʰ� ����
		}
		i++;
	}
	strcpy(str, nstr);						 // stirng.h�� ������ strcpy�� Ȱ�� ���� ���� �ʾҴٸ� for������ ����

}

void quiz5()
{
	char input[200] = { 0 };
	printf("������ �Է��Ͻÿ�: ");
	scanf("%[^\n]s", input);
	convertString(input);
	printf("%s", input);
}

//===========================================================================


int main()
{
	//quiz1();								 //�۵�o
	//quiz2();								 //�۵�o
	//quiz3();								 //�۵�o
	//quiz4();								 //�۵�o, false �� ����
	//quiz5();								 //�۵�o

	return 0;
}