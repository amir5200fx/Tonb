#pragma once
#ifndef _Mesh_CurveOptmPoint_BisectCorrection_Base_Header
#define _Mesh_CurveOptmPoint_BisectCorrection_Base_Header

#include <Global_Done.hxx>
#include <Mesh_CurveEntity.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>

#include <memory>

namespace tnbLib
{

	class Mesh_CurveOptmPoint_BisectCorrection_Base
	{

	public:

		typedef NumAlg_BisectionSolver_Info info;

	private:

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theGuess0_;
		Standard_Real theGuess1_;

		Standard_Real theCorrected_;
		Standard_Real theLen_;

		const std::shared_ptr<info>& theInfo_;


	protected:

		// default constructor [6/8/2022 Amir]


		// constructors [6/8/2022 Amir]

		Mesh_CurveOptmPoint_BisectCorrection_Base
		(
			const Standard_Real theU0,
			const Standard_Real theGuess0,
			const Standard_Real theGuess1,
			const std::shared_ptr<info>& theInfo
		)
			: theU0_(theU0)
			, theGuess0_(theGuess0)
			, theGuess1_(theGuess1)
			, theInfo_(theInfo)
			, theCorrected_(0)
			, theLen_(1.0)
		{}


		auto& CorrectedRef()
		{
			return theCorrected_;
		}

	public:


		// public functions and operators [6/8/2022 Amir]

		auto U0() const
		{
			return theU0_;
		}

		auto Guess0() const
		{
			return theGuess0_;
		}

		auto Guess1() const
		{
			return theGuess1_;
		}

		auto Len() const
		{
			return theLen_;
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		auto Corrected() const
		{
			return theCorrected_;
		}

		void SetLen(const Standard_Real x)
		{
			theLen_ = x;
		}
	};
}


#endif // !_Mesh_CurveOptmPoint_BisectCorrection_Base_Header
