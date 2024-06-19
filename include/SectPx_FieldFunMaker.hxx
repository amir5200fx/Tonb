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
	class SectPx_ParRegistry;

	namespace maker
	{

		class FieldFun
			: public SectPx_Maker<SectPx_ParRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_ParRegistry>>(*this);
			}

			FieldFun()
			{}

		public:

			explicit FieldFun
			(
				const std::shared_ptr<SectPx_ParRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_ParRegistry>(theRegistry)
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

			TnbSectPx_EXPORT Standard_Integer CreateMin(const std::shared_ptr<SectPx_FieldFun>& theField0,
				const std::shared_ptr<SectPx_FieldFun>& theField1) const;
			TnbSectPx_EXPORT Standard_Integer CreateMax(const std::shared_ptr<SectPx_FieldFun>& theField0,
				const std::shared_ptr<SectPx_FieldFun>& theField1) const;

			TnbSectPx_EXPORT Standard_Integer CreateAdd(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
			TnbSectPx_EXPORT Standard_Integer CreateSubtract(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
			TnbSectPx_EXPORT Standard_Integer CreateCross(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);
			TnbSectPx_EXPORT Standard_Integer CreateDivide(const std::shared_ptr<SectPx_FieldFun>& f0, const std::shared_ptr<SectPx_FieldFun>& f1);

			TnbSectPx_EXPORT Standard_Integer CreateAbs(const std::shared_ptr<SectPx_FieldFun>&);
			TnbSectPx_EXPORT Standard_Integer CreateSqrt(const std::shared_ptr<SectPx_FieldFun>&);

			TnbSectPx_EXPORT Standard_Integer CreateSin(const std::shared_ptr<SectPx_FieldFun>&);
			TnbSectPx_EXPORT Standard_Integer CreateCos(const std::shared_ptr<SectPx_FieldFun>&);
			TnbSectPx_EXPORT Standard_Integer CreateTan(const std::shared_ptr<SectPx_FieldFun>&);
			TnbSectPx_EXPORT Standard_Integer CreateAsin(const std::shared_ptr<SectPx_FieldFun>&);
			TnbSectPx_EXPORT Standard_Integer CreateAcos(const std::shared_ptr<SectPx_FieldFun>&);
			TnbSectPx_EXPORT Standard_Integer CreateAtan(const std::shared_ptr<SectPx_FieldFun>&);

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_FieldFun>> RetrieveFieldFuns() const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::FieldFun);

#endif // !_SectPx_FieldFunMaker_Header
