#pragma once
#ifndef _PtdModel_BladeSection_Header
#define _PtdModel_BladeSection_Header

#include <Pnt3d.hxx>
#include <PtdModel_Module.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_BladeSection
	{

		/*Private Data*/

		std::vector<Pnt3d> theFace_;
		std::vector<Pnt3d> theBack_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	protected:

		//- default constructor

		PtdModel_BladeSection()
		{}

		//- constructors

		TnbPtdModel_EXPORT PtdModel_BladeSection
		(
			const std::vector<Pnt3d>& theFace, 
			const std::vector<Pnt3d>& theBack
		);

		TnbPtdModel_EXPORT PtdModel_BladeSection
		(
			std::vector<Pnt3d>&& theFace,
			std::vector<Pnt3d>&& theBack
		);

	public:

		virtual ~PtdModel_BladeSection()
		{}


		//- public functions and operators

		inline Standard_Integer NbSpans() const;

		const auto& Face() const
		{
			return theFace_;
		}

		const auto& Back() const
		{
			return theBack_;
		}

		inline void SetFace(std::vector<Pnt3d>&&);
		inline void SetBack(std::vector<Pnt3d>&&);
	};
}

#include <PtdModel_BladeSectionI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_BladeSection);

#endif // !_PtdModel_BladeSection_Header
