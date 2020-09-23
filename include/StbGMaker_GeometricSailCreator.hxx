#pragma once
#ifndef _StbGMaker_GeometricSailCreator_Header
#define _StbGMaker_GeometricSailCreator_Header

#include <StbGMaker_SailCreator.hxx>

namespace tnbLib
{

	class StbGMaker_GeometricSailCreator
		: public StbGMaker_SailCreator
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		StbGMaker_GeometricSailCreator(_Types&&... _Args)
			: StbGMaker_SailCreator(_Args...)
		{}

	public:

		Standard_Boolean IsGeometric() const override;
	};
}

#endif // !_StbGMaker_GeometricSailCreator_Header
