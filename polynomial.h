/******************************************************************************
	Data Structure
	Programming Assignment #1
															T.A. Kyunglag Kwon
	
	Polynomials by using Linked List
	- add, subtract, multiply, divide, valueOf
******************************************************************************/

class CPolynomialNode
{
public:
	// 생성자
	CPolynomialNode(double _coefficient = 0, int _exponent = 0)
	{
		_link = NULL;
		SetCoefficient(_coefficient);
		SetExponent(_exponent);
	}

	// 소멸자
	~CPolynomialNode();

	// 현재 노드의 계수를 가져오는 함수
	double GetCoefficient()
	{
		return _coefficient;
	}

	// 현재 노드의 지수를 가져오는 함수
	int GetExponent()
	{
		return _exponent;
	}

	// 현재 노드의 계수를 설정하는 함수
	void SetCoefficient(double dCoefficient)
	{
		_coefficient = dCoefficient;
	}

	// 현재 노드의 지수를 설정하는 함수
	void SetExponent(int nExponent)
	{
		_exponent = nExponent;
	}

	// 다음 항의 정보를 가진 노드를 가져오는 함수
	CPolynomialNode* GetNext()
	{
		return _link;
	}

	// 연산자 오버로딩을 이용하여 다항식 연산
	CPolynomialNode operator+(CPolynomialNode &_rightHand);			// 덧셈
	CPolynomialNode operator-(CPolynomialNode &_rightHand);			// 뺄셈
	CPolynomialNode operator-();									// 부호변경
	CPolynomialNode operator*(CPolynomialNode &_rightHand);			// 곱셈
	CPolynomialNode operator/(CPolynomialNode &_rightHand);			// 나눗셈

	void Rearrange();									// 수식 재정렬 (차수에 맞춰 내림차순 정렬)
	void DeleteAllNode();

	// 최고차항의 계수를 가져옴
	// - Rearrange() 함수에서 사용
	int GetHighestExponent();

	// 새로운 항을 추가
	void AddNode(double _coefficient, int _exponent);

	// 수식 출력
	void PrintOut();

	// x값에 대입하여 계산
	double Evaluate(double x);

private:
	double _coefficient;
	int _exponent;

	CPolynomialNode *_link;
};

void ToyTest();

void RealTest();

void ShowComputationResults(CPolynomialNode p, CPolynomialNode q, int valueOf);
