#pragma once
#ifndef _ShapePx_ContinProfile_Custom_Header
#define _ShapePx_ContinProfile_Custom_Header

#include <ShapePx_ContinProfile.hxx>

namespace tnbLib
{

	namespace shapePxLib
	{

		class ContinProfile_Custom
			: public ShapePx_ContinProfile
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<ShapePx_ContinProfile>(*this);
			}

		protected:

			
			template<class... _Types>
			ContinProfile_Custom(_Types&&... _Args)
				: ShapePx_ContinProfile(_Args...)
			{}

		public:

			TnbShapePx_EXPORT virtual Standard_Boolean IsOffset() const;

			TnbShapePx_EXPORT virtual Standard_Boolean IsGenerated() const;
		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::shapePxLib::ContinProfile_Custom);

#endif // !_ShapePx_ContinProfile_Custom_Header
