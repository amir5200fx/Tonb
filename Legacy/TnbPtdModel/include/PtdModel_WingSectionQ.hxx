#pragma once
#ifndef _PtdModel_WingSectionQ_Header
#define _PtdModel_WingSectionQ_Header

#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_WingSectionQ
	{

	public:

		struct UpperFace
		{
			std::vector<Pnt2d> Points;

			//- default constructor
			UpperFace()
			{}

			//- constructors

			UpperFace(std::vector<Pnt2d>&&);
		};

		struct LowerFace
		{
			std::vector<Pnt2d> Points;

			//- default constructor
			LowerFace()
			{}

			//- constructors

			LowerFace(std::vector<Pnt2d>&&);
		};

	private:

		/*Private Data*/

		UpperFace theUpper_;
		LowerFace theLower_;

	public:

		//- default constructor

		PtdModel_WingSectionQ()
		{}


		//- constructors

		inline PtdModel_WingSectionQ(const UpperFace& theUpper, const LowerFace& theLower);
		inline PtdModel_WingSectionQ(UpperFace&& theUpper, LowerFace&& theLower);


		//- public functions and operators

		const auto& Upper() const
		{
			return theUpper_;
		}

		const auto& Lower() const
		{
			return theLower_;
		}

		inline void SetUpper(const UpperFace&);
		inline void SetLower(const LowerFace&);
		inline void SetUpper(UpperFace&&);
		inline void SetLower(LowerFace&&);

	};
}

#include <PtdModel_WingSectionQI.hxx>

#endif // !_PtdModel_WingSectionQ_Header
