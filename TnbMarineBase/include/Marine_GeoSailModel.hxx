#pragma once
#ifndef _Marine_GeoSailModel_Header
#define _Marine_GeoSailModel_Header

#include <Marine_SailModel.hxx>

namespace tnbLib
{

	class Marine_GeoSailModel
		: public Marine_SailModel
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		Marine_GeoSailModel(_Types&&... _Args)
			: Marine_SailModel(_Args...)
		{}

	public:


	};
}

#endif // !_Marine_GeoSailModel_Header
