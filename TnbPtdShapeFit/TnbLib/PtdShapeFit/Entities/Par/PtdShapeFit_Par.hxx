#pragma once
#ifndef _PtdShapeFit_Par_Header
#define _PtdShapeFit_Par_Header

#include <PtdShapeFit_Entity.hxx>

namespace tnbLib
{

	class PtdShapeFit_Par
		: public PtdShapeFit_Entity
	{

		/*Private Data*/

		Standard_Real theLowerVal_;
		Standard_Real theUpperVal_;


		// Private functions and operators [2/9/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<PtdShapeFit_Entity>(*this);
			ar& theLowerVal_;
			ar& theUpperVal_;
		}

	public:

		// default constructor [2/9/2023 Payvand]

		PtdShapeFit_Par()
			: theLowerVal_(0)
			, theUpperVal_(0)
		{}


		// constructors [2/9/2023 Payvand]

		PtdShapeFit_Par(const Standard_Real theLowerVal, const Standard_Real theUpperVal)
			: theLowerVal_(theLowerVal)
			, theUpperVal_(theUpperVal)
		{}


		// Public functions and operators [2/9/2023 Payvand]

		auto LowerVal() const
		{
			return theLowerVal_;
		}

		auto UpperVal() const
		{
			return theUpperVal_;
		}

		void SetLowerVal(const Standard_Real theValue)
		{
			theLowerVal_ = theValue;
		}

		void SetUpperVal(const Standard_Real theValue)
		{
			theUpperVal_ = theValue;
		}

	};
}

#endif // !_PtdShapeFit_Par_Header
