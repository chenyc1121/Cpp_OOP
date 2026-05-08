#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
// 在此处补充你的代码
	char num[220];//倒序存储数据
	public:
		CHugeInt(int n){
			int k=0;
			if(n==0){
				num[k]='0';
				num[k+1]='\0';
				return;
			}
			while(n){
				num[k]=n%10+'0';
				k++;
				n/=10;
			}
			num[k]='\0';
		}
		CHugeInt(char * s){
			int len=strlen(s);
			for(int i=0,k=len-1;i<len;i++,k--){
				num[i]=s[k];
			}
			num[len]='\0';
		}
		CHugeInt operator+(const CHugeInt& b) const {
			CHugeInt res(0);
			int i = 0, carry = 0;
			int lenA = strlen(num);
			int lenB = strlen(b.num);
			
			while (i < lenA || i < lenB || carry) {
				int v1 = (i < lenA) ? (num[i] - '0') : 0;
				int v2 = (i < lenB) ? (b.num[i] - '0') : 0;
				int sum = v1 + v2 + carry;
				res.num[i] = (sum % 10) + '0';
				carry = sum / 10;
				i++;
			}
			res.num[i] = '\0';
			return res;
		}
		friend CHugeInt operator+(int n,const CHugeInt & other){
			return other+n;
		}
		CHugeInt & operator+=(int n){
			*this= *this+n;
			return *this;
		}
		CHugeInt & operator++(){
			*this+=1;
			return *this;
		}
		CHugeInt operator++(int){
			CHugeInt old=*this;
			*this+=1;
			return old;
		}
		friend ostream & operator<<(ostream & out,const CHugeInt & other){
			int len=strlen(other.num);
			for(int i=len-1;i>=0;i--){
				out<<other.num[i];
			}
			return out;
		}

};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}