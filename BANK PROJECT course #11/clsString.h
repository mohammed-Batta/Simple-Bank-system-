#pragma once
#include <iostream>
#include <vector>
using namespace std;
class clsString
{
private:
	string _Value;
	static char InvertChar(char c) {

		return (islower(c) ? toupper(c) : tolower(c));

	}

public:
	

	clsString(string value = "") {
		_Value = value;
	}

	void setValue(string value) {
		_Value = value;
	}

	string getValue() {
		return _Value;
	}

	_declspec(property(get = getValue, put = setValue)) string Value;


    static void PrintFirstLetterOfEachWordInString(string text) {

		for (int i = 0; i < text.length(); i++) {

			if (i == 0 && text[i] != ' ')
				cout << text[i] << endl;

			if (text[i] == ' ' && text[i + 1] != ' ')
				cout << text[i + 1] << endl;
		}

	}
	void PrintFirstLetterOfEachWordInString() {

		PrintFirstLetterOfEachWordInString(_Value);
	}


	static string UpperFirstLetterOfEachWordInString(string text) {

		for (int i = 0; i < text.length(); i++) {

			if (i == 0 && text[i] != ' ')
				text[i] = toupper(text[i]);

			if (text[i] == ' ' && text[i + 1] != ' ')
				text[i + 1] = toupper(text[i + 1]);
		}

		return text;

	}
	void UpperFirstLetterOfEachWordInString(){

		_Value = UpperFirstLetterOfEachWordInString(_Value);
	}


  	static string LowerFirstLetterOfEachWordInString(string text) {

		if (text[0] != ' ')
			text[0] = tolower(text[0]);

		for (int i = 0; i < text.length(); i++) {
			if (text[i] == ' ' && text[i + 1] != ' ')
				text[i + 1] = tolower(text[i + 1]);
		}

		return text;
	}
	void LowerFirstLetterOfEachWordInString() {
		_Value = LowerFirstLetterOfEachWordInString(_Value);

	}

	static string ToUpperString(string text) {

		for (int i = 0; i < text.length(); i++) {

			text[i] = toupper(text[i]);
		}

		return text;

	}
	void ToUpperString(){
		_Value = ToUpperString(_Value);
	}


	static string ToLowerString(string text) {

		for (int i = 0; i < text.length(); i++) {

			text[i] = tolower(text[i]);
		}

		return text;

	}
	void ToLowerString() {
		_Value = ToLowerString(_Value);
	}

	static string InvertLettersCase(string text) {
		for (int i = 0; i < text.length(); i++)
			text[i] = InvertChar(text[i]);

		return text;
	}
	void InvertLettersCase() {
		_Value = InvertLettersCase(_Value);
	}

	static int countSpacificLetter(string text, char letter, bool MatchCase = true) {


		int counter = 0;
		for (int i = 0; i < text.length(); i++) {

			if (MatchCase) {
				if (text[i] == letter)
					counter++;
			}
			else {

				if (tolower(text[i]) == tolower(letter))
					counter++;
			}


		}
		return counter;
	}
	int countSpacificLetter(char letter, bool MatchCase = true) {
		return countSpacificLetter(_Value, letter, MatchCase);
	}

	static bool IsVowel(char letter) {

		char Vowels[5] = { 'a','e','i','o','u' };

		for (short i = 0; i < 5; i++)
			if (tolower(letter) == Vowels[i])
				return true;

		return false;
	}

	static int CountVowels(string text) {
		int counter = 0;
		for (int i = 0; i < text.length(); i++)
			if (IsVowel(text[i]))
				counter++;

		return counter;
	}
	int CountVowels() {
		return CountVowels(_Value);
	}

	static vector<string> SplitString(string text, string sprater = " ") {
		string word = "";
		int SpraterPosition = 0;

		vector<string> vWords;
		while ((SpraterPosition = text.find(sprater)) != text.npos) {

			word = text.substr(0, SpraterPosition);

			if (!word.empty())
				vWords.push_back(word);

			text.erase(0, SpraterPosition + sprater.length());
		}
		if (!text.empty())
			vWords.push_back(text);

		return vWords;
	}
	vector<string> SplitString(string sprater = " ") {
		return SplitString(_Value, sprater);
	}

	static int countWords(string text, string sprater ) {
		return SplitString(text, sprater).size();
	}
	int countWords(string sprater = " ") {
		return SplitString(_Value, sprater).size();

	}

	static string TrimLeft(string text) {

		for (short i = 0; i < text.length(); i++) {
			if (text[i] != ' ')
				return text.substr(i, text.length() - i);
		}
		return "";
	}
	void TrimLeft() {
		_Value= TrimLeft(_Value);
	}

	static string TrimRight(string text) {

		for (short i = text.length() - 1; i >= 0; i--) {
			if (text[i] != ' ')
				return text.substr(0, i + 1);
		}
		return "";
	}
	void TrimRight() {
		_Value = TrimRight(_Value);
	}

	static string Trim(string text) {
		return TrimLeft(TrimRight(text));
	}
	void Trim() {
		_Value = TrimLeft(TrimRight(_Value));
	}

	static string ReversString(string text) {

		vector<string> words = SplitString(text," ");
		string reversedText = "";

		for (short i = words.size() - 1; i >= 0; i--)
			reversedText += words[i] + " ";

		return reversedText.substr(0, reversedText.length() - 1); // to reomver the last sapce
	}
	void ReversString() {
		_Value =  ReversString(_Value);
	}

	static string JoinString(vector<string> vWords, string sprater = " ") {
		string join = "";

		for (string& word : vWords) {
			join += word + sprater;
		}

		return join.substr(0, join.length() - sprater.length());
	}
	static string JoinString(string Arr[], short ArrayLength, string sprater = " ") {
		string join = "";

		for (short i = 0; i < ArrayLength; i++) {
			join += Arr[i] + sprater;
		}

		return join.substr(0, join.length() - sprater.length());
	}

	static string ReplaceWordsInString(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
	{
		vector<string> vString = SplitString(S1, " ");
		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}
			}
			else
			{
				if (ToLowerString(s) == ToLowerString(StringToReplace))
				{
					s = sRepalceTo;
				}
			}
		}
		return JoinString(vString, " ");
	}
	void ReplaceWordsInString(string StringToReplace, string sRepalceTo, bool MatchCase = true) {
		setValue(ReplaceWordsInString(_Value, StringToReplace, sRepalceTo, MatchCase));
	}

	static string RemovePunctuationsFromString(string text)
	{

		for (short i = 0; i < text.length(); i++) {
			if (ispunct(text[i]))
				text.erase(i, 1);
		}

		return text;
	}
	void RemovePunctuationsFromString() {
		_Value = RemovePunctuationsFromString(_Value);
	}
};

