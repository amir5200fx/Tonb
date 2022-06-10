#pragma once
#ifndef _SectPx_ExtrProfile_Uniform_Header
#define _SectPx_ExtrProfile_Uniform_Header

#include <SectPx_ExtrProfile.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;

	namespace sectPxLib
	{

		class ExtrProfile_Uniform
			: public SectPx_ExtrProfile
		{

			/*Private Data*/

			std::weak_ptr<SectPx_Par> theValue_;

			std::weak_ptr<SectPx_Par> theX0_;
			std::weak_ptr<SectPx_Par> theX1_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:


			static TnbSectPx_EXPORT const char* typeName_;
			static TnbSectPx_EXPORT const short nbPoints_;


			//- default constructors

			ExtrProfile_Uniform()
			{}


			//- constructors

			TnbSectPx_EXPORT ExtrProfile_Uniform
			(
				const Standard_Integer theIndex
			);

			TnbSectPx_EXPORT ExtrProfile_Uniform
			(
				const Standard_Integer theIndex, 
				const word& theName
			);


			//- public functions and operators

			const auto& X0() const
			{
				return theX0_;
			}

			const auto& X1() const
			{
				return theX1_;
			}

			const auto& Value() const
			{
				return theValue_;
			}

			TnbSectPx_EXPORT void SetX0(const std::shared_ptr<SectPx_Par>& thePar);

			TnbSectPx_EXPORT void SetX1(const std::shared_ptr<SectPx_Par>& thePar);

			TnbSectPx_EXPORT void SetValue(const std::shared_ptr<SectPx_Par>& thePar);

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Par> Start() const override;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Par> End() const override;

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT std::vector<Standard_Real> X() const override;

			//- override virtual functions from extrProfile base class

			SectPx_ExtrProfileType ExtrProfileType() const override
			{
				return SectPx_ExtrProfileType::uniform;
			}

			TnbSectPx_EXPORT Standard_Real MinLower() const override;

			TnbSectPx_EXPORT Standard_Real MaxUpper() const override;

			TnbSectPx_EXPORT Standard_Integer NbPoints() const override;

			TnbSectPx_EXPORT Pnt2d Point(const Standard_Integer theIndex) const override;


			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean 
				HasChild
				(
					const std::shared_ptr<SectPx_Child>& thePar
				) const override;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
				RetrieveChildren() const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::ExtrProfile_Uniform);

#endif // !_SectPx_ExtrProfile_Uniform_Header
