#pragma once
#ifndef _PtdModel_Value_Header
#define _PtdModel_Value_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

namespace tnbLib
{

	class PtdModel_Value
	{

		/*Private Data*/

		Standard_Real theValue_;

		Standard_Boolean IsSpecified_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theValue_;
			ar & IsSpecified_;
		}
		

	public:

		//- default constructor

		inline PtdModel_Value();

		//- constructors

		inline PtdModel_Value(const Standard_Real x);


		//- public functions and operators

		auto Value() const
		{
			return theValue_;
		}

		auto IsSpecified() const
		{
			return IsSpecified_;
		}


		TnbPtdModel_EXPORT virtual void SetValue(const Standard_Real x);
	};
}

#include <PtdModel_ValueI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_Value);

#endif // !_PtdModel_Value_Header
