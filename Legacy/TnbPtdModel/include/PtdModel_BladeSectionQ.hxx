#pragma once
#ifndef _PtdModel_BladeSectionQ_Header
#define _PtdModel_BladeSectionQ_Header

#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_BladeSectionQ
	{

		/*Private Data*/

		std::vector<Pnt2d> theBack_;
		std::vector<Pnt2d> theFace_;

	public:

		//- default constructor

		PtdModel_BladeSectionQ()
		{}


		//- constructors

		PtdModel_BladeSectionQ
		(
			const std::vector<Pnt2d>& theBack,
			const std::vector<Pnt2d>& theFace
		)
			: theBack_(theBack)
			, theFace_(theFace)
		{}

		PtdModel_BladeSectionQ
		(
			std::vector<Pnt2d>&& theBack,
			std::vector<Pnt2d>&& theFace
		)
			: theBack_(std::move(theBack))
			, theFace_(std::move(theFace))
		{}


		//- public functions and operators

		const auto& Back() const
		{
			return theBack_;
		}

		const auto& Face() const
		{
			return theFace_;
		}

		inline void SetBack(const std::vector<Pnt2d>&);
		inline void SetBack(std::vector<Pnt2d>&&);
		inline void SetFace(const std::vector<Pnt2d>&);
		inline void SetFace(std::vector<Pnt2d>&&);
	};
}

#include <PtdModel_BladeSectionQI.hxx>

#endif // !_PtdModel_BladeSectionQ_Header
