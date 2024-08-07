#pragma once
#ifndef _Geo_ProfileFun_Header
#define _Geo_ProfileFun_Header

#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Global_Bound.hxx>
#include <Geo_Module.hxx>

#include <memory>

namespace tnbLib
{

	class Geo_ProfileFun
		: public Global_Indexed
		, public Global_Named
		, public Global_Bound<Standard_Real>
		, public std::enable_shared_from_this<Geo_ProfileFun>
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
			ar & boost::serialization::base_object<Global_Bound<Standard_Real>>(*this);
		}

	protected:


		//- constructors

		Geo_ProfileFun
		(
			const Standard_Real theLower,
			const Standard_Real theUpper
		)
			: Global_Bound<Standard_Real>(theLower, theUpper)
		{}

		Geo_ProfileFun
		(
			const Standard_Integer theIndex,
			const Standard_Real theLower, 
			const Standard_Real theUpper
		)
			: Global_Indexed(theIndex)
			, Global_Bound<Standard_Real>(theLower, theUpper)
		{}

		Geo_ProfileFun
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theLower,
			const Standard_Real theUpper
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, Global_Bound<Standard_Real>(theLower, theUpper)
		{}

	public:

		static TnbGeo_EXPORT const std::string extension;

		//- public functions and operators

		virtual Standard_Real Value(const Standard_Real x) const = 0;

		virtual ~Geo_ProfileFun()
		{}

		std::shared_ptr<Geo_ProfileFun> This() const
		{
			return std::const_pointer_cast<Geo_ProfileFun>(this->shared_from_this());
		}
	};
}

#endif // !_Geo_ProfileFun_Header
