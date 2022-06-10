#pragma once
#ifndef _Mesh_CurveOptmPoint_Correction_Base_Header
#define _Mesh_CurveOptmPoint_Correction_Base_Header

#include <Global_Done.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>

namespace tnbLib
{

	class Mesh_CurveOptmPoint_Correction_Base
	{

	public:

		typedef Mesh_CurveOptmPoint_Correction_Info info;

	private:

		/*Private Data*/

		Standard_Real theU0_;
		Standard_Real theGuess_;

		Standard_Real theCorrected_;
		Standard_Real theLen_;

		const info& theInfo_;

	protected:


		// default constructor [1/16/2022 Amir]


		// constructors [1/16/2022 Amir]

		Mesh_CurveOptmPoint_Correction_Base
		(
			const Standard_Real theU0,
			const Standard_Real theGuess,
			const info& theInfo
		)
			: theU0_(theU0)
			, theGuess_(theGuess)
			, theInfo_(theInfo)
			, theCorrected_(0)
			, theLen_(1.0)
		{}

		auto& ChangeCorrected()
		{
			return theCorrected_;
		}

	public:


		// public functions and operators [1/16/2022 Amir]

		const auto& Info() const
		{
			return theInfo_;
		}

		auto Corrected() const
		{
			return theCorrected_;
		}

		//- macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, U0)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Guess)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Len)
	};
}

#endif // !_Mesh_CurveOptmPoint_Correction_Base_Header
