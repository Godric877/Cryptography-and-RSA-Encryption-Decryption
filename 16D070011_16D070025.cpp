//Note:Made in Code::Blocks version 16.01
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include<math.h>
#include<stdlib.h>

#define MAX 10000

using namespace std;
class BigInteger {    //BIGINTEGER INITIALIZATIONS.......SOURCE:https://github.com/panks/BigInteger/blob/master/BigIntegerSingleFile.cpp
private:
    string number;
    bool sign;
public:
    BigInteger(); // empty constructor initializes zero
    BigInteger(string s); // "string" constructor
    BigInteger(string s, bool sin); // "string" constructor
    BigInteger(int n); // "int" constructor
    void setNumber(string s);
    const string& getNumber(); // retrieves the number
    void setSign(bool s);
    const bool& getSign();
    BigInteger absolute(); // returns the absolute value
    void operator = (BigInteger b);
    bool operator == (BigInteger b);
    bool operator != (BigInteger b);
    bool operator > (BigInteger b);
    bool operator < (BigInteger b);
    bool operator >= (BigInteger b);
    bool operator <= (BigInteger b);
    BigInteger& operator ++(); // prefix
    BigInteger  operator ++(int); // postfix
    BigInteger& operator --(); // prefix
    BigInteger  operator --(int); // postfix
    BigInteger operator + (BigInteger b);
    BigInteger operator - (BigInteger b);
    BigInteger operator * (BigInteger b);
    BigInteger operator / (BigInteger b);
    BigInteger operator % (BigInteger b);
    BigInteger& operator += (BigInteger b);
    BigInteger& operator -= (BigInteger b);
    BigInteger& operator *= (BigInteger b);
    BigInteger& operator /= (BigInteger b);
    BigInteger& operator %= (BigInteger b);
    BigInteger& operator [] (int n);
    BigInteger operator -(); // unary minus sign
    operator string(); // for conversion from BigInteger to string
private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
};BigInteger a=929,b=937;
   BigInteger p=(a-1)*(b-1);
   BigInteger q=a*b;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//BIG INTEGER CODE STARTS FROM HERE
//SOURCE :https://github.com/panks/BigInteger/blob/master/BigIntegerSingleFile.cpp
//
//
BigInteger::BigInteger() { // empty constructor initializes zero
    number = "0";
    sign = false;
}

BigInteger::BigInteger(string s) { // "string" constructor
    if( isdigit(s[0]) ) { // if not signed
        setNumber(s);
        sign = false; // +ve
    } else {
        setNumber( s.substr(1) );
        sign = (s[0] == '-');
    }
}

BigInteger::BigInteger(string s, bool sin) { // "string" constructor
    setNumber( s );
    setSign( sin );
}

BigInteger::BigInteger(int n) { // "int" constructor
    stringstream ss;
    string s;
    ss << n;
    ss >> s;


    if( isdigit(s[0]) ) { // if not signed
        setNumber( s );
        setSign( false ); // +ve
    } else {
        setNumber( s.substr(1) );
        setSign( s[0] == '-' );
    }
}

void BigInteger::setNumber(string s) {
    number = s;
}

const string& BigInteger::getNumber() { // retrieves the number
    return number;
}

void BigInteger::setSign(bool s) {
    sign = s;
}

const bool& BigInteger::getSign() {
    return sign;
}

BigInteger BigInteger::absolute() {
    return BigInteger( getNumber() ); // +ve by default
}

void BigInteger::operator = (BigInteger b) {
    setNumber( b.getNumber() );
    setSign( b.getSign() );
}

bool BigInteger::operator == (BigInteger b) {
    return equals((*this) , b);
}

bool BigInteger::operator != (BigInteger b) {
    return ! equals((*this) , b);
}

bool BigInteger::operator > (BigInteger b) {
    return greater((*this) , b);
}

bool BigInteger::operator < (BigInteger b) {
    return less((*this) , b);
}

bool BigInteger::operator >= (BigInteger b) {
    return equals((*this) , b)
           || greater((*this), b);
}

bool BigInteger::operator <= (BigInteger b) {
    return equals((*this) , b)
           || less((*this) , b);
}

BigInteger& BigInteger::operator ++() { // prefix
    (*this) = (*this) + 1;
    return (*this);
}

BigInteger BigInteger::operator ++(int) { // postfix
    BigInteger before = (*this);

    (*this) = (*this) + 1;

    return before;
}

BigInteger& BigInteger::operator --() { // prefix
    (*this) = (*this) - 1;
    return (*this);

}

BigInteger BigInteger::operator --(int) { // postfix
    BigInteger before = (*this);

    (*this) = (*this) - 1;

    return before;
}

BigInteger BigInteger::operator + (BigInteger b) {
    BigInteger addition;
    if( getSign() == b.getSign() ) { // both +ve or -ve
        addition.setNumber( add(getNumber(), b.getNumber() ) );
        addition.setSign( getSign() );
    } else { // sign different
        if( absolute() > b.absolute() ) {
            addition.setNumber( subtract(getNumber(), b.getNumber() ) );
            addition.setSign( getSign() );
        } else {
            addition.setNumber( subtract(b.getNumber(), getNumber() ) );
            addition.setSign( b.getSign() );
        }
    }
    if(addition.getNumber() == "0") // avoid (-0) problem
        addition.setSign(false);

    return addition;
}

BigInteger BigInteger::operator - (BigInteger b) {
    b.setSign( ! b.getSign() ); // x - y = x + (-y)
    return (*this) + b;
}

BigInteger BigInteger::operator * (BigInteger b) {
    BigInteger mul;

    mul.setNumber( multiply(getNumber(), b.getNumber() ) );
    mul.setSign( getSign() != b.getSign() );

    if(mul.getNumber() == "0") // avoid (-0) problem
        mul.setSign(false);

    return mul;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator / (BigInteger b) {
    long long den = toInt( b.getNumber() );
    BigInteger div;

    div.setNumber( divide(getNumber(), den).first );
    div.setSign( getSign() != b.getSign() );

    if(div.getNumber() == "0") // avoid (-0) problem
        div.setSign(false);

    return div;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator % (BigInteger b) {
    long long den = toInt( b.getNumber() );

    BigInteger rem;
    long long rem_int = divide(number, den).second;
    rem.setNumber( toString(rem_int) );
    rem.setSign( getSign() != b.getSign() );

    if(rem.getNumber() == "0") // avoid (-0) problem
        rem.setSign(false);

    return rem;
}

BigInteger& BigInteger::operator += (BigInteger b) {
    (*this) = (*this) + b;
    return (*this);
}

BigInteger& BigInteger::operator -= (BigInteger b) {
    (*this) = (*this) - b;
    return (*this);
}

BigInteger& BigInteger::operator *= (BigInteger b) {
    (*this) = (*this) * b;
    return (*this);
}

BigInteger& BigInteger::operator /= (BigInteger b) {
    (*this) = (*this) / b;
    return (*this);
}

BigInteger& BigInteger::operator %= (BigInteger b) {
    (*this) = (*this) % b;
    return (*this);
}

BigInteger& BigInteger::operator [] (int n) {
    return *(this + (n*sizeof(BigInteger)));
}

BigInteger BigInteger::operator -() { // unary minus sign
    return (*this) * -1;
}

BigInteger::operator string() { // for conversion from BigInteger to string
    string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
    signedString += number;
    return signedString;
}

bool BigInteger::equals(BigInteger n1, BigInteger n2) {
    return n1.getNumber() == n2.getNumber()
           && n1.getSign() == n2.getSign();
}

bool BigInteger::less(BigInteger n1, BigInteger n2) {
    bool sign1 = n1.getSign();
    bool sign2 = n2.getSign();

    if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
        return true;

    else if(! sign1 && sign2)
        return false;

    else if(! sign1) { // both +ve
        if(n1.getNumber().length() < n2.getNumber().length() )
            return true;
        if(n1.getNumber().length() > n2.getNumber().length() )
            return false;
        return n1.getNumber() < n2.getNumber();
    } else { // both -ve
        if(n1.getNumber().length() > n2.getNumber().length())
            return true;
        if(n1.getNumber().length() < n2.getNumber().length())
            return false;
        return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
    }
}

bool BigInteger::greater(BigInteger n1, BigInteger n2) {
    return ! equals(n1, n2) && ! less(n1, n2);
}

string BigInteger::add(string number1, string number2) {
    string add = (number1.length() > number2.length()) ?  number1 : number2;
    char carry = '0';
    int differenceInLength = abs( (int) (number1.size() - number2.size()) );

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else// if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.size()-1; i>=0; --i) {
        add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

        if(i != 0) {
            if(add[i] > '9') {
                add[i] -= 10;
                carry = '1';
            } else
                carry = '0';
        }
    }
    if(add[0] > '9') {
        add[0]-= 10;
        add.insert(0,1,'1');
    }
    return add;
}

string BigInteger::subtract(string number1, string number2) {
    string sub = (number1.length()>number2.length())? number1 : number2;
    int differenceInLength = abs( (int)(number1.size() - number2.size()) );

    if(number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for(int i=number1.length()-1; i>=0; --i) {
        if(number1[i] < number2[i]) {
            number1[i] += 10;
            number1[i-1]--;
        }
        sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
    }

    while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
        sub.erase(0,1);

    return sub;
}

string BigInteger::multiply(string n1, string n2) {
    if(n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for(int i=n1.length()-1; i>=0; --i) {
        string temp = n2;
        int currentDigit = n1[i]-'0';
        int carry = 0;

        for(int j=temp.length()-1; j>=0; --j) {
            temp[j] = ((temp[j]-'0') * currentDigit) + carry;

            if(temp[j] > 9) {
                carry = (temp[j]/10);
                temp[j] -= (carry*10);
            } else
                carry = 0;

            temp[j] += '0'; // back to string mood
        }

        if(carry > 0)
            temp.insert(0, 1, (carry+'0'));

        temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

        res = add(res, temp); // O(n)
    }

    while(res[0] == '0' && res.length()!=1) // erase leading zeros
        res.erase(0,1);

    return res;
}

pair<string, long long> BigInteger::divide(string n, long long den) {
    long long rem = 0;
    string result;
    result.resize(MAX);

    for(int indx=0, len = n.length(); indx<len; ++indx) {
        rem = (rem * 10) + (n[indx] - '0');
        result[indx] = rem / den + '0';
        rem %= den;
    }
    result.resize( n.length() );

    while( result[0] == '0' && result.length() != 1)
        result.erase(0,1);

    if(result.length() == 0)
        result = "0";

    return make_pair(result, rem);
}

string BigInteger::toString(long long n) {
    stringstream ss;
    string temp;

    ss << n;
    ss >> temp;

    return temp;
}

long long BigInteger::toInt(string s) {
    long long sum = 0;

    for(int i=0; i<s.length(); i++)
        sum = (sum*10) + (s[i] - '0');

    return sum;
}
BigInteger inverse(BigInteger a,BigInteger b)//brute force method check later
{

    a %= b;
    for(BigInteger x = 1; x < b; x++) {
        if((a*x) % b == 1) return x;

}
return 0;
}
BigInteger bruteLog(BigInteger b,BigInteger c,BigInteger m){
   BigInteger s = 1;
    for (BigInteger i=0;i<m;i++){
        s = (s * b) % m;
        if (s == c){
            return i + 1;}}
    return -1;}
    BigInteger gcd(BigInteger a,BigInteger b)
 {
     BigInteger max,min;if(a>b){max=a;min=b;}else{max=b;min=a;}
     while(max%min!=0)
     {
         BigInteger t=min;
         min=max%min;
         max=t;
     }
     return min;
 }
BigInteger keyGeneration()
{

   BigInteger e= 17;
   while(gcd(e,p)!=1){e=e+81242;}
   return e;
}

BigInteger emodulus(BigInteger a,BigInteger e,BigInteger c)
{
    BigInteger i=e,mo=a%c;i--;
    while(i>0)
    {
        mo=(mo*a)%c;i--;
    }
    return mo;
}
BigInteger encryption(string msg,BigInteger e)
{
    BigInteger f;f.setNumber(msg);
    BigInteger g=emodulus(f,e,q);
    return g;
}
BigInteger decryption(string emsg,BigInteger e)
{
    BigInteger f=inverse(e,p),k;k.setNumber(emsg);
    BigInteger l=emodulus(k,f,q);return l;
}
void reverse(string &a){
	int n =a.length();
	if(n%2==0){
		for(int i=0;i<n/2;i++){
			char temp=a[i];
			a[i]=a[n-1-i];
			a[n-1-i]=temp;
		}
	}else{
			for(int i=0;i<=n/2-1;i++){
			char temp=a[i];
			a[i]=a[n-1-i];
			a[n-1-i]=temp;
		}
	}
}

string addBin(string a1,string a2){
	int n,min;
	int n1=a1.length(),n2=a2.length();
	reverse(a1);
//	cout<<a1;
	reverse(a2);
//	cout<<a2;
	string r="";
if(n1>=n2){
	n=n1;
	min=n2;
}else{
	n=n2;
	min=n1;
}
	for(int i=0;i<n;i++){
		if(i<min){
			if((a1[i]=='1' && a2[i]=='0') || (a1[i]=='0' && a2[i]=='1')){
				r="1"+r;
			}else{
				r="0"+r;
			}
		//	cout<<r<<endl;
		}else{
			if(a1[i]=='1' || a2[i]=='1'){
				r="1"+r;
			}else{
				r="0"+r;
			}
		}
	}
	return r;
}

string multiplyBin(string a1,string a2){
	int n1=a1.length();
	int n2=a2.length();
	int n,min;
	string a,b;
	if(n1>=n2){
	n=n1;
	a=a2;
	min=n2;
	b=a1;
}else{
	n=n2;
	a=a1;
	min=n1;
	b=a2;
}
string r="0";
for(int i=0;i<min;i++){
	if(a[min-i-1]=='1'){
		string temp=b;
		for(int j=0;j<i;j++){
		temp=temp+"0";
		}
	//	cout<<temp<<endl;
		r=addBin(r,temp);
	//	cout<<r<<endl;
	}
}
return r;

}

int main()
{int i,o,l,z,y,u;string s1,s2,s3,t[100],t1[100],t2[100];BigInteger a,b,c,d;
   do
   {cout<<endl;
     cout<<"Enter your choice:"<<endl;
     cout<<"1.Modulo Addition"<<endl;

     cout<<"2.Modulo Multiplication"<<endl;
     cout<<"3.GCD"<<endl;

     cout<<"4.Modular Inverse"<<endl;
     cout<<"5.Modular Exponentiation"<<endl;
     cout<<"6.Discrete Logarithm"<<endl;
     cout<<"7.RSA Encryption and Decryption"<<endl;
     cout<<"8.Field Operiations in Binary Field"<<endl;
     cout<<"Enter 0 to exit"<<endl;;cin>>i;if(i==0)break;
     switch(i)
     {   default:cout<<"invalid entry"<<endl;break;
         case 1:cout<<"Enter three numbers in abc format(calculates a+b modc)"<<endl;cin>>s1>>s2>>s3;d.setNumber(s3);
         a.setNumber(s1);b.setNumber(s2);c=(a+b)%d;cout<<endl<<c.getNumber();break;
         case 2:cout<<"Enter three numbers in abc format(calculates a*b modc"<<endl;cin>>s1>>s2>>s3;d.setNumber(s3);
         a.setNumber(s1);b.setNumber(s2);c=(a*b)%d;cout<<endl<<c.getNumber();break;
         case 3:cout<<"Enter two numbers"<<endl;cin>>s1>>s2;
         a.setNumber(s1);b.setNumber(s2);c=gcd(a,b);cout<<endl<<c.getNumber();break;
         case 4:cout<<"enter two numbers in format ab (calculates inverse of a mod b"<<endl;cin>>s1>>s2;
         a.setNumber(s1);b.setNumber(s2);c=inverse(a,b);cout<<endl<<c.getNumber();break;
         case 5:cout<<"enter three numbers in order:base,exponentiation,modulus"<<endl;cin>>s1>>s2>>s3;
         a.setNumber(s1);b.setNumber(s2);c.setNumber(s3);d=emodulus(a,b,c);cout<<endl<<d.getNumber();break;
         case 6:cout<<"enter your three numbers"<<endl;cin>>s1>>s2>>s3;
          a.setNumber(s1);b.setNumber(s2);c.setNumber(s3);d=bruteLog(a,b,c);cout<<endl<<d.getNumber();break;
         case 7:cout<<"enter your message";cin>>s1;a=keyGeneration();
         l=s1.length();z=0;y=0;
         while(z+5<l)
         {
             t[y]=s1.substr(z,5);z+=5;y++;
         }
         if(l%5!=0){t[y]=s1.substr(z,l-z);}u=0;
         while(u<(l/5)+1){c=encryption(t[u],a);t1[u]=c.getNumber();u++;}u=0;
         while(u<(l/5)+1){c=decryption(t1[u],a);t2[u]=c.getNumber();u++;}u=0;cout<<"encrpyted message: ";
         while(u<(l/5)+1) {cout<<t1[u];u++;}cout<<endl;u=0;cout<<"decrypted message: ";
         while(u<(l/5)+1) {cout<<t2[u];u++;}                    break;
         case 8:cout<<endl<<"enter choice:"<<endl<<"1.)addition"<<endl<<" 2.)multiplication";cin>>o;
         if(o==1){cout<<endl<<"enter numbers"<<endl;cin>>s1>>s2;cout<<addBin(s1,s2)<<endl;}else{cout<<endl<<"enter numbers"<<endl;cin>>s1>>s2;cout<<multiplyBin(s1,s2)<<endl;}
     }
   }while(true);

}
