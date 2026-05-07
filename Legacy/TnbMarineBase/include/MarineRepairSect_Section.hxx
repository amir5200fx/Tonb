#pragma once
#ifndef _MarineRepairSect_Section_Header
#define _MarineRepairSect_Section_Header

#include <Marine_Entity.hxx>
#include <Cad2d_RemoveNonManifold.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	class MarineRepairSect_Section
		: public Marine_Entity
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_Entity>(*this);
		}

	protected:

		//- default constructor

		MarineRepairSect_Section()
		{}


		//- constructors

		MarineRepairSect_Section
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Marine_Entity(theIndex, theName)
		{}


	public:

		virtual ~MarineRepairSect_Section()
		{}


		//- public functions and operators

		virtual std::vector<std::shared_ptr<Pln_Curve>> FillingCurves() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::MarineRepairSect_Section);

#endif // !_MarineRepairSect_Section_Header
