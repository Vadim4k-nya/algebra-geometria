#include <iostream>
#include <Windows.h>
#include <string>

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
	/*Integer(double number) {
		if (number < 0)
		{
			sign_ = true;
			units_ = ::abs(number);
		}
		else {
			sign_ = false;
			units_ = static_cast<unsigned>(number);
		}
	}*/
	Integer(std::string number) {
		units_ = ::abs(std::stoi(number));
		if (number[0] == '-')
		{
			sign_ = true;
		}
		else {
			sign_ = false;
		}
	}

	//способы обработки объектов

	void SetSign(bool newSign) {
		this->sign_ = newSign;
	}

	void SetUnits(unsigned newUnits) {
		this->units_ = newUnits;
	}

	bool GetSign()const {
		return sign_;
	}

	unsigned GetUnits()const {
		return units_;
	}

	//способы проверки состояния

	//Четность
	bool isOdd()const {
		return !(units_ % 2);
	}

	//Положительность
	bool isPositive()const {
		return !sign_;
	}

	//Простота
	bool isPrime()const {
		for (int i = 2; i <= sqrt(units_); i++) {
			if (units_ % i == 0) {
				return 0;
			}
		}
		return 1;
	}

	//Взаимная простота
	static bool isСoprime(const Integer& A, const Integer& B) {
		if (NOD(A, B) == 1)
		{
			return 1;
		}
		return 0;
	}

	// Наибольший общий делитель
	static Integer NOD(const Integer& A, const Integer& B) {
		Integer result;
		if (A % B == 0)
			return B.units_;
		if (B % A == 0)
			return A.units_;
		if (A > B)
		{
			result = NOD(A % B, B);
			return result.units_;
		}
		result = NOD(A, B % A);
		return result.units_;
	}

	//Наименьшее общее кратное
	static Integer NOK(const Integer& A, const Integer& B) {
		Integer result;
		result = (A * B) / NOD(A, B);
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
		if (A.sign_ == B.sign_)
		{
			result.sign_ = false;
		}
		else
		{
			result.sign_ = true;
		}
		return result;
	}

	friend Integer operator/(const Integer& A, const Integer& B) {
		if (B.units_ == 0)
		{
			return 0;
		}
		Integer result;
		result = A.units_ / B.units_;
		if (A.sign_ == B.sign_)
		{
			result.sign_ = false;
		}
		else
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


	Integer operator+=(Integer A) {
		Integer result(*this);
		if (sign_ == A.sign_)
		{
			units_ = units_ + A.units_;
		}
		else
		{
			units_ = units_ - A.units_;
		}
		return result;
	}

	Integer operator-=(Integer A) {
		Integer result(*this);
		if (sign_ == A.sign_)
		{
			units_ = units_ - A.units_;
		}
		else
		{
			units_ = units_ + A.units_;
		}
		return result;
	}

	Integer operator*=(Integer A) {
		Integer result(*this);
		if (sign_ == A.sign_)
		{
			sign_ = false;
			units_ = units_ * A.units_;
		}
		else
		{
			sign_ = true;
			units_ = units_ * A.units_;
		}
		return result;
	}

	Integer operator/=(Integer A) {
		Integer result(*this);
		if (sign_ == A.sign_)
		{
			sign_ = false;
			units_ = units_ / A.units_;
		}
		else
		{
			sign_ = true;
			units_ = units_ / A.units_;
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

	Integer operator+() {
		return { sign_, units_ };
	}

	Integer operator-() {
		return { !sign_, units_ };
	}


	bool operator!() {
		return !sign_;
	}

	friend bool operator==(const Integer& A, const Integer& B) {
		if (A.sign_ == B.sign_ && A.units_ == B.units_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool operator!=(const Integer& A, const Integer& B) {
		return !(A == B);
	}

	friend bool operator<(const Integer& A, const Integer& B) {
		if (B.sign_ < A.sign_)
		{
			return false;
		}
		else if (B.sign_ && A.sign_) {
			if (B.units_ < A.units_) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (!B.sign_ && !A.sign_) {
			if (B.units_ > A.units_) {
				return true;
			}
			else {
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	friend bool operator<=(const Integer& A, const Integer& B) {
		if (A == B || A < B)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	friend bool operator>(const Integer& A, const Integer& B) {
		if (B.sign_ > A.sign_)
		{
			return false;
		}
		else if (B.sign_ && A.sign_) {
			if (B.units_ > A.units_) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (!B.sign_ && !A.sign_) {
			if (B.units_ < A.units_) {
				return true;
			}
			else {
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	friend bool operator>=(const Integer& A, const Integer& B) {
		if (A == B || A > B)
		{
			return true;
		}
		else
		{
			return false;
		}
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

	//способы создания объектов

	Rational() :Rational(0u, 0u) {};
	Rational(Integer numerator, Integer denominator) :numerator_(numerator), denominator_(denominator) {};
	Rational(int numerator, int denominator) {
		Integer num = numerator, den = denominator;
		this->numerator_ = num;
		this->denominator_ = den;
	};
	Rational(double number) {
		int intPart;
		this->denominator_ = 100;
		intPart = number;
		number -= intPart;
		this->numerator_ = (number * 100) + (intPart * denominator_);
	}
	Rational(std::string number) {
		double stod = std::stod(number);
		int intPart;
		this->denominator_ = 100;
		intPart = stod;
		stod -= intPart;
		this->numerator_ = (stod * 100) + (intPart * denominator_);
	}

	//способы обработки объектов
		
	void SetNumerator(Integer& newNumerator) {
		this->numerator_ = newNumerator;
	}

	void SetDeniminator(Integer& newDeniminator) {
		this->denominator_ = newDeniminator;
	}

	Integer GetNumerator()const
	{
		return numerator_;
	}

	Integer GetDenominator()const
	{
		return denominator_;
	}

	//способы проверки состояния

	//Правильность дроби
	bool isProper()const {
		if (numerator_.GetUnits() < denominator_.GetUnits())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Положительность дроби
	bool isPositive()const {
		if (numerator_.GetSign() == denominator_.GetSign())
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	//являются ли 2 числа одним и тем же объектом в программе
	bool isSameThing()const
	{
		if (numerator_ == denominator_)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	// Методы для получения значений

	//Обратная дробь
	Rational Reverse() 
	{
		Integer numer = denominator_,
			denom = numerator_;
		return { numer, denom };
	}

	//Упрощение дроби
	Rational Simplifying()
	{
		Integer numer = numerator_,
			denom = denominator_;
		numer = numer / Integer::NOD(numer, denom);
		denom = denom / Integer::NOD(numer, denom);
		return { numer, denom };
	}

	//Найти целую часть
	Integer IntParts() 
	{
		return numerator_ / denominator_;
	}

	//Найти дробную часть
	Rational FractPart()
	{
		return { numerator_ % denominator_, denominator_ };
	}

	// Методы для модификации дроби

	//Модификатор упрощения дроби
	void ModSimplifying() 
	{
		numerator_ = numerator_ / Integer::NOD(numerator_, denominator_);
		denominator_ = denominator_ / Integer::NOD(numerator_, denominator_);
	}

	//Медификатор переворачивания дроби
	void ModReverse()
	{
		std::swap(numerator_, denominator_);
	}

	// Операторы

	friend Rational operator+(const Rational& A, const Rational& B) 
	{
		Rational result;
		result.numerator_ = A.numerator_ * B.denominator_ + B.numerator_ * A.denominator_;
		result.denominator_ = A.denominator_ * B.numerator_;
	}

	friend Rational operator-(const Rational& A, const Rational& B) 
	{
		Rational result;
		result.numerator_ = A.numerator_ * B.denominator_ - B.numerator_ * A.denominator_;
		result.denominator_ = A.denominator_ * B.numerator_;
	}

	friend Rational operator*(const Rational& A, const Rational& B) 
	{
		Rational result;
		result.numerator_ = A.numerator_ * B.numerator_;
		result.denominator_ = A.denominator_ * B.denominator_;
	}

	friend Rational operator/(const Rational& A, const Rational& B) 
	{
		Rational result;
		result.numerator_ = A.numerator_ * B.denominator_;
		result.denominator_ = A.denominator_ * B.numerator_;
	}

	//Присваивающие версии операторов надо будет сделать

	// Унарные +- надо будет сделать

	friend bool operator==(const Rational& A, const Rational& B) {
		if (A.numerator_ == B.numerator_ && A.denominator_ == B.denominator_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool operator!=(const Rational& A, const Rational& B) {
		return !(A == B);
	}

	friend bool operator<(const Rational& A, const Rational& B) {
		if (A.denominator_ == B.denominator_)
		{
			return A.numerator_ < B.numerator_;
		}
		else if (A.numerator_ == B.numerator_)
		{
			return !(A.denominator_ < B.denominator_);
		}
		else 
		{
			Integer NOK = Integer::NOK(A.denominator_, B.denominator_);
			return (A.numerator_ * NOK) < (B.numerator_ * NOK);
		}
	}

	friend bool operator<=(const Rational& A, const Rational& B) {
		if (A < B && A == B)
		{
			return true;
		}
		return false;
	}

	friend bool operator>(const Rational& A, const Rational& B) {
		if (A.denominator_ == B.denominator_)
		{
			return A.numerator_ > B.numerator_;
		}
		else if (A.numerator_ == B.numerator_)
		{
			return !(A.denominator_ > B.denominator_);
		}
		else
		{
			Integer NOK = Integer::NOK(A.denominator_, B.denominator_);
			return (A.numerator_ * NOK) > (B.numerator_ * NOK);
		}
	}

	friend bool operator>=(const Rational& A, const Rational& B) {
		if (A > B && A == B)
		{
			return true;
		}
		return false;
	}


	friend std::ostream& operator<<(std::ostream& out, const Rational obj) {
		out << obj.numerator_ << " /" << obj.denominator_;
		return out;
	}

private:
	Integer numerator_;
	Integer denominator_;
};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	/*Integer num1{6};
	Integer num2{ -5 };

	std::cout << num1 << '\n';
	std::cout << (num1.isOdd() ? "Четное" : "Не четное") << '\n';
	std::cout << (num1.isPositive() ? "Положительное" : "Отрицательное") << '\n';
	std::cout << (num1.isPrime() ? "Простое" : "Сложное") << "\n\n";

	std::cout << num1 << " и " << num2 << (Integer::isСoprime(num1, num2) ? " Взаимно простые" : " Взаимно сложные") << '\n';
	
	std::cout << "\n\nНаибольший общий делитель " << num1 << " и " << num2 << ": " << Integer::NOD(num1, num2) << '\n';
	std::cout << "Наименьшее общее кратное " << num1 << " и " << num2 << ": " << Integer::NOK(num1, num2) << '\n';

	Rational num3 {2,3};
	Rational num4{ 3,3 };*/

	return 0;
}
