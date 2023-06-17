#pragma once
#ifndef _PtdShapeFit2d_Airfoil_Header
#define _PtdShapeFit2d_Airfoil_Header

#include <PtdShapeFit_Section.hxx>

namespace tnbLib
{

	// Forward Declarations [4/25/2023 Payvand]

	class Cad2d_Plane;
	class Pln_Curve;

	class PtdShapeFit2d_Airfoil
		: public PtdShapeFit_Section
	{

		/*Private Data*/

		// Private functions and operators [4/29/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<PtdShapeFit_Section>(*this);
		}

	protected:

		// default constructor [4/25/2023 Payvand]

		PtdShapeFit2d_Airfoil()
		{}


	public:

		struct UpperCurve
		{
			const std::shared_ptr<Pln_Curve> curve;
		};

		struct LowerCurve
		{
			const std::shared_ptr<Pln_Curve> curve;
		};

		// Public functions and operators [4/25/2023 Payvand]

		static std::tuple<std::shared_ptr<UpperCurve>, std::shared_ptr<LowerCurve>>
			RetrieveAirfoilGeometry(const Cad2d_Plane&);

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_Airfoil);

#endif // !_PtdShapeFit2d_Airfoil_Header
