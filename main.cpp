#include <iostream>
#include <Windows.h>

int NOD(int num1, int num2) {
	if (num1 < num2) {
		std::swap(num1, num2);
	}
	while (num1 % num2 != 0) {
		num1 = num1 % num2;
		std::swap(num1, num2);
	}
	return num2;
}

int NOK(int num1, int num2) {
	return num1 * num2 / NOD(num1, num2);
}


class Integer {
public:

	//способы создания объектов

	Integer() :Integer(false, 0u) {}
	Integer(bool sign, unsigned untils) :sign_(sign), untils_(untils) {}
	Integer(bool sign, unsigned untils, bool sign2, unsigned untils2) :sign_(sign), untils_(untils), sign2_(sign), untils2_(untils) {}
	Integer(int number) {
		if (number < 0)
		{
			sign_ = true;
			untils_ = ::abs(number);
		}
		else {
			sign_ = false;
			untils_ = static_cast<unsigned>(number);
		}
	}
	Integer(int number1, int number2) {
		if (number1 < 0)
		{
			sign_ = true;
			untils_ = ::abs(number1);
		}
		else {
			sign_ = false;
			untils_ = static_cast<unsigned>(number1);
		}
		
		if (number2 < 0)
		{
			sign2_ = true;
			untils2_ = ::abs(number2);
		}
		else {
			sign2_ = false;
			untils2_ = static_cast<unsigned>(number2);
		}
	}

	//способы обработки объектов

	void SetSign(bool sign) {
		this->sign_ = sign;
	}

	void SetUntils(unsigned untils) {
		this->untils_ = untils;
	}

	bool GetSign()const {
		return sign_;
	}

	unsigned GetUntils()const {
		return untils_;
	}

	//способы проверки состояния

	bool isOdd()const {
		return bool(untils_ % 2);
	}

	bool isPositive()const {
		return !sign_;
	}

	bool isPrime()const {
		for (int i = 2; i <= sqrt(untils_); i++) {
			if (untils_ % i == 0) {
				return 0;
			}
		}
		return 1;
	}

	bool isСoprime()const {
		if (NOD(untils_, untils2_) == 1)
		{
			return 1;
		}
		return 0;
	}

	//перегрузки операторов

	Integer operator+(Integer other)const {
		return Integer();
	}

	friend Integer operator*(Integer a, Integer b);

private:
	bool sign_;
	unsigned untils_;

	bool sign2_;
	unsigned untils2_;

};
Integer operator*(Integer a, Integer b) {
	return Integer();
}



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
		
	int num1 = 37;
	int num2 = 42;

	std::cout << num1 << " не четное(1) или четное(0): " << Integer(num1).isOdd() << '\n';
	std::cout << num1 << " положительное(1) или отрицательное(0): " << Integer(num1).isPositive() << '\n';
	std::cout << num1 << " простое(1) или сложное(0): " << Integer(num1).isPrime() << '\n';
	std::cout << num1 << " и " << num2 << " взаимнопростые(1) или взаимно сложные(0): " << Integer(num1, num2).isСoprime() << '\n';
	
	std::cout << "Наибольший общий делитель " << num1 << " и " << num2 << " : " << NOD(Integer(num1).GetUntils(), Integer(num2).GetUntils()) << '\n';
	//std::cout << "Наименьшее общее кратное " << num1 << " и " << num2 << " : " << NOK(Integer(num1).GetUntils(), Integer(num2).GetUntils()) << '\n';
	
	return 0;
}

