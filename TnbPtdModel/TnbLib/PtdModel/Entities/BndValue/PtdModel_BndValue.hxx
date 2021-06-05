#pragma once
#ifndef _PtdModel_BndValue_Header
#define _PtdModel_BndValue_Header

#include <PtdModel_Value.hxx>

namespace tnbLib
{

	class PtdModel_BndValue
		: public PtdModel_Value
	{

		/*Private Data*/

		Standard_Real theLower_;
		Standard_Real theUpper_;


		//- default constructor

		PtdModel_BndValue()
		{}


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<PtdModel_Value>(*this);
			ar & theLower_;
			ar & theUpper_;
		}

		inline static void Check(const Standard_Real theLower, const Standard_Real theUpper);

	public:

		//- default constructor


		//- constructors

		inline PtdModel_BndValue
		(
			const Standard_Real theLower,
			const Standard_Real theUpper
		);

		inline PtdModel_BndValue
		(
			const Standard_Real theLower, 
			const Standard_Real theUpper,
			const Standard_Real x
		);


		//- public functions and operators

		auto Lower() const
		{
			return theLower_;
		}

		auto Upper() const
		{
			return theUpper_;
		}

		inline Standard_Boolean IsNull() const;
		inline Standard_Boolean IsInside(const Standard_Real x) const;

		TnbPtdModel_EXPORT void SetValue(const Standard_Real x) override;


		inline static PtdModel_BndValue NormalizedValue(const Standard_Real x);
	};
}

#include <PtdModel_BndValueI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_BndValue);

#endif // !_PtdModel_BndValue_Header
