#pragma once
#ifndef _SectPx_FixedKnots_Header
#define _SectPx_FixedKnots_Header

#include <SectPx_KnotVector.hxx>

namespace tnbLib
{

	class SectPx_FixedKnots
		: public SectPx_KnotVector
	{

		/*Private Data*/

		std::vector<Standard_Real> theKnots_;


		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_KnotVector>(*this);
			ar & theKnots_;
		}

	protected:

		SectPx_FixedKnots()
		{}

	public:

		SectPx_FixedKnots(const std::vector<Standard_Real>& theKnots)
			: theKnots_(theKnots)
		{}

		SectPx_FixedKnots(std::vector<Standard_Real>&& theKnots)
			: theKnots_(std::move(theKnots))
		{}

		const auto& Knots() const
		{
			return theKnots_;
		}

		auto& KnotsRef()
		{
			return theKnots_;
		}

		std::vector<Standard_Real> 
			CreateKnots
			(
				const std::vector<Pnt2d>& theCoords,
				const Standard_Integer degree
			) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_FixedKnots);

#endif // !_SectPx_FixedKnots_Header
