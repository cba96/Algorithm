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
	// ������
	CPolynomialNode(double _coefficient = 0, int _exponent = 0)
	{
		_link = NULL;
		SetCoefficient(_coefficient);
		SetExponent(_exponent);
	}

	// �Ҹ���
	~CPolynomialNode();

	// ���� ����� ����� �������� �Լ�
	double GetCoefficient()
	{
		return _coefficient;
	}

	// ���� ����� ������ �������� �Լ�
	int GetExponent()
	{
		return _exponent;
	}

	// ���� ����� ����� �����ϴ� �Լ�
	void SetCoefficient(double dCoefficient)
	{
		_coefficient = dCoefficient;
	}

	// ���� ����� ������ �����ϴ� �Լ�
	void SetExponent(int nExponent)
	{
		_exponent = nExponent;
	}

	// ���� ���� ������ ���� ��带 �������� �Լ�
	CPolynomialNode* GetNext()
	{
		return _link;
	}

	// ������ �����ε��� �̿��Ͽ� ���׽� ����
	CPolynomialNode operator+(CPolynomialNode &_rightHand);			// ����
	CPolynomialNode operator-(CPolynomialNode &_rightHand);			// ����
	CPolynomialNode operator-();									// ��ȣ����
	CPolynomialNode operator*(CPolynomialNode &_rightHand);			// ����
	CPolynomialNode operator/(CPolynomialNode &_rightHand);			// ������

	void Rearrange();									// ���� ������ (������ ���� �������� ����)
	void DeleteAllNode();

	// �ְ������� ����� ������
	// - Rearrange() �Լ����� ���
	int GetHighestExponent();

	// ���ο� ���� �߰�
	void AddNode(double _coefficient, int _exponent);

	// ���� ���
	void PrintOut();

	// x���� �����Ͽ� ���
	double Evaluate(double x);

private:
	double _coefficient;
	int _exponent;

	CPolynomialNode *_link;
};

void ToyTest();

void RealTest();

void ShowComputationResults(CPolynomialNode p, CPolynomialNode q, int valueOf);
