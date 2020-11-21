#pragma once
#ifndef _StbGMaker_AreaSailCreator_Const_Header
#define _StbGMaker_AreaSailCreator_Const_Header

#include <StbGMaker_AreaSailCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class AreaSailCreator_Const
			: public StbGMaker_AreaSailCreator
		{

			/*Private Data*/

			Standard_Real theArea_;
			Standard_Real theZbar_;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<StbGMaker_AreaSailCreator>(*this);
				ar & theArea_;
				ar & theZbar_;
			}

			AreaSailCreator_Const()
			{}

		public:

			TnbStbGMaker_EXPORT AreaSailCreator_Const
			(
				const Standard_Real theArea, 
				const Standard_Real theZbar
			);

			TnbStbGMaker_EXPORT AreaSailCreator_Const
			(
				const Standard_Integer theIndex, 
				const Standard_Real theArea,
				const Standard_Real theZbar
			);

			TnbStbGMaker_EXPORT AreaSailCreator_Const
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const Standard_Real theArea, 
				const Standard_Real theZbar
			);

			auto Area() const
			{
				return theArea_;
			}

			auto zBar() const
			{
				return theZbar_;
			}

			TnbStbGMaker_EXPORT stbGmakerLib::sailCreatotType Type() const override;

			TnbStbGMaker_EXPORT void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::AreaSailCreator_Const);

#endif // !_StbGMaker_AreaSailCreator_Const_Header
