#include <MeshPost3d_StellarOpt.hxx>

#include <Entity3d_Tetrahedralization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::MeshPost3d_StellarOpt::verbose(0);

#include "lib/Stellar.h"

class StellarOptRunTime
{
	/*Private Data*/
	static void Configs();
public:
	// default constructor
	StellarOptRunTime()
	{
		Configs();
	}
};

void StellarOptRunTime::Configs()
{
	primitivesinit();
}

static const StellarOptRunTime StellarOptRunTimeObj;

void tnbLib::MeshPost3d_StellarOpt::Init(behavior* b)
{
	b->inspherecount = 0;
	b->orientcount = 0;
	b->orient4dcount = 0;
	b->tetcircumcentercount = 0;
	b->tricircumcentercount = 0;

	b->poly = b->refine = b->quality = 0;
	b->varvolume = b->fixedvolume = b->usertest = 0;
	b->regionattrib = b->convex = b->weighted = b->jettison = 0;
	b->firstnumber = 1;
	b->edgesout = b->facesout = b->voronoi = b->neighbors = b->geomview = 0;
	b->nobound = b->nopolywritten = b->nonodewritten = b->noelewritten = 0;
	b->noiterationnum = 0;
	b->noholes = b->noexact = 0;
	b->docheck = 0;
	b->nobisect = 0;
	b->conformdel = 0;
	/* A negative `steiner' value indicates no constraint on number of */
	/*   Steiner points.                                               */
	b->steiner = -1;
	b->order = 1;
	b->qmeasure = 0.0;
	b->minangle = 0.0;
	/* A negative volume indicates no constraint on tetrahedron volumes. */
	b->maxvolume = -1.0;
	b->quiet = b->verbose = 0;
#ifndef STARLIBRARY
	b->innodefilename[0] = '\0';
#endif /* not STARLIBRARY */
}

namespace tnbLib
{
	void ImportVertices(const Entity3d_Tetrahedralization& tet, inputs* in)
	{
		const auto& pnts = tet.Points();
		in->vertexcount = pnts.size();
		in->attribcount = 0; // no attribution
		in->deadvertexcount = 0;
		if (in->vertexcount < 4)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< " - Input must have at least 4 vertices." << endl
				<< abort(FatalError);
		}
		in->firstnumber = 1;
		// readnodefileflag from behaviour should be 0
		
		size_t vertexbytes = sizeof(vertexshort) +
			(size_t)in->attribcount * sizeof(starreal);
		auto vertices = (starreal*)starmalloc((size_t)(in->vertexcount * vertexbytes));
		// read the vertices
		for (arraypoolulong i = 0; i < in->vertexcount; i++)
		{
			auto vertexptr = (vertexshort*)&vertices[i * vertexbytes];
			/* Read the vertex coordinates and attributes. */
			for (unsigned int j = 0; j < 3 + in->attribcount; j++)
			{
				vertexptr->coord[j] = pnts.at(i).Coord(j + 1);
			}
		}
	}

	void ImportTets(const Entity3d_Tetrahedralization& tet, inputs* in, outputs* out, proxipool* vertexpool, tetcomplex* plex)
	{
		const auto& elements = tet.Connectivity();
		in->tetcount = tet.NbConnectivity();
		in->tetattribcount = 0;

		tetcomplexinit(plex, vertexpool, MeshPost3d_StellarOpt::verbose);

		arraypoolulong boundaryfacecount = 0;
		for (arraypoolulong elementnumber = 1; elementnumber < in->tetcount; elementnumber++)
		{
			arraypoolulong corner[4];
			tag cornertag[4];
			for (int i = 0; i < 4; i++)
			{
				corner[i] = elements.at(elementnumber - 1).Value(i);
				if ((corner[i] < 1) OR (corner[i] >= 1 + in->vertexcount))
				{
					FatalErrorIn(FunctionSIG) << endl
						<< " - Tetrahedron has an invalid vertex index." << endl
						<< abort(FatalError);
				}
				//cornertag[i] = in->vertextags[corner[i] - 1];
			}
			auto result = tetcomplexinserttet(plex, cornertag[0], cornertag[1],
				cornertag[2], cornertag[3]);
			if (result > 0) {
				boundaryfacecount += (result - 6);
			}
		}

		out->vertexcount = in->vertexcount - in->deadvertexcount;
		out->tetcount = tetcomplextetcount(plex);
		out->boundaryfacecount = boundaryfacecount;
		out->facecount = 2 * out->tetcount + (out->boundaryfacecount / 2);
		out->edgecount = out->vertexcount + out->facecount - out->tetcount - 1;
	}
}

void tnbLib::MeshPost3d_StellarOpt::Perform()
{
	behavior behave;
	inputs in;
	outputs out;
	proxipool vertexpool;
	tetcomplex mesh;

	ImportVertices(*Mesh(), &in);
	/* Compute an array mapping vertex numbers to their tags. */
	inputmaketagmap(&vertexpool, in.firstnumber, in.vertextags);
	/* Read and reconstruct a mesh. */
	ImportTets(*Mesh(), &in, &out, &vertexpool, &mesh);


}
