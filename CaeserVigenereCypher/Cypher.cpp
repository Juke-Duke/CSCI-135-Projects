#include <iostream>
#include <cctype>
#include <string>

char shiftChar(char c, int rshift);
char unshiftChar(char c, int rshift);
std::string encryptCaesar(std::string plaintext, int rshift);
std::string encryptVigenere(std::string plaintext, std::string keyword);
std::string decryptCaesar(std::string ciphertext, int rshift);
std::string decryptVigenere(std::string ciphertext, std::string keyword);

int main()
{
	std::string line, keyword;
	int shift = 0;


	//Asks user for a string
	std::cout << "Input plaintext: ";
	getline(std::cin, line);

	std::cout << "= Caeser =" << std::endl;
	std::cout << "Enter Shift	: ";
	std::cin >> shift;
	std::cout << "Ciphertext	: " << encryptCaesar(line, shift) << std::endl;
	std::cout << "Decrypted	: " << decryptCaesar(encryptCaesar(line, shift), shift) << "\n\n";

	std::cout << "= Vigenere =" << std::endl;
	std::cout << "Enter Keyword	: ";
	std::cin >> keyword;
	std::cout << "Ciphertext	: " << encryptVigenere(line, keyword) << std::endl;
	std::cout << "Decrypted	: " << decryptVigenere(encryptVigenere(line, keyword), keyword) << std::endl;
	

	return 0;
}

char shiftChar(char c, int rshift)
{
	int value = (int)c;
	char newC;

	//If the char is uppercase, finds new value in interval 65-90
	if (isupper(c))
	{
		value += rshift;
		if (value > 90)
		{
			int diff = 0;
			diff = value - 90;
			value = 64 + diff;

			newC = char(value);
			return newC;
		}
		else
		{
			newC = char(value);
			return newC;
		}
	}
	//If the char is lowercase, finds new value in interval 97-122
	else if (islower(c))
	{
		value += rshift;
		if (value > 122)
		{
			int diff = 0;
			diff = value - 122;
			value = 96 + diff;

			newC = char(value);
			return newC;
		}
		else
		{
			newC = char(value);
			return newC;
		}
	}

	//Anything else is kept the same
	return c;

}

std::string encryptCaesar(std::string plaintext, int rshift)
{
	//Runs the shiftChar function for each character in the line and replaces it with the new shift
	for (int i = 0; i < plaintext.size(); i++)
	{
		plaintext[i] = shiftChar(plaintext[i], rshift);
	}

	return plaintext;
}

std::string encryptVigenere(std::string plaintext, std::string keyword)
{
	//Makes a counter for when we reach the end of the keyword
	int counter = 0;
	int shift = 0;
	for (int i = 0; i <= plaintext.size(); i++)
	{
		//If its not a letter, it stays the same
		if (!isalpha(plaintext[i]))
		{
			plaintext[i] = plaintext[i];
		}
		//If it is a letter, then shift it using the counter were up to
		else
		{
			shift = int(keyword[counter]) - 97;
			plaintext[i] = shiftChar(plaintext[i], shift);
			counter++;
		}
		//If the counter has reached, reset it so we start over
		if (counter >= keyword.size())
		{
			counter = 0;
		}
	}
	return plaintext;
}

char unshiftChar(char c, int rshift)
{
	int value = (int)c;
	char newC;

	//If the char is uppercase, finds new value in interval 65-90
	if (isupper(c))
	{
		value -= rshift;
		if (value < 65)
		{
			int diff = 0;
			diff = 65 - value;
			value = 91 - diff;

			newC = char(value);
			return newC;
		}
		else
		{
			newC = char(value);
			return newC;
		}
	}
	//If the char is lowercase, finds new value in interval 97-122
	else if (islower(c))
	{
		value -= rshift;
		if (value < 97)
		{
			int diff = 0;
			diff = 97 - value;
			value = 123 - diff;

			newC = char(value);
			return newC;
		}
		else
		{
			newC = char(value);
			return newC;
		}
	}

	//Anything else is kept the same
	return c;

}

std::string decryptCaesar(std::string ciphertext, int rshift)
{
	//Runs the shiftChar function for each character in the line and replaces it with the new shift
	for (int i = 0; i < ciphertext.size(); i++)
	{
		ciphertext[i] = unshiftChar(ciphertext[i], rshift);
	}

	return ciphertext;
}

std::string decryptVigenere(std::string ciphertext, std::string keyword)
{
	//Makes a counter for when we reach the end of the keyword
	int counter = 0;
	int shift = 0;
	for (int i = 0; i <= ciphertext.size(); i++)
	{
		//If its not a letter, it stays the same
		if (!isalpha(ciphertext[i]))
		{
			ciphertext[i] = ciphertext[i];
		}
		//If it is a letter, then shift it using the counter were up to
		else
		{
			shift = int(keyword[counter]) - 97;
			ciphertext[i] = unshiftChar(ciphertext[i], shift);
			counter++;
		}
		//If the counter has reached, reset it so we start over
		if (counter >= keyword.size())
		{
			counter = 0;
		}
	}
	return ciphertext;
}
