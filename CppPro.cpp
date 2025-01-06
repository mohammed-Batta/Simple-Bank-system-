
#include <iostream>
using namespace std;

enum class enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum class enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };

struct stQuestion {
	int FirstNumber;
	int SecondNumber;
	int Answer;
	enOpType OpType;
};


struct stQuiz {
	int NumberOfQuestions;
	int NumberOfRightAnswers;
	int NumberOfWrongAnswers;
	enQuestionsLevel QuestionsLevel;
	enOpType OpType;
};

int ReadPositiveNumber(string msg) {
	int number = 0;
	do {
		cout << msg;
		cin >> number;
	} while (number <= 0);
	return number;
}

int RandomNumber(int From, int To) {

	int random = rand() % (To - From + 1) + From;
	return random;
}

int ReadNumberInRange(int From, int To, string msg) {
	int number = 0;
	do {
		cout << msg;
		cin >> number;
	} while (number < From || number > To);

	return number;
}

enQuestionsLevel GetQuestionsLevel(int num) {
	return enQuestionsLevel(num);
}

enOpType GetOpType(int num) {
	return enOpType(num);
}

string GetOperationChar(enOpType OpType) {
	switch (OpType)
	{
	case enOpType::Add:
		return "+";
	case enOpType::Sub:
		return "-";
	case enOpType::Mul:
		return "*";
	case enOpType::Div:
		return "/";
	case enOpType::Mix:
		return "Mix";
	}
	return "ERROR";
}

int GetAnswer(int FirstNumber, int SecondNumber, enOpType OpType) {
	switch (OpType)
	{
	case enOpType::Add:
		return FirstNumber + SecondNumber;
	case enOpType::Sub:
		return FirstNumber - SecondNumber;
	case enOpType::Mul:
		return FirstNumber * SecondNumber;
	case enOpType::Div:
		return FirstNumber / SecondNumber;
	}
	return -1;

}

int GetNumberForOperation(enQuestionsLevel questionsLevel) {

	switch (questionsLevel)
	{
	case enQuestionsLevel::Easy:
		return RandomNumber(1, 10);
	case enQuestionsLevel::Med:
		return RandomNumber(10, 50);
	case enQuestionsLevel::Hard:
		return RandomNumber(50, 100);
	default:
		return -1;
	}

}

stQuestion GetQuestion(enQuestionsLevel questionsLevel, enOpType OpType) {
	stQuestion question;
	if (questionsLevel == enQuestionsLevel::Mix) {
		enQuestionsLevel PickLevelRandomly = (enQuestionsLevel)RandomNumber(1, 3);
		question.FirstNumber = GetNumberForOperation(PickLevelRandomly);
		question.SecondNumber = GetNumberForOperation(PickLevelRandomly);
	}
	else {
		question.FirstNumber = GetNumberForOperation(questionsLevel);
		question.SecondNumber = GetNumberForOperation(questionsLevel);

	}

	if (OpType == enOpType::Mix) {
		question.OpType = (enOpType)RandomNumber(1, 4);
	}
	else {
		question.OpType = OpType;
	}


	return question;
}

stQuiz PlayQuiz(int NumberOfQuestions, enQuestionsLevel questionsLevel, enOpType OpType) {
	int NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;

	for (int NumberOfQuestion = 1; NumberOfQuestion <= NumberOfQuestions; NumberOfQuestion++) {
		cout << "\n\nQuestion [" << NumberOfQuestion << "/" << NumberOfQuestions << "]\n\n";
		stQuestion question = GetQuestion(questionsLevel, OpType);
		int input = 0;
		cout << question.FirstNumber << endl << question.SecondNumber << " " << GetOperationChar(question.OpType) << endl;
		cout << "__________________" << endl;
		cin >> input;
		int Answer = GetAnswer(question.FirstNumber, question.SecondNumber, question.OpType);
		if (input == Answer) {
			NumberOfRightAnswers++;
			cout << "Right Answer :-)";
			system("color 2F");
		}
		else {
			NumberOfWrongAnswers++;
			cout << "Wrong Answer :-(";
			cout << endl << "Right answer is " << Answer;
			system("color 4F");
			cout << '\a';

		}

	}
	stQuiz Quiz;
	Quiz.NumberOfQuestions = NumberOfQuestions;
	Quiz.NumberOfRightAnswers = NumberOfRightAnswers;
	Quiz.NumberOfWrongAnswers = NumberOfWrongAnswers;
	Quiz.OpType = OpType;
	Quiz.QuestionsLevel = questionsLevel;

	return Quiz;

}

bool IsPass(int NumberOfRightAnswers, int NumberOfWrongAnswers) {
	if (NumberOfRightAnswers > NumberOfWrongAnswers)
		return true;

	return false;
}

void PrintFinalResultsHeader(int NumberOfRightAnswers, int NumberOfWrongAnswers) {
	cout << "\n\n___________________________________\n\n";
	cout << " Final Results is";
	if (IsPass(NumberOfRightAnswers, NumberOfWrongAnswers)) {
		cout << " Pass :-)\n\n";
		system("color 2F");
	}
	else {
		cout << " Fail :-(\n\n";
		system("color 4F");
	}
	cout << "___________________________________\n\n";
}

string GetQuestionsLevelInString(enQuestionsLevel ql) {
	switch (ql)
	{
	case enQuestionsLevel::Easy:
		return "Easy";
	case enQuestionsLevel::Med:
		return "Med";
	case enQuestionsLevel::Hard:
		return "Hard";
	case enQuestionsLevel::Mix:
		return "Mix";
	}
	return "ERROR";

}

void ShowFinalResults(stQuiz quiz) {
	PrintFinalResultsHeader(quiz.NumberOfRightAnswers, quiz.NumberOfWrongAnswers);
	cout << "Number of Questions: " << quiz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionsLevelInString(quiz.QuestionsLevel) << endl;
	cout << "Operation Type     : " << GetOperationChar(quiz.OpType) << endl;
	cout << "Number of Right Answers: " << quiz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << quiz.NumberOfWrongAnswers << endl;
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame() {
	char PlayMore = 'y';
	do {
		ResetScreen();
		int NumberOfQuestions = ReadPositiveNumber("How Many Questions do you want to answer : ");
		enQuestionsLevel questionsLevel = GetQuestionsLevel(ReadNumberInRange(1, 4, "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix : "));
		enOpType OpType = GetOpType(ReadNumberInRange(1, 5, "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix : "));
		stQuiz quiz = PlayQuiz(NumberOfQuestions, questionsLevel, OpType);
		ShowFinalResults(quiz);
		cout << "\n\nDo you want to Play again y/n : ";
		cin >> PlayMore;
	} while (tolower(PlayMore) == 'y');
}

int main() {
	srand((unsigned)time(NULL));


	StartGame();


	return 0;
}


