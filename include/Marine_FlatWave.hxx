#pragma once
#ifndef _Marine_FlatWave_Header
#define _Marine_FlatWave_Header

#include <Marine_Wave.hxx>

namespace tnbLib
{

	class Marine_FlatWave
		: public Marine_Wave
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_Wave>(*this);
		}

		TnbMarine_EXPORT void MakeProfileCurve(const Pnt2d& x0, const Pnt2d& x1) override;

	protected:

		//- default constructor

		Marine_FlatWave()
		{}

		TnbMarine_EXPORT Dir3d SurfaceDirection() const override;

	public:


		//- constructor

		Marine_FlatWave(const std::shared_ptr<Marine_Domain>& theDomain)
			: Marine_Wave(theDomain)
		{}


		//- public functions and operators

		Standard_Real Z() const override
		{
			return PointOnWater().Z();
		}

		static void dummy()
		{}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_FlatWave);

#endif // !_Marine_FlatWave_Header
