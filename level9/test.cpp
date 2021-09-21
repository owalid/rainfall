#include <iostream>

class F
{
public:
	int nb;
	int nb2;

	F(int nb)
	{
		this->nb = nb;
		this->nb2 = nb;
	}

	int modify(int nb2)
	{
		this->nb = nb2 + 5;
		return this->nb;
	}
};

int main() {
	F *f;
	f = new F(50);
	f->modify(40);
    std::cout << f->nb;
    return 0;
}
