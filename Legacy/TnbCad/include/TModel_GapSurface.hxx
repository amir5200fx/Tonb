#pragma once
#ifndef _TModel_GapSurface_Header
#define _TModel_GapSurface_Header

#include <TModel_deGeneratedSurface.hxx>

namespace tnbLib
{

	class TModel_GapSurface
		: public TModel_deGeneratedSurface
	{

		/*Private Data*/


		// Private functions and operators [3/8/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<TModel_deGeneratedSurface>(*this);
		}

	public:

		// default constructor [3/8/2023 Payvand]

		TModel_GapSurface()
		{}


		// constructors [3/8/2023 Payvand]

		TModel_GapSurface(const Standard_Integer theIndex, const word& theName)
			: TModel_deGeneratedSurface(theIndex, theName)
		{}


		// Public functions and operators [3/8/2023 Payvand]

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_GapSurface);

#endif // !_TModel_GapSurface_Header
