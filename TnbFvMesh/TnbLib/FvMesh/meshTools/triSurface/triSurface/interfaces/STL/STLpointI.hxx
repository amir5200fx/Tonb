#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	inline STLpoint::STLpoint()
	{}

	inline STLpoint::STLpoint(float x, float y, float z)
		:
		Vector<float>(x, y, z)
	{}

	inline STLpoint::STLpoint(const point& pt)
		:
		Vector<float>(float(pt.x()), float(pt.y()), float(pt.z()))
	{}

	inline STLpoint::STLpoint(Istream& is)
		:
		Vector<float>(is)
	{}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	inline STLpoint::operator point() const
	{
		return point(x(), y(), z());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //