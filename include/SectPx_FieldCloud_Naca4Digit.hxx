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


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		protected:

			Standard_Boolean CloseTail_ = Standard_False;


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

			void SetChord(const std::shared_ptr<SectPx_Par>& thePar);

			void SetMaxCamber(const std::shared_ptr<SectPx_Par>& thePar);

			void SetMaxCamberLoc(const std::shared_ptr<SectPx_Par>& thePar);

			void SetMaxThickness(const std::shared_ptr<SectPx_Par>& thePar);

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

			Standard_Integer NbChildren() const override;

			Standard_Boolean IsComplete() const override;

			Standard_Boolean HasChildren() const override;

			Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			std::vector<std::shared_ptr<SectPx_Child>>
				RetrieveChildren() const override;

			void RemoveThisFromChildren() const override;

			void AddThisToChildren() const override;

			void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			void RemoveThisFromChild
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

				void Update() const override;

			public:

				static const char* typeName_;

				template<class... _Types>
				UpperEdge(_Types&&... _Args)
					: FieldCloud_Naca4DigitBase(_Args...)
				{}

				word RegObjTypeName() const override;
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

				void Update() const override;

			public:

				static const char* typeName_;

				template<class... _Types>
				LowerEdge(_Types&&... _Args)
					: FieldCloud_Naca4DigitBase(_Args...)
				{}

				word RegObjTypeName() const override;
			};

			
		}
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::sectPxLib::FieldCloud_Naca4DigitBase);
BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::naca::UpperEdge);
BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::naca::LowerEdge);

#endif // !_SectPx_FieldCloud_Naca4Digit_Header
