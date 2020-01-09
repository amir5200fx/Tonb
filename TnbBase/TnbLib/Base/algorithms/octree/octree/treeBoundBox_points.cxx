#include <treeBoundBox.hxx>

#include <ListOps.hxx>
#include <pointField.hxx>
#include <Field.hxx>

tnbLib::pointField tnbLib::treeBoundBox::points() const
{
	pointField points(8);
	forAll(points, octant)
	{
		points[octant] = corner(octant);

	}
	return points;
}