#include <Aft3d_Edge.hxx>

Standard_Boolean 
tnbLib::legLib::Aft3d_Edge::IsOrphan() const
{
	if (NOT NbElements())
	{
		if (NOT NbFacets())
		{
#ifdef _DEBUG
			if (NbFronts())
			{
				FatalErrorIn(FunctionSIG)
					<< "the edge still has some fronts on itself!" << endl
					<< abort(FatalError);
			}
#endif // _DEBUG
			return Standard_True;
		}// else is on boundary [6/2/2023 Payvand]
	}
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Edge::IsInterior() const
{
	return Standard_False;
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Edge::IsBoundary() const
{
	return Standard_True;
}