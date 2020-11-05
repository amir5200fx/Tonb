#pragma once
#ifndef _SectPx_ParameterMaker_Header
#define _SectPx_ParameterMaker_Header

#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_FieldFun;

	namespace maker
	{

		class Parameter
			: public SectPx_Maker
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker>(*this);
			}

			Parameter()
			{}

		public:

			explicit Parameter
			(
				const std::shared_ptr<SectPx_Registry>& theRegistry
			)
				: SectPx_Maker(theRegistry)
			{}


			std::shared_ptr<SectPx_Par>
				SelectParameter
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer
				CreateFree
				(
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			Standard_Integer
				CreateFree
				(
					const word& theName,
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			Standard_Integer
				CreateFixed
				(
					const Standard_Real x
				) const;

			Standard_Integer
				CreateFixed
				(
					const word& theName,
					const Standard_Real x
				) const;

			Standard_Integer
				CreateConstant
				(
					const Standard_Real x
				) const;

			Standard_Integer
				CreateConstant
				(
					const word& theName,
					const Standard_Real x
				) const;

			std::shared_ptr<SectPx_Par>
				RemoveParameter
				(
					const Standard_Integer theIndex
				) const;

			std::vector<std::shared_ptr<SectPx_Par>> 
				RetrieveFixedParameters() const;

			std::vector<std::shared_ptr<SectPx_Par>> 
				RetrieveFreeParameters() const;

			std::vector<std::shared_ptr<SectPx_Par>> 
				RetrieveConstParameters() const;

			std::vector<std::shared_ptr<SectPx_Par>> 
				RetrieveParameters() const;

			void Print
			(
				OSstream& out
			) const;
		};
	}
}

#endif // !_SectPx_ParameterMaker_Header
