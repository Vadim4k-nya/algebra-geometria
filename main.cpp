#include <iostream>
#include <Windows.h>

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

	bool isСoprime(Integer B)const {
		Integer A = units_;
		if (A.NOD(B) == 1)
		{
			return 1;
		}
		return 0;
	}

	int NOD(Integer B) {
		Integer A = units_;
		if (A.units_ < B.units_) {
			std::swap(A.units_, B.units_);
		}
		while (A.units_ % B.units_ != 0) {
			A.units_ = A.units_ % B.units_;
			std::swap(A.units_, B.units_);
		}
		return B.units_;
	}

	int NOK(Integer B) {
		Integer A = units_;
		Integer result;
		result = A * B / A.NOD(B);
		return result.units_;
	}

	//перегрузки операторов

	friend Integer operator+(const Integer& A, const Integer& B) {
		Integer result;
		if (A.sign_ == B.sign_) {
			result.sign_ = A.sign_;
			result.units_ = A.units_ + B.units_;
		}
		else
		{
			if (A.units_ > B.units_)
			{
				result.sign_ = A.sign_;
				result.units_ = A.units_ - B.units_;
			}
			else if (A.units_ < B.units_) {
				result.sign_ = B.sign_;
				result.units_ = B.units_ - A.units_;
			}
			else {
				result.sign_ = false;
				result.units_ = true;
			}
		}
		return result;
	}

	friend Integer operator-(const Integer& A, const Integer& B) {
		Integer tmp = B;
		tmp.sign_ = !tmp.sign_;
		return A + tmp;
	}

	friend Integer operator*(const Integer& A, const Integer& B) {
		Integer result;
		for (int i = 0; i < B.GetUnits(); i++)
		{
			result.units_ += A.units_;
		}
		if (A.sign_ || B.sign_)
		{
			result.sign_ = true;
		}
		return result;
	}

	friend Integer operator/(const Integer& A, const Integer& B) {
		Integer result;
		result = A.units_ / B.units_;
		if (A.sign_ || B.sign_)
		{
			result.sign_ = true;
		}
		return result;
	}

	friend Integer operator%(const Integer& A, const Integer& B) {
		Integer result;
		result = A.units_ % B.units_;
		if (A.sign_ || B.sign_ && result.units_ != 0)
		{
			result.sign_ = true;
		}
		return result;
	}


	Integer operator+=(int A) {
		Integer result(*this);
		if (sign_)
		{
			units_ = units_ - A;
		}
		else
		{
			units_ = units_ + A;
		}
		return result;
	}

	Integer operator-=(int A) {
		Integer result(*this);
		if (sign_)
		{
			units_ = units_ + A;
		}
		else
		{
			units_ = units_ - A;
		}
		return result;
	}

	Integer operator*=(int A) {
		Integer result(*this);
		if (sign_)
		{
			units_ = units_ * A;
		}
		else
		{
			units_ = units_ * A;
		}
		return result;
	}

	Integer operator/=(int A) {
		Integer result(*this);
		if (sign_)
		{
			units_ = units_ / A;
		}
		else
		{
			units_ = units_ / A;
		}
		return result;
	}


	Integer operator++() {
		if (sign_)
		{
			units_ -= 1;
		}
		else
		{
			units_ += 1;
		}
		return *this;
	}

	Integer operator++(int) {
		Integer result(*this);
		if (sign_)
		{
			units_ -= 1;
		}
		else
		{
			units_ += 1;
		}
		return result;
	}

	Integer operator--() {
		if (sign_)
		{
			units_ += 1;
		}
		else
		{
			units_ -= 1;
		}
		return *this;
	}

	Integer operator--(int) {
		Integer result(*this);
		if (sign_)
		{
			units_ += 1;
		}
		else
		{
			units_ -= 1;
		}
		return result;
	}


	friend std::ostream& operator<<(std::ostream& out, const Integer obj) {
		out << (obj.sign_ ? '-' : ' ') << obj.units_;
		return out;
	}
	
private:
	bool sign_;
	unsigned units_;
};

class Rational {
public:

	Rational() :Rational(0u, 0u) {};
	Rational(Integer numerator, Integer denominator) :numerator_(numerator), denominator_(denominator) {};
	Rational(int numerator_, int denominator_) {};

	void SetSign(bool newSign) {
		this->sign_ = newSign;
	}

	void SetNumerator(Integer newNumerator) {
		this->numerator_ = newNumerator;
	}

	bool GetSign()const {
		return sign_;
	}


	friend std::ostream& operator<<(std::ostream& out, const Rational obj) {
		out << obj.numerator_ << "/" << obj.denominator_;
		return out;
	}

private:
	bool sign_;
	Integer numerator_;
	Integer denominator_;
};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Integer num1{ 37 };
	Integer num2{ -42 };

	std::cout << num1 << '\n';
	std::cout << (num1.isOdd() ? "Четное" : "Не четное") << '\n';
	std::cout << (num1.isPositive() ? "Положительное" : "Отрицательное") << '\n';
	std::cout << (num1.isPrime() ? "Простое" : "Сложное") << "\n\n";

	std::cout << num1 << " и " << num2 << (num1.isСoprime(num2) ? " Взаимно простые" : "Взаимно сложные") << '\n';
	
	std::cout << "\n\nНаибольший общий делитель " << num1 << " и " << num2 << ": " << num1.NOD(num2) << '\n';
	std::cout << "Наименьшее общее кратное " << num1 << " и " << num2 << ": " << num1.NOK(num2) << '\n';
	

	return 0;
}
