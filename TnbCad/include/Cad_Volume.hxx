#pragma once
#ifndef _Cad_Volume_Header
#define _Cad_Volume_Header

#include <Cad_Module.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [6/13/2023 Payvand]
	class Cad_Solid;

	class Cad_Volume
		: public Global_Named
		, public Global_Indexed
	{

		/*Private Data*/


		// Private functions and operators [6/13/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<Global_Named>(*this);
			ar& boost::serialization::base_object<Global_Indexed>(*this);
		}

	protected:

		// default constructor [6/13/2023 Payvand]

		Cad_Volume()
		{}


		// constructors [6/13/2023 Payvand]

		Cad_Volume
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: Global_Named(theName)
			, Global_Indexed(theIndex)
		{}

	public:

		static TnbCad_EXPORT const std::string extension;

		// Public functions and operators [6/13/2023 Payvand]

		virtual Standard_Integer NbVolumes() const = 0;
		virtual std::shared_ptr<Cad_Solid> Volume(const Standard_Integer theIndex) const = 0;

		virtual std::vector<std::shared_ptr<Cad_Solid>> Volumes() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_Volume);

#endif // !_Cad_Volume_Header
