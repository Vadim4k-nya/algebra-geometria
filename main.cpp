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

	bool isСoprime(Integer& B)const {
		Integer A = units_;
		if (A.NOD(B) == 1)
		{
			return 1;
		}
		return 0;
	}

	int NOD(Integer& B)const {
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

	int NOK(Integer& B)const {
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
		if (B.units_ == 0)
		{
			return 0;
		}
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
		if (A == B)
		{
			return true;
		}
		if (A < B) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	friend bool operator>(const Integer& A, const Integer& B) {
		return !(A < B);
	}

	friend bool operator>=(const Integer& A, const Integer& B) {
		if (A == B)
		{
			return true;
		}
		if (A > B)
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

	bool Proper()const {
		if (numerator_.GetUnits() < denominator_.GetUnits())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Positive()const {
		if (numerator_.GetSign() == denominator_.GetSign())
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	bool SameThing()const
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

	Rational Reverse() 
	{
		Integer numer = denominator_,
			denom = numerator_;
		return { numer, denom };
	}

	Rational Simplifying()
	{
		Integer numer = numerator_,
			denom = denominator_;
		numer /= numer.NOD(denom);
		denom /= numer.NOD(denom);
		return { numer, denom };
	}

	Integer IntParts() 
	{
		return numerator_ / denominator_;
	}

	Rational FractPart()
	{
		return { numerator_ % denominator_, denominator_ };
	}

	// Методы для модификации дроби

	void ModSimplifying() 
	{
		numerator_ /= numerator_.NOD(denominator_);
		denominator_ /= numerator_.NOD(denominator_);
	}

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

	// Унарные +-

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
		
	}

	friend bool operator<=(const Rational& A, const Rational& B) {
		if (A == B)
		{
			return true;
		}
		if (A < B)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool operator>(const Rational& A, const Rational& B) {
		return !(A < B);
	}

	friend bool operator>=(const Rational& A, const Rational& B) {
		if (A == B)
		{
			return true;
		}
		if (A > B)
		{
			return true;
		}
		else
		{
			return false;
		}
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

	Integer num1{ 37 };
	Integer num2{ -42 };

	std::cout << num1 << '\n';
	std::cout << (num1.isOdd() ? "Четное" : "Не четное") << '\n';
	std::cout << (num1.isPositive() ? "Положительное" : "Отрицательное") << '\n';
	std::cout << (num1.isPrime() ? "Простое" : "Сложное") << "\n\n";

	std::cout << num1 << " и " << num2 << (num1.isСoprime(num2) ? " Взаимно простые" : "Взаимно сложные") << '\n';
	
	std::cout << "\n\nНаибольший общий делитель " << num1 << " и " << num2 << ": " << num1.NOD(num2) << '\n';
	std::cout << "Наименьшее общее кратное " << num1 << " и " << num2 << ": " << num1.NOK(num2) << '\n';

	Rational num3 {20,300};

	num3.ModSimplifying();
	std::cout << num3;

	return 0;
}
