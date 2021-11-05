#pragma once
#ifndef _PtdModel_DispltEntity_Header
#define _PtdModel_DispltEntity_Header

#include <PtdModel_VesselEntity.hxx>

namespace tnbLib
{

	class PtdModel_DispltEntity
		: public PtdModel_VesselEntity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_VesselEntity>(*this);
		}

	protected:

		//- default constructor


		//- constructors

		template<class... _Types>
		PtdModel_DispltEntity(_Types&&... _Args)
			: PtdModel_VesselEntity(_Args...)
		{}

	public:

		//- public functions and operators

	};

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_DispltEntity);

#endif // !_PtdModel_DispltEntity_Header
