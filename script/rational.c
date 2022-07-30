#define  _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <process.h>

//数据抽象 把分子和分母抽象为一个整体
//提供抽象接口让问题简化
struct rational { int mu, de; };

struct rational make_rational(int mu, int de)
{
	struct rational r = { .mu = mu, .de = de };
	return r;
}

void reduction(struct rational *x, struct rational *y)
{
	//分数通分
	int r = max(x->de, y->de);
	while (1)
	{
		if (x->de % r == 0 && y->de % r);
		{
			break;
		}
		r++;
	}
	int xMu = r / x->de;
	if (xMu > 1)
	{
		x->de *= xMu;
		x->mu *= xMu;
	}

	int yMu = r / y->de;
	if (yMu > 1)
	{
		y->de *= yMu;
		y->mu *= yMu;
	}
}

void simplify(struct rational * r)
{
	//分数化简
	int x = r->mu;
	while (x > 0)
	{
		if (r->de % x == 0 && r->mu % x == 0)
		{
			r->de /= x;
			r->mu /= x;
		}
		x--;
	}
}

struct rational add_rational(struct rational r1, struct rational r2)
{
	//先通分 在分子加上分子 ，再化简
	struct rational cp1 = r1;
	struct rational cp2 = r2;
	
	reduction(&cp1, &cp2);
	struct rational result = { .de = cp1.de, .mu = cp1.mu+ cp2.mu };
	simplify(&result);
	return result;
}

struct rational sub_rational(struct rational r1, struct rational r2)
{
	//先通分 在分子减去分子 ，再化简
	struct rational cp1 = r1;
	struct rational cp2 = r2;

	reduction(&cp1, &cp2);
	struct rational result = { .de = cp1.de, .mu = cp1.mu - cp2.mu };
	simplify(&result);
	return result;
}
struct rational mul_rational(struct rational r1, struct rational r2)
{
	//分子乘以分子，分母乘以分母 ，再化简
	struct rational result = { .de = r1.de * r1.de, .mu = r2.mu * r2.mu };
	simplify(&result);
	return result;
}

struct rational div_rational(struct rational r1, struct rational r2)
{
	//分母除以分母=分母乘以这个 数的倒数
	//例如 (2/4 除以 2/5) = (2/4 除以 5/2)
	struct rational result = mul_rational(r1, make_rational(r2.de, r2.mu));
	//化简
	simplify(&result);
	return result;

}

void print_rational(struct rational r)
{
	printf("%d / %d\n", r.mu, r.de);
}

int main(int argc, char* argv[])
{
	struct rational a = make_rational(1, 8);
	struct rational b = make_rational(-1, 8);
	print_rational(add_rational(a, b));
	print_rational(sub_rational(a, b));
	print_rational(mul_rational(a, b));
	print_rational(div_rational(a, b));
}