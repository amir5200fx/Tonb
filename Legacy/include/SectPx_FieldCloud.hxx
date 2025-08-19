#pragma once
#ifndef _SectPx_FieldCloud_Header
#define _SectPx_FieldCloud_Header

#include <SectPx_Cloud.hxx>
#include <SectPx_ParsFwd.hxx>

namespace tnbLib
{

	class SectPx_FieldCloud
		: public SectPx_Cloud
	{

		/*Private Data*/



		// private functions and operators [4/27/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Cloud>(*this);
		}

	protected:


		// default constructor [4/27/2022 Amir]

		SectPx_FieldCloud()
		{}


		// constructors [4/27/2022 Amir]

		explicit SectPx_FieldCloud(const Standard_Integer theIndex)
			: SectPx_Cloud(theIndex)
		{}


		SectPx_FieldCloud
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: SectPx_Cloud(theIndex, theName)
		{}


	public:

		// public functions and operators [4/27/2022 Amir]
		
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_FieldCloud);

#endif // !_SectPx_FieldCloud_Header
