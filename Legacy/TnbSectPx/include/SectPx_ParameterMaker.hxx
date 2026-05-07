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
	class SectPx_ParRegistry;

	namespace maker
	{

		class Parameter
			: public SectPx_Maker<SectPx_ParRegistry>
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_ParRegistry>>(*this);
			}

			Parameter()
			{}

		public:

			explicit Parameter
			(
				const std::shared_ptr<SectPx_ParRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_ParRegistry>(theRegistry)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_Par>
				SelectParameter
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateFree
				(
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateFree
				(
					const word& theName,
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateFixed
				(
					const Standard_Real x,
					const Standard_Real theMin,
					const Standard_Real theMax
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateFixed
				(
					const word& theName,
					const Standard_Real x,
					const Standard_Real theMin,
					const Standard_Real theMax
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateConstant
				(
					const Standard_Real x
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateConstant
				(
					const word& theName,
					const Standard_Real x
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Par>
				RemoveParameter
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>>
				RetrieveFixedParameters() const;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>>
				RetrieveFreeParameters() const;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>>
				RetrieveConstParameters() const;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Par>>
				RetrieveParameters() const;

			TnbSectPx_EXPORT void Print
			(
				OSstream& out
			) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Parameter);

#endif // !_SectPx_ParameterMaker_Header
