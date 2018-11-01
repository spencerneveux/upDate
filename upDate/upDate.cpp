//Spencer Neveux
//CECS 282 upDate project
//11/1/18

#include "upDate.hpp"
#include <iostream>

using namespace std;

int upDate::count = 0;

int Greg2Julian(int month, int day, int year) {
    int JD = day - 32075 + 1461 * (year + 4800 + (month - 14) / 12) / 4 + 367
    * (month - 2 - (month - 14) / 12 * 12) / 12 - 3
    * ((year + 4900 + (month - 14) / 12) / 100) / 4;
    return JD;
}

void Julian2Greg(int JD, int & month, int & day, int & year) {
    int L = JD + 68569;
    int N = 4 * L / 146097;
    L = L - (146097 * N + 3) / 4;
    int I = 4000 * (L + 1) / 1461001;
    L = L - 1461 * I / 4 + 31;
    int J = 80 * L / 2447;
    int K = L - 2447 * J / 80;
    L = J / 11;
    J = J + 2 - 12 * L;
    I = 100 * (N - 49) + I + L;
    
    year = I;
    month = J;
    day = K;
}

// Null Constructor
upDate::upDate() {
    dptr = new int[3];
    dptr[0] = 5;
    dptr[1] = 11;
    dptr[2] = 1959;
    count++;
}

//Overloaded Constructor
upDate::upDate(int M, int D, int Y) {
    dptr = new int[3];
    dptr[0] = M;
    dptr[1] = D;
    dptr[2] = Y;
    
    int jd = Greg2Julian(M, D, Y);
    Julian2Greg(jd, M, D, Y);
    if (M == dptr[0] && D == dptr[1] && Y == dptr[2])
    {
        dptr[0] = M;
        dptr[1] = D;
        dptr[2] = Y;
    }
    else {
        dptr[0] = 5;
        dptr[1] = 11;
        dptr[2] = 1959;
    }
    count++;
}

//Constructor for Julian Date
upDate::upDate(int j) {
    dptr = new int[3];
    Julian2Greg(j, dptr[0], dptr[1], dptr[2]);
    count++;
}

//Destructor
upDate::~upDate() {
    count--;
    delete []dptr;
}

//SetDate method
void upDate::setDate(int M, int D, int Y) {
    dptr = new int[3];
    dptr[0] = M;
    dptr[1] = D;
    dptr[2] = Y;
    
    int jd = Greg2Julian(M, D, Y);
    Julian2Greg(jd, M, D, Y);
    if (M == dptr[0] && D == dptr[1] && Y == dptr[2])
    {
        dptr[0] = M;
        dptr[1] = D;
        dptr[2] = Y;
    }
    else {
        dptr[0] = 5;
        dptr[1] = 11;
        dptr[2] = 1959;
    }
}

//Copy Constructor
upDate::upDate(const upDate &obj) {
    dptr = new int[3];
    dptr[0] = obj.dptr[0];
    dptr[1] = obj.dptr[1];
    dptr[2] = obj.dptr[2];
    
    count++;
}

//Get Month Method
int upDate::getMonth() {
    return dptr[0];
}

// Get Day Method
int upDate::getDay() {
    return dptr[1];
}

//Get year method
int upDate::getYear() {
    return dptr[2];
}

//Get month name
string upDate::getMonthName() {
    string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    return months[dptr[0] - 1];
}

//Get count of how many upDate objects there are
int upDate::GetDateCount() {
    return count;
}

//Get int value of julian
int upDate::julian() {
    int month, day, year;
    month = dptr[0];
    day = dptr[1];
    year = dptr[2];
    
    int JD = day - 32075 + 1461 * (year + 4800 + (month - 14) / 12) / 4 + 367
    * (month - 2 - (month - 14) / 12 * 12) / 12 - 3
    * ((year + 4900 + (month - 14) / 12) / 100) / 4;
    return JD;
}

//======================================OVERLOADED OPERATORS============================//

//Operator =
upDate upDate::operator=(upDate D) {
    dptr = new int[3];
    dptr[0] = D.dptr[0];
    dptr[1] = D.dptr[1];
    dptr[2] = D.dptr[2];
    return (*this);
}

//Operator +=
upDate upDate::operator+=(int n) {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    jd += n;
    Julian2Greg(jd, dptr[0], dptr[1], dptr[2]);
    return temp;
}

//Operator -=
upDate upDate::operator-=(int n) {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    jd -= n;
    Julian2Greg(jd, dptr[0], dptr[1], dptr[2]);
    return temp;
}


//Operator +
upDate upDate::operator+(int n) {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    jd += n;
    Julian2Greg(jd, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    return temp;
}

//Operator + friend
upDate operator+(int n, upDate D) {
    return D + n;
}

//Operator -
upDate upDate::operator-(int n) {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    jd -= n;
    Julian2Greg(jd, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    return temp;
}

//Operator - Friend
upDate operator-(int n, upDate D) {
    return D - n;
}


//upDate - upDate operator
int upDate::operator-(upDate D) {
    int jd1 = Greg2Julian(dptr[0], dptr[1], dptr[2]);
    int jd2 = Greg2Julian(D.dptr[0], D.dptr[1], D.dptr[2]);
    int result = jd1 - jd2;
    return result;
}

//Operator <<
ostream &operator<<(ostream& out, upDate D) {
    out << D.getMonth() << "/" << D.getDay() << "/" << D.getYear();
    return out;
}

//operator ++
upDate upDate::operator++() {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    jd += 1;
    Julian2Greg(jd, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    return temp;
}

upDate upDate::operator++(int n) {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    ++jd;
    Julian2Greg(jd, dptr[0], dptr[1], dptr[2]);
    return temp;
}

//operator --
upDate upDate::operator--() {
    upDate temp(*this);
    int jd = Greg2Julian(temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    jd -= 1;
    Julian2Greg(jd, temp.dptr[0], temp.dptr[1], temp.dptr[2]);
    return temp;
}

upDate upDate::operator--(int n) {
    upDate temp(*this);
    --*this;
    return temp;
}

//Operator <
bool upDate::operator<(upDate D) {
    if (this->julian() < D.julian()) {
        return true;
    }
    else {
        return false;
    }
}

//Operator >
bool upDate::operator>(upDate D) {
    if (this->julian() > D.julian())
        return true;
    else
        return false;
}

//Operator ==
bool upDate::operator==(upDate D) {
    if (this->julian() == D.julian())
        return true;
    else
        return false;
}

int main() {
	// Testing null constructor
	upDate D;

	//Testing getMonth/GetDay/getYear
	cout << D.getMonth() << " " << D.getDay() << " " << D.getYear() << endl;

	// Testing valid date overloaded constructor
	upDate D1(3, 25, 1992);
	cout << D1.getMonth() << " " << D1.getDay() << " " << D1.getYear() << endl;

	//Testing invalid date Overloaded constructor
	upDate D2(3, 41, 1992);
	cout << D2.getMonth() << " " << D2.getDay() << " " << D2.getYear() << endl;

	//Testing julian date constructor
	upDate D3(2458418.28747);
	cout << D3.getMonth() << " " << D3.getDay() << " " << D3.getYear() << endl;

	//Testing setDate method
	D3.setDate(10, 27, 2018);
	cout << D3.getMonth() << " " << D3.getDay() << " " << D3.getYear() << endl;

	//Testing invalid setDate method
	D3.setDate(10, 41, 2018);
	cout << D3.getMonth() << " " << D3.getDay() << " " << D3.getYear() << endl;

	//Testing copy constructor
	upDate cpy1(1, 2, 2018);
	upDate cpy2(cpy1);
	cout << cpy2.getMonth() << " " << cpy2.getDay() << " " << cpy2.getYear() << endl;

	//Testing get Month name
	cout << D1.getMonthName() << endl;

	//Testing assignment operator
	cout << D1.getMonth() << " " << D1.getDay() << " " << D1.getYear() << endl;
	D1 = D2;
	cout << D1.getMonth() << " " << D1.getDay() << " " << D1.getYear() << endl;


	//Testing operator+= operator
	upDate D5(1, 2, 2018);
	D5 += 5;
	cout << D5.getMonth() << " " << D5.getDay() << " " << D5.getYear() << endl;

	//Testing operator -= operator
	upDate D6(2, 1, 2018);
	D6 -= 3;
	cout << D6.getMonth() << " " << D6.getDay() << " " << D6.getYear() << endl;

	//Testing operator +
	upDate D7 = D6 + 5;
	cout << D7.getMonth() << " " << D7.getDay() << " " << D7.getYear() << endl;

	//Testing friend operator +
	upDate D8 = 5 + D7;
	cout << D8.getMonth() << " " << D8.getDay() << " " << D8.getYear() << endl;

	//Testing operator -
	upDate D9(1, 2, 2018);
	upDate D10 = D9 - 1;
	cout << D10.getMonth() << " " << D10.getDay() << " " << D10.getYear() << endl;

	//Testing opeator friend -
	D10 = 7 - D9;
	cout << D10.getMonth() << " " << D10.getDay() << " " << D10.getYear() << endl;
	
	//Testing upDate1 - upDate 2
	upDate d1(1, 1, 2018);
	upDate d2(1, 3, 2018);
	int x = d1 - d2;
	cout << "The days between is: " << x << endl;
	
	//Testing getDateCount
	cout << upDate::GetDateCount() << endl;


	//Testing << operator
	upDate d3(10, 29, 2018);
	cout << d3 << endl;

	//Testing ++ operator
	upDate d4(1, 1, 1929);
	d4++;
	cout << d4 << endl;
	++d4;
	cout << d4 << endl;

	//Testing -- operator
	upDate d5(2, 3, 1930);
	d5--;
	cout << d5 << endl;
	--d5; 
	cout << d5 << endl;

	//Testing julian()
	cout << d5.julian() << endl;

	//Testing >,<, ==
	upDate d6(1, 1, 2018);
	upDate d7(1, 2, 2018);
	
	// First test <
	bool result = d6 < d7;
	cout << "Result should be true " << result << endl;
	result = d7 < d6;
	cout << "Result should be false " << result << endl;

	//Test > 
	result = d6 > d7;
	cout << "Result should be false " << result << endl;
	result = d7 > d6;
	cout << "Result should be true " << result << endl;

	//Test ==
	result = d6 == d7;
	cout << "Result should be false " << result << endl;
	d7--;
	result = d6 == d7;
	cout << "Result should be true " << result << endl;
	return 0;
}
