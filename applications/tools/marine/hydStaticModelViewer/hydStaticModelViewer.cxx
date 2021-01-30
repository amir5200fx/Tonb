#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <Marine_Wave.hxx>
#include <HydStatic_Model.hxx>
#include <HydStatic_FloatBody.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<HydStatic_Model> model_t;
	typedef std::shared_ptr<Marine_Wave> wave_t;

	static model_t myModel;
	static size_t verbose = 0;

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);
		if (NOT f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to open the file" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ar(f);
		ar >> myModel;

		if (verbose)
		{
			Info << " the model is loaded from: " << fn << ", successfully!" << endl;
		}
	}

	void exportToPlt(const wave_t& w, const std::string& name)
	{
		if (w)
		{
			if (NOT w->IsDone())
			{
				w->Perform();
			}
			OFstream f(name);
			const auto& geom = w->SurfaceGeometry();

			auto tri = Cad_Tools::Triangulation(geom, 15, 15);
			tri->ExportToPlt(f);
		}
	}
}