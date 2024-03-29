// question1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <cstring>			//included to use the standard library function strcmp() to compare the value of num1 and num2
using namespace std;

void reverse_str(char *num, int length);		//store 
void big_nums_subtract(char num1[], int size1, char num2[], int size2);

int main()
{
	char num1[50] = { 0 }, num2[50] = { 0 };	//initalise the elements of two num arrays all to 0 first before storing actual data
	char input1, input2;			//reading into the num array one digit by digit;
	int count1 = 0, count2 = 0;	//keep counting how many digits have been input
	bool success = true;

	cout << "Please enter the first positive integers up to 50 digits. (This number will be the minuend.)" << endl;

	do
	{
		cin.get(input1);

		if ((!isdigit(input1)) && (input1 != '\n'))		//catching potential error - input letter, symbols rather than digit number;
			success = false;
		else if (count1 >= 50)								//catching potential error - if the user enter a number more than 50 digits
			success = false;
		else if ((input1 != '\n') && count1 < 50)	//only when the input format is correct and less than 50 digits will be stored into the array
		{
			num1[count1] = input1;
			count1++;
			success = true;
		}

		if (!success)				//any wrong input will be cleared and ask for new input again
		{
			cin.clear();
			for (int i = 0; i < 50; i++) {
				num1[i] = 0;
			}
			count1 = 0;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again!" << endl;
		}

	} while (input1 != '\n');


	cout << "Now the second positive integers up to 50 digits. (This number will be the subtrahend.)" << endl;		//similar criteria for reading in the second big interger.
	do
	{
		cin.get(input2);

		if ((!isdigit(input2)) && (input2 != '\n'))
			success = false;
		else if (count2 >= 50)
			success = false;
		else if ((input2 != '\n') && count2 < 50)
		{
			num2[count2] = input2;
			count2++;
			success = true;
		}

		if (!success)
		{
			cin.clear();
			for (int i = 0; i < 50; i++) {
				num2[i] = 0;
			}
			count2 = 0;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, try again!" << endl;
		}

	} while (input2 != '\n');

	big_nums_subtract(num1, 50, num2, 50);

	return 0;
}

// I have learned how to reverse a string from the internet and motified into this block of codes for storing two numbers in a reversed order
void reverse_str(char *num, int length)
{
	for (int i = 0; i < length / 2; i++)
	{
		char temp = num[i];
		num[i] = num[length - i - 1];
		num[length - i - 1] = temp;
	}
}

void big_nums_subtract(char num1[], int size1, char num2[], int size2) //pass inputted two big number arrays
{
	int num1_len = strlen(num1);
	int num2_len = strlen(num2);

	reverse_str(num1, num1_len);			//two numbers are stored in a reversed order in order to subtract starting from the lowest place 
	reverse_str(num2, num2_len);
	char num3[51] = { 0 };					//num3 is the result storing in a char array. the size [51] is to store the extra potential '-'
	bool flag = false;						//a mark to check whether the final result need to add the symbol '-' minus in front of the number

	//the first scenario - num1 is bigger than num2 as num1 has a longer length (has more digits).
	if (num1_len > num2_len)
	{
		for (int i = 0; i < num1_len || i < num2_len; i++)
		{
			num3[i] += num1[i] - num2[i];

			if (i >= num1_len || i >= num2_len)
			{
				num3[i] -= '0';
			}

			//if the current element of result is less than 0, that means the digit in num1[i] is smaller than the digit in num2[i].
			//in this case, it need to add/carry a value of 10 in num3[i].
			//as a result, reduce 1 from the higher place i.e. the next index element num3[i+1]
			if (num3[i] < 0)
			{
				num3[i] += 10;
				num3[i + 1] -= 1;
			}
		}
	}

	// the second scenario - num1 is smaller than num2 as num1 has a shorter length (has fewer digits).
	// in this case, num3 = - (num2 - num1)
	else if (num1_len < num2_len)
	{
		flag = true;
		for (int i = 0; i < num1_len || i < num2_len; i++)
		{
			num3[i] += num2[i] - num1[i];

			if (i >= num1_len || i >= num2_len)
			{
				num3[i] -= '0';
			}

			if (num3[i] < 0)
			{
				num3[i] += 10;
				num3[i + 1] -= 1;
			}
		}
	}

	//the third scenario - num1 and num2 have the same length so need to compare which one has a bigger value.
	else
	{
		if (strcmp(num1, num2) >= 0)		//this means either the value of num1 is greater than num2 or the content of num1 and num2 are equal.
		{
			for (int i = 0; i < num1_len || i < num2_len; i++)
			{
				num3[i] += num1[i] - num2[i];

				if (i >= num1_len || i >= num2_len)
				{
					num3[i] -= '0';
				}

				if (num3[i] < 0)
				{
					num3[i] += 10;
					num3[i + 1] -= 1;
				}
			}
		}

		else							//this means num1 has smaller value than num2
		{
			flag = true;
			for (int i = 0; i < num1_len || i < num2_len; i++)
			{
				num3[i] += num2[i] - num1[i];

				if (i >= num1_len || i >= num2_len)
				{
					num3[i] -= '0';
				}

				if (num3[i] < 0)
				{
					num3[i] += 10;
					num3[i + 1] -= 1;
				}
			}
		}
	}

	//remove any potential zero in front of the actual digits.
	int max_len = num1_len > num2_len ? num1_len : num2_len;
	int a;

	for (a = max_len; a > 0; a--)
	{
		if (num3[a] != 0)
		{
			break;
		}

	}

	cout << "The difference between these two integers is: ";
	if (flag)
		cout << "-";

	for (int i = a; i >= 0; i--)
	{
		cout << (int)num3[i];
		//print out the final result from a char array into a int array in a reverse order (i.e. printing out from the highest digit place to the lowest).
	}
	cout << endl;
}
