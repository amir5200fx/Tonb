#include <GeoIO_Writer_OBJ.hxx>

#include <Entity3d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <token.hxx>

void tnbLib::GeoIO_Writer_OBJ::Perform(const std::string& theName)
{
	OFstream myFile(theName);
	if (Mtl())
	{
		myFile << "mtllib " << Mtl()->name << ".mtl" << endl;
	}
	for (const auto& x : Mesh()->Points())
	{
		myFile << "v" 
			<< token::SPACE 
			<< x.X() 
			<< token::SPACE 
			<< x.Y() 
			<< token::SPACE 
			<< x.Z() 
			<< endl;
	}
	if (Mtl())
	{
		Standard_Integer k = 0;
		std::map<Standard_Integer, connectivity::triple> elemMap;
		for (const auto& x : Mesh()->Connectivity())
		{
			elemMap.insert({ ++k,x });
		}
		for (const auto& x : Sets())
		{
			for (auto elm : x->elements)
			{
				auto iter = elemMap.find(elm);
				if (iter IS_EQUAL elemMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the element is not belong to the mesh." << endl
						<< abort(FatalError);
				}
				elemMap.erase(iter);
			}
		}
		if (elemMap.size())
		{
			myFile << "#unspecified element region" << endl;
			/*for (const auto& x : elemMap)
			{
				auto i0
			}*/
		}
		else
		{

		}
	}
	else
	{
		for (const auto& x : Mesh()->Connectivity())
		{
			myFile << "f" 
				<< token::SPACE 
				<< x.Value(0) 
				<< token::SPACE 
				<< x.Value(1) 
				<< token::SPACE 
				<< x.Value(2) 
				<< endl;
		}
	}
}