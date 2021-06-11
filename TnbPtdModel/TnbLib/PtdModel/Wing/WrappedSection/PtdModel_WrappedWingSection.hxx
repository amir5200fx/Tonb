#pragma once
#ifndef _PtdModel_WrappedWingSection_Header
#define _PtdModel_WrappedWingSection_Header

#include <Pnt3d.hxx>
#include <PtdModel_AirfoilSectionQ.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_WrappedWingSection
		: public PtdModel_AirfoilSectionQ<Pnt3d>
	{

		typedef PtdModel_AirfoilSectionQ<Pnt3d> base;

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<PtdModel_AirfoilSectionQ<Pnt3d>>(*this);
		}

	public:

		//- default constructor

		PtdModel_WrappedWingSection()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_WrappedWingSection
		(
			const std::vector<Pnt3d>& theFace,
			const std::vector<Pnt3d>& theBack
		);

		TnbPtdModel_EXPORT PtdModel_WrappedWingSection
		(
			std::vector<Pnt3d>&& theFace,
			std::vector<Pnt3d>&& theBack
		);

	public:


		//- public functions and operators

		inline Standard_Integer NbSpans() const;

		const auto& Face() const
		{
			return base::FaceQ().Points;
		}

		const auto& Back() const
		{
			return base::BackQ().Points;
		}

		inline void SetFace(std::vector<Pnt3d>&&);
		inline void SetBack(std::vector<Pnt3d>&&);

	};
}

#include <PtdModel_WrappedWingSectionI.hxx>

#endif // !_PtdModel_WrappedWingSection_Header
