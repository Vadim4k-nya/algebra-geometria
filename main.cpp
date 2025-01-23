#include <iostream>
#include <Windows.h>



/*int NOK(int num1, int num2) {
	return num1 * num2 / NOD(num1, num2);
}*/


class Integer {
public:

	//способы создания объектов

	Integer() :Integer(false, 0u) {}
	Integer(bool sign, unsigned units) :sign_(sign), units_(units) {}
	Integer(int number) {
		if (number < 0)
		{
			sign_ = true;
			units_ = ::abs(number);
		}
		else {
			sign_ = false;
			units_ = static_cast<unsigned>(number);
		}
	}

	//способы обработки объектов

	void SetSign(bool newSign) {
		this->sign_ = newSign;
	}

	void SetUnits(unsigned newunits) {
		this->units_ = newunits;
	}

	bool GetSign()const {
		return sign_;
	}

	unsigned GetUnits()const {
		return units_;
	}

	void Print()const {
		std::cout << (sign_ ? '-' : ' ') << units_ << '\n';
	}

	//способы проверки состояния

	bool isOdd()const {
		return !bool(units_ % 2);
	}

	bool isPositive()const {
		return !sign_;
	}

	bool isPrime()const {
		for (int i = 2; i <= sqrt(units_); i++) {
			if (units_ % i == 0) {
				return 0;
			}
		}
		return 1;
	}

	/*bool isСoprime()const {
		if (NOD(units_) == 1)
		{
			return 1;
		}
		return 0;
	}*/

	/*int NOD(Integer a, Integer b) {
		if (a < b) {
			std::swap(a, b);
		}
		while (a % b != 0) {
			a = a % b;
			std::swap(a, b);
		}
		return b;
	}*/

	//перегрузки операторов

	Integer operator+(const Integer& other)const {
		Integer result;
		if (sign_ == other.sign_) {
			result.sign_ = sign_;
			result.units_ = units_ + other.units_;
		}
		else
		{
			if (units_ > other.units_)
			{
				result.sign_ = sign_;
				result.units_ = units_ - other.units_;
			}
			else if (units_ < other.units_) {
				result.sign_ = other.sign_;
				result.units_ = other.units_ - units_;
			}
			else {
				result.sign_ = false;
				result.units_ = true;
			}
		}
		return result;
	}

	friend Integer operator-(const Integer& a, const Integer& b) {
		Integer tmp = b;
		tmp.sign_ = !tmp.sign_;
		return a + tmp;
	}

	friend Integer operator*(Integer a, Integer b) {
		return Integer();
	}

	


private:
	bool sign_;
	unsigned units_;
};




int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Integer num1{ !37 };
	Integer num2{ -42 };
	
	num1.Print();
	std::cout << (num1.isOdd() ? "Четное" : "Не четное") << '\n';
	std::cout << (num1.isPositive() ? "Положительное" : "Отрицательное") << '\n';
	std::cout << (num1.isPrime() ? "Простое" : "Сложное") << '\n';
	//std::cout << num1 << " и " << num2 << " взаимнопростые(1) или взаимносложные(0): " << num1, num2.isСoprime() << '\n';
	
	//std::cout << "Наибольший общий делитель " << num1 << " и " << num2 << " : " << NOD(num1, num2) << '\n';
	//std::cout << "Наименьшее общее кратное " << num1 << " и " << num2 << " : " << NOK(Integer(num1).Getunits(), Integer(num2).Getunits()) << '\n';
	
	return 0;
}

