#pragma once
#ifndef _SectPx_FieldFunMaker_Header
#define _SectPx_FieldFunMaker_Header

#include <SectPx_Coord.hxx>
#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_FieldFun;
	class SectPx_Coord;

	namespace maker
	{

		class FieldFun
			: public SectPx_Maker
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker>(*this);
			}

			FieldFun()
			{}

		public:

			explicit FieldFun
			(
				const std::shared_ptr<SectPx_Registry>& theRegistry
			)
				: SectPx_Maker(theRegistry)
			{}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_FieldFun>
				SelectFieldFun
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_FieldFun>
				RemoveFieldFun
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateUniform
				(
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateInverse
				(
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateUniform
				(
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateInverse
				(
					const std::shared_ptr<SectPx_FieldFun>& theField
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateReadingX
				(
					const std::shared_ptr<SectPx_Coord>& theCoord
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateReadingY
				(
					const std::shared_ptr<SectPx_Coord>& theCoord
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateExpression
				(
					const word& expr
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateLinearForm
				(
					const std::shared_ptr<SectPx_FieldFun>& theF0,
					const std::shared_ptr<SectPx_FieldFun>& theF1, 
					const std::shared_ptr<SectPx_Par>& thePar
				) const;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_FieldFun>> RetrieveFieldFuns() const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::FieldFun);

#endif // !_SectPx_FieldFunMaker_Header
