#pragma once
#ifndef _Marine_FlatWave_Header
#define _Marine_FlatWave_Header

#include <Marine_Wave.hxx>

namespace tnbLib
{

	class Marine_FlatWave
		: public Marine_Wave
	{

		/*Private Data*/

		TnbMarine_EXPORT void MakeProfileCurve(const Pnt2d& x0, const Pnt2d& x1) override;

	protected:

		TnbMarine_EXPORT Dir3d SurfaceDirection() const override;

	public:

		Marine_FlatWave(const std::shared_ptr<Entity3d_Box>& theDomain)
			: Marine_Wave(theDomain)
		{}

	};
}

#endif // !_Marine_FlatWave_Header
