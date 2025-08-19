#pragma once
#ifndef _PtdModel_BladeFace_Header
#define _PtdModel_BladeFace_Header

#include <PtdModel_Face.hxx>

namespace tnbLib
{

	class PtdModel_BladeFace
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

		PtdModel_BladeFace()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_BladeFace(const Handle(Geom_Surface)&);

		TnbPtdModel_EXPORT PtdModel_BladeFace(Handle(Geom_Surface)&&);


	public:


	};
}


BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_BladeFace);

#endif // !_PtdModel_BladeFace_Header
