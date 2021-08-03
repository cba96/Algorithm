#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>	// Memory Leak Problem: _CrtDumpMemoryLeaks();

#include <iostream>
#include <math.h>
#include "polynomial.h"

using namespace std;

int main(void)
{
	// 연습용 (문제의 예제)
	ToyTest();

	cout << endl << endl;

	// 실전용
	RealTest();

	// Check Memory Leak Problem
	_CrtDumpMemoryLeaks();

	return 0;
}

/******************************************************************************
	테스트 함수
******************************************************************************/
void ToyTest()
{
	cout << "For the toy test,..." << endl;
	// For Toy Test,...
	CPolynomialNode a(2, 2);
	a.AddNode(-2, 0);
	a.Rearrange();

	CPolynomialNode b(1, 1);
	b.AddNode(1, 0);
	b.Rearrange();

	ShowComputationResults(a, b, 5);

	a.DeleteAllNode();
	b.DeleteAllNode();
}

void RealTest()
{
	cout << "For the actual test in the other book,..." << endl;

	// For actual test in the other book,...
	CPolynomialNode p(-3, 5);
	p.AddNode(-1, 7);
	p.AddNode(9, 1);
	p.AddNode(15, 0);
	p.AddNode(2, 2);
	p.Rearrange();

	CPolynomialNode q(6, 0);
	q.AddNode(-2, 5);
	q.AddNode(3, 3);
	q.AddNode(-4, 2);
	q.Rearrange();

	ShowComputationResults(p, q, 3);

	p.DeleteAllNode();
	q.DeleteAllNode();
}

void ShowComputationResults(CPolynomialNode p, CPolynomialNode q, int valueOf)
{
	// Display two equations,...
	cout << "Input data:" << endl;
	cout << "===========" << endl;

	cout << "1st polynomial equation (A):\t";
	p.PrintOut();
	cout << endl;

	cout << "2nd polynomial equation (B):\t";
	q.PrintOut();
	cout << endl;

	// Show results of computations,...
	cout << endl << endl;
	cout << "Results:" << endl;
	cout << "========" << endl;

	// operator+
	cout << "1. Addition (A + B):\t\t";
	(p + q).PrintOut();
	cout << endl;

	// operator~
	cout << "2. Negation (-B):\t\t";
	(-q).PrintOut();
	cout << endl;

	// operator- ==> p + (-q)
	cout << "3. Subtraction (A - B):\t\t";
	(p - q).PrintOut();
	cout << endl;

	// operator*
	cout << "4. Multiplication (A * B):\t";
	(p * q).PrintOut();
	cout << endl;

	// operator/
	cout << "5. Division (A / B):\t\t";
	(p / q).PrintOut();
	cout << endl;

	// Evaluations,...
	cout << "6-1. Evaluation A(" << valueOf << "): " << p.Evaluate(valueOf) << endl;
	cout << "6-2. Evaluation B(" << valueOf << "): " << q.Evaluate(valueOf) << endl;
}

/******************************************************************************
	기본 함수
******************************************************************************/
int CPolynomialNode::GetHighestExponent()
{
	CPolynomialNode *poly = this;
	int nExponent = 0;

	while (poly != NULL)
	{
		if (nExponent < poly->GetExponent())
		{
			nExponent = poly->GetExponent();
		}

		poly = poly->GetNext();
	}

	return nExponent;
}

void CPolynomialNode::AddNode(double _coefficient, int _exponent)
{
	if (this->_link == NULL)
	{
		if (this->GetCoefficient() == 0 && this->GetExponent() == 0)
		{
			this->SetCoefficient(_coefficient);
			this->SetExponent(_exponent);
			return;
		}

		CPolynomialNode *newNode = new CPolynomialNode(_coefficient, _exponent);
		this->_link = newNode;
	}
	else
	{
		CPolynomialNode *temp = this;

		if (temp->GetCoefficient() == 0 && temp->GetExponent() == 0)
		{
			temp->SetCoefficient(_coefficient);
			temp->SetExponent(_exponent);
			return;
		}

		while (temp->_link != NULL)
		{
			// 포인터를 삽입 가능한 마지막 노드(NULL)로 이동
			temp = temp->GetNext();
		}

		CPolynomialNode *newNode = new CPolynomialNode(_coefficient, _exponent);
		temp->_link = newNode;
	}
}

void CPolynomialNode::PrintOut()
{
	CPolynomialNode *temp = this;
	double dCoefficent = 0;
	int nExponent = 0;

	dCoefficent = temp->GetCoefficient();
	nExponent = temp->GetExponent();

	do
	{
		if (dCoefficent == 0)
		{
			// 0이므로 생략
		}
		else if (nExponent == 0)
		{
			cout << dCoefficent;
		}
		else
		{
			if (dCoefficent == -1)
			{
				cout << "-";
			}
			else if (dCoefficent == 1)
			{
				// 1 생략
			}
			else
			{
				cout << dCoefficent;
			}

			cout << "x";

			if (nExponent != 1)
			{
				cout << "^" << nExponent;
			}
		}

		if (temp->_link == NULL)
		{
			break;
		}
		else
		{
			temp = temp->GetNext();

			dCoefficent = temp->GetCoefficient();
			nExponent = temp->GetExponent();

			if (dCoefficent < 0)
			{
				cout << " - ";
				dCoefficent *= -1;
			}
			else
			{
				cout << " + ";
			}
		}

	} while (true);
}

void CPolynomialNode::DeleteAllNode()
{
	CPolynomialNode	*head = this;
	head->SetCoefficient(0);
	head->SetExponent(0);

	head = head->GetNext();
	while (head != NULL)
	{
		CPolynomialNode *nextNode = head->GetNext();
		delete head;
		head = nextNode;
	}

	delete head;
	this->_link = NULL;
}

void CPolynomialNode::Rearrange()
{
	CPolynomialNode *poly = this;

	int nHighestExponent = this->GetHighestExponent();
	double *dArrCoefficients = new double[nHighestExponent + 1];

	for (int i = 0; i < nHighestExponent + 1; i++)
	{
		dArrCoefficients[i] = 0;
	}

	while (poly != NULL)
	{
		dArrCoefficients[poly->GetExponent()] += poly->GetCoefficient();
		poly = poly->GetNext();
	}

	this->DeleteAllNode();

	for (int i = nHighestExponent; i >= 0; i--)
	{
		if (dArrCoefficients[i] != 0)
		{
			this->AddNode(dArrCoefficients[i], i);
		}
	}

	delete[] dArrCoefficients;
}

double CPolynomialNode::Evaluate(double x)
{
	CPolynomialNode *poly = this;
	double result = 0;

	while (poly != NULL)
	{
		result += poly->GetCoefficient() * pow(x, poly->GetExponent());
		poly = poly->GetNext();
	}

	return result;
}

/******************************************************************************
	연산자 오버로딩
******************************************************************************/
CPolynomialNode CPolynomialNode::operator+(CPolynomialNode &_rightHand)
{
	CPolynomialNode resultPoly;
	CPolynomialNode *leftHand = this;
	CPolynomialNode *rightHand = &_rightHand;

	while (leftHand != NULL && rightHand != NULL)
	{
		if (leftHand->_exponent == rightHand->GetExponent())
		{
			resultPoly.AddNode(leftHand->_coefficient +  rightHand->GetCoefficient(), leftHand->_exponent);
			leftHand = leftHand->GetNext();
			rightHand = rightHand->GetNext();
		}
		else if (leftHand->_exponent > rightHand->GetExponent())
		{
			resultPoly.AddNode(leftHand->_coefficient, leftHand->_exponent);
			leftHand = leftHand->GetNext();
		}
		else
		{
			resultPoly.AddNode(rightHand->_coefficient, rightHand->_exponent);
			rightHand = rightHand->GetNext();
		}
	}

	// 마지막 부분 처리
	if (leftHand != NULL)
	{
		resultPoly.AddNode(leftHand->_coefficient, leftHand->_exponent);
		leftHand = leftHand->GetNext();
	}

	if (rightHand != NULL)
	{
		resultPoly.AddNode(rightHand->_coefficient, rightHand->_exponent);
		rightHand = rightHand->GetNext();
	}

	// Assertion
	if (leftHand != NULL && rightHand != NULL)
	{
		// 절대 발생하지 않는 코드
		throw new exception();
	}

	resultPoly.Rearrange();

	return resultPoly;
}

CPolynomialNode CPolynomialNode::operator-(CPolynomialNode &_rightHand)
{
	return *this + -_rightHand;
}

CPolynomialNode CPolynomialNode::operator-()
{
	CPolynomialNode resultPoly;
	CPolynomialNode *poly = this;

	while (poly != NULL)
	{
		resultPoly.AddNode(poly->GetCoefficient() * -1, poly->GetExponent());
		poly = poly->GetNext();
	}

	resultPoly.Rearrange();

	return resultPoly;
}

CPolynomialNode CPolynomialNode::operator*(CPolynomialNode &_rightHand)
{
	CPolynomialNode resultPoly;
	CPolynomialNode *leftHand = this;
	CPolynomialNode *rightHand = &_rightHand;

	while (leftHand != NULL)
	{
		double coefficient = leftHand->_coefficient;
		int exponent = leftHand->_exponent;

		while (rightHand != NULL)
		{
			resultPoly.AddNode(coefficient * rightHand->GetCoefficient(), exponent + rightHand->_exponent);
			rightHand = rightHand->GetNext();
		}

		rightHand = &_rightHand;
		leftHand = leftHand->GetNext();
	}

	// Assertion
	if (leftHand != NULL && rightHand != NULL)
	{
		// 절대 발생하지 않는 코드
		throw new exception();
	}

	resultPoly.Rearrange();

	return resultPoly;
}

CPolynomialNode CPolynomialNode::operator/(CPolynomialNode &_rightHand)
{
	CPolynomialNode *leftHand = this;
	CPolynomialNode *rightHand = &_rightHand;

	if (leftHand != NULL && rightHand != NULL)
	{
		if (leftHand->GetExponent() < rightHand->GetExponent())
		{
			return CPolynomialNode();
		}
		else if (leftHand->GetExponent() == rightHand->GetExponent())
		{ // 최고차항의 차수가 같으면,...
			return CPolynomialNode(leftHand->GetCoefficient() / rightHand->GetCoefficient());
		}
		else
		{
			CPolynomialNode resultPoly;
			CPolynomialNode interimPoly = *leftHand;

			int nRightExponent = rightHand->GetExponent();
			double dRightCoefficient = rightHand->GetCoefficient();

			while (interimPoly.GetExponent() >= nRightExponent)
			{
				double dDivide = interimPoly.GetCoefficient() / dRightCoefficient;
				int nInterimExponent = interimPoly.GetExponent();
				CPolynomialNode polyNode(dDivide, nInterimExponent - nRightExponent);
				interimPoly = interimPoly - (*rightHand * polyNode);
				resultPoly.AddNode(dDivide, nInterimExponent - nRightExponent);
			}

			resultPoly.Rearrange();

			return resultPoly;
		}
	}
	else
	{
		return CPolynomialNode();
	}
}

CPolynomialNode::~CPolynomialNode()
{
	// DeleteAllNode()로 대체 처리
}
