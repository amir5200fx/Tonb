#pragma once
#ifndef _SectPx_PntConstructor_Header
#define _SectPx_PntConstructor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		template<class PntType>
		class InnerPnt
			: public PntType
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<PntType>(*this);
			}

		public:

			template<class... _Types>
			InnerPnt(_Types&&... _Args)
				: PntType(_Args...)
			{}

			Standard_Boolean IsInner() const override
			{
				return Standard_True;
			}
		};


		template<class PntType>
		class OuterPnt
			: public PntType
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<PntType>(*this);
			}

		public:

			template<class... _Types>
			OuterPnt(_Types&&... _Args)
				: PntType(_Args...)
			{}

			Standard_Boolean IsOuter() const override
			{
				return Standard_True;
			}

			Standard_Boolean IsBoundary() const override
			{
				return Standard_True;
			}
		};

	}
}


#endif // !_SectPx_PntConstructor_Header
