#pragma once
#ifndef _HydStatic_StbFun_IntgFun_Header
#define _HydStatic_StbFun_IntgFun_Header

#include <NumAlg_IntegFunc.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		template<class StbFun>
		class StbFun_IntgFun
			: public NumAlg_IntegFunc
		{

			typedef StbFun entity;

			/*Private Data*/

			const entity& theEntity_;

			Standard_Real theY0_;

		public:

			StbFun_IntgFun(const entity& theEntity, const Standard_Real theY0)
				: theEntity_(theEntity)
				, theY0_(theY0)
			{}

			const auto& Entity() const
			{
				return theEntity_;
			}

			auto Y0() const
			{
				return theY0_;
			}

			Standard_Real Value(const Standard_Real x) const override;
		};
	}
}

#include <HydStatic_StbFun_IntgFunI.hxx>

#endif // !_HydStatic_StbFun_IntgFun_Header
