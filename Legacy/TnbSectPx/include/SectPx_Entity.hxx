#pragma once
#ifndef _SectPx_Entity_Header
#define _SectPx_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<SectPx_Entity>
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		// default constructor [4/27/2022 Amir]

		SectPx_Entity()
		{}


		// constructors [4/27/2022 Amir]

		explicit SectPx_Entity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		SectPx_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:


		// public functions and operators [4/27/2022 Amir]

		virtual ~SectPx_Entity()
		{}

		std::shared_ptr<SectPx_Entity> This() const
		{
			return std::const_pointer_cast<SectPx_Entity>(this->shared_from_this());
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Entity);

#endif // !_SectPx_Entity_Header
