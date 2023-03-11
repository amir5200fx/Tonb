#pragma once
#ifndef _TModel_deGeneratedSurface_Header
#define _TModel_deGeneratedSurface_Header

#include <TModel_Surface.hxx>

namespace tnbLib
{

	class TModel_deGeneratedSurface
		: public TModel_Surface
	{

		/*Private Data*/


		// Private functions and operators [3/8/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<TModel_Surface>(*this);
		}

	protected:

		// default constructor [3/8/2023 Payvand]

		TModel_deGeneratedSurface()
		{}


		// constructors [3/8/2023 Payvand]

		TModel_deGeneratedSurface(const Standard_Integer theIndex, const word& theName)
			: TModel_Surface(theIndex, theName)
		{}

	public:


		// Public functions and operators [3/8/2023 Payvand]

		TnbCad_EXPORT Standard_Boolean IsDegenerated() const override;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::TModel_deGeneratedSurface);

#endif // !_TModel_deGeneratedSurface_Header
