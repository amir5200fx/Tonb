#pragma once
#ifndef _ShapePx_ParValue_Header
#define _ShapePx_ParValue_Header

#include <Standard_TypeDef.hxx>
#include <ShapePx_Module.hxx>

#include <map>

namespace tnbLib
{

	class ShapePx_ParValue
	{

		/*Private Data*/

		std::map<Standard_Integer, Standard_Real> theValues_;


		//- private functions and operators

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theValues_;
		}

	public:

		ShapePx_ParValue()
		{}

		const auto& Values() const
		{
			return theValues_;
		}

		TnbShapePx_EXPORT void SetValue(const Standard_Integer theParIndex, const Standard_Real x);

		TnbShapePx_EXPORT void Remove(const Standard_Integer theParIndex);
	};
}

#endif // !_ShapePx_ParValue_Header
