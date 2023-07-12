#pragma once
#ifndef _HydStatic_GzQP2_Header
#define _HydStatic_GzQP2_Header

#include <HydStatic_GzQ.hxx>

namespace tnbLib
{

	class HydStatic_GzQP2
		: public HydStatic_GzQ
	{

		/*Private Data*/

		Standard_Real theParameter0_;
		Standard_Real theParameter1_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<HydStatic_GzQ>(*this);
			ar & theParameter0_;
			ar & theParameter1_;
		}

	public:

		HydStatic_GzQP2()
		{}

		HydStatic_GzQP2
		(
			const Standard_Real theHeel,
			const Standard_Real theArm, 
			const Standard_Real theParam0,
			const Standard_Real theParam1
		)
			: HydStatic_GzQ(theHeel, theArm)
			, theParameter0_(theParam0)
			, theParameter1_(theParam1)
		{}


		//- public functions and operators

		TnbHydStatic_EXPORT std::shared_ptr<HydStatic_GzQ> Mirrored(const Pnt2d& theO) const override;

		TnbHydStatic_EXPORT std::shared_ptr<HydStatic_GzQ> Mirrored(const gp_Ax2d& theAx) const override;

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter0)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter1)
	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_GzQP2);

#endif // !_HydStatic_GzQP2_Header
