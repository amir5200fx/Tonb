#pragma once
#ifndef _SectPx_FieldCloud_Naca4Digit_Header
#define _SectPx_FieldCloud_Naca4Digit_Header

#include <SectPx_FieldCloud.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;

	namespace sectPxLib
	{

		class FieldCloud_Naca4DigitBase
			: public SectPx_FieldCloud
		{

			/*Private Data*/

			std::weak_ptr<SectPx_Par> theChord_;
			std::weak_ptr<SectPx_Par> theMaxCamber_;
			std::weak_ptr<SectPx_Par> theMaxCamberLoc_;
			std::weak_ptr<SectPx_Par> theMaxThickness_;

			Standard_Integer theNbSegments_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		protected:

			Standard_Boolean CloseTail_ = Standard_False;


			// default constructor [4/27/2022 Amir]

			// constructors [4/27/2022 Amir]

			FieldCloud_Naca4DigitBase
			(
				const Standard_Integer nbSegments = DEFAULT_NB_SEGMENTS
			)
				: theNbSegments_(nbSegments)
			{}

			FieldCloud_Naca4DigitBase
			(
				const Standard_Integer theIndex, 
				const Standard_Integer nbSegments
			)
				: SectPx_FieldCloud(theIndex)
				, theNbSegments_(nbSegments)
			{}

			FieldCloud_Naca4DigitBase
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Standard_Integer nbSegments
			)
				: SectPx_FieldCloud(theIndex, theName)
				, theNbSegments_(nbSegments)
			{}

		public:

			static const Standard_Integer DEFAULT_NB_SEGMENTS = 25;


			// public functions and operators [4/27/2022 Amir]

			const auto& Chord() const
			{
				return theChord_;
			}

			const auto& MaxCamber() const
			{
				return theMaxCamber_;
			}

			const auto& MaxCamberLoc() const
			{
				return theMaxCamberLoc_;
			}

			const auto& MaxThickness() const
			{
				return theMaxThickness_;
			}

			auto NbSegments() const
			{
				return theNbSegments_;
			}

			TnbSectPx_EXPORT void SetChord(const std::shared_ptr<SectPx_Par>& thePar);
			TnbSectPx_EXPORT void SetMaxCamber(const std::shared_ptr<SectPx_Par>& thePar);
			TnbSectPx_EXPORT void SetMaxCamberLoc(const std::shared_ptr<SectPx_Par>& thePar);
			TnbSectPx_EXPORT void SetMaxThickness(const std::shared_ptr<SectPx_Par>& thePar);

			void SetNbSegments(const Standard_Integer nb)
			{
				theNbSegments_ = nb;
			}

			void SetCloseTail(const Standard_Boolean close)
			{
				CloseTail_ = close;
			}


			//- override virtual functions from field cloud abstract class 


			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildren() const override;
			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;
			TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
				RetrieveChildren() const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;
		};

		namespace naca
		{

			class UpperEdge
				: public FieldCloud_Naca4DigitBase
			{

				/*Private Data*/


				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive &ar, const unsigned int file_version)
				{
					ar & boost::serialization::base_object<FieldCloud_Naca4DigitBase>(*this);
				}

				TnbSectPx_EXPORT void Update() const override;

			public:

				static const char* typeName_;

				template<class... _Types>
				UpperEdge(_Types&&... _Args)
					: FieldCloud_Naca4DigitBase(_Args...)
				{}

				TnbSectPx_EXPORT word RegObjTypeName() const override;
			};


			class LowerEdge
				: public FieldCloud_Naca4DigitBase
			{

				/*Private Data*/

				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive &ar, const unsigned int file_version)
				{
					ar & boost::serialization::base_object<FieldCloud_Naca4DigitBase>(*this);
				}

				TnbSectPx_EXPORT void Update() const override;

			public:

				static const char* typeName_;

				template<class... _Types>
				LowerEdge(_Types&&... _Args)
					: FieldCloud_Naca4DigitBase(_Args...)
				{}

				TnbSectPx_EXPORT word RegObjTypeName() const override;
			};

			
		}
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::sectPxLib::FieldCloud_Naca4DigitBase);
BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::naca::UpperEdge);
BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::naca::LowerEdge);

#endif // !_SectPx_FieldCloud_Naca4Digit_Header
