#include <iostream>
#include <vector>
using namespace std;

class String {
private:
	int size;
	char* str;	

public:
	String()
	{
		size = 0; 
		str = new char[size];
	}

	String(const char* arr)
	{
		size = strlen(arr);
		str = new char[size + 1];
		memcpy(str, arr, size + 1);
	}

	bool isEmpty() const
	{
		return str[0] == ' ';
	}

	void resizeString(int additional)
	{
		char* biggerStr = new char[size + additional];
		for (int i = 0; i < size; ++i)
		{
			biggerStr[i] = str[i];
		}

		size += additional;
		delete[] str;
		biggerStr = str;
	}

	void swapByIndex(int firstIndex, int secondIndex)
	{
		swap(str[firstIndex], str[secondIndex]);
	}

	char* getString() const
	{
		return str;
	}

	int getSize() const
	{
		return size;
	}

	void writeTo(ostream& out) const
	{
		out << str;
	}

	char& operator[](int i)
	{
		if (i >= size || i < 0)
		{
			cout << "Invalid index. " << endl;
			exit(1);
		}

		return str[i];
	}

	char& operator[](int i) const
	{
		if (i >= size || i < 0)
		{
			cout << "Invalid index. " << endl;
			exit(1);
		}

		return str[i];
	}

	String operator=(const String& S)
	{
		for (int i = 0; i < S.getSize(); ++i)
		{
			str[i] = S[i];
		}

		return *this;
	}

	String operator+(const String& S)
	{
		String result;
		int newSize = getSize() + S.getSize();
		result.resizeString(newSize);

		int i = 0;
		for (; i < size; ++i)
		{
			result.getString()[i] = this->str[i];
		}

		int k = 0;
		for (; i < newSize; ++i, ++k)
		{
			result.getString()[i] = S.getString()[k];
		}

		return result;
	}

	String operator+=(char a)
	{
		String result;
		result.resizeString(size + 1);
		result[size] = a;
		return result;
	}

	void print() const
	{
		for (int i = 0; i < size; ++i)
		{
			cout << str[i];
		}
		cout << endl;
	}
};

ostream& operator<<(ostream& out, const String& S)
{
	S.writeTo(out);
	return out;
}

class MarkovAlgorithm {
private:
	vector<pair<String, String>> rules;

public:
	void addRule(const String& pattern, const String& change)
	{
		rules.push_back(make_pair(pattern, change));

	}

	int quantityOfRules() const
	{
		return rules.size();
	}

	String applyRule(String& inputString) const
	{
		string result = inputString.getString();
		for (const auto& rule : rules)
		{
			string pattern = rule.first.getString();
			string replacement = rule.second.getString();
			size_t position = result.find(pattern);
			while (position != string::npos)
			{
				result.replace(position, pattern.size(), replacement);
				position = result.find(pattern, position + replacement.size());
			}
		}
		return String(result.c_str());
	}

};

int main() {
	MarkovAlgorithm MA;
	MA.addRule(String("aa"), String("b"));
	MA.addRule(String("aaa"), String("c"));
	MA.addRule(String("cd"), String("e"));
	MA.addRule(String("r"), String("R"));
	MA.addRule(String("la"), String("mo"));

	string expression;
	cout << "Demonstration of the work of Markov Algorithm (rules are stated below): " << endl;
	cout << "Rule 1: ab - - - - - - > ba\nRule 2: ba - - - - - - >  V\nRule 3: cd - - - - - - >  e\nRule 4:  r - - - - - - >  R\nRule 5: la - - - - - - > mo" << endl;
	cout << "Enter an expression for Markov Algorithm: ";
	cin >> expression;
	const char* array = expression.c_str();
	String in(array);

	String C = MA.applyRule(in);
	cout << "Your result: " << C << endl;

	MarkovAlgorithm M;
	M.addRule(String("+|"), String("|+"));
	M.addRule(String("+"), String(""));
	M.addRule(String("|-|"), String("-"));
	M.addRule(String("-"), String(""));
	string expression2;
	cout << "Enter Expression in such form (||+||-):" << endl;
	cin >> expression2;
	const char* array2 = expression2.c_str();
	String A(array2);
	String Result = M.applyRule(A);
	cout << "Your result: " << Result << endl;
	return 0;
}