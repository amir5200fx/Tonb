#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class FrontType, class SizeFun>
inline void tnbLib::Aft_OptNode<FrontType, SizeFun, void, void, void>::Perform()
{
#ifdef _DEBUG
	if (NOT this->Front())
	{
		FatalErrorIn(FunctionSIG)
			<< "no front entity has been found!" << endl
			<< abort(FatalError);
	}

	if (NOT this->MetricMap())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric map has been found!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	if (this->Size() <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid element size has been detected" << endl
			<< abort(FatalError);
	}

	analyOptNodeCalc alg(this->Size(), *this->Front());
	alg.Perform();
	Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

	this->ChangeCoord() = alg.Coord();
	this->Change_IsDone() = Standard_True;
}