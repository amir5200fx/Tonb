#pragma once
#ifndef _Aft_CavityData_Header
#define _Aft_CavityData_Header

#include <Mesh_RegisterEntityM.hxx>

namespace tnbLib
{

	Mesh_RegisterEntity(UnCertaintyCavitie, FrontEnity);
	Mesh_RegisterEntity(CertaintyCavitie, FrontEntity);

	template<class FrontEntity>
	class Mesh_CavityData
		: public Mesh_RegisterCertaintyCavitie<FrontEntity>
		, public Mesh_RegisterUnCertaintyCavitie<FrontEntity>
	{

		/*Private Data*/


		//- Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_RegisterCertaintyCavitie<FrontEntity>>(*this);
			ar & boost::serialization::base_object<Mesh_RegisterUnCertaintyCavitie<FrontEntity>>(*this);
		}

	protected:

		//- default constructor

		Mesh_CavityData()
		{}


		//- constructors

	public:

		//- Public functions and operators

	};
}

#endif // !_Aft_CavityData_Header