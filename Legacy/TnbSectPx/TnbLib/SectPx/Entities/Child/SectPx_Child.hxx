#pragma once
#ifndef _SectPx_Child_Header
#define _SectPx_Child_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_ParentAdaptor.hxx>
#include <SectPx_Module.hxx>

namespace tnbLib
{

	class SectPx_Child
		: public SectPx_RegObj
		, public SectPx_ParentAdaptor
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_RegObj>(*this);
			ar & boost::serialization::base_object<SectPx_ParentAdaptor>(*this);
		}

	protected:


		// default constructor [4/27/2022 Amir]

		SectPx_Child()
		{}


		// constructors [4/27/2022 Amir]

		explicit SectPx_Child(const Standard_Integer theIndex)
			: SectPx_RegObj(theIndex)
		{}

		SectPx_Child
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: SectPx_RegObj(theIndex, theName)
		{}


	public:


		// override functions and operators [4/27/2022 Amir]

		TnbSectPx_EXPORT Standard_Boolean IsChild() const override;
		TnbSectPx_EXPORT Standard_Boolean IsParRegObj() const override;


		// public functions and operators [4/27/2022 Amir]

		

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Child);

#endif // !_SectPx_Child_Header
