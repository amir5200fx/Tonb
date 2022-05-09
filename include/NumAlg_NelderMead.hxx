#pragma once
#ifndef _NumAlg_NelderMead_Header
#define _NumAlg_NelderMead_Header

#include <NumAlg_NelderMeadCoeffs.hxx>
#include <NumAlg_NelderMeadInfo.hxx>

#include <memory>

namespace tnbLib
{


	template<class Function>
	struct NumAlg_NelderMead_Cache
	{

	protected:

		typedef typename Function::varType varType;

		Standard_Integer Lo;  // best vertex
		Standard_Integer Hi;  // worst vertex;

		Standard_Integer Li; // after the best vertex
		Standard_Integer Ho; // after the worst vertex

		Standard_Real YR;
		Standard_Real YE;
		Standard_Real YC;

		varType M;
		varType E;
		varType R;
		varType C;
	};

	template<class Function>
	class NumAlg_NelderMead
		: public NumAlg_NelderMead_Cache<Function>
		, public NumAlg_NelderMeadCoeffs
		, public Function
	{

	public:

		typedef typename Function::varType varType;
		typedef Function fun;
		typedef NumAlg_NelderMead_Cache<Function> cache;
		typedef NumAlg_NelderMeadCoeffs coeff;

	private:

		/*Private Data*/

		varType theVariables_[fun::dim + 1];
		Standard_Real theY_[fun::dim + 1];

		Standard_Boolean IsConv;

		std::shared_ptr<NumAlg_NelderMeadInfo> theInfo_;

		// private functions and operators [5/6/2022 Amir]

		varType& ChangeVariable(const int theIndex)
		{
			return theVariables_[theIndex];
		}

		auto& ChangeY(const int theIndex)
		{
			return theY_[theIndex];
		}

		Standard_Real Size() const;

		void Order();
		void NewPoints();
		void Shrink();
		void Replace();
		void Improve();

	public:

		// default constructor [5/6/2022 Amir]

		NumAlg_NelderMead()
			: IsConv(Standard_False)
		{}


		// constructors [5/6/2022 Amir]


		// public functions and operators [5/6/2022 Amir]

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		auto NbVariables() const
		{
			return (Standard_Integer)Function::nbVariables;
		}

		auto IsConverged() const
		{
			return IsConv;
		}

		const auto& Variable(const int theIndex) const
		{
			return theVariables_[theIndex];
		}

		auto Y(const int theIndex) const
		{
			return theY_[theIndex];
		}

		auto MinY() const
		{
			return theY_[cache::Lo];
		}

		const auto& BestVertex() const
		{
			return Variable(cache::Lo);
		}

		void Perform();

		void SetInfo(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#include <NumAlg_NelderMeadI.hxx>

#endif // !_NumAlg_NelderMead_Header
