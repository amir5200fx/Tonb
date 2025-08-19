#pragma once
#ifndef _Geo3d_PatchCloud_NoneInternal_Header
#define _Geo3d_PatchCloud_NoneInternal_Header

#include <Geo3d_PatchCloud.hxx>

namespace tnbLib
{

	class Geo3d_PatchCloud_NoneInternal
		: public Geo3d_PatchCloud
	{

		/*Private Data*/


		// Private functions and operators [10/16/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo3d_PatchCloud>(*this);
		}

	public:

		// default constructor [10/15/2022 Amir]

		Geo3d_PatchCloud_NoneInternal()
		{}

		// constructors [10/16/2022 Amir]


		// public functions and operators [10/16/2022 Amir]

		TnbMesh_EXPORT std::vector<Pnt2d> CalcCloud(const Entity2d_Triangulation&) const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_PatchCloud_NoneInternal);

#endif // !_Geo3d_PatchCloud_NoneInternal_Header
