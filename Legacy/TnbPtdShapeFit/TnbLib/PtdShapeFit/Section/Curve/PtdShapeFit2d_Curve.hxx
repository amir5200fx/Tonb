#pragma once
#ifndef _PtdShapeFit2d_Curve_Header
#define _PtdShapeFit2d_Curve_Header

#include <PtdShapeFit_Section.hxx>

namespace tnbLib
{

	// Forward Declarations [5/5/2023 Payvand]

	class Pln_Curve;

	class PtdShapeFit2d_Curve
		: public PtdShapeFit_Section
	{

		/*Private Data*/


		// Private functions and operators [5/5/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<PtdShapeFit_Section>(*this);
		}

	protected:

		// default constructor [5/5/2023 Payvand]

		PtdShapeFit2d_Curve()
		{}

		// constructors [5/5/2023 Payvand]

	public:

		struct UpperCurve
		{
			const std::shared_ptr<Pln_Curve> curve;
		};

		struct LowerCurve
		{
			const std::shared_ptr<Pln_Curve> curve;
		};


		// Public functions and operators [5/5/2023 Payvand]

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_Curve);

#endif // !_PtdShapeFit2d_Curve_Header
