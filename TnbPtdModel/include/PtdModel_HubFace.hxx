#pragma once
#ifndef _PtdModel_HubFace_Header
#define _PtdModel_HubFace_Header

#include <PtdModel_Face.hxx>

namespace tnbLib
{

	class PtdModel_HubFace
		: public PtdModel_Face
	{

		/*Private Data*/



		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<PtdModel_Face>(*this);
		}

	protected:

		//- default constructor

		PtdModel_HubFace()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_HubFace(const Handle(Geom_Surface)&);

		TnbPtdModel_EXPORT PtdModel_HubFace(Handle(Geom_Surface)&&);

	public:


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_HubFace);

#endif // !_PtdModel_HubFace_Header
