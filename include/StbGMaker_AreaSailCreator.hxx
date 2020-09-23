#pragma once
#ifndef _StbGMaker_AreaSailCreator_Header
#define _StbGMaker_AreaSailCreator_Header

#include <StbGMaker_SailCreator.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class StbGMaker_AreaSailCreator
		: public StbGMaker_SailCreator
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		StbGMaker_AreaSailCreator(_Types&&... _Args)
			: StbGMaker_SailCreator(_Args...)
		{}

	public:

		Standard_Boolean IsArea() const override;
	};
}

#endif // !_StbGMaker_AreaSailCreator_Header

